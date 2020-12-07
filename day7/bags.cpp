#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct bag {
    string name;
    unordered_map<string, int> inner;
    unordered_set<string> outer;

    bag() {}
    bag(string name) {
        this->name = name;
    }

    bool empty() {
        return inner.empty();
    }

    bool max() {
        return outer.empty();
    }
};

int part1(unordered_map<string, bag>& table, bag& current) {
    static unordered_set<string> visited;
    int count = 0;
    for (auto container : current.outer) {
        if (visited.find(container) == visited.end()) {
            visited.insert(container);
            bag next = table[container];
            count += 1;
            count += part1(table, next);
        }
    }
    return count;
}

int part2(unordered_map<string, bag> table, bag& current) {
    if (current.inner.empty()) return 0;
    int count = 0;
    for (auto inside : current.inner) {
        bag next = table[inside.first];
        count += inside.second;
        count += inside.second * part2(table, next);
    }
    return count;
}

int main() {
    ifstream in_file ("input.txt");
    if (!in_file.is_open()) {
        cout << "fuck\n";
        exit(1);
    }

    vector<string> lines;
    string line;
    while (getline(in_file, line)) {
        lines.push_back(line);
    }

    unordered_map<string, bag> bags;

    for (string info : lines) {
        smatch name;
        regex_match(info, name, regex("^(\\w+ \\w+).+$"));
        string contains = info.substr(name[1].length()+14);

        bag newBag(name[1]);
        if (contains == "no other bags.") {
            bags.insert(make_pair(name[1], newBag));
            continue;
        }
        regex delim {", "};
        sregex_token_iterator start {contains.begin(), contains.end(), delim, -1}, end;
        vector<string> connections(start, end);
        for (string type : connections) {
            smatch sm;
            regex_match(type, sm, regex("^(\\d+) (\\w+ \\w+).*$"));
            newBag.inner.insert(make_pair(sm[2], stoi(sm[1])));
        }

        auto insert = bags.insert(make_pair(name[1], newBag));
    }

    for (auto data : bags) {
        bag current = data.second;
        for (auto inside : current.inner) {
            bags[inside.first].outer.insert(current.name);
        }
    }

    string start = "shiny gold";

    cout << "Part 1: " << part1(bags, bags[start]) << endl;
    cout << "Part 2: " << part2(bags, bags[start]) << endl;
}