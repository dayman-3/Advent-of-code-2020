#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int treeCount(vector<string> slope, int distance, int width, int right, int down) {
    int count = 0;
    int pos = 0;
    for (int i = 0; i < slope.size(); i += down) {
        if (slope[i][pos] == '#') {
            count++;
        }
        pos = (pos + right) % width;
    }
    return count;
}

int main() {
    ifstream in_file ("input.txt");
    if (!in_file.is_open()) {
        cout << "fuck\n";
        exit(1);
    }

    vector<string> path;
    string line;
    int dist = 0;
    while (in_file >> line) {
        path.push_back(line);
        dist++;
    }
    
    cout << "Part 1: ";
    cout << treeCount(path, dist, line.length(), 3, 1) << endl;

    cout << "Part 2: ";
    cout << (
        treeCount(path, dist, line.length(), 1, 1) *
        treeCount(path, dist, line.length(), 3, 1) *
        treeCount(path, dist, line.length(), 5, 1) *
        treeCount(path, dist, line.length(), 7, 1) *
        treeCount(path, dist, line.length(), 1, 2)
    ) << endl;
}