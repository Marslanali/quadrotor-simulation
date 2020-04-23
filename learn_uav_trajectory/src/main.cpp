//
// Created by arslan on 3/11/19.
//

/**
 * @author: Arslan Ali
 * @email: arslanali800@hotmail.com
 *
 * C++ Implementation of gaussian mixture model and gaussain mixture regression for learning 3-dof
 * task. The data set contains mutliple demonstrations of the task which are trained using gaussian
 * mixture model. Gaussian Mixture Regression had been used for generating single generalized trajectory
 * with expected mean and expected covariance matrices.The learned generalized trajectory is exectued on
 * the robot using simple PD controller.The algorithm is tested on 3-degree freedom phantom premium robot.
 *
 */
#include <iostream>
#include <mlpack/methods/kmeans/kmeans.hpp>
#include <sstream>
#include <fstream>
#include <memory>
#include "include/datapoints.h"
#include "emInitilization.h"
#include "emInitilizationMlpack.h"
#include "include/matplotlibcpp.h"
#include "include/gmm.h"
#include "include/gmr.h"

#define nb_states 100
#define nbVar 4
#define nbData 200

namespace plt = matplotlibcpp;
using namespace mlpack::kmeans;


int main(int argc, char **argv)
{


    //Datapoints* position_data = new Datapoints();
    std::shared_ptr<Datapoints> position_data = std::make_shared<Datapoints>();

    //Load dataset containing cartesian position of the robot

    position_data->load_from_file("../data/input_data/data_xy.txt");

    std::cout<<"Data :\n"<< position_data->get_data_points()<<std::endl;
    std::cout<<"nb_vars :\n"<< position_data->get_num_vars()<<std::endl;
    std::cout<<"nb_data_points :\n"<< position_data->get_num_points()<<std::endl;

    //std::cout<<"Time: "<<position_data.get_data_points()(0,span::all)<<std::endl;
    std::cout<<"Position X\n"<<position_data->get_data_points()(0, arma::span::all)<<std::endl;
    std::cout<<"Position Y\n"<<position_data->get_data_points()(1, arma::span::all)<<std::endl;
    //std::cout<<"Position Z\n"<<position_data.get_data_points()(2,span::all)<<std::endl;

    // Initial estimation of the parameters using kmeans algorithm

    //EmInitilizationMlpack* em_init_kmean_mlpack = new EmInitilizationMlpack();
    std::shared_ptr<EmInitilizationMlpack> em_init_kmean_mlpack = std::make_shared<EmInitilizationMlpack>();
    em_init_kmean_mlpack->learn_kmean_mlpack(position_data->get_data_points(), nb_states);

    /*
     * print learned priors, means and covarainces matrices
     */

    std::cout<<"Priors Kmeans MLPACK :\n"<<em_init_kmean_mlpack->get_priors().t()<<std::endl;

    for (int j = 0; j < em_init_kmean_mlpack->get_mu().size(); ++j)
        std::cout << "Mu Kmeans MLPACK:\n" << em_init_kmean_mlpack->get_mu()[j] << std::endl;

    for (int k = 0; k < em_init_kmean_mlpack->get_sigma().size(); ++k)
        std::cout<<"Sigma Kmeans MLPACK:\n"<<em_init_kmean_mlpack->get_sigma()[k]<<std::endl;

    /*EM_Initilization em_init_kmeans;
    em_init_kmeans.learn_kmeans(position_data.get_data_points(), nb_states);

    std::cout<<"Priors : "<<em_init_kmeans.get_priors().t()<<std::endl;

    for (int j = 0; j < em_init_kmeans.get_mu().size(); ++j)
        std::cout << "\n Mu : \n" << em_init_kmeans.get_mu()[j] << std::endl;

    for (int k = 0; k < em_init_kmeans.get_sigma().size(); ++k)
        std::cout<<"\n Sigma :\n "<<em_init_kmeans.get_sigma()[k]<<std::endl;
*/

    // Final estimation of the parameters using gaussian mixture model

    //GMM* gmm = new GMM();
    std::shared_ptr<GMM> gmm = std::make_shared<GMM>();
    gmm->EM(position_data->get_data_points(), em_init_kmean_mlpack->get_priors(), em_init_kmean_mlpack->get_mu(), em_init_kmean_mlpack->get_sigma());

       std::cout<<"Final Priors are:\n"<<gmm->return_priors()<<std::endl;
    for (int i =0; i<gmm->return_mu().size(); ++i)
       std::cout<<"Final Mu are :\n"<<gmm->return_mu()[i]<<std::endl;
    for (int i = 0; i < gmm->return_sigma().size() ; ++i)
       std::cout<<"Final Sigma are:\n"<<gmm->return_sigma()[i]<<std::endl;


    /*
     * GMR for expected mean and covariances
     * we can get learned generalized trajectory using Gaussian Mixture Regression which time variable
     * as an input and mean, covariance matrix as ouptut. The time variable can be generated using linspace
     */
     arma::Mat<double> clock_signal =  arma::linspace<arma::Col<double>>(min(position_data->get_data_points()(0, arma::span::all)),max(position_data->get_data_points()(0, arma::span::all)), position_data->get_num_points());
    clock_signal = clock_signal.t();

    std::cout<<"Clock Signal  "<<clock_signal<<std::endl;

    const  arma::span in(0);
    const  arma::span out(1, position_data->get_num_vars() - 1);
    /**
     * computing GMR with time variable as input
     */

    /*GMR* gmr = new GMR();
    std::shared_ptr<GMR> gmr = std::make_shared<GMR>();
    gmr.Compute_GMR(gmm.return_priors(), gmm.return_mu(), gmm.return_sigma(), clock_signal,in, out);

    std::cout<<"Expected Mean: "<<gmr->return_expected_mu()<<std::endl;
    std::cout<<"Expected Mean Size: "<<size(gmr->return_expected_mu())<<std::endl;*/
    std::ofstream file_kmean_mu("../plots/kmeans_mu.txt");
    std::ofstream file_kmean_sigma("../plots/kmeans_sigma.txt");
    std::ofstream file_gmm_mu("/../plots/gmm_mu.txt");
    std::ofstream file_gmm_sigma("../plots/gmm_sigma.txt");
/*
    std::ofstream fileGMR_mu("../plots/gmr_mu.txt");
    std::ofstream fileGMR_sigma("../plots/gmr_sigma.txt");
*/

    int dim = 2;

    // save the current kmeans parameters

    std::ofstream file_kmean("../data/kmeans/kmeans.txt");
    //file << 2 << " ";
    //file << nb_states << std::endl;
    for(int i=0;i<nb_states;i++)
        file_kmean << em_init_kmean_mlpack->get_priors()[i] << " ";
    file_kmean << std::endl;
    for(int s=0;s<nb_states;s++) {
        for(int i=0;i<dim;i++) {
            file_kmean << em_init_kmean_mlpack->get_mu()[s](i) << " ";
        }
        file_kmean << std::endl;
    }
    for(int s=0;s<nb_states;s++) {
        for(int j=0;j<dim;j++) {
            for(int i=0;i<dim;i++) {
                file_kmean << em_init_kmean_mlpack->get_sigma()[s](i,j) << " ";
            }
            file_kmean << std::endl;
        }
    }


    // save the current gmm parameters
    std::ofstream file_gmm("../data/gmm/gmm.txt");
    //file << 2 << " ";
    //file << nb_states << std::endl;
    for(int i=0;i<nb_states;i++)
        file_gmm << gmm->return_priors()[i] << " ";
    file_gmm << std::endl;
    for(int s=0;s<nb_states;s++) {
        for(int i=0;i<dim;i++) {
            file_gmm << gmm->return_mu()[s](i) << " ";
        }
        file_gmm << std::endl;
    }
    for(int s=0;s<nb_states;s++) {
        for(int j=0;j<dim;j++) {
            for(int i=0;i<dim;i++) {
                file_gmm << gmm->return_sigma()[s](i,j) << " ";
            }
            file_gmm << std::endl;
        }
    }


//    // save the current gmr parameters
//
//    std::ofstream file_gmr("/home/arslan/CLionProjects/cpp_learning_from_demonstration/data/gmr/gmr.txt");
//    //file << 2 << " ";
//    //file << nb_states << std::endl;
//    for(int s=0;s<nb_states;s++) {
//        for(int i=0;i<dim;i++) {
//            file_gmr << gmr.return_expected_mu()[s](i) << " ";
//        }
//        file_gmr << std::endl;
//    }
//    for(int s=0;s<nb_states;s++) {
//        for(int j=0;j<dim;j++) {
//            for(int i=0;i<dim;i++) {
//                file_gmr << gmr.returnExpectedSigma()[s](i,j) << " ";
//            }
//            file_gmr << std::endl;
//        }
//    }
//
//

    std::vector<double> time, position_x, position_y, position_z;
    std::vector<double>  px, py, pz;
    std::vector<double>  plot_clock;


    for (int i = 0; i <position_data->get_num_points() ; ++i)
    {

        // time.push_back(position_data.get_data_points()(0,i));
        position_x.push_back(position_data->get_data_points()(0,i));
        position_y.push_back(position_data->get_data_points()(1,i));
        //  position_z.push_back(position_data.get_data_points()(3,i));

    }

 /*   for (int i = 0; i <gmr->return_expected_mu().n_cols ; ++i)
    {
        px.push_back(gmr->return_expected_mu()(0,i));
        py.push_back(gmr->return_expected_mu()(1,i));
        //pz.push_back(gmr.return_expected_mu()(2,i));
    }
*/

    for (int i = 0; i <position_data->get_num_points() ; ++i)
        plot_clock.push_back(clock_signal(0,i));

    plt::figure();
    plt::plot(plot_clock);
    plt::title("Input clock");
    plt::save("../plots/input_clock.jpg");
    plt::show();

    std::vector <double> x,y;

    for (int i = 0; i <nb_states ; ++i) {
        x.push_back(gmm->return_mu()[i](0));
        y.push_back(gmm->return_mu()[i](1));
    }

    plt::figure();
    plt::title("GMM centroids");
    plt::stem(x,y,".*");
    plt::save("../plots/centroids_gmm.jpg");
    plt::show();

    plt::plot(position_x,position_y,"red");
    plt::title("2-D Input data");
    plt::save("../plots/input_data_2D.jpg");
    plt::show();

    plt::figure();
    plt::subplot(2,1,1);
    //plt::plot(time,"red");
    // plt::subplot(2,2,2);
    plt::plot(position_x,"red");
    plt::title("Input data, x-axis position");
    plt::subplot(2,1,2);
    plt::plot(position_y,"red");
    plt::title("Input data, y-axis position" );
    plt::save("../plots/input_data_1D.jpg");
    //plt::subplot(2,2,4);
    //plt::plot(position_z,"red");
    plt::show();

/*    delete position_data;
    delete em_init_kmean_mlpack;
    delete gmm, gmr;*/


    return 0;
}
