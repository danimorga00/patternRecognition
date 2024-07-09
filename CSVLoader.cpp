#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// Funzione per estrarre una colonna specifica da un file CSV e convertire i valori in interi
std::vector<int> getColumn(const std::string& filename, int columnIdx, char delimiter) {
    std::vector<int> column;

    // Apri il file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Errore: Impossibile aprire il file " << filename << std::endl;
        return column;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        int columnIndex = 0;
        
        // Scorrere le celle della riga fino a raggiungere la colonna desiderata
        while (std::getline(ss, cell, delimiter)) {
            if (columnIndex == columnIdx) {
                // Convertire il valore della cella in intero e aggiungerlo al vettore della colonna
                try {
                    int value = std::stoi(cell);
                    column.push_back(value);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Errore: Conversione fallita per il valore '" << cell << "': " << e.what() << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Errore: Overflow durante la conversione per il valore '" << cell << "': " << e.what() << std::endl;
                }
                break; // Esci dal loop interno una volta trovata la colonna desiderata
            }
            columnIndex++;
        }
    }

    file.close(); // Chiudi il file

    return column;
}
