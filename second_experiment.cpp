//
// Created by danie on 16/10/2024.
//
#include "findBestMatch.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <omp.h>
#include <random>
#include <chrono>
#include <ctime>

#include "CSVLoader.hpp"
#include "findBestMatch.hpp"

std::vector<ExperimentResult> secondExperiment(int maxThreads) {

    std::vector<ExperimentResult> results;

    ExperimentResult result = {0};
    std::string filename = "../BTC-2019min.csv";
    int columnIndex = 3, min = 1, max = 10000;

    std::vector<double> timeSeries = getColumn(filename, columnIndex);
    std::vector<double> query = generateRandomDoubleArray(100, min, max);

    for(int i=1; i<=maxThreads; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        int index = findBestMatch_parallelized(timeSeries, query, i);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        if (index != -1) {
            std::cout << "La serie corta corrisponde meglio alla serie lunga all'indice " << index << " con SAD" << std::endl;
        } else {
            std::cout << "Nessuna corrispondenza trovata." << std::endl;
        }
        std::cout << "Tempo di esecuzione: " << ((float)duration.count())/1000000 << " secondi" << std::endl;
        std::cout << "Number of Threads: " << i << std::endl;

        result.querySize = 100;
        result.T_par = ((float)duration.count())/1000000;
        result.speedUp = result.T_seq/result.T_par;
        result.numThreads = i;

        results.push_back(result);
    }
    return results;
}