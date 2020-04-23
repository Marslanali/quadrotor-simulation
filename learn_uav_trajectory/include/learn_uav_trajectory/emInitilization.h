//
// Created by arslan on 16/11/19.
//

#ifndef PROGRAMMING_BY_DEMONSTRATION_EMINITILIZATION_H
#define PROGRAMMING_BY_DEMONSTRATION_EMINITILIZATION_H

#include <armadillo>
#include <vector>


class EmInitilization
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

    void learn_kmeans(const  arma::Mat<double>& _data, uint _nb_states);

    arma::Col<double> get_priors();
    std::vector<arma::Col<double>> get_mu();
    std::vector< arma::Mat<double>> get_sigma();

};

#endif //PROGRAMMING_BY_DEMONSTRATION_EMINITILIZATION_H
