//
// Created by arslan on 16/11/19.
//

#include "../include/emInitilization.h"
void EmInitilization::learn_kmeans(const  arma::Mat<double>& _data, uint _nb_states)
{
    data = _data;
    nb_states = _nb_states;

    nb_vars = data.n_rows;
    nb_data_points = data.n_cols;

    // Initialization of Gaussian Mixture Model (GMM) parameters by clustering
    // the data into equal bins based on the first variable (time steps).
    const float diag_reg_fact = 1e-4f;

    arma::Col<double> timing_sep = arma::linspace<arma::Col<double>>(data(0, 0), data(0, data.n_cols - 1), nb_states + 1);
    std::cout<<"Timming_sep: "<<timing_sep<<std::endl;
    mu.clear();
    sigma.clear();
    priors = arma::Col<double>(nb_states);


    for (unsigned int i = 0; i < nb_states; ++i)
    {
        arma::Col<arma::uword> idtmp = find( (data(0, arma::span::all) >= timing_sep(i)) && (data(0, arma::span::all) < timing_sep(i + 1)) );

        //std::cout<<"\ndata ids: \n"<< i<<std::endl;

        priors(i) = idtmp.size();
        mu.push_back(mean(data.cols(idtmp), 1));
        std::cout<<"Data Cols: "<<data.cols(idtmp).t()<<std::endl;

        arma::Mat<double> sigma_tmp = cov(data.cols(idtmp).t(), data.cols(idtmp).t());
        std::cout<<"Sigma: "<<sigma_tmp<<std::endl;
        // Optional regularization term to avoid numerical instability
       // sigma = sigma + eye(nb_vars, nb_vars) * diag_reg_fact;

        sigma.push_back(sigma_tmp);
    }


    priors = priors / sum(priors);


}


arma::Col<double> EmInitilization::get_priors()
{
    return priors;

}

std::vector<arma::Col<double>> EmInitilization::get_mu()
{
    return mu;

}

std::vector < arma::Mat<double>> EmInitilization::get_sigma()
{
    return sigma;
}

/*
    //**********************************************************************************************************************
    // kmeans clustering testing

    mat X1 = randu(100,2)*0.75+ones(100,2);
    mat X2 = randu(100,2)*0.5-ones(100,2);

    mat X = join_cols(X1,X2);

    std::cout<<"\n "<<X<<std::endl;
    std::cout<<X.n_rows<<std::endl;
    std::cout<<X.n_cols<<std::endl;

    std::vector<double> random_data_X;
    std::vector<double> random_data_Y;

    for (int i=0; i<X.n_rows; ++i)
    {
        random_data_X.push_back(X(i,0));
        random_data_Y.push_back(X(i,1));
    }

    plt::figure();
    plt::plot(random_data_X,random_data_Y,".");
    plt::title("Random Data");
    plt::show();

    //**********************************************************************************************************************
*/