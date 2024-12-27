#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <math.h>

void PartOne();
void PartTwo();

using namespace std;


int main() {
    // PartOne();
    PartTwo();
}

bool rule[100][100];

void PartOne() {
    ifstream file("input5.txt");
    string s;

    int64_t total = 0 ;
    while (getline(file, s)) {
        if (s.empty()) continue;
        if (s.length() >=3 && s[2] == '|') {
            int a = stoi(s.substr(0, 2));
            int b = stoi(s.substr(3, 2));
            rule[a][b] = true;
            continue;
        }

        stringstream ss(s);
        string num;
        vector<int> v;
        while (getline(ss, num , ',')) {
            v.emplace_back(stoi(num));
        }
        int sz = static_cast<int>(v.size());
        bool good =true;
        for (int i =0 ; i < sz ; i++) {
           for (int j = i + 1; j < sz ; j++) {
               if (rule[v[j]][v[i]]) {
                   good = false;
               }
           }
        }

        if (good) {
            total += v[sz/2];
        }
    }

    cout << total << '\n' ;
}

void PartTwo(){
    ifstream file("input5.txt");
    string s;

    map<int, int> mp;
    int64_t total = 0 ;
    while (getline(file, s)) {
        if (s.empty()) continue;
        if (s.length() >=3 && s[2] == '|') {
            int a = stoi(s.substr(0, 2));
            int b = stoi(s.substr(3, 2));
            rule[a][b] = true;
            mp[a]++;
            mp[b]++;
            continue;
        }

        stringstream ss(s);
        string num;
        vector<int> v;
        while (getline(ss, num , ',')) {
            v.emplace_back(stoi(num));
        }

        int sz = static_cast<int>(v.size());
        bool good =true;
        for (int i =0 ; i < sz ; i++) {
            for (int j = i + 1; j < sz ; j++) {
                if (rule[v[j]][v[i]]) {
                    good = false;
                }
            }
        }

        if (!good) {
            sort(v.begin(), v.end(), [](const int a , const int b) {
               if (rule[a][b]) {
                   return true ;
               }
               if (rule[b][a]) {
                   return false;
               }

                return false;
           });
            total += v[sz/2];
        }

    }
    cout << total << '\n' ;
}

