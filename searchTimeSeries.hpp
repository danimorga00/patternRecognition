#ifndef TIMESERIESSEARCH_H
#define TIMESERIESSEARCH_H

#include <vector>
#include <iostream>
#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For time()

// Dichiarazione della funzione per cercare la serie temporale corta nella serie temporale lunga
std::vector<int> searchTimeSeries(const std::vector<int>& longSeries, const std::vector<int>& shortSeries);
std::vector<int> extractRandomSubarray(const std::vector<int>& array, int n);
int findBestMatch(const std::vector<double>& longSeries, const std::vector<double>& shortSeries);
double calculateSAD(const std::vector<double>& series1, const std::vector<double>& series2, int startIdx);


#endif // TIMESERIESSEARCH_H
