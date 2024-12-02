#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool isSafe(const vector<int> levels) {
    bool increasing = true;
    bool decreasing = true;

    for (int i = 1; i < levels.size(); i++) {
        int diff = levels[i] - levels[i - 1];

        if (abs(diff) < 1 || abs(diff) > 3) {
            return false;
        }

        if (diff > 0) {
            decreasing = false;
        }
        if (diff < 0) {
            increasing = false;
        }
    }

    if (increasing == true || decreasing == true) {
        return true;
    }
}

int main() {
    ifstream file("input.txt");

    string line;
    int safe = 0;

    while (getline(file, line)) {
        istringstream iss(line);
        vector<int> levels;
        int level;

        while (iss >> level) {
            levels.push_back(level);
        }

        if (isSafe(levels)) {
            safe++;
        }
    }

    cout << safe;
}