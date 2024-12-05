#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int countMatches(const string& str, const string& pattern) {
    if (str.size() < pattern.size())
        return 0;  // Evita l'errore
    int count = 0;
    for (size_t i = 0; i <= str.size() - pattern.size(); ++i) {
        if (str.substr(i, pattern.size()) == pattern) {
            count++;
        }
    }
    return count;
}

int countOccurrences(const vector<vector<char>>& matrix, const string& pattern) {
    int count = 0;
    size_t n = matrix.size();
    size_t m = matrix[0].size();

    for (size_t i = 0; i < n; ++i) {
        string row, col;
        for (size_t j = 0; j < m; ++j) {
            row += matrix[i][j];
            col += matrix[j][i];
        }
        count += countMatches(row, pattern);
        count += countMatches(string(row.rbegin(), row.rend()), pattern);
        count += countMatches(col, pattern);
        count += countMatches(string(col.rbegin(), col.rend()), pattern);
    }

    for (int d = -(int)n + 1; d < (int)m; ++d) {
        string mainDiag, antiDiag;
        for (size_t i = 0; i < n; ++i) {
            size_t jMain = i + d;
            size_t jAnti = m - 1 - i - d;
            if (jMain < m && jMain >= 0)
                mainDiag += matrix[i][jMain];
            if (jAnti < m && jAnti >= 0)
                antiDiag += matrix[i][jAnti];
        }
        count += countMatches(mainDiag, pattern);
        count += countMatches(string(mainDiag.rbegin(), mainDiag.rend()), pattern);
        count += countMatches(antiDiag, pattern);
        count += countMatches(string(antiDiag.rbegin(), antiDiag.rend()), pattern);
    }

    return count;
}

int main() {
    vector<vector<char>> matrix;
    ifstream file("input.txt");

    string line;
    while (getline(file, line)) {
        matrix.push_back(vector<char>(line.begin(), line.end()));
    }
    file.close();

    for (size_t i = 0; i < matrix.size(); ++i) {
        if (matrix[i].size() != matrix[0].size()) {
            cerr << "Errore: righe di lunghezza diversa nella matrice." << endl;
            return 1;
        }
    }

    string pattern = "XMAS";
    int totalCount = countOccurrences(matrix, pattern);

    cout << totalCount << endl;

    return 0;
}
