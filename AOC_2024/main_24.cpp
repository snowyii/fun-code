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

void PartOne();
void PartTwo();
void printGraph();

using namespace std;

int main() {
    // PartOne();
    PartTwo();
}


map<int ,array<int, 3>> dep;
map<int , int> res;
vector<string> decode;

map<string ,int> commandMap = {
    {"XOR", 1 }, {"OR", 2} , {"AND",3}
};
map<int, string> decodeCmd = {
    {1 , "XOR" }, { 2, "OR"} , {3, "AND"}
};
int dfs(const int &s) {
    if (auto it = res.find(s); it != res.end()) {
        return it->second;
    }

    auto [ a, cmd , b] = dep[s];
    bool result;
    if (cmd == 1 ) {
        result = dfs(a) ^ dfs(b);
    }else if (cmd == 2) {
        result = dfs(a) | dfs(b);
    }else if (cmd == 3){
        result = dfs(a) & dfs(b);
    }

    return res[s] = result;
}

map<string, int> regis;
int number = 0;

int getNumber(string s) {
    int num;
    if (auto it = regis.find(s); it == regis.end()) {
        decode.push_back(s);
        num = regis[s] = number++;
    }else {
        num = it->second;
    }
    return num;
}

void PartOne() {
    ifstream file("input24.txt");
    string line;
    bool split = false;

    while (getline(file, line)) {
        if (line.length() == 0) {
            split = true ;
            continue ;
        }

        if (!split) {
            string s = line.substr(0, 3);
            res[getNumber(s)] = stoi(line.substr(5, 1)) ;
        }else {
            stringstream ss(line);
            vector<string> tokens;
            string tk;
            while (ss >> tk) {
                tokens.push_back(tk);
            }

            int A = getNumber(tokens[0]);
            int B = getNumber(tokens[2]);
            int C = getNumber(tokens[4]);

            dep[C] = {A , commandMap[tokens[1]] , B};
        }

    }

    int64_t total = 0 , bit = 1;
    for (const auto &[s , x] : regis) {
        int d = dfs(x);
        if (s[0] == 'z') {
            cout << x << " " << d << '\n' ;
            if ( d== 1) total += bit;
            bit <<= 1;
        }
    }

    cout << total << '\n' ;
    cout << regis.size() << '\n' ;
}

void PartTwo() {
    ifstream file("input24.txt");
    string line;
    bool split = false;

    while (getline(file, line)) {
        if (line.length() == 0) {
            split = true ;
            continue ;
        }

        if (!split) {
            string s = line.substr(0, 3);
            res[getNumber(s)] = stoi(line.substr(5, 1)) ;
        }else {
            stringstream ss(line);
            vector<string> tokens;
            string tk;
            while (ss >> tk) {
                tokens.push_back(tk);
            }

            int A = getNumber(tokens[0]);
            int B = getNumber(tokens[2]);
            int C = getNumber(tokens[4]);

            dep[C] = {A , commandMap[tokens[1]] , B};
        }
    }

    swap(dep[getNumber("frn")], dep[getNumber("z05")]);
    swap(dep[getNumber("vtj")], dep[getNumber("wnf")]);
    swap(dep[getNumber("gmq")], dep[getNumber("z21")]);
    swap(dep[getNumber("z39")], dep[getNumber("wtt")]);


    for (auto [x, _] : dep) {
        dfs(x);
    }

    int64_t resZ =0, resX = 0 ,resY =0 ;
    int64_t dx =1 , dy = 1, dz = 1;
    for (auto [ x, num] : regis) {
        const int v = res[num];
        if (x[0] == 'z') {
            if (v == 1) resZ += dz;
            dz<<= 1;
        }else if ( x[0] == 'x') {
            if (v == 1) resX += dx;
            dx <<= 1;
        }else if ( x[0] == 'y') {
            if (v == 1) resY += dy;
            dy <<= 1;
        }
    }

    cout << bitset<64>(resX) << '\n' ;
    cout << bitset<64>(resY) << '\n' ;
    int64_t resT = resX + resY;
    cout << bitset<64>(resT) << '\n' ;
    cout  << bitset<64>(resZ) << '\n' ;

    vector<string> s = {"frn", "z05","vtj","wnf","gmq","z21","z39","wtt"};
    sort(s.begin(), s.end());
    for (int i =0 ; i < static_cast<int>(s.size()); i++) {
        if (i > 0 ) cout << ",";
        cout << s[i];
    }
    cout << '\n' ;


    // dot -Tpng test1.dot -o out.png
    // printGraph();
}

void printGraph() {
    cout << "graph g {" << '\n';
    cout << "splines=ortho;" << '\n' ;
    cout << "nodesep=0.005" << '\n';
    cout << "rankdir=\"LR\";" << '\n';
    cout << "node [shape=box width=.5];" << '\n';
    for (auto [x, t]  : regis) {
        cout << x ;
        if (t < 90) cout <<  " [shape=none]";
        cout << ";\n";
    }

    for (const auto &[c ,v ] : dep) {
        cout << decode[c] << " [label=\"" << decodeCmd[v[1]] << "_" << decode[c] << "\"];" << '\n';
    }

    for (const auto &[c ,v ] : dep) {
        auto [ a ,  cmd , b] = v;

        cout << decode[a] << " -- " << decode[c]  << ";\n" ;
        cout << decode[b] << " -- " << decode[c]  << ";\n" ;
    }


    cout << "}\n";
}


