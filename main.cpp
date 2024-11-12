#include <iostream>
#include <chrono>
#include "CSVLoader.hpp"
#include "findBestMatch.hpp"
#include <cmath>
#include <vector>

int main() {

    std::vector<ExperimentResult> results = secondExperiment(3, 500);
    writeToCSV(results, "exp2.csv");     //FIXME non crea il file
}