//
// Created by arslan on 16/11/19.
//

#ifndef PROGRAMMING_BY_DEMONSTRATION_MVN_H
#define PROGRAMMING_BY_DEMONSTRATION_MVN_H

#include <stdio.h>
#include <armadillo>
#include <vector>
#include <cfloat>


class GaussianDistribution
{
private:

    uint nb_vars;
    uint nb_data_points;

    arma::Mat<double> data;
    arma::Col<double> mu;
    arma::Mat<double> sigma;

public:

    arma::Col<double> gausspdf_vec(const  arma::Mat<double>& _data, const arma::Col<double>& _mu, const  arma::Mat<double>& _sigma);

};

#endif //PROGRAMMING_BY_DEMONSTRATION_MVN_H
