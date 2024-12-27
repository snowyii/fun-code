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
    // PartOne();
    PartTwo();
}

inline bool isNumber(const char &c ) {
    return c >= '0' && c <= '9';
}

void PartOne() {
    ifstream file("input3.txt");
    stringstream ss;
    ss << file.rdbuf();
    string s = ss.str();
    int cursor =0 ;
    int sz = static_cast<int>(s.size());
    int64_t total =0 ;
    while (cursor < s.size()) {
        if (s.substr(cursor ,4 ) == "mul(") {
            int nxt = cursor + 4 ;
            vector<string> nums ;
            string cur ;
            bool seen = false;
            while (nxt < s.size() && (isNumber(s[nxt]) || (s[nxt] == ',' && !seen))) {
                if (s[nxt] == ',') {
                    if (!cur.empty() ) nums.emplace_back(cur) ;
                    else {
                        break ;
                    }
                    cur = "";
                    seen = true;
                }else {
                    cur += s[nxt] ;
                }
                nxt++;
            }

            if (nxt < sz && s[nxt] == ')') {
                if(!cur.empty()) nums.emplace_back(cur) ;
                cursor = nxt+1;
            }else {
                cursor =nxt;
            }

            if (nums.size() == 2) {
                int cur =stoll(nums[0]) * stoll(nums[1]);
                cout << cur << '\n' ;
                total += cur;
            }
        }else {
            cursor++;
        }
    }
    cout << total << endl;
}


void PartTwo() {
    ifstream file("input3.txt");
    stringstream ss;
    ss << file.rdbuf();
    string s = ss.str();
    int cursor =0 ;
    int sz = static_cast<int>(s.size());
    int64_t total =0 ;
    bool enable = true ;
    while (cursor < s.size()) {
        if (s.substr(cursor , 4 ) == "do()") {
            enable = true ;
            cursor++;
            continue;
        }
        if (s.substr(cursor ,7 ) == "don't()") {
            enable = false;
            cursor++;
            continue;
        }
        if (s.substr(cursor ,4 ) == "mul(") {
            int nxt = cursor + 4 ;
            vector<string> nums ;
            string cur ;
            bool seen = false;
            while (nxt < s.size() && (isNumber(s[nxt]) || (s[nxt] == ',' && !seen))) {
                if (s[nxt] == ',') {
                    if (!cur.empty() ) nums.emplace_back(cur) ;
                    else {
                        break ;
                    }
                    cur = "";
                    seen = true;
                }else {
                    cur += s[nxt] ;
                }
                nxt++;
            }

            if (nxt < sz && s[nxt] == ')') {
                if(!cur.empty()) nums.emplace_back(cur) ;
                cursor = nxt+1;
            }else {
                cursor =nxt;
            }

            if (nums.size() == 2) {
                int cur =stoll(nums[0]) * stoll(nums[1]);
                cout << cur << '\n' ;
                if (enable) total += cur;
            }
        }else {
            cursor++;
        }
    }
    cout << total << endl;
}