#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

pair<int, int> part1(vector<string> instructions) {
    int stepCount = instructions.size();

    int acc = 0;

    bool *visited = new bool [stepCount] {false};
    bool stop = false;
    int index = 0;
    while (index < stepCount) {
        if (visited[index]) break;

        string step = instructions[index];
        string type = step.substr(0, 3);
        int direction = (step[4] == '+' ? 1 : -1);
        int n = stoi(step.substr(5)) * direction;

        visited[index] = true;
        
        if (type == "jmp") {
            index += n;
            continue;
        }

        if (type == "nop") {
            index += 1;
            continue;
        }

        if (type == "acc") {
            acc += n;
            index += 1;
            continue;
        }
    }
    delete[] visited;

    return make_pair(acc, index);
}

int part2(vector<string> instructions) {
    for (int i = 0; i < instructions.size(); i++) {
        string type = instructions[i].substr(0, 3);
        string swap = "acc";
        if (type == "jmp") swap = "nop";
        else if (type == "nop") swap = "jmp";
        instructions[i].replace(0, 3, swap);

        pair<int, int> result = part1(instructions);
        if (result.second >= instructions.size()) return result.first;
        instructions[i].replace(0, 3, type);
    }
}

int main() {
    ifstream in_file("input.txt");

    vector<string> instructions;
    string line;
    while (getline(in_file, line)) {
        instructions.push_back(line);
    }
    

    cout << "Part 1: " << part1(instructions).first  << endl;
    cout << "Part 2: " << part2(instructions) << endl;
}