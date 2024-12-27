#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include<algorithm>
#include<numeric>
#include <set>
#include <array>
#include <queue>
#include <unistd.h>


void PartOne();
void PartTwo();

using namespace std;

int main() {
    // PartOne();
    PartTwo();
}

map<string, int64_t> mp;
vector<string> pattern;
int64_t doAble(string &s) {
    cout << s << '\n' ;
    if (s.size() == 0) return true;

    if (auto it = mp.find(s); it  != mp.end()) {
        return it->second;
    }

    int64_t total =0 ;
    for (auto &x : pattern) {
        if (x.size() <= s.size()) {
            bool good = true;
            for (int d =0 ; d < x.size() ; d++) {
                if (x[d] != s[d]) good = false;
            }

            if (good) {
                string newStr = s.substr(x.size());
                total += doAble(newStr);
            }
        }
    }

    return mp[s] = total;
}

void PartOne() {
    ifstream file("input19.txt");
    string line;
    vector<string> words;
    getline(file, line);
    stringstream ss(line);

    while (ss >> line) {
        pattern.push_back(line.substr(0,line.find(',')));
    }

    while (getline(file, line)) {
        if (!line.empty()) {
            words.push_back(line);
        }
    }

    int cnt =0 ;
    for (auto &q : words) {
        bool t = doAble(q);
        if (t) ++cnt;
    }

    cout << cnt << '\n';
}

void PartTwo() {
    ifstream file("input19.txt");
    string line;
    vector<string> words;
    getline(file, line);
    stringstream ss(line);

    while (ss >> line) {
        pattern.push_back(line.substr(0,line.find(',')));
    }

    while (getline(file, line)) {
        if (!line.empty()) {
            words.push_back(line);
        }
    }

    int64_t cnt =0 ;
    for (auto &q : words) {
        int64_t t = doAble(q);
        cnt+= t;
    }

    cout << cnt << '\n';
}

