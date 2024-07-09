#include <iostream>
#include <chrono>
#include "CSVLoader.hpp"
#include "searchTimeSeries.hpp"

int main() {

    std::string filename = "C:/Users/danie/CLionProjects/patternRecognition/BTC-2019min.csv";
    int columnIndex = 3; // Estrarre la terza colonna (indice 2), ad esempio
    int n = 3; // Dimensione del sottoarray da estrarre

    std::vector<double> timeSeries = getColumn(filename, columnIndex);
    std::vector<double> query = {4.0, 5.5, 6.0, 2, 3};

    // Trova la migliore corrispondenza
    auto start = std::chrono::high_resolution_clock::now();
    int index = findBestMatch(timeSeries, query);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    if (index != -1) {
        std::cout << "La serie corta corrisponde meglio alla serie lunga all'indice " << index << " con SAD" << std::endl;
    } else {
        std::cout << "Nessuna corrispondenza trovata." << std::endl;
    }
    std::cout << "Tempo di esecuzione: " << duration.count() << " microsecondi" << std::endl;

}