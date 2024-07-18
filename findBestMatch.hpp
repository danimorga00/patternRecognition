#ifndef TIMESERIESSEARCH_H
#define TIMESERIESSEARCH_H

#include <vector>
#include <iostream>
#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For time()

int findBestMatch_sequential(const std::vector<double>& longSeries, const std::vector<double>& shortSeries);
int findBestMatch_parallelized(const std::vector<double>& longSeries, const std::vector<double>& shortSeries) ;
double calculateSAD(const std::vector<double>& series1, const std::vector<double>& series2, int startIdx);
std::vector<double> generateRandomDoubleArray(int size, double min, double max) ;


#endif // TIMESERIESSEARCH_H
