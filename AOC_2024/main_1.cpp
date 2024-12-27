#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
void PartOne();
void PartTwo();

using namespace std;

struct Tk {
    vector<string> tokens;
    bool isOK() const {
        return !tokens.empty();
    }
};

Tk split(const string &s) {
    istringstream iss(s);
    string tok;
    Tk token;
    while (iss >> tok) {
        token.tokens.push_back(tok);
    }

    return token;
}


int main() {
    PartTwo();
}

void PartOne() {
    std::string s;
    vector<int> a, b;
    ifstream file("input.txt");
    while (getline(file  ,s )) {
        Tk line = split(s);
        if (!line.isOK()) {
            break ;
        }
        a.emplace_back(stoi(line.tokens[0])) ;
        b.emplace_back(stoi(line.tokens[1]));
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int64_t total =0 ;
    for (int i =0 ; i < a.size() ; i++) {
        total += abs(a[i] -b[i]);
    }

    cout << total << '\n' ;
}

void PartTwo() {
    std::string s;
    vector<int> a, b;
    ifstream file("input1.txt");
    if (!file) {
        cerr << "File not found" << endl;
    }
    while (getline(file  ,s )) {
        Tk line = split(s);
        if (!line.isOK()) {
            break ;
        }
        a.emplace_back(stoi(line.tokens[0])) ;
        b.emplace_back(stoi(line.tokens[1]));
    }
    map<int, int> mp;
    for (const auto &x : b) {
        mp[x]++;
    }

    int64_t total =0 ;
    for (const auto &x :a) {
        const int64_t k = static_cast<int64_t>(x) * mp[x];
        total += k ;
    }

    cout << total << '\n' ;
}