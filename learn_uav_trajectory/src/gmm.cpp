//
// Created by arslan on 16/11/19.
//
/**
 This class learns the parameters of a Gaussian Mixture Model
 (GMM) using a recursive Expectation-Maximization (EM) algorithm, starting
 from an initial estimation of the parameters.


 Inputs -----------------------------------------------------------------
   o _data:    D x N array representing N datapoints of D dimensions.
   o _priors: 1 x K array representing the initial prior probabilities
              of the K GMM components.
   o _mu:     D x K array representing the initial centers of the K GMM
              components.
   o _sigma:  D x D x K array representing the initial covariance matrices
              of the K GMM components.
 Outputs ----------------------------------------------------------------
   o Priors:  1 x K array representing the prior probabilities of the K GMM
              components.
   o mu:      D x K array representing the centers of the K GMM components.
   o sigma:   D x D x K array representing the covariance matrices of the
              K GMM components.

*/

#include "../include/gmm.h"
#include <iostream>

void GMM::EM(const  arma::Mat<double>& _data,  const arma::Col<double>& _priors, const std::vector<arma::Col<double>>& _mu, const std::vector< arma::Mat<double>>& _sigma)
{
    nb_vars = _data.n_rows;
    nb_data_points = _data.n_cols;
    nb_states = _sigma.size();

    data = _data;
    mu = _mu;
    sigma = _sigma;
    priors = _priors;


    /**
     * Training of a Gaussian mixture model (GMM) with an expectation-maximization
     * (EM) algorithm.
     */

    const int nb_max_steps = 100;			// Maximum number of iterations allowed
    const int nb_min_steps = 5;				// Minimum number of iterations allowed
    const double max_diff_log_likelihood = 1e-4;	// Likelihood increase threshold
    // to stop the algorithm
    std::vector<double> log_likelihoods;

    int count_steps=0;

    for (int iter = 0; iter < nb_max_steps; ++iter)
    {
        count_steps += 1;
        //******************E-STEP************************************
        arma::Mat<double> pxi =  arma::zeros(nb_data_points, nb_states);

        for (int i = 0; i < nb_states; ++i)
        {
            //Compute probability p(x|i)
            pxi( arma::span::all, i) = pdf.gausspdf_vec(data, mu[i], sigma[i]);
            //std::cout<<"\nPxi\n"<<pxi<<std::endl;

        }
        //Compute posterior probability p(i|x)
        arma::Mat<double> pix_tmp = repmat(priors.t(), nb_data_points, 1) % pxi;
        arma::Mat<double> pix = pix_tmp / repmat(sum(pix_tmp, 1), 1, nb_states);
        //compute cumulated posterior probability
        arma::Mat<double> E = sum(pix,0);


        //*********************************M-Step***************************************

        for (int i = 0; i < nb_states; ++i)
        {
            //Update the priors
            priors[i] = E[i] / nb_data_points;
            //Update the centers
            mu[i] = data * pix( arma::span::all, i) / E[i];
            // update the covariance matrices
             arma::Mat<double> data_tmp1 = data - repmat(mu[i], 1, nb_data_points);
            sigma[i] = (repmat(pix( arma::span::all, i).t(), nb_vars, 1) % data_tmp1 * data_tmp1.t()) / E[i];
            // Add a tiny variance to avoid numerical instability
            sigma[i] = sigma[i] +  arma::eye(data.n_rows, data.n_rows) * diag_reg_fact;

        }

        // EM stopping criteria
        arma::Mat<double> L =  arma::zeros(nb_states, data.n_cols);

        for (int i = 0; i < nb_states; ++i)
        {
            L(i,  arma::span::all) = priors(i) *  arma::Mat<double>(pdf.gausspdf_vec(data, mu[i], sigma[i])).t();
        }

        // Compute average log-likelihood
        log_likelihoods.push_back(arma::Col<double>(sum(log(sum(L, 0)), 1))[0] / data.n_cols);

        // Stop the algorithm if EM converged (small change of log-likelihood)
        if (iter >= nb_min_steps)
        {
            if (log_likelihoods[iter] - log_likelihoods[iter - 1] < max_diff_log_likelihood)
                break;
        }


    }

   // std::cout<<"Total EM Steps are: "<<count_steps<<std::endl;

}


arma::Col<double> GMM::return_priors()
{
    return priors;
}

std::vector<arma::Col<double>> GMM::return_mu()
{
    return mu;
}

std::vector< arma::Mat<double>> GMM::return_sigma()
{
    return sigma;
}