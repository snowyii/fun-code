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
#include <signal.h>
#include <unistd.h>


void PartOne();
void PartTwo();

using namespace std;


int main() {
    // PartOne();
    PartTwo();
}

void PartOne() {
    ifstream file("input23.txt");
    string line;

    set<string> st;
    map<pair<string ,string>, bool> mp;
    while (getline(file, line)) {
        string a = line.substr(0, 2);
        string b = line.substr(3, 2);
        mp[{a,b}] = true;
        mp[{b,a}] = true;

        st.insert(a);
        st.insert(b);
    }

    vector<string> nodes;
    nodes.reserve(st.size());
    cout << st.size() << '\n';
    for (auto &x : st) {
        nodes.push_back(x);
    }

    cout << nodes.size() << '\n';
    set<array<string , 3>> removeDup;
    int f =0 ;
    for (auto &x : nodes) {
        for (auto &y : nodes) {
            if (!mp[{x,y}]) continue;
            for (auto &z : nodes) {
                f++;
                cout << f << '\n';
                if (x != y && y != z && z != x) {
                    if (x[0] =='t' || y[0] == 't' || z[0] == 't') {
                        if (mp[{x,y}] && mp[{y,z}] && mp[{z,x}]) {
                            array<string ,3> arr = {x , y , z};
                            sort(arr.begin(), arr.end());
                            removeDup.insert(arr);
                        }
                    }
                }
            }
        }
    }
    cout << removeDup.size() << '\n';
}

int SZ;
bool mat[600][600] ;
vector<string> decode;
int cliqueSZ;

set<vector<int>>pass;
set<string> ans;
void dfs(vector<int> &v, int i, vector<vector<int>> &adj) {
    vector<int> g = v;
    sort(g.begin(), g.end());
    pass.insert(g);
    if ( i == cliqueSZ) {

        vector<string> name;
        for (int t =0 ; t < i ; t++) {
            name.push_back(decode[v[t]]);
        }

        sort(name.begin(), name.end());
        string ANS;
        for (int t =0 ; t < name.size() ; t++) {
            ANS += (t > 0 ? "," : "" ) + name[t];
        }

        ans.insert(ANS);
        // cout << ANS << '\n' ;
        return ;
    }

    if ( i == 0 ) {
        for (int d =0 ;d < SZ ; d++) {
            v.push_back(d);
            dfs(v , i +1, adj);
            v.pop_back();
        }
    }else {
        int last = v[i-1];
        for (int nxt : adj[last]) {
            bool good = true;
            for (int d =0 ; d < i -1  ; d++) {
                if (!mat[v[d]][nxt]) {
                    good = false;
                    break ;
                }
            }


            if (good) {
                v.push_back(nxt);
                g = v;
                sort(g.begin(), g.end());
                if (!pass.contains(g)) {
                    dfs(v , i + 1, adj) ;
                }
                v.pop_back();
            }
        }
    }
}

void PartTwo() {
    ifstream file("input23.txt");
    string line;

    map<string, int> st;
    vector<pair<int, int>> edges;
    int number = 0;
    while (getline(file, line)) {
        string a = line.substr(0, 2);
        string b = line.substr(3, 2);

        int A, B;
        if (auto it = st.find(a); it != st.end()) {
            A = it->second;
        }else {
            decode.push_back(a);
            A = st[a] = number++;
        }

        if (auto it = st.find(b); it != st.end()) {
            B = it->second;
        }else {
            decode.push_back(b);
            B = st[b] = number++;
        }

        edges.push_back({A, B});
    }

    SZ = st.size();
    vector<vector<int>> adj(SZ);

    for (auto [ a , b] : edges) {
        adj[a].push_back(b);
        adj[b].push_back(a);

        mat[a][b] = true;
        mat[b][a] = true;
    }

    vector<int> cur;

    for (int i = 13; i <= 13; i++) {
        cliqueSZ = i;
        cout << "Clique Size: " << cliqueSZ << '\n';
        dfs(cur, 0, adj) ;
        cout << ans.size() << '\n';
    }

    for (auto &x : ans) {
        cout << x << '\n' ;
    }

}

