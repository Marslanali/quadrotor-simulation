//
// Created by arslan on 18/12/19.
//

#ifndef PROGRAMMING_BY_DEMONSTRATION_EMINITILIZATIONMLPACK_H
#define PROGRAMMING_BY_DEMONSTRATION_EMINITILIZATIONMLPACK_H
#include <mlpack/methods/kmeans/kmeans.hpp>

using namespace mlpack::kmeans;

#include <armadillo>
#include <vector>


class EmInitilizationMlpack
{
private:
    arma::Mat<double> data;
    uint nb_states;
    uint nb_vars;
    uint nb_data_points;

    std::vector<arma::Col<double>> mu;
    std::vector< arma::Mat<double>> sigma;
    arma::Col<double> priors;

public:

    void learn_kmean_mlpack(const  arma::Mat<double>& _data, uint _nb_states);
    void save_kmean_parm(const char file_name []);

    arma::Col<double> get_priors();
    std::vector<arma::Col<double>> get_mu();
    std::vector< arma::Mat<double>> get_sigma();

};




#endif //PROGRAMMING_BY_DEMONSTRATION_EMINITILIZATIONMLPACK_H
