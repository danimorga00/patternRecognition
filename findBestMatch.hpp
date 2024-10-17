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
    int querySize;
    int numThreads;
}ExperimentResult;

int findBestMatch_sequential(const std::vector<double>& longSeries, const std::vector<double>& shortSeries);
int findBestMatch_parallelized(const std::vector<double>& longSeries, const std::vector<double>& shortSeries, int numThreads) ;
double calculateSAD(const std::vector<double>& series1, const std::vector<double>& series2, int startIdx);
std::vector<double> generateRandomDoubleArray(int size, double min, double max) ;
std::vector<ExperimentResult> firstExperiment(int iterations, int expConstant) ;
std::vector<ExperimentResult> secondExperiment(int maxThreads);
void writeToCSV(const std::vector<ExperimentResult>& results, const std::string& filename);



#endif // TIMESERIESSEARCH_H
