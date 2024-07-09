#ifndef CSVLOADER_H
#define CSVLOADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<int> getColumn(const std::string& filename, int columnIdx, char delimiter = ',');

#endif // CSVLOADER_H
