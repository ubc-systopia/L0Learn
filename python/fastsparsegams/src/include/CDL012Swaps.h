#ifndef CDL012SWAPS_H
#define CDL012SWAPS_H
#include <map>

#include "BetaVector.h"
#include "CD.h"
#include "CDL012.h"
#include "CDSwaps.h"
#include "FitResult.h"
#include "Params.h"
#include "arma_includes.h"
#include "utils.h"

template <class T>
class CDL012Swaps : public CDSwaps<T> {
 public:
  CDL012Swaps(const T &Xi, const arma::vec &yi, const Params<T> &Pi);

  FitResult<T> _FitWithBounds() final;

  FitResult<T> _Fit() final;

  double Objective(const arma::vec &r, const beta_vector &B) final;

  double Objective() final;
};

template <class T>
inline double CDL012Swaps<T>::Objective(const arma::vec &r,
                                        const beta_vector &B) {
  auto l2norm = arma::norm(B, 2);
  return 0.5 * arma::dot(r, r) + this->lambda0 * n_nonzero(B) +
         this->lambda1 * arma::norm(B, 1) + this->lambda2 * l2norm * l2norm;
}

template <class T>
inline double CDL012Swaps<T>::Objective() {
  throw std::runtime_error("CDL012Swaps does not have this->r.");
}

template <class T>
CDL012Swaps<T>::CDL012Swaps(const T &Xi, const arma::vec &yi,
                            const Params<T> &Pi)
    : CDSwaps<T>(Xi, yi, Pi) {}

template <class T>
FitResult<T> CDL012Swaps<T>::_FitWithBounds() {
  throw "This Error should not happen. Please report it as an issue to "
        "https://github.com/hazimehh/L0Learn ";
}

template <class T>
FitResult<T> CDL012Swaps<T>::_Fit() {
  auto result = CDL012<T>(*(this->X), this->y, this->P)
                    .Fit();  // result will be maintained till the end
  this->B = result.B;
  this->b0 = result.b0;
  double objective = result.Objective;
  this->P.Init = 'u';

  bool foundbetter = false;

	arma::rowvec frequency_count = arma::zeros<arma::rowvec>(this->p);
  for (std::size_t t = 0; t < this->MaxNumSwaps; ++t) {
    ///////////////////////////////////////////////////// Original Method, Method I
    /* std::vector<std::size_t> NnzIndices = nnzIndicies(this->B, this->NoSelectK); */
		///////////////////////////////////////////////////// Priority Queue order, Method II
		std::vector<std::size_t> NnzIndices = nnzIndicies(this->B, this->NoSelectK);
		std::sort(NnzIndices.begin(), NnzIndices.end(), [&](std::size_t i, std::size_t j){
				if (frequency_count(i) == frequency_count(j)){
					return i < j;
				}
				return frequency_count(i) < frequency_count(j);
		});
		///////////////////////////////////////////////////// 

    foundbetter = false;

    // TODO: shuffle NNz Indices to prevent bias.
    // std::shuffle(std::begin(Order), std::end(Order), engine);

    // TODO: This calculation is already preformed in a previous step
    // Can be pulled/stored
    arma::vec r = this->y - *(this->X) * this->B - this->b0;

    for (auto &i : NnzIndices) {
      arma::rowvec riX =
          (r + this->B[i] * matrix_column_get(*(this->X), i)).t() * *(this->X);

      double maxcorr = -1;
      std::size_t maxindex = -1;

      for (std::size_t j = this->NoSelectK; j < this->p; ++j) {
        // TODO: Account for bounds when determining best swap
        // Loops through each column and finds the column with the highest
        // correlation to residuals In non-constrained cases, the highest
        // correlation will always be the best option However, if bounds
        // restrict the value of B[j], it is possible that swapping column 'i'
        // and column 'j' might be rejected as B[j], when constrained, is not
        // able to take a value with sufficient magnitude to utilize the
        // correlation. Therefore, we must ensure that 'j' was not already
        // rejected.
        if (std::fabs(riX[j]) > maxcorr && this->B[j] == 0) {
          maxcorr = std::fabs(riX[j]);
          maxindex = j;
        }
      }

      // Check if the correlation is sufficiently large to make up for
      // regularization
      if (maxcorr > (1 + 2 * this->ModelParams[2]) * std::fabs(this->B[i]) +
                        this->ModelParams[1]) {
        // Rcpp::Rcout << t << ": Proposing Swap " << i << " => NNZ and " <<
        // maxindex << " => 0 \n"; Proposed new Swap Value (without considering
        // bounds are solvable in closed form) Must be clamped to bounds

        this->B[i] = 0;

        // Bi with No Bounds (nb);
        double Bi_nb = (riX[maxindex] -
                        std::copysign(this->ModelParams[1], riX[maxindex])) /
                       (1 + 2 * this->ModelParams[2]);
        // double Bi_wb = clamp(Bi_nb, this->Lows[maxindex],
        // this->Highs[maxindex]);  // Bi With Bounds (wb)
        this->B[maxindex] = Bi_nb;

        // Change initial solution to Swapped value to seed standard CD
        // algorithm.
        this->P.InitialSol = &(this->B);
        *this->P.r = this->y - *(this->X) * (this->B) - this->b0;
        // this->P already has access to b0.

        // proposed_result object.
        // Keep tack of previous_best result object
        // Only override previous_best if proposed_result has a better
        // objective.
        result = CDL012<T>(*(this->X), this->y, this->P).Fit();

        // Rcpp::Rcout << "Swap Objective  " <<  result.Objective << " \n";
        // Rcpp::Rcout << "Old Objective  " <<  objective << " \n";
        this->B = result.B;
        objective = result.Objective;
        foundbetter = true;
        break;
      }
			else {
				frequency_count(i) += 1;
			}
    }

    if (!foundbetter) {
      // Early exit to prevent looping
      return result;
    }
  }

  return result;
}


#endif
