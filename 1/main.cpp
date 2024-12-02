#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

ifstream file("input.txt");

int main() {
    vector<int> array1;
    vector<int> array2;
    vector<int> resultArray;
    int i = 0;
    int word;
    int result = 0;

    while (file >> word) {  // create two vectors from two columns
        if (i == 0) {
            array1.push_back(word);
        } else if (i % 2 == 0) {
            array1.push_back(word);
        } else if (i % 2 != 0) {
            array2.push_back(word);
        }
        i++;
    }

    sort(array1.begin(), array1.end());  //  increasing sorting in vectors
    sort(array2.begin(), array2.end());

    // for (int i = 0; i < array1.size(); i++) {
    //     cout << array1[i] << endl;
    // }

    // cout << "---------------------------------------------" << endl;

    // for (int i = 0; i < array2.size(); i++) {
    //     cout << array2[i] << endl;
    // }

    for (int i = 0; i < array1.size(); i++) {
        int partialResult = 0;

        partialResult = (array1[i] - array2[i]);
        if (partialResult < 0) {
            partialResult = partialResult * -1;
        }
        resultArray.push_back(partialResult);
    }

    // for (int i = 0; i < resultArray.size(); i++) {
    //     cout << resultArray[i] << endl;
    // }

    result = accumulate(resultArray.begin(), resultArray.end(), 0);
    cout << "result: " << result << endl;

    int score = 0;

    for (int i = 0; i < array1.size(); i++) {
        int occurrence = 0;
        for (int j = 0; j < array2.size(); j++) {
            if (array1[i] == array2[j]) {
                occurrence++;
            }
        }
        score = score + (array1[i] * occurrence);
    }

    cout << "score: " << score << endl;
}