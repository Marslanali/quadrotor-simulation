//
// Created by arslan on 16/11/19.
//


#ifndef PROGRAMMING_BY_DEMONSTRATION_GMR_H
#define PROGRAMMING_BY_DEMONSTRATION_GMR_H

#include "../include/mvn.h"
#include <armadillo>
#include <vector>


class GMR
{
private:
    uint nb_vars;
    uint nb_states;
    uint nb_data_points;
    
    arma::Col<double> priors;
    std::vector<arma::Col<double>> mu;
    std::vector< arma::Mat<double> > sigma;
    arma::Mat<double> x;  //clock signal as input
    arma::span in;
    arma::span out;

    GaussianDistribution pdf;
    arma::Mat<double> expected_mu;


public:

    void compute_gmr ( const arma::Col<double>& _priors, const std::vector<arma::Col<double>>& _mu, const  std::vector< arma::Mat<double>>& _sigma, const  arma::Mat<double>& _x, arma::span _in, arma::span _out);
     arma::Mat<double>  return_expected_mu();



};

#endif //PROGRAMMING_BY_DEMONSTRATION_GMR_H
