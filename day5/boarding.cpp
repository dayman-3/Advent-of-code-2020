#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int seatID(string pass) {
    int row = 0;
    int col = 0;

    for (int i = 0; i < 7; i++) {
        row += (pass[i] == 'B' ? (64 >> i) : 0);
    }

    for (int i = 0; i < 3; i++) {
        col += (pass[i+7] == 'R' ? (4 >> i) : 0);
    }

    return (row * 8) + col;
}

int main() {
    ifstream in_file("input.txt");
    string line;

    int highestID = 0;
    vector<bool> occupied (128, false);
    int mine = 0;
    while (in_file >> line) {
        int id = seatID(line);
        if (id > highestID) highestID = id;
        occupied[id] = true;
    }
    for (int i = 9; i < 1016; i++) {
        if (!occupied[i] && occupied[i-1] && occupied[i+1]) {
            mine = i;
            break;
        }
    }

    cout << "Part 1: " << highestID << endl;
    cout << "Part 2: " << mine << endl;
}