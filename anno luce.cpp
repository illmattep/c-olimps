#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile || !outputFile) {
        cerr << "errore durante la creazione dei file" << endl;
        return 1;
    }

    int N; // primo valore di input.txt che indica il numro di stelle
    inputFile >> N;

    vector<int> X(N), Y(N), Z(N); // Vettori dinamici per le coordinate delle stelle

    for (int i = 0; i < N; i++) {
        inputFile >> X[i] >> Y[i] >> Z[i]; //lettura da input.txt
    }

    int Q; // Numero di query 
    inputFile >> Q;

    vector<double> distanze(N); // Vettore per le distanze
    for (int i = 0; i < N; i++) {
        distanze[i] = sqrt(X[i] * X[i] + Y[i] * Y[i] + Z[i] * Z[i]);
    }

    for (int i = 0; i < Q; i++) {  //esecuzione delle query
        int distanzaQuery;
        inputFile >> distanzaQuery;
        int stelleRaggiungibili = 0;

        for (int j = 0; j < N; j++) if (distanze[j] <= distanzaQuery) stelleRaggiungibili++;
        outputFile << stelleRaggiungibili << endl;
    }

    inputFile.close(); // Chiude il file di input
    outputFile.close(); // Chiude il file di output

    return 0;
}
