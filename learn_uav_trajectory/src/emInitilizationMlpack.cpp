//
// Created by arslan on 18/12/19.
//

/**
 * This class implements kmeans clustering algorithm using C++ MLPACK Libraray
 Inputs -----------------------------------------------------------------
   o data:     D x N array representing N datapoints of D dimensions.
   o nb_states: D representing the K GMM components.
 Outputs ----------------------------------------------------------------
   o priors:  Q x N array representing the retrieved N datapoints of
              Q dimensions, i.e. expected means.
   o mu:      Q x Q x N array representing the N expected covariance
              matrices retrieved.
   o sigma:   Q x Q x N array representing the N expected covariance
              matrices retrieved.
 */

#include "../include/emInitilizationMlpack.h"

void EmInitilizationMlpack::learn_kmean_mlpack(const  arma::Mat<double>& _data, uint _nb_states)
{
    // The dataset we are clustering.
    data = _data;

    nb_states = _nb_states;
    nb_vars = _data.n_rows;
    nb_data_points = _data.n_cols;

    // Initialization of Gaussian Mixture Model (GMM) parameters by clustering
    // the data into equal bins based on the first variable (time steps).
    const float diag_reg_fact = 1e-4f;

    mu.clear();
    sigma.clear();
    priors.clear();

    // The number of clusters we are getting.
    size_t clusters = nb_states;
    // The assignments will be stored in this vector.
    arma::Row <size_t> assignments;
    // The centroids will be stored in this matrix.
    arma::Mat <double> centroids;
    // Initialize with the default arguments.
    KMeans<> k;
    k.Cluster(data, clusters, assignments, centroids);

    std::cout<<"Assignments:\n"<<assignments<<std::endl;
    std::cout<<"Centroids:\n"<<centroids<<std::endl;

    arma::Col<arma::uword> idtmp;
    arma::Col <double> priors_tmp (nb_states);

    for (int i = 0; i < nb_states; ++i)
        mu.push_back(centroids( arma::span::all,i));

    for (int i = 0; i < nb_states; ++i)
    {
        idtmp = find(assignments==i);
        std::cout<<"\n IDTMP: \n "<<idtmp.n_elem<<std::endl;
        priors_tmp(i) = idtmp.n_elem;
        std::cout<<"\n KMEANS priors: \n "<< priors_tmp(i)<<std::endl;
        std::cout<<"\n Data for specific Index: \n "<<data.cols(idtmp).t()<<std::endl;

        arma::Mat<double> sigma_tmp = cov(data.cols(idtmp).t());
        std::cout<<"Covariances Matrices:\n"<<sigma_tmp<<std::endl;

/*
        try {
            if(sigma_tmp.n_rows==nb_vars && sigma_tmp.n_cols==nb_vars)
                // Optional regularization term to avoid numerical instability
                sigma_tmp = sigma_tmp + eye(nb_vars, nb_vars) * diag_reg_fact;
           else
                throw "Something went wrong sigma Error!!!!!!\n";
        }
        catch(char const * e) {
            sigma_tmp = eye(nb_vars, nb_vars) * diag_reg_fact;
            cout << "Error message: " << e << endl;
        }
*/

        if(sigma_tmp.n_rows==nb_vars && sigma_tmp.n_cols==nb_vars)
            // Optional regularization term to avoid numerical instability
            sigma_tmp = sigma_tmp +  arma::eye(nb_vars, nb_vars) * diag_reg_fact;


        else {
            std::cout << "\n Something went wrong sigma Error!!!!!!\n" << std::endl;
            sigma_tmp =  arma::eye(nb_vars, nb_vars) * diag_reg_fact;
        }

        sigma.push_back(sigma_tmp);
    }

    priors = priors_tmp / sum(priors_tmp);
    // std::cout<<"Overall priors:\n"<<priors_tmp<<std::endl;
    //std::cout<<"priors Sum:\n"<< sum(priors_tmp)<<std::endl;

}


arma::Col <double> EmInitilizationMlpack::get_priors()
{
    return priors;

}

std::vector<arma::Col<double>> EmInitilizationMlpack::get_mu()
{
    return mu;

}

std::vector < arma::Mat<double>> EmInitilizationMlpack::get_sigma()
{
    return sigma;
}


void EmInitilizationMlpack::save_kmean_parm(const char filename [])
{/*
    // save the current kmeans parameters, coefficents to a file, to be retrieved
    // by the loadParams method
    std::ofstream file(filename);
    file << dim << " ";
    file << nb_states << std::endl;
    for(int i=0;i<nb_states;i++) file << priors_tmp[i] << " ";
    file << std::endl;
    for(int s=0;s<nb_states;s++) {
        for(int i=0;i<dim;i++) {
            file << mu(s,i) << " ";
        }
        file << std::endl;
    }
    for(int s=0;s<nb_states;s++) {
        for(int j=0;j<dim;j++) {
            for(int i=0;i<dim;i++) {
                file << sigma_tmp[s](i,j) << " ";
            }
            file << std::endl;
        }
    }
    */
}