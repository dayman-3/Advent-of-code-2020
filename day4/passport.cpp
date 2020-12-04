#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

enum FIELD {
    byr,
    iyr,
    eyr,
    hgt,
    hcl,
    ecl,
    pid,
    cid
};

struct passport {
    map<string, string> fuckd {
        {"byr", "n/a"},
        {"iyr", "n/a"},
        {"eyr", "n/a"},
        {"hgt", "n/a"},
        {"hcl", "n/a"},
        {"ecl", "n/a"},
        {"pid", "n/a"},
        {"cid", "n/a"},
    };

    passport() {
        for (auto it = fuckd.begin(); it != fuckd.end(); ++it) {
            (*it).second = "n/a";
        }
    }

    void addField(string info) {
        string field = info.substr(0, 3);
        string value = info.substr(4, 15);

        fuckd[field] = value;
    }

    bool valid() {
        bool complete = (
            fuckd["byr"] != "n/a" &&
            fuckd["iyr"] != "n/a" &&
            fuckd["eyr"] != "n/a" &&
            fuckd["hgt"] != "n/a" &&
            fuckd["hcl"] != "n/a" &&
            fuckd["ecl"] != "n/a" &&
            fuckd["pid"] != "n/a" 
        );
        if (!complete) return false;

        if (fuckd["byr"] != "n/a") {
            smatch sm;
            bool match = regex_match(fuckd["byr"], sm, regex("^\\d{4}$"));
            if (!match) return false;
            int year = stoi(fuckd["byr"]);
            if (year < 1920 || year > 2002) return false;
        }

        if (fuckd["iyr"] != "n/a") {
            smatch sm;
            bool match = regex_match(fuckd["iyr"], sm, regex("^\\d{4}$"));
            if (!match) return false;
            int year = stoi(fuckd["iyr"]);
            if (year < 2010 || year > 2020) return false;
        }
        
        if (fuckd["eyr"] != "n/a") {
            smatch sm;
            bool match = regex_match(fuckd["eyr"], sm, regex("^\\d{4}$"));
            if (!match) return false;
            int year = stoi(fuckd["eyr"]);
            if (year < 2020 || year > 2030) return false;
        }

        if (fuckd["hgt"] != "n/a") {
            smatch sm;
            bool match = regex_match(fuckd["hgt"], sm, regex("^(\\d+)(cm|in)$"));
            if (!match) return false;
            int height = stoi(sm[1]);
            if (sm[2] == "cm") {
                if (height < 150 || height > 193) return false;
            } else {
                if (height < 59 || height > 76) return false;
            }
        }

        if (fuckd["hcl"] != "n/a") {
            smatch sm;
            bool match = regex_match(fuckd["hcl"], sm, regex("^#[0-9|a-f]{6}$"));
            if (!match) return false;
        }

        if (fuckd["ecl"] != "n/a") {
            smatch sm;
            bool match = regex_match(fuckd["ecl"], sm, regex("^(amb)|(blu)|(brn)|(gry)|(grn)|(hzl)|(oth)$"));
            if (!match) return false;
        }

        if (fuckd["pid"] != "n/a") {
            smatch sm;
            bool match = regex_match(fuckd["pid"], sm, regex("^[0-9]{9}$"));
            if (!match) return false;
        }

        return true;
    }

    void print() {
        cout << "--------\n";
        for (auto it = fuckd.begin(); it != fuckd.end(); ++it) {
            cout << (*it).first << ": " << (*it).second << "\n";
        }
        cout << "--------\n" << (valid() ? "valid" : "invalid") << "\n";
    }
};

int validPassports(vector<passport> list) {
    int count = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        // (*it).print();
        if ((*it).valid()) count++;
    }
    return count;
}

int main() {
    ifstream in_file("input.txt");
    if (!in_file.is_open()) {
        cout << "fuck\n";
        exit(1);
    }

    vector<passport> passports;
    string line;
    passport *current = new passport();
    while (getline(in_file, line)) {
        if (line.empty()) {
            passports.push_back(*current);
            delete current;
            current = new passport();
            continue;
        }
        regex r {"\\s"};
        sregex_token_iterator start {line.begin(), line.end(), r, -1}, end;
        vector<string> lineFields (start, end);
        for (auto it = lineFields.begin(); it != lineFields.end(); ++it) {
            current->addField(*it);
        }
    }
    passports.push_back(*current);
    delete current;

    cout << validPassports(passports) << endl;
}