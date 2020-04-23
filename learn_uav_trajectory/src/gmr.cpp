//
// Created by arslan on 16/11/19.
//

/**
 * This class performs Gaussian Mixture Regression (GMR), using the
 * parameters of a Gaussian Mixture Model (GMM). Given partial input data,
 * the algorithm computes the expected distribution for the resulting
 * dimensions. By providing temporal values as inputs, it thus outputs a
 * smooth generalized version of the data encoded in GMM, and associated
 * constraints expressed by covariance matrices.

 Inputs -----------------------------------------------------------------
   o Priors:  1 x K array representing the prior probabilities of the K GMM
              components.
   o mu:      D x K array representing the centers of the K GMM components.
   o sigma:   D x D x K array representing the covariance matrices of the
              K GMM components.
   o x:       P x N array representing N datapoints of P dimensions.
   o in:      1 x P array representing the dimensions to consider as
              inputs.
   o out:     1 x Q array representing the dimensions to consider as
              outputs (D=P+Q).
 Outputs ----------------------------------------------------------------
   o y:       Q x N array representing the retrieved N datapoints of
              Q dimensions, i.e. expected means.
   o Sigma_y: Q x Q x N array representing the N expected covariance
              matrices retrieved.

 */
#include "../include/gmr.h"
#include <iostream>
#include <fstream>


void GMR::compute_gmr( const arma::Col<double>& _priors, const std::vector<arma::Col<double>>& _mu, const  std::vector< arma::Mat<double>>& _sigma, const  arma::Mat<double>& _x,  arma::span _in,  arma::span _out)
{

    nb_vars = _mu.size();
    nb_data_points = _x.n_cols;
    nb_states= _sigma.size();

    priors = _priors;
    mu = _mu;
    sigma = _sigma;
    x = _x;
    in = _in;
    out = _out;

    std::ofstream position_file("/home/arslan/Arslan Ali/Arslan_Data/GMM-GMR-v2.0/data/Position.txt");

   // const int in = 0;
    //const span out(1, nb_vars - 1);
    const int nb_var_out = out.b - out.a + 1;
    const float diag_reg_fact = 1e-8f;

    // arma::Mat<double> mu_tmp = zeros(nb_var_out, nb_states);
    arma::Mat <double> mu_tmp =  arma::zeros(nb_var_out, nb_states);

    //std::cout<<"input:\n"<<x<<std::endl;

    //-----------------------------------------------------------------------------
    // compute the infulence of each GMM component, given input x
    //-----------------------------------------------------------------------------

    // arma::Mat<double> pxi = zeros(nb_data_points, nb_states);
    arma::Mat <double> pxi =  arma::zeros(nb_data_points, nb_states);
    arma::Col <double> pdf_vec;


    for (int i = 0; i < nb_states; ++i)
    {
        arma::Mat <double> sigma_tmp(1, 1);
        //std::cout<<"pdf_vec\n"<<pdf.gausspdf_vec(x, mu[i](in), sigma[i](in,in))<<std::endl;
        //pdf_vec = pdf.gausspdf_vec(x, mu[i](in), sigma[i](in,in));
        pxi( arma::span::all, i) = priors(i) * pdf.gausspdf_vec(x, mu[i](in), sigma[i](in,in));  // Equation 1.1 ....Error element wise muliplication is not working

    }


    //std::cout<<"Pxi\n"<<pxi<<std::endl;
    //std::cout<<"DBL_MIN\n"<<DBL_MIN<<std::endl;

    arma::Mat<double> beta = pxi / repmat(sum(pxi,1)+ DBL_MIN,1,nb_states);

    //std::cout<<"beta:\n" <<beta<<std::endl;

    //-----------------------------------------------------------------------------
    // Compute expected means y, given input x
    //-----------------------------------------------------------------------------

    arma::Cube <double> y_tmp(nb_var_out,nb_data_points,nb_states);  // output, dataPoints, nb_states

    for (int i = 0; i < nb_states; ++i)
        y_tmp.slice(i) = repmat(mu[i](out),1,nb_data_points) + sigma[i](out,in) * inv (sigma[i](in,in)) * (x - repmat(mu[i](in),1,nb_data_points));

    const  arma::uword N = 1;
    const  arma::uword num_rows = nb_data_points;
    const  arma::uword num_cols = nb_states;

    arma::Cube<double> beta_tmp(num_rows, num_cols, 1);

    beta_tmp.slice(0) = beta;
    beta_tmp.reshape(1, nb_data_points, nb_states);

   // std::cout << "beta_tmp:\n"<< beta_tmp<<std::endl;
    //std::cout<<"Size beta\n"<<size(beta)<<"\nsize beta_tmp:\n"<<size(beta_tmp)<<std::endl;

    arma::Cube<double> beta_tmp2(nb_var_out,nb_data_points,nb_states);  //out,datapionts, states
    for (int i = 0; i < nb_states; ++i) {

        beta_tmp2.slice(i)=repmat(beta_tmp.slice(0),3,1);

    }

    //std::cout<<"beta_tmp3 size: "<<size(beta_tmp3)<<std::endl;
   // Cube <double> y_tmp2 (nb_var_out, nb_data_points, nb_states);
    arma::Cube <double> y_tmp2  = beta_tmp2 % y_tmp;
    //std::cout<<"\ny_tmp2\n"<<y_tmp2<<std::endl;
   // Mat <double > y = zeros (nb_var_out,nb_data_points);
    //beta_tmp3.slice(i)= repmat(beta_tmp.slice(1),3,1) % y_tmp;
    expected_mu =  arma::zeros (nb_var_out,nb_data_points);
    //std::cout<< "expected mean: "<< y <<std::endl;
    //std::cout<< "expected mean size: "<<size(y)<<std::endl;
    // arma::Mat<double> y = randu< arma::Mat<double>>(2,2);
    // arma::Mat<double> y1=sum(y,0);
    //std::cout<<"input\n"<<y<<"\noutput\n"<<y1<<std::endl;

    arma::Mat <double> position_x(nb_states, nb_data_points);
    arma::Mat <double> position_y(nb_states, nb_data_points);
    arma::Mat <double> position_z(nb_states, nb_data_points);


    for (int i = 0; i < nb_states; ++i) {

        position_x(i, arma::span::all) = y_tmp2.slice(i)(0, arma::span::all);
        position_y(i, arma::span::all) = y_tmp2.slice(i)(1, arma::span::all);
        position_z(i, arma::span::all) = y_tmp2.slice(i)(2, arma::span::all);

    }

    expected_mu(0, arma::span::all) = sum(position_x,0);
    expected_mu(1, arma::span::all) = sum(position_y,0);
    expected_mu(2, arma::span::all) = sum(position_z,0);


/*
    std::vector <double> s1;
    std::vector <double> s2;
    std::vector <double> s3;

    std::vector <std::vector<double>> x;
    std::vector <double> y;
    std::vector <double> z;

    for (int i = 0; i < nb_states; ++i) {
        for (int j = 0; j < nb_data_points; ++j) {

            x.push_back(y_tmp2.slice(i)(0,j));


        }

    }




    for (int i = 0; i < nb_data_points; ++i) {
        s1.push_back(y_tmp2.slice(0)(0,i) + y_tmp2.slice(1)(0,i) );
        s2.push_back(y_tmp2.slice(0)(1,i) + y_tmp2.slice(1)(1,i));
        s3.push_back(y_tmp2.slice(0)(2,i) + y_tmp2.slice(1)(2,i));
    }

    for (int j = 0; j < 200 ; ++j)
    std::cout<<"Sumis \n"<<s1[j]<<std::endl;



    for (int i = 0; i < 200; ++i) {

        position_file<<s1[i]<<std::endl;

    }

*/
}


 arma::Mat<double> GMR::return_expected_mu()
{
    return expected_mu ;
}
