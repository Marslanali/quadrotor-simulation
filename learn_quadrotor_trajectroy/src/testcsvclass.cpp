//
// Created by arslanali on 9/3/20.
//


/*
 * project: decision tree and random forest for YouTube Datasets
 * author: arslanali800@hotmail.com
 */


#include "../include/learn_quadrotor_trajectroy/testcsvclass.h"

std::vector<std::vector<std::string> > CSVReader::get_data()
{
    std::string file_path = file_path_;

    std::ifstream file(file_path);

    if (!file)
        std::cerr << "Could not open the file!" << std::endl;
    else{
        std::vector<std::vector<std::string> > data_list;

        std::string line = "";
        // Iterate through each line and split the content using delimeter
        while (getline(file, line))
        {
            std::vector<std::string> vec;
            boost::algorithm::split(vec, line, boost::is_any_of(delimeter_));
            data_list.push_back(vec);
        }
        // Close the File
        file.close();

        return data_list;


    }


}


