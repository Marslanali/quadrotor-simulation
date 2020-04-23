//
// Created by arslan on 16/11/19.
//
//The class Datapoints allows to access samples of n-points and n-variables
//stored in a Armadillo matrix.


#ifndef PROGRAMMING_BY_DEMONSTRATION_DATAPOINTS_H
#define PROGRAMMING_BY_DEMONSTRATION_DATAPOINTS_H


#include <armadillo>
#include <fstream>
#include <vector>



class Datapoints
{
private:
    uint nb_vars;
    uint nb_points;
    std::vector<std::string> vars_names;
    arma::Mat<double> data;

public:

    Datapoints(){};
    Datapoints( uint _nb_vars , uint _nb_points);

    arma::Mat<double> get_data_points();
    uint get_num_points();
    uint get_num_vars();
    std::vector <std::string> get_var_names();

    void set_data(const  arma::Mat<double>& _data);
    void load_from_file(std::string path, bool is_transpose = false);
    void save_file(std::string path);
};



#endif //PROGRAMMING_BY_DEMONSTRATION_DATAPOINTS_H



