#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int sum2(vector<int> report, int sum) {
    unordered_map<int, int> table;
    for (auto it = report.begin(); it != report.end(); ++it) {
        table[sum - *it] = *it;
    }
    for (auto it = report.begin(); it != report.end(); ++it) {
        if (table.find(*it) != table.end()) {
            return (*it * table[*it]);
        }
    }
    return 0;
}

int sum3(vector<int> report) {
    for (auto it = report.begin(); it != report.end(); ++it) {
        int remainder = 2020 - *it;
        int prod = sum2(report, remainder);
        if (prod != -1) {
            return *it * prod;
        }
    }
    return 0;
}

int main() {
    fstream in_file ("input.txt");
    if (!in_file.is_open()) {
        cout << "Bad file\n";
        exit(1);
    }
    
    vector<int> expenseReport (0);
    int entry;
    while (in_file >> entry) {
        expenseReport.push_back(entry);
    }

    cout << sum3(expenseReport) << endl;
}   