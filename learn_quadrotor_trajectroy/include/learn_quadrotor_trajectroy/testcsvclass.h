//
// Created by arslanali on 9/3/20.
//

/*
 * project: decision tree and random forest for YouTube Datasets
 * author: arslanali800@hotmail.com
 */

#ifndef READING_CSV_CPP_TESTCSVCLASS_H
#define READING_CSV_CPP_TESTCSVCLASS_H

#include <string>
#include <iostream>
#include <armadillo>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <boost/algorithm/string.hpp>

class CSVReader
{
    std::string file_path_;
    std::string delimeter_;

public:
    CSVReader(std::string file_path, std::string delimeter = ",") :
              file_path_(file_path),delimeter_(delimeter)
    { }

    // Function to fetch data from a CSV File
    std::vector<std::vector<std::string> > get_data();
};




#endif //READING_CSV_CPP_TESTCSVCLASS_H
