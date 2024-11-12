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

std::vector<ExperimentResult> firstExperiment(int iterations, int expConstant) {

    std::vector<ExperimentResult> results;
    int j=1;
    int querySize;
    for(int i=0; i<iterations;i++) {

        querySize = j*expConstant;
        ExperimentResult result = {0};
        std::string filename = "../BTC-2019min.csv";
        int columnIndex = 3, min = 1, max = 10000;

        std::vector<double> timeSeries = getColumn(filename, columnIndex);
        std::vector<double> query = generateRandomDoubleArray(querySize, min, max);

        auto start = std::chrono::high_resolution_clock::now();
        int index = findBestMatch(timeSeries, query, 1);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_seq = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "------------------------------------- Versione sequenziale --------------------------------------- " << std::endl;
        if (index != -1) {
            std::cout << "La serie corta corrisponde meglio alla serie lunga all'indice " << index << " con SAD" << std::endl;
        } else {
            std::cout << "Nessuna corrispondenza trovata." << std::endl;
        }
        std::cout << "Tempo di esecuzione: " << ((float)duration_seq.count())/1000000<< " microsecondi" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        index = findBestMatch(timeSeries, query, 20);
        end = std::chrono::high_resolution_clock::now();
        auto duration_par = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << std::endl << "--------------------------------------Versione parallela ----------------------------------------- " << std::endl;
        if (index != -1) {
            std::cout << "La serie corta corrisponde meglio alla serie lunga all'indice " << index << " con SAD" << std::endl;
        } else {
            std::cout << "Nessuna corrispondenza trovata." << std::endl;
        }
        std::cout << "Tempo di esecuzione: " << ((float)duration_par.count())/1000000 << " secondi" << std::endl;
        float speedup = float(duration_seq.count())/float(duration_par.count());
        std::cout << "Query size: " << querySize << std::endl;
        std::cout << "Speedup: " << speedup <<  std::endl;

        result.querySize = querySize;
        result.T_par = ((float)duration_par.count())/1000000;
        result.T_seq = ((float)duration_seq.count())/1000000;
        result.speedUp = result.T_seq/result.T_par;

        results.push_back(result);
        j=pow(2,i);
    }
    return results;
}