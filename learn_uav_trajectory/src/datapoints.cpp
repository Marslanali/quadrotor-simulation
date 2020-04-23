//
// Created by arslan on 16/11/19.
//


#include "../include/datapoints.h"

Datapoints::Datapoints(uint _nb_vars, uint _nb_points)
{
    nb_vars = _nb_vars;
    nb_points = _nb_points;
    data = arma::zeros(_nb_vars, _nb_points);
}


arma::Mat<double> Datapoints::get_data_points()
{
    return data;
}

uint Datapoints::get_num_vars()
{
    return nb_vars;
}

uint Datapoints::get_num_points()
{
    return nb_points;
}

std::vector <std::string> Datapoints::get_var_names()
{

}

void Datapoints::set_data(const  arma::Mat<double>& _data)
{
    data = _data;
    nb_vars = data.n_rows;
    nb_points = data.n_cols;
}

void Datapoints::load_from_file(std::string path, bool is_transpose)
{
    arma::Mat<double> data;
    data.load(path,  arma::raw_ascii);
    if(is_transpose)
        data = data.t();
    set_data(data);


}


void Datapoints::save_file(std::string path)
{
    data.save(path, arma::raw_ascii);
}
