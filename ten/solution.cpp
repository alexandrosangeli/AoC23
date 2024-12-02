#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Node {

    Node* north;
    Node* south;
    Node* west;
    Node* east;

    char c;
    int row;
    int col;
    bool seen;
    int type;
    int step;
};


int main() {
    
    // Read file into a matrix and find the starting coordinates
    ifstream f("input.txt");
    string line;
    vector<vector<char>> matrix;
    int x;
    int y;
    int rows = 0;
    int cols = 0;
    while (getline(f, line)) {
        vector<char> row;
        cols = 0;
        for (char c : line) {
            row.push_back(c);
            if (c == 'S') {
                x = cols;
                y = rows;
            }
            cols++;
        }
        matrix.push_back(row);
        rows++;
    }
    f.close();

    Node* node_matrix[rows][cols];
    queue<Node*> q;

    
    // Fill with nodes
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char c = matrix[i][j];
            Node* curr = new Node{nullptr, nullptr, nullptr, nullptr, c, i, j, false, 0, 0};
            node_matrix[i][j] = curr;
        }
    }


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Node* current_node = node_matrix[i][j];
            char c = current_node-> c;
                switch (c) {
                    case '|':
                        if (i > 0) {
                            char c_ = node_matrix[i - 1][j]->c;
                            if (c_ == '|' || c_ == '7' || c_ == 'F' || c_ == 'S')
                            node_matrix[i - 1][j]->south = current_node;
                        }
                        if (i < rows - 1) {
                            char c_ = node_matrix[i + 1][j]->c;
                            if (c_ == '|' || c_ == 'L' || c_ == 'J' || c_ == 'S')
                            node_matrix[i + 1][j]->north = current_node;
                        }
                        break;

                    case '-':
                        if (j > 0) {
                            char c_ = node_matrix[i][j - 1]->c;
                            if (c_ == '-' || c_ == 'L' || c_ == 'F' || c_ == 'S')
                            node_matrix[i][j - 1]->east = current_node;
                        }
                        if (j < cols - 1) {
                            char c_ = node_matrix[i][j + 1]->c;
                            if (c_ == '-' || c_ == '7' || c_ == 'J' || c_ == 'S')
                            node_matrix[i][j + 1]->west = current_node;
                        }
                        break;

                    case 'L':
                        if (i > 0) {
                            char c_ = node_matrix[i - 1][j]->c;
                            if (c_ == '|' || c_ == '7' || c_ == 'F' || c_ == 'S')
                            node_matrix[i - 1][j]->south = current_node;
                        }
                        if (j < cols - 1) {
                            char c_ = node_matrix[i][j + 1]->c;
                            if (c_ == '-' || c_ == '7' || c_ == 'J' || c_ == 'S')
                            node_matrix[i][j + 1]->west = current_node;
                        }
                        break;

                    case 'J':
                        if (i > 0) {
                            char c_ = node_matrix[i - 1][j]->c;
                            if (c_ == '|' || c_ == '7' || c_ == 'F' || c_ == 'S')
                            node_matrix[i - 1][j]->south = current_node;
                        }
                        if (j > 0) {
                            char c_ = node_matrix[i][j - 1]->c;
                            if (c_ == '-' || c_ == 'L' || c_ == 'F' || c_ == 'S')
                            node_matrix[i][j - 1]->east = current_node;
                        }
                        break;

                    case '7':
                        if (i < rows - 1) {
                            char c_ = node_matrix[i + 1][j]->c;
                            if (c_ == '|' || c_ == 'L' || c_ == 'J' || c_ == 'S')
                            node_matrix[i + 1][j]->north = current_node;
                        }
                        if (j > 0) {
                            char c_ = node_matrix[i][j - 1]->c;
                            if (c_ == '-' || c_ == 'L' || c_ == 'F' || c_ == 'S')
                            node_matrix[i][j - 1]->east = current_node;
                        }
                        break;

                    case 'F':
                        if (i < rows - 1) {
                            char c_ = node_matrix[i + 1][j]->c;
                            if (c_ == '|' || c_ == 'L' || c_ == 'J' || c_ == 'S')
                            node_matrix[i + 1][j]->north = current_node;
                        }
                        if (j < cols - 1) {
                            char c_ = node_matrix[i][j + 1]->c;
                            if (c_ == '-' || c_ == '7' || c_ == 'J' || c_ == 'S')
                            node_matrix[i][j + 1]->west = current_node;
                        }
                        break;
                }
            }
        }
    

    // for (int i = 0; i < rows; i++) {
    //     for (int j = 0; j < cols; j++) {
    //         cout << node_matrix[i][j]->row << ',' << node_matrix[i][j]->col << ',' << node_matrix[i][j]->c << ',' << node_matrix[i][j]->type << endl;

    //         if (node_matrix[i][j]->north != nullptr)
    //         cout << node_matrix[i][j]->north->c << endl;

    //         if (node_matrix[i][j]->south != nullptr)
    //         cout << node_matrix[i][j]->south->c << endl;

    //         if (node_matrix[i][j]->east != nullptr)
    //         cout << node_matrix[i][j]->east->c << endl;

    //         if (node_matrix[i][j]->west != nullptr)
    //         cout << node_matrix[i][j]->west->c << endl;
    //     }
    // }

    Node* starting_node = node_matrix[y][x];
    q.push(starting_node);
    if (starting_node->north != nullptr) {
        starting_node->north->type = 1;
        q.push(starting_node->north);

    }

    if (starting_node->south != nullptr) {
        starting_node->south->type = 2;
        q.push(starting_node->south);

    }

    if (starting_node->east != nullptr) {
        starting_node->east->type = 3;
        q.push(starting_node->east);

    }

    if (starting_node->west != nullptr) {
        starting_node->west->type = 4;
        q.push(starting_node->west);

    }
    starting_node->seen = true;
    bool found = false;
    int total_steps;

    while (!q.empty() && !found) {
        Node* curr = q.front();
        q.pop();
        if (curr->seen) {
            continue;
        }

        if (curr->north != nullptr) {
            if (curr->north->type != 0 && curr->north->type != curr->type) {
                found = true;
                total_steps = curr->step + curr->north->step;
            }
            curr->north->type = curr->type;
            curr->north->step = curr->step + 1;
            q.push(curr->north);
        }

        if (curr->south != nullptr) {
            if (curr->south->type != 0 && curr->south->type != curr->type) {
                found = true;
                total_steps = curr->step + curr->south->step;
            }
            curr->south->type = curr->type;
            curr->south->step = curr->step + 1;
            q.push(curr->south);
        }

        if (curr->east != nullptr) {
            if (curr->east->type != 0 && curr->east->type != curr->type) {
                found = true;
                total_steps = curr->step + curr->east->step;
            }
           curr->east->type = curr->type;
           curr->east->step = curr->step + 1;
            q.push(curr->east);
        }

        if (curr->west != nullptr) {
            if (curr->west->type != 0 && curr->west->type != curr->type) {
                found = true;
                total_steps = curr->step + curr->west->step;
            }
           curr->west->type = curr->type;
           curr->west->step = curr->step + 1;
            q.push(curr->west);
        }

        curr->seen = true;
    }

    total_steps += 2;
    int total_half = (total_steps + 1) / 2;

    cout << "The answer for Day 9 Part 1 is: " << total_half << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            delete node_matrix[i][j];
        }
    }

    return 0;
}