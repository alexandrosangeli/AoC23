#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int final_eval(int size, int prod)
{
    switch (size)
    {
        case 5: return 0;
        case 4: return 1;
        case 3: return (prod == 4) ? 2 : 3;
        case 2: return (prod == 6) ? 4 : 5;
        case 1: return 6;
        default: return -1;
    }
}

int eval_hand_prt1(string hand)
{
    int prod = 1;
    unordered_map<char, int> unique_chars;
    for (char c : hand) { unique_chars[c]++; }
    for (auto [k, v] : unique_chars) { prod *= v; }
    return final_eval(unique_chars.size(), prod);
}

int eval_hand_prt2(string hand)
{
    char max_v = 0;
    char num_j = 0;
    char max_k;
    int prod = 1;
    unordered_map<char, int> unique_chars;

    for (char c : hand)
    {
        if (c == 'J') { num_j++; continue; }
        unique_chars[c]++;
    }

    for (auto [k, v] : unique_chars)
    {
        if (v > max_v)
        {
            max_v = v;
            max_k = k;
        }
    }

    if (num_j == 5) { return 6; }
    unique_chars.find(max_k)->second += num_j; 
    for (auto [k, v] : unique_chars) { prod *= v; }
    return final_eval(unique_chars.size(), prod);

}

void solve(bool two, int (*fn)(string))
{
    unordered_map<char, int> card_val = 
    {
        {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5},
        {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
        {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13},
        {'A', 14}
    };

    if (two) { card_val.find('J')->second = 1; }

    unordered_map<int, vector<vector<string>>> hands;

    for (int i = 0; i < 7; i++)
    {
        vector<vector<string>> vec = {};
        hands.insert(make_pair(i, vec));
    }

    ifstream f("input.txt");
    string line;

    while (getline(f, line))
    {
        size_t space_index = line.find(' ');
        string hand = line.substr(0, space_index);
        string bid = line.substr(space_index + 1, line.size());
        vector<string> vec = {hand, bid};
        hands[fn(hand)].push_back(vec);
    }


    for (int i = 0; i < 7; i++)
    // sort each array
    {
        sort(hands[i].begin(), hands[i].end(), [&card_val](const vector<string>& a, const vector<string>& b) {
            char key_a;
            char key_b;
            int j = 0;
            for (j = 0; j < 5; j++) { if (a[0][j] != b[0][j]) {break;} }

            key_a = a[0][j];
            key_b = b[0][j];

            unordered_map<char, int>::const_iterator it_a = card_val.find(key_a);
            unordered_map<char, int>::const_iterator it_b = card_val.find(key_b);

            return it_a->second < it_b->second;
        });
    }

    int line_counter = 1;
    long result = 0;
    for (int i = 0; i < 7; i++)
    {
        for (vector<string> s : hands.at(i))
        {
            int bid = stoi(s[1]);
            result += line_counter * bid;   
            line_counter++;
        }
    }

    cout << "The answer for Day 7 Part " << (two ? "2" : "1") << " is: " << result << endl;
}


int main()
{
    solve(false, eval_hand_prt1);
    solve(true, eval_hand_prt2);
    return 0;
}