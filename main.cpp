#include <iostream>
#include <chrono>
#include "CSVLoader.hpp"
#include "findBestMatch.hpp"
#include <cmath>
#include <vector>

int main() {

    std::vector<ExperimentResult> results;
    int j=1;
    for(int i=0; i<2;i++) {
        results.push_back(firstExperiment(j*100));
        j=pow(2,i);
    }
    writeToCSV(results, "experiment1_results");     //FIXME non crea il file
}