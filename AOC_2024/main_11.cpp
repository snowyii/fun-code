#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <array>
#include <queue>


void PartOne();
void PartTwo();

using namespace std;

int main() {
    // PartOne();
    PartTwo();
}

int MX = 25;
map<pair<string ,int>, long long> mp;

long long cur(string &s, int i) {
    if (i == MX) return 1;
    string x;
    bool flag = false;
    for (auto &c : s) {
        if (c != '0') flag = true;
        if (flag) x += c;
    }

    if ( x ==  "") {
        string ns = "1";
        return mp[{s , i}] = cur(ns, i + 1);
    }

    auto it = mp.find({x , i});
    if (it!= mp.end()) {
        return it->second;
    }
    int sz = static_cast<int>(x.length());
    if (sz % 2 == 0) {

        string S1 = x.substr(0 , sz/2);
        string S2 = x.substr(sz/2, sz);
        return mp[{x, i}] = cur(S1, i + 1)  + cur(S2, i + 1);
    }

    long long nxt = stoll(x) * 2024;
    string nxtS = to_string(nxt) ;
    return mp[{s , i}] = cur(nxtS , i + 1);
}

void PartOne() {
    ifstream file("input11.txt");
    string s;
    getline(file ,s );
    stringstream ss(s);
    vector<string> input;
    string x;
    while (ss >> x) {
        input.emplace_back(x);
    }
    long long ans =0 ;
    for (auto &x : input) {
        ans += cur(x, 0);
    }
    cout << ans << '\n';
}

void PartTwo() {
    MX = 75;
    ifstream file("input11.txt");
    string s;
    getline(file ,s );
    stringstream ss(s);
    vector<string> input;
    string x;
    while (ss >> x) {
        input.emplace_back(x);
    }
    long long ans =0 ;
    for (auto &x : input) {
        ans += cur(x, 0);
    }
    cout << ans << '\n';
}
