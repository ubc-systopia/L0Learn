#include "CDL012.h"


template <class T>
CDL012<T>::CDL012(const T& Xi, const arma::vec& yi, const Params<T>& P) : CD<T>(Xi, yi, P) {
    Onep2lamda2 = 1 + 2 * this->lambda2; 
    
    this->thr2 = 2 * this->lambda0 / Onep2lamda2;
    this->thr = std::sqrt(this->thr2);
    this->r = *P.r;
    this->result.r = P.r;
}

template <class T>
FitResult<T> CDL012<T>::Fit() {
    
    this->B = clamp_by_vector(this->B, this->Lows, this->Highs);
    
    this->objective = Objective(this->r, this->B);
    
    std::vector<std::size_t> FullOrder = this->Order;
    bool FirstRestrictedPass = true;
    if (this->ActiveSet) {
        this->Order.resize(std::min((int) (this->B.n_nonzero + this->ScreenSize + this->NoSelectK), (int)(this->p))); // std::min(1000,Order.size())
    }
    
    bool ActiveSetInitial = this->ActiveSet;

    for (std::size_t t = 0; t < this->MaxIters; ++t) {
        this->Bprev = this->B;
        
        if (this->isSparse && this->intercept){
            this->UpdateSparse_b0(this->r);
        }
        
        for (auto& i : this->Order) {
            this->UpdateBi(i);
            
        }
        
        //B.print();
        if (this->Converged()) {
            if(FirstRestrictedPass && ActiveSetInitial) {
                if (CWMinCheck()) {
                    break;
                }
                FirstRestrictedPass = false;
                this->Order = FullOrder;
                this->Stabilized = false;
                this->ActiveSet = true;
            } else {
                if (this->Stabilized && ActiveSetInitial) { // && !SecondPass
                    if (CWMinCheck()) {
                        break;
                    }
                    this->Order = this->OldOrder; // Recycle over all coordinates to make sure the achieved point is a CW-min.
                    //SecondPass = true; // a 2nd pass will be performed
                    this->Stabilized = false;
                    this->ActiveSet = true;
                } else {
                    break;
                }
            }
        }
        if (this->ActiveSet) {
            this->SupportStabilized();
        }
    }
    
    if (this->isSparse && this->intercept){
        this->UpdateSparse_b0(this->r);
    }
    
    this->result.Objective = this->objective;
    this->result.B = this->B;
    *(this->result.r) = this->r; // change to pointer later
    this->result.IterNum = this->CurrentIters;
    this->result.b0 = this->b0;
    return this->result;
}

template <class T>
bool CDL012<T>::CWMinCheck(){
    // Get the Sc = FullOrder - Order
    std::vector<std::size_t> S;
    for(arma::sp_mat::const_iterator it = this->B.begin(); it != this->B.end(); ++it) {
        S.push_back(it.row());
    }
    
    std::vector<std::size_t> Sc;
    set_difference(
        this->Range1p.begin(),
        this->Range1p.end(),
        S.begin(),
        S.end(),
        back_inserter(Sc));
    
    bool Cwmin = true;
    for (auto& i : Sc) {
        Cwmin = this->UpdateBiCWMinCheck(i, Cwmin);
    }
    return Cwmin;
    
}

template class CDL012<arma::mat>;
template class CDL012<arma::sp_mat>;
