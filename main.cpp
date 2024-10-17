#include <iostream>
#include <chrono>
#include "CSVLoader.hpp"
#include "findBestMatch.hpp"
#include <cmath>
#include <vector>

int main() {

    std::vector<ExperimentResult> results = firstExperiment(10, 100);
    writeToCSV(results, "exp1.csv");     //FIXME non crea il file
}