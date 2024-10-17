#ifndef TIMESERIESSEARCH_H
#define TIMESERIESSEARCH_H

#include <vector>
#include <iostream>
#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For time()

typedef struct {
    float T_seq;
    float T_par;
    float speedUp;
    float querySize;
}ExperimentResult;

int findBestMatch_sequential(const std::vector<double>& longSeries, const std::vector<double>& shortSeries);
int findBestMatch_parallelized(const std::vector<double>& longSeries, const std::vector<double>& shortSeries) ;
double calculateSAD(const std::vector<double>& series1, const std::vector<double>& series2, int startIdx);
std::vector<double> generateRandomDoubleArray(int size, double min, double max) ;
ExperimentResult firstExperiment(int querySize) ;
void writeToCSV(const std::vector<ExperimentResult>& results, const std::string& filename);



#endif // TIMESERIESSEARCH_H
