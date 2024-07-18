#include "searchTimeSeries.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <omp.h>

double calculateSAD(const std::vector<double>& series1, const std::vector<double>& series2, int startIdx) {
    double sad = 0.0;
    int size = series2.size();
    for (int i = 0; i < size; ++i) {
        sad += std::abs(series1[startIdx + i] - series2[i]);
    }
    return sad;
}

int findBestMatch(const std::vector<double>& longSeries, const std::vector<double>& shortSeries) {
    int longSize = longSeries.size();
    int shortSize = shortSeries.size();
    double minSAD = std::numeric_limits<double>::max();
    int bestMatchIdx = -1;

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
// Definizione della funzione per cercare la serie temporale corta nella serie temporale lunga
std::vector<int> searchTimeSeries(const std::vector<int>& longSeries, const std::vector<int>& shortSeries) {
    std::vector<int> results;

    // Itera attraverso la serie temporale lunga fino a quando è possibile ospitare la serie temporale corta
    #pragma omp parallel for
    for (int i = 0; i <= longSeries.size() - shortSeries.size(); ++i) {
        bool found = true;

        // Verifica se la serie temporale corta si trova in questa posizione della serie temporale lunga
        for (int j = 0; j < shortSeries.size(); ++j) {
            if (longSeries[i + j] != shortSeries[j]) {
                found = false;
                break;
            }
        }

        // Se trovato è vero, significa che abbiamo trovato una corrispondenza
        if (found) {
            results.push_back(i);  // Aggiungi l'indice di inizio della serie trovata
        }
    }

    return results;
}

// Funzione per estrarre casualmente un sottoarray di dimensione n dall'array grande
std::vector<int> extractRandomSubarray(const std::vector<int>& array, int n) {
    std::vector<int> subarray;

    // Controllo se l'array è sufficientemente grande per contenere il sottoarray di dimensione n
    if (array.size() < n) {
        std::cerr << "Errore: Dimensione del sottoarray richiesta maggiore della dimensione dell'array." << std::endl;
        return subarray; // Ritorno un sottoarray vuoto in caso di errore
    }

    // Generazione di un indice casuale i compreso tra 0 e array.size() - n
    int maxIndex = array.size() - n;
    if (maxIndex < 0) {
        std::cerr << "Errore: Impossibile estrarre un sottoarray di dimensione " << n << " dall'array dato." << std::endl;
        return subarray; // Ritorno un sottoarray vuoto in caso di errore
    }

    // Inizializzazione del generatore di numeri casuali con il tempo corrente
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generazione di un indice casuale i
    int startIndex = std::rand() % (maxIndex + 1);

    // Estrazione del sottoarray di dimensione n a partire dall'indice startIndex
    subarray.insert(subarray.end(), array.begin() + startIndex, array.begin() + startIndex + n);

    return subarray;
}


