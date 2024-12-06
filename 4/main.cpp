#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int countMatches(const string& str, const string& pattern) {
    if (str.size() < pattern.size())
        return 0;
    int count = 0;
    for (size_t i = 0; i <= str.size() - pattern.size(); ++i) {
        if (str.substr(i, pattern.size()) == pattern) {
            count++;
        }
    }
    return count;
}

bool MASChecker(char newMatrix[3][3]) {
    string line;
    string line2;
    string pattern2 = "MAS";
    int score = 0;

    line += newMatrix[0][0];
    line += newMatrix[1][1];
    line += newMatrix[2][2];

    line2 += newMatrix[0][2];
    line2 += newMatrix[1][1];
    line2 += newMatrix[2][0];

    if (line == pattern2) {
        score++;
    }

    if (line2 == pattern2) {
        score++;
    }

    if ((string(line.rbegin(), line.rend()) == pattern2)) {
        score++;
    }

    if ((string(line2.rbegin(), line2.rend()) == pattern2)) {
        score++;
    }

    if (score == 2) {
        return true;
    } else {
        return false;
    }
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
    const int newMatrixSize = 3;
    char newMatrix[newMatrixSize][newMatrixSize];
    ifstream file("input.txt");

    string line;
    while (getline(file, line)) {
        matrix.push_back(vector<char>(line.begin(), line.end()));
    }
    file.close();

    int supremeCounter = 0;

    for (int i = 0; i < matrix.size() - 2; i++) {
        for (int j = 0; j < matrix[i].size() - 2; j++) {
            for (int ki = 0; ki < newMatrixSize; ki++) {
                for (size_t kj = 0; kj < newMatrixSize; kj++) {
                    newMatrix[ki][kj] = matrix[i + ki][j + kj];
                    // cout << "(" << ki << ")(" << kj << ") = (" << i + ki << ")(" << j + kj << ")   ";
                    // cout << newMatrix[ki][kj] << " ";
                }
                // cout << endl;
            }
            // cout << endl << endl;

            if (newMatrix[1][1] == 'A') {
                if (MASChecker(newMatrix)) {
                    supremeCounter++;
                }
            }
        }
    }

    string pattern = "XMAS";
    int totalCount = countOccurrences(matrix, pattern);

    cout << "supremeCounter: " << supremeCounter << endl;
    cout << "totalCount: " << totalCount << endl;

    return 0;
}
