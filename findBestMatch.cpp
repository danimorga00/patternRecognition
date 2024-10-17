#include "findBestMatch.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <omp.h>
#include <random>
#include <ctime>
#include <fstream>

double calculateSAD(const std::vector<double>& series1, const std::vector<double>& series2, int startIdx) {
    double sad = 0.0;
    int size = series2.size();
    for (int i = 0; i < size; ++i) {
        sad += std::abs(series1[startIdx + i] - series2[i]);
    }
    return sad;
}

std::vector<double> generateRandomDoubleArray(int size, double min, double max) {
    std::vector<double> randomArray(size);
    std::mt19937 generator(std::time(nullptr)); // Utilizza il tempo corrente come seed
    std::uniform_real_distribution<double> distribution(min, max);

    for (double& num : randomArray) {
        num = distribution(generator);
    }

    return randomArray;
}

int findBestMatch_sequential(const std::vector<double>& longSeries, const std::vector<double>& shortSeries) {
    int longSize = longSeries.size();
    int shortSize = shortSeries.size();
    double minSAD = std::numeric_limits<double>::max();
    int bestMatchIdx = -1;

    for (int i = 0; i <= longSize - shortSize; ++i) {
        double sad = calculateSAD(longSeries, shortSeries, i);
        if (sad < minSAD) {
            {
                minSAD = sad;
                bestMatchIdx = i;
            }
        }
    }
    return bestMatchIdx;
}

int findBestMatch_parallelized(const std::vector<double>& longSeries, const std::vector<double>& shortSeries, int numThreads) {
    int longSize = longSeries.size();
    int shortSize = shortSeries.size();
    double minSAD = std::numeric_limits<double>::max();
    int bestMatchIdx = -1;

    omp_set_num_threads(numThreads);

    #pragma omp parallel for
    for (int i = 0; i <= longSize - shortSize; ++i) {
        double sad = calculateSAD(longSeries, shortSeries, i);
        if (sad < minSAD) {
            #pragma omp critical
            {
                minSAD = sad;
                bestMatchIdx = i;
            }
        }
    }
    return bestMatchIdx;
}
// Funzione per scrivere il vettore di struct in un file CSV
void writeToCSV(const std::vector<ExperimentResult>& results, const std::string& filename) {
    // Apri il file in modalità scrittura
    std::ofstream file;
    file.open (filename);
    // Controlla se il file è aperto correttamente
    if (!file.is_open()) {
        std::cerr << "Errore nell'aprire il file!" << std::endl;
        return;
    }

    // Scrivi l'intestazione del CSV (opzionale)
    file << "T_seq,T_par,querySize\n";

    // Itera attraverso la lista di risultati e scrivi ogni struct nel CSV
    for (const auto& result : results) {
        file << result.querySize << "," << result.T_seq << "," << result.T_par << "," << result.speedUp << "," << result.numThreads <<"\n";
    }

    // Chiudi il file
    file.close();

    std::cout << "File CSV scritto correttamente." << std::endl;
}