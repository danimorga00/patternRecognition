#include <iostream>
#include <chrono>
#include "CSVLoader.hpp"
#include "searchTimeSeries.hpp"

int main() {

    std::string filename = "C:/Users/danie/CLionProjects/patternRecognition/BTC-2019min.csv";
    int columnIndex = 3; // Estrarre la terza colonna (indice 2), ad esempio
    int n = 3; // Dimensione del sottoarray da estrarre

    std::vector<int> timeSeries = getColumn(filename, columnIndex);

    std::vector<int> query = extractRandomSubarray(timeSeries, n);

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> results = searchTimeSeries(timeSeries, query);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Posizione sottoarray:  " << results[0] << " di " << timeSeries.size() << "\n ";
    std::cout << "Tempo di esecuzione: " << duration.count() << " microsecondi" << std::endl;

}