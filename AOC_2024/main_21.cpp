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
int64_t moveB(int , int ,int , int);

using namespace std;

int main() {
    // PartOne();
    PartTwo();
}

map<int , vector<int>> adj = {
    {0 ,{2 ,10, - 1, - 1}},
    {1, {4 , 2, - 1, -1}},
    {2, {5 , 3 , 0, 1}},
    {3, {6 ,- 1, 10, 2}},
    {4, {7, 5 ,1, -1}},
    {5, {8, 6, 2, 4}},
    {6, {9 , - 1, 3, 5}},
    {7, {-1, 8, 4, -1}},
    {8, {-1 , 9, 5, 7}},
    {9 , {-1, -1, 6 , 8}},
    {10, {3 , -1 ,-1, 0}}
};

map<int, vector<int>> key = {
    {0 , {-1 , 4 , 2 , - 1}},
    {1, {4 , -1 ,-1 , 2}},
    {2, {0 , 1 , -1 , 3}},
    {3, {-1 , 2, -1 , -1}},
    {4 , {{-1 , -1 , 1 , 0 }}}
};


int dist[11][11];
int distKey[5][5];
int64_t totalMoveA[11][11];
int64_t totalMoveB[30][5][5][5];
vector<char> decode = {'^', '>' , 'v' , '<', 'A'};


// the number of move in C to make B move from a to b
int64_t moveC(int a, int b) {
    return distKey[a][b] + 1;
}

// == number of robot in between - 2
int END = 23;

int64_t dfsB(vector<int> &seq, int start, int cur,  int mxMove, int fin, int i) {
    if (totalMoveB[i][cur][start][fin] != -1) {
        return totalMoveB[i][cur][start][fin];
    }
    if (start == fin && i == END) {
        cout <<"DBG" <<  i << " " << decode[start] << " " << decode[cur] << " "  << decode[fin] << '\n' ;
        return 1;
    }
    if (seq.size() == mxMove) {
        for (auto j : seq) {
            cout << decode[j] << " ";
        }
        cout << '\n';
        int64_t used =0 ;
        int startC = 4;
        for (auto x : seq) {
            int64_t d=0;
            if (i == END) {
                d = moveC(startC , x) ;
            }else {
                d = moveB( startC , startC ,  x, i +1);
            }
            used += d ;
            startC = x;
        }
        int64_t roll = 0 ;
        if (i == END) {
            roll = moveC(startC, 4);
        }else {
            roll = moveB(startC , startC ,  4 , i+1);
        }
        used += roll;
        cout << "============\n" ;
        cout << i << " " << "SEQUENCE move from " << decode[start] << " to " << decode[fin] << '\n';
        cout << "USED " << used << '\n' ;
        cout << "============\n" ;
        return used;
        // totalMoveB[i][start][fin] = min(totalMoveB[i][start][fin], used);
        // return 0;
    }


    int64_t used = LLONG_MAX ;
    for (int d =0 ; d < 4 ; d++) {
        int nxt = key[cur][d];
        if (nxt != -1 && seq.size() + 1 + distKey[nxt][fin] == mxMove) {
            seq.push_back(d);
            int64_t g = dfsB(seq, start, nxt , mxMove, fin, i) ;
            used = min(used , g) ;
            seq.pop_back();
        }
    }

    return totalMoveB[i][cur][start][fin] = used;
}


int64_t moveB(int cur, int a, int b, int start) {
    vector<int> seq;
    int64_t p = 0 ;
    int64_t x =dfsB(seq, a , cur , distKey[a][b] ,b, start ) ;
    p +=x ;
    if (start == 0) {
        cout << "A" << decode[a] << " " << decode[b] << '\n' ;
        cout << "X " << x << '\n' ;
    }

    return p;
}




void dfsA(vector<int> &seq,int start, int cur ,  int mxMove, int fin) {
    if (seq.size() == mxMove) {
        int64_t used =0 ;
        int startB = 4;

        // for (auto x : seq) {
        //     cout << decode[x] << ' ' ;
        // }

        // cout << '\n';
        int last = 4;
        for (auto x : seq) {
            int64_t d = moveB(last, last , x, 0 ) ;
            last =x ;
            used += d;
            startB = x;
        }

        cout << "USED " << used << '\n' ;
        used += moveB(startB, startB, 4,0  ) ;
        totalMoveA[start][fin] = min(totalMoveA[start][fin], used);
        return ;
    }

    for (int d =0 ; d < 4 ; d++) {
        int nxt = adj[cur][d];
        if (nxt != -1 && seq.size() + 1 + dist[nxt][fin] == mxMove) {
            seq.push_back(d);
            dfsA(seq, start , nxt , mxMove , fin);
            seq.pop_back();
        }
    }
}



void moveA(int a, int b) {
	int move = dist[a][b];
    vector<int> seq;
    dfsA(seq, a, a , move,  b);
}





void PartOne() {
	for (int i =0 ; i <= 10 ; i++) {
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (auto nxt: adj[x]) {
                if (nxt != -1 && dist[i][nxt] == 0 && nxt != i ) {
                    dist[i][nxt] = dist[i][x] + 1;
                    q.push(nxt);
                }
            }
        }
	}

    for (int i = 0 ; i < 5 ; i++ ) {
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (auto nxt: key[x]) {
                if (nxt != -1 && distKey[i][nxt] == 0 && nxt != i) {
                    distKey[i][nxt] = distKey[i][x] + 1;
                    q.push(nxt);
                }
            }
        }
    }


    for (int i = 0 ; i < 11 ; i++) {
        for (int j =0 ; j < 11 ; j++) {
            totalMoveA[i][j] = LLONG_MAX;
        }
    }
    for (int d= 0 ;d < 30 ; d++) {
        for (int x =0 ; x < 5 ; x++) {
            for (int i =0 ; i < 5 ; i++) {
                for (int j =0 ; j < 5 ; j++) {
                    totalMoveB[d][x][i][j] = -1;
                }
            }
        }
    }

    // 10 -> 0: 18
    // 0 - > 2 :12
    // 2 -> 9 : 20

    ifstream file("input21.txt");
    string line;
    vector<int64_t> mul;
    vector<array<int, 5>> list;
    while (getline(file,line)) {
        mul.push_back(stoi(line.substr(0 , 3)));
        array<int , 5> arr;
        arr[0] = 10;
        int i = 1;
        for (auto x : line) {
            int d= 0 ;
            if (x == 'A') {
                d = 10;
            }else {
                d = x-'0';
            }
            arr[i] = d;
            i++;
        }

        list.push_back(arr);
    }


    // int a[] = {10 , 9 , 8, 0, 10};
    // int a[] = {9 , 10 };

    int64_t total =0 ;
    int k =0 ;
    for (auto x : list) {
        int64_t move = 0 ;
        for (int t =0 ; t <  x.size() - 1 ; t++) {
            moveA(x[t] , x[t+1]);
            move += totalMoveA[x[t]][x[t+1]];
        }

        cout << "MOVE " << move << '\n';
        total += mul[k] * move;
        k++;
    }


    cout << total << '\n' ;
    // int move =0 ;
    // for (int g =0 ;g <= 3; g++) {
    //     moveA(a[g], a[g+1]);
    //     move += totalMoveA[a[g]][a[g+1]];
    // }
    //
    // cout <<move << '\n';

    // <vA>^A<v<A>^A>AAvA^A
    // <v<A>A>^AAAvA<^A>A
}

void PartTwo() {
    	for (int i =0 ; i <= 10 ; i++) {
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (auto nxt: adj[x]) {
                if (nxt != -1 && dist[i][nxt] == 0 && nxt != i ) {
                    dist[i][nxt] = dist[i][x] + 1;
                    q.push(nxt);
                }
            }
        }
	}

    for (int i = 0 ; i < 5 ; i++ ) {
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (auto nxt: key[x]) {
                if (nxt != -1 && distKey[i][nxt] == 0 && nxt != i) {
                    distKey[i][nxt] = distKey[i][x] + 1;
                    q.push(nxt);
                }
            }
        }
    }


    for (int i = 0 ; i < 11 ; i++) {
        for (int j =0 ; j < 11 ; j++) {
            totalMoveA[i][j] = LLONG_MAX;
        }
    }
    for (int d= 0 ;d < 30 ; d++) {
        for (int x =0 ; x < 5 ; x++) {
            for (int i =0 ; i < 5 ; i++) {
                for (int j =0 ; j < 5 ; j++) {
                    totalMoveB[d][x][i][j] = -1;
                }
            }
        }
    }

    // 10 -> 0: 18
    // 0 - > 2 :12
    // 2 -> 9 : 20

    ifstream file("input21.txt");
    string line;
    vector<int64_t> mul;
    vector<array<int, 5>> list;
    while (getline(file,line)) {
        mul.push_back(stoi(line.substr(0 , 3)));
        array<int , 5> arr;
        arr[0] = 10;
        int i = 1;
        for (auto x : line) {
            int d= 0 ;
            if (x == 'A') {
                d = 10;
            }else {
                d = x-'0';
            }
            arr[i] = d;
            i++;
        }

        list.push_back(arr);
    }


    // int a[] = {10 , 9 , 8, 0, 10};
    // int a[] = {10 , 2 , 0, 8 , 10};

    int64_t total =0 ;
    int k =0 ;
    for (auto x : list) {
        int64_t move = 0 ;
        for (int t =0 ; t <  x.size() - 1 ; t++) {
            moveA(x[t] , x[t+1]);
            move += totalMoveA[x[t]][x[t+1]];
        }

        cout << "MOVE " << move << '\n';
        total += mul[k] * move;
        k++;
    }

    cout << total << '\n' ;
}

