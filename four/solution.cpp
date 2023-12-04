#include <iostream>
#include <fstream> 
#include <vector>
#include <cmath>

using namespace std;

void part_one()
{
    
}

int main()
{
    ifstream f("input.txt");
    string line;

    int sum = 0;
    int num_of_lines = 201;
    int lines[num_of_lines];

    for (int i = 0; i < num_of_lines; i++) { lines[i] = 1; }

    int current_line = 0;
    while (getline(f, line))
    {
        size_t column_i = line.find(":");
        size_t bar_i = line.find("|");
        size_t len = line.size();
        size_t first_digit = line.find_first_of("123456789", column_i);
        size_t bar_left = bar_i - first_digit;
        size_t bar_right = len - bar_i - 2;
        string winning_nums_str = line.substr(first_digit, bar_left);
        string having_nums_str = line.substr(bar_i + 2, bar_right);

        vector<int> winning_nums;
        vector<int> having_nums;

        size_t i;

        while (winning_nums_str.size() > 0)
        {
            i = winning_nums_str.find(" ");

            if (i == 0) // landed on a space
            {
                winning_nums_str = winning_nums_str.substr(1, winning_nums_str.size() - 1); // consume one char
                continue;
            }

            string num;
            if (i == string::npos)
            {
                num = winning_nums_str;
                winning_nums_str = "";
            } else {
                num = winning_nums_str.substr(0, i);
                winning_nums_str = winning_nums_str.substr(i + 1, winning_nums_str.size() - 1);
            }

            winning_nums.push_back(stoi(num));
        }

        while (having_nums_str.size() > 0)
        {
            i = having_nums_str.find(" ");

            if (i == 0) // landed on a space
            {
                having_nums_str = having_nums_str.substr(1, having_nums_str.size() - 1); // consume one char
                continue;
            }

            string num;
            if (i == string::npos)
            {
                num = having_nums_str;
                having_nums_str = "";
            } else {
                num = having_nums_str.substr(0, i);
                having_nums_str = having_nums_str.substr(i + 1, having_nums_str.size() - 1);
            }

            having_nums.push_back(stoi(num));
        }

        int exponent = 0;
        for (int i = 0; i < having_nums.size(); i++)
        {
            for (int j = 0; j < winning_nums.size(); j++)
            {   
                if (having_nums[i] == winning_nums[j]) { exponent++; }
            }
        }

        sum += (exponent > 0) ? pow(2, (exponent - 1)) : 0;

        for (int i = 0; i < exponent; i++) { lines[current_line + i + 1] += lines[current_line]; }

        current_line++;
    }

    int total_scratchcards = 0;
    for (int n : lines) { total_scratchcards += n; }

    cout << "The answer for Day 4 Part 1 is: " << sum << endl;
    cout << "The answer for Day 4 Part 2 is: " << total_scratchcards << endl;
}