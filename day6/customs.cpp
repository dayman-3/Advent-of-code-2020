#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

int any(vector<string> list) {
    bool answers[26] {false};
    int count = 0;
    for (auto s = list.begin(); s != list.end(); ++s) {
        int n = (*s).length();
        for (auto c = (*s).begin(); c != (*s).end(); ++c) {
            int index = *c - 97;
            if (!answers[index]) {
                answers[index] = true;
                count++;
            }
        }
    }

    return count;
}

int every(vector<string> list) {
    unordered_set<char> answers (0);
    for (int i = 0; i < list.size(); i++) {

        // First string
        if (i == 0) {
            for (int c = 0; c < list[i].length(); c++) {
                answers.insert(list[i][c]);
            }
        }

        // Every other string
        unordered_set<char> copy (answers);
        for (const auto entry : copy) { 
            if (list[i].find(entry) == string::npos) {
                answers.erase(entry);
            }
        }

    }
    return answers.size();
}

int main() {
    ifstream in_file ("input.txt");
    if (!in_file.is_open()) {
        cout << "bad\n";
        exit(1);
    }

    string line;
    vector<string> group;
    int sum_1;
    int sum_2;
    while (getline(in_file, line)) {
        if (line.empty()) {
            sum_1 += any(group);
            sum_2 += every(group);
            group.clear();
            continue;
        }
        group.push_back(line);
    }
    sum_1 += any(group);
    sum_2 += every(group);

    cout << "Part 1: " << sum_1 << endl;
    cout << "Part 2: " << sum_2 << endl;
}