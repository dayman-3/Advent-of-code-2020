#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <sstream>

using namespace std;

bool validate1(char *password, int min, int max, char c) {
    int n = strlen(password);
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (password[i] == c) count++;
    }
    return (count >= min && count <= max);
}

bool validate2(char *password, int pos1, int pos2, char c) {
    return ((password[pos1-1] == c) != (password[pos2-1] == c)); // xor
}

int main() {
    fstream in_file ("input.txt");
    if (!in_file.is_open()) {
        cout << "fuck\n";
        exit(1);
    }

    int validCount = 0;

    while (in_file.good()) {
        char line [1000];
        in_file.getline(line, 512);
        int n1, n2;
        char c;
        char password [512];
        sscanf(line, "%d-%d %c: %s", &n1, &n2, &c, password);
        if (validate2(password, n1, n2, c)) validCount++;
    }

    cout << validCount << endl;
}