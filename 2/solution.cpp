#include <algorithm>
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
    return increasing || decreasing;
}

int main() {
    ifstream file("input.txt");

    string line;
    int safe = 0;
    int newSafe = 0;

    while (getline(file, line)) {
        // build report of levels
        istringstream iss(line);
        vector<int> levels;
        int level;

        while (iss >> level) {
            levels.push_back(level);
        }

        // check if report is safe
        if (isSafe(levels)) {
            safe++;
        }

        // check if report is safe even removing any level
        vector<int> array;
        array.resize(levels.size());

        for (int i = 0; i < levels.size(); i++) {
            array[i] = levels[i];
        }

        if (isSafe(array)) {
            newSafe++;
        } else {
            for (int i = 0; i < array.size(); i++) {
                int temp = array[i];
                array.erase(array.begin() + i);

                if (isSafe(array)) {
                    newSafe++;
                    break;
                }

                array.insert(array.begin() + i, temp);
            }
        }
    }

    cout << safe << endl;
    cout << newSafe << endl;
}