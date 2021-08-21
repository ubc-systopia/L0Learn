// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppArmadillo.h>
#include <Rcpp.h>

using namespace Rcpp;

// cor_matrix
Rcpp::NumericMatrix cor_matrix(const int p, const double base_cor);
RcppExport SEXP _L0Learn_cor_matrix(SEXP pSEXP, SEXP base_corSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const int >::type p(pSEXP);
    Rcpp::traits::input_parameter< const double >::type base_cor(base_corSEXP);
    rcpp_result_gen = Rcpp::wrap(cor_matrix(p, base_cor));
    return rcpp_result_gen;
END_RCPP
}
// L0LearnFit_sparse
void L0LearnFit_sparse(const arma::sp_mat& X, const arma::vec& y, const std::string Loss, const std::string Penalty, const std::string Algorithm, const std::size_t NnzStopNum, const std::size_t G_ncols, const std::size_t G_nrows, const double Lambda2Max, const double Lambda2Min, const bool PartialSort, const std::size_t MaxIters, const double rtol, const double atol, const bool ActiveSet, const std::size_t ActiveSetNum, const std::size_t MaxNumSwaps, const double ScaleDownFactor, const std::size_t ScreenSize, const bool LambdaU, const std::vector< std::vector<double> > Lambdas, const std::size_t ExcludeFirstK, const bool Intercept, const bool withBounds, const arma::vec& Lows, const arma::vec& Highs);
RcppExport SEXP _L0Learn_L0LearnFit_sparse(SEXP XSEXP, SEXP ySEXP, SEXP LossSEXP, SEXP PenaltySEXP, SEXP AlgorithmSEXP, SEXP NnzStopNumSEXP, SEXP G_ncolsSEXP, SEXP G_nrowsSEXP, SEXP Lambda2MaxSEXP, SEXP Lambda2MinSEXP, SEXP PartialSortSEXP, SEXP MaxItersSEXP, SEXP rtolSEXP, SEXP atolSEXP, SEXP ActiveSetSEXP, SEXP ActiveSetNumSEXP, SEXP MaxNumSwapsSEXP, SEXP ScaleDownFactorSEXP, SEXP ScreenSizeSEXP, SEXP LambdaUSEXP, SEXP LambdasSEXP, SEXP ExcludeFirstKSEXP, SEXP InterceptSEXP, SEXP withBoundsSEXP, SEXP LowsSEXP, SEXP HighsSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::sp_mat& >::type X(XSEXP);
    Rcpp::traits::input_parameter< const arma::vec& >::type y(ySEXP);
    Rcpp::traits::input_parameter< const std::string >::type Loss(LossSEXP);
    Rcpp::traits::input_parameter< const std::string >::type Penalty(PenaltySEXP);
    Rcpp::traits::input_parameter< const std::string >::type Algorithm(AlgorithmSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type NnzStopNum(NnzStopNumSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type G_ncols(G_ncolsSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type G_nrows(G_nrowsSEXP);
    Rcpp::traits::input_parameter< const double >::type Lambda2Max(Lambda2MaxSEXP);
    Rcpp::traits::input_parameter< const double >::type Lambda2Min(Lambda2MinSEXP);
    Rcpp::traits::input_parameter< const bool >::type PartialSort(PartialSortSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type MaxIters(MaxItersSEXP);
    Rcpp::traits::input_parameter< const double >::type rtol(rtolSEXP);
    Rcpp::traits::input_parameter< const double >::type atol(atolSEXP);
    Rcpp::traits::input_parameter< const bool >::type ActiveSet(ActiveSetSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type ActiveSetNum(ActiveSetNumSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type MaxNumSwaps(MaxNumSwapsSEXP);
    Rcpp::traits::input_parameter< const double >::type ScaleDownFactor(ScaleDownFactorSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type ScreenSize(ScreenSizeSEXP);
    Rcpp::traits::input_parameter< const bool >::type LambdaU(LambdaUSEXP);
    Rcpp::traits::input_parameter< const std::vector< std::vector<double> > >::type Lambdas(LambdasSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type ExcludeFirstK(ExcludeFirstKSEXP);
    Rcpp::traits::input_parameter< const bool >::type Intercept(InterceptSEXP);
    Rcpp::traits::input_parameter< const bool >::type withBounds(withBoundsSEXP);
    Rcpp::traits::input_parameter< const arma::vec& >::type Lows(LowsSEXP);
    Rcpp::traits::input_parameter< const arma::vec& >::type Highs(HighsSEXP);
    L0LearnFit_sparse(X, y, Loss, Penalty, Algorithm, NnzStopNum, G_ncols, G_nrows, Lambda2Max, Lambda2Min, PartialSort, MaxIters, rtol, atol, ActiveSet, ActiveSetNum, MaxNumSwaps, ScaleDownFactor, ScreenSize, LambdaU, Lambdas, ExcludeFirstK, Intercept, withBounds, Lows, Highs);
    return R_NilValue;
END_RCPP
}
// L0LearnFit_dense
void L0LearnFit_dense(const arma::mat& X, const arma::vec& y, const std::string Loss, const std::string Penalty, const std::string Algorithm, const std::size_t NnzStopNum, const std::size_t G_ncols, const std::size_t G_nrows, const double Lambda2Max, const double Lambda2Min, const bool PartialSort, const std::size_t MaxIters, const double rtol, const double atol, const bool ActiveSet, const std::size_t ActiveSetNum, const std::size_t MaxNumSwaps, const double ScaleDownFactor, const std::size_t ScreenSize, const bool LambdaU, const std::vector< std::vector<double> > Lambdas, const std::size_t ExcludeFirstK, const bool Intercept, const bool withBounds, const arma::vec& Lows, const arma::vec& Highs);
RcppExport SEXP _L0Learn_L0LearnFit_dense(SEXP XSEXP, SEXP ySEXP, SEXP LossSEXP, SEXP PenaltySEXP, SEXP AlgorithmSEXP, SEXP NnzStopNumSEXP, SEXP G_ncolsSEXP, SEXP G_nrowsSEXP, SEXP Lambda2MaxSEXP, SEXP Lambda2MinSEXP, SEXP PartialSortSEXP, SEXP MaxItersSEXP, SEXP rtolSEXP, SEXP atolSEXP, SEXP ActiveSetSEXP, SEXP ActiveSetNumSEXP, SEXP MaxNumSwapsSEXP, SEXP ScaleDownFactorSEXP, SEXP ScreenSizeSEXP, SEXP LambdaUSEXP, SEXP LambdasSEXP, SEXP ExcludeFirstKSEXP, SEXP InterceptSEXP, SEXP withBoundsSEXP, SEXP LowsSEXP, SEXP HighsSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::mat& >::type X(XSEXP);
    Rcpp::traits::input_parameter< const arma::vec& >::type y(ySEXP);
    Rcpp::traits::input_parameter< const std::string >::type Loss(LossSEXP);
    Rcpp::traits::input_parameter< const std::string >::type Penalty(PenaltySEXP);
    Rcpp::traits::input_parameter< const std::string >::type Algorithm(AlgorithmSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type NnzStopNum(NnzStopNumSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type G_ncols(G_ncolsSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type G_nrows(G_nrowsSEXP);
    Rcpp::traits::input_parameter< const double >::type Lambda2Max(Lambda2MaxSEXP);
    Rcpp::traits::input_parameter< const double >::type Lambda2Min(Lambda2MinSEXP);
    Rcpp::traits::input_parameter< const bool >::type PartialSort(PartialSortSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type MaxIters(MaxItersSEXP);
    Rcpp::traits::input_parameter< const double >::type rtol(rtolSEXP);
    Rcpp::traits::input_parameter< const double >::type atol(atolSEXP);
    Rcpp::traits::input_parameter< const bool >::type ActiveSet(ActiveSetSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type ActiveSetNum(ActiveSetNumSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type MaxNumSwaps(MaxNumSwapsSEXP);
    Rcpp::traits::input_parameter< const double >::type ScaleDownFactor(ScaleDownFactorSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type ScreenSize(ScreenSizeSEXP);
    Rcpp::traits::input_parameter< const bool >::type LambdaU(LambdaUSEXP);
    Rcpp::traits::input_parameter< const std::vector< std::vector<double> > >::type Lambdas(LambdasSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type ExcludeFirstK(ExcludeFirstKSEXP);
    Rcpp::traits::input_parameter< const bool >::type Intercept(InterceptSEXP);
    Rcpp::traits::input_parameter< const bool >::type withBounds(withBoundsSEXP);
    Rcpp::traits::input_parameter< const arma::vec& >::type Lows(LowsSEXP);
    Rcpp::traits::input_parameter< const arma::vec& >::type Highs(HighsSEXP);
    L0LearnFit_dense(X, y, Loss, Penalty, Algorithm, NnzStopNum, G_ncols, G_nrows, Lambda2Max, Lambda2Min, PartialSort, MaxIters, rtol, atol, ActiveSet, ActiveSetNum, MaxNumSwaps, ScaleDownFactor, ScreenSize, LambdaU, Lambdas, ExcludeFirstK, Intercept, withBounds, Lows, Highs);
    return R_NilValue;
END_RCPP
}
// L0LearnCV_sparse
void L0LearnCV_sparse(const arma::sp_mat& X, const arma::vec& y, const std::string Loss, const std::string Penalty, const std::string Algorithm, const std::size_t NnzStopNum, const std::size_t G_ncols, const std::size_t G_nrows, const double Lambda2Max, const double Lambda2Min, const bool PartialSort, const std::size_t MaxIters, const double rtol, const double atol, const bool ActiveSet, const std::size_t ActiveSetNum, const std::size_t MaxNumSwaps, const double ScaleDownFactor, const std::size_t ScreenSize, const bool LambdaU, const std::vector< std::vector<double> > Lambdas, const std::size_t nfolds, const double seed, const std::size_t ExcludeFirstK, const bool Intercept, const bool withBounds, const arma::vec& Lows, const arma::vec& Highs);
RcppExport SEXP _L0Learn_L0LearnCV_sparse(SEXP XSEXP, SEXP ySEXP, SEXP LossSEXP, SEXP PenaltySEXP, SEXP AlgorithmSEXP, SEXP NnzStopNumSEXP, SEXP G_ncolsSEXP, SEXP G_nrowsSEXP, SEXP Lambda2MaxSEXP, SEXP Lambda2MinSEXP, SEXP PartialSortSEXP, SEXP MaxItersSEXP, SEXP rtolSEXP, SEXP atolSEXP, SEXP ActiveSetSEXP, SEXP ActiveSetNumSEXP, SEXP MaxNumSwapsSEXP, SEXP ScaleDownFactorSEXP, SEXP ScreenSizeSEXP, SEXP LambdaUSEXP, SEXP LambdasSEXP, SEXP nfoldsSEXP, SEXP seedSEXP, SEXP ExcludeFirstKSEXP, SEXP InterceptSEXP, SEXP withBoundsSEXP, SEXP LowsSEXP, SEXP HighsSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::sp_mat& >::type X(XSEXP);
    Rcpp::traits::input_parameter< const arma::vec& >::type y(ySEXP);
    Rcpp::traits::input_parameter< const std::string >::type Loss(LossSEXP);
    Rcpp::traits::input_parameter< const std::string >::type Penalty(PenaltySEXP);
    Rcpp::traits::input_parameter< const std::string >::type Algorithm(AlgorithmSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type NnzStopNum(NnzStopNumSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type G_ncols(G_ncolsSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type G_nrows(G_nrowsSEXP);
    Rcpp::traits::input_parameter< const double >::type Lambda2Max(Lambda2MaxSEXP);
    Rcpp::traits::input_parameter< const double >::type Lambda2Min(Lambda2MinSEXP);
    Rcpp::traits::input_parameter< const bool >::type PartialSort(PartialSortSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type MaxIters(MaxItersSEXP);
    Rcpp::traits::input_parameter< const double >::type rtol(rtolSEXP);
    Rcpp::traits::input_parameter< const double >::type atol(atolSEXP);
    Rcpp::traits::input_parameter< const bool >::type ActiveSet(ActiveSetSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type ActiveSetNum(ActiveSetNumSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type MaxNumSwaps(MaxNumSwapsSEXP);
    Rcpp::traits::input_parameter< const double >::type ScaleDownFactor(ScaleDownFactorSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type ScreenSize(ScreenSizeSEXP);
    Rcpp::traits::input_parameter< const bool >::type LambdaU(LambdaUSEXP);
    Rcpp::traits::input_parameter< const std::vector< std::vector<double> > >::type Lambdas(LambdasSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type nfolds(nfoldsSEXP);
    Rcpp::traits::input_parameter< const double >::type seed(seedSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type ExcludeFirstK(ExcludeFirstKSEXP);
    Rcpp::traits::input_parameter< const bool >::type Intercept(InterceptSEXP);
    Rcpp::traits::input_parameter< const bool >::type withBounds(withBoundsSEXP);
    Rcpp::traits::input_parameter< const arma::vec& >::type Lows(LowsSEXP);
    Rcpp::traits::input_parameter< const arma::vec& >::type Highs(HighsSEXP);
    L0LearnCV_sparse(X, y, Loss, Penalty, Algorithm, NnzStopNum, G_ncols, G_nrows, Lambda2Max, Lambda2Min, PartialSort, MaxIters, rtol, atol, ActiveSet, ActiveSetNum, MaxNumSwaps, ScaleDownFactor, ScreenSize, LambdaU, Lambdas, nfolds, seed, ExcludeFirstK, Intercept, withBounds, Lows, Highs);
    return R_NilValue;
END_RCPP
}
// L0LearnCV_dense
void L0LearnCV_dense(const arma::mat& X, const arma::vec& y, const std::string Loss, const std::string Penalty, const std::string Algorithm, const std::size_t NnzStopNum, const std::size_t G_ncols, const std::size_t G_nrows, const double Lambda2Max, const double Lambda2Min, const bool PartialSort, const std::size_t MaxIters, const double rtol, const double atol, const bool ActiveSet, const std::size_t ActiveSetNum, const std::size_t MaxNumSwaps, const double ScaleDownFactor, const std::size_t ScreenSize, const bool LambdaU, const std::vector< std::vector<double> > Lambdas, const std::size_t nfolds, const double seed, const std::size_t ExcludeFirstK, const bool Intercept, const bool withBounds, const arma::vec& Lows, const arma::vec& Highs);
RcppExport SEXP _L0Learn_L0LearnCV_dense(SEXP XSEXP, SEXP ySEXP, SEXP LossSEXP, SEXP PenaltySEXP, SEXP AlgorithmSEXP, SEXP NnzStopNumSEXP, SEXP G_ncolsSEXP, SEXP G_nrowsSEXP, SEXP Lambda2MaxSEXP, SEXP Lambda2MinSEXP, SEXP PartialSortSEXP, SEXP MaxItersSEXP, SEXP rtolSEXP, SEXP atolSEXP, SEXP ActiveSetSEXP, SEXP ActiveSetNumSEXP, SEXP MaxNumSwapsSEXP, SEXP ScaleDownFactorSEXP, SEXP ScreenSizeSEXP, SEXP LambdaUSEXP, SEXP LambdasSEXP, SEXP nfoldsSEXP, SEXP seedSEXP, SEXP ExcludeFirstKSEXP, SEXP InterceptSEXP, SEXP withBoundsSEXP, SEXP LowsSEXP, SEXP HighsSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::mat& >::type X(XSEXP);
    Rcpp::traits::input_parameter< const arma::vec& >::type y(ySEXP);
    Rcpp::traits::input_parameter< const std::string >::type Loss(LossSEXP);
    Rcpp::traits::input_parameter< const std::string >::type Penalty(PenaltySEXP);
    Rcpp::traits::input_parameter< const std::string >::type Algorithm(AlgorithmSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type NnzStopNum(NnzStopNumSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type G_ncols(G_ncolsSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type G_nrows(G_nrowsSEXP);
    Rcpp::traits::input_parameter< const double >::type Lambda2Max(Lambda2MaxSEXP);
    Rcpp::traits::input_parameter< const double >::type Lambda2Min(Lambda2MinSEXP);
    Rcpp::traits::input_parameter< const bool >::type PartialSort(PartialSortSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type MaxIters(MaxItersSEXP);
    Rcpp::traits::input_parameter< const double >::type rtol(rtolSEXP);
    Rcpp::traits::input_parameter< const double >::type atol(atolSEXP);
    Rcpp::traits::input_parameter< const bool >::type ActiveSet(ActiveSetSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type ActiveSetNum(ActiveSetNumSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type MaxNumSwaps(MaxNumSwapsSEXP);
    Rcpp::traits::input_parameter< const double >::type ScaleDownFactor(ScaleDownFactorSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type ScreenSize(ScreenSizeSEXP);
    Rcpp::traits::input_parameter< const bool >::type LambdaU(LambdaUSEXP);
    Rcpp::traits::input_parameter< const std::vector< std::vector<double> > >::type Lambdas(LambdasSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type nfolds(nfoldsSEXP);
    Rcpp::traits::input_parameter< const double >::type seed(seedSEXP);
    Rcpp::traits::input_parameter< const std::size_t >::type ExcludeFirstK(ExcludeFirstKSEXP);
    Rcpp::traits::input_parameter< const bool >::type Intercept(InterceptSEXP);
    Rcpp::traits::input_parameter< const bool >::type withBounds(withBoundsSEXP);
    Rcpp::traits::input_parameter< const arma::vec& >::type Lows(LowsSEXP);
    Rcpp::traits::input_parameter< const arma::vec& >::type Highs(HighsSEXP);
    L0LearnCV_dense(X, y, Loss, Penalty, Algorithm, NnzStopNum, G_ncols, G_nrows, Lambda2Max, Lambda2Min, PartialSort, MaxIters, rtol, atol, ActiveSet, ActiveSetNum, MaxNumSwaps, ScaleDownFactor, ScreenSize, LambdaU, Lambdas, nfolds, seed, ExcludeFirstK, Intercept, withBounds, Lows, Highs);
    return R_NilValue;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_L0Learn_cor_matrix", (DL_FUNC) &_L0Learn_cor_matrix, 2},
    {"_L0Learn_L0LearnFit_sparse", (DL_FUNC) &_L0Learn_L0LearnFit_sparse, 26},
    {"_L0Learn_L0LearnFit_dense", (DL_FUNC) &_L0Learn_L0LearnFit_dense, 26},
    {"_L0Learn_L0LearnCV_sparse", (DL_FUNC) &_L0Learn_L0LearnCV_sparse, 28},
    {"_L0Learn_L0LearnCV_dense", (DL_FUNC) &_L0Learn_L0LearnCV_dense, 28},
    {NULL, NULL, 0}
};

RcppExport void R_init_L0Learn(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
