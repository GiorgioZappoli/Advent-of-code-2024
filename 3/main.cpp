#include <exception>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

using namespace std;

int main() {
    ifstream file("input.txt");

    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    regex pattern1(R"((mul\((\d+),(\d+)\))|(do\(\))|(don't\(\)))");

    smatch match;
    sregex_iterator begin(content.begin(), content.end(), pattern1);
    sregex_iterator end;

    int total = 0;
    bool enabled = true;

    for (sregex_iterator i = begin; i != end; i++) {
        smatch match = *i;

        if (match[1].matched && enabled) {
            try {
                int x = stoi(match[2].str());
                int y = stoi(match[3].str());

                total += x * y;

            } catch (const std::invalid_argument& e) {
                cerr << "invalid argument error.\n";
            } catch (const std::out_of_range& e) {
                cerr << "out of range errors.\n";
            }
        }

        else if (match.str() == "do()") {
            enabled = true;
        }

        else if (match.str() == "don't()") {
            enabled = false;
        }
    }

    cout << total << endl;
}
