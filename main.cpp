#include <iostream>
#include <chrono>
#include "CSVLoader.hpp"
#include "findBestMatch.hpp"

int main() {

    std::string filename = "../BTC-2019min.csv";
    int columnIndex = 3, querySize = 1000, min = 1, max = 10000;

    std::vector<double> timeSeries = getColumn(filename, columnIndex);
    std::vector<double> query = generateRandomDoubleArray(querySize, min, max);

    auto start = std::chrono::high_resolution_clock::now();
    int index = findBestMatch_sequential(timeSeries, query);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_seq = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "------------------------------------- Versione sequenziale --------------------------------------- " << std::endl;
    if (index != -1) {
        std::cout << "La serie corta corrisponde meglio alla serie lunga all'indice " << index << " con SAD" << std::endl;
    } else {
        std::cout << "Nessuna corrispondenza trovata." << std::endl;
    }
    std::cout << "Tempo di esecuzione: " << duration_seq.count() << " microsecondi" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    index = findBestMatch_parallelized(timeSeries, query);
    end = std::chrono::high_resolution_clock::now();
    auto duration_par = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << std::endl << "--------------------------------------Versione parallela ----------------------------------------- " << std::endl;
    if (index != -1) {
        std::cout << "La serie corta corrisponde meglio alla serie lunga all'indice " << index << " con SAD" << std::endl;
    } else {
        std::cout << "Nessuna corrispondenza trovata." << std::endl;
    }
    std::cout << "Tempo di esecuzione: " << duration_par.count() << " microsecondi" << std::endl;
    float speedup = float(duration_seq.count())/float(duration_par.count());
    std::cout << "Speedup: " << speedup <<  std::endl;

}