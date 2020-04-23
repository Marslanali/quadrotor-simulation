//
// Created by arslan on 16/11/19.
//

/**
 * This class computer the gaussian distribution.

   Inputs -----------------------------------------------------------------
   o data:
   o mu:
   o sigma:

  Outputs ----------------------------------------------------------------
   o prob:    N array representing the computed probability density function

 *
 */

#include "../include/mvn.h"

arma::Col<double> GaussianDistribution::gausspdf_vec(const  arma::Mat<double>& _data, const arma::Col<double>& _mu, const  arma::Mat<double>& _sigma)
{

    data = _data;
    mu = _mu;
    sigma = _sigma;

    nb_vars = data.n_rows;;
    nb_data_points = data.n_cols;

    data = data.t() - repmat(mu.t(), nb_data_points,1);
    arma::Col<double> prob = sum((data*inv(sigma)) % data,1);
    prob = exp(-0.5*prob) / sqrt(pow(2* arma::datum::pi,nb_vars) * det(sigma) + DBL_MIN);

    return prob;


}