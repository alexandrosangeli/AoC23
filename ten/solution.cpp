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
    Node* prev;

    char c;
    int row;
    int col;
    bool seen;
    int type;
    int step;
    bool pipe;
};


int main() {

    /*
    
        Apologies in advance to anyone who will try to read the code below :)
    
    */
    
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
            Node* curr = new Node{nullptr, nullptr, nullptr, nullptr, nullptr, c, i, j, false, 0, 0, false};
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
    starting_node->pipe = true;
    q.push(starting_node);
    if (starting_node->north != nullptr) {
        starting_node->north->type = 1;
        starting_node->north->prev = starting_node;
        q.push(starting_node->north);

    }

    if (starting_node->south != nullptr) {
        starting_node->south->type = 2;
        starting_node->south->prev = starting_node;
        q.push(starting_node->south);

    }

    if (starting_node->east != nullptr) {
        starting_node->east->type = 3;
        starting_node->east->prev = starting_node;
        q.push(starting_node->east);

    }

    if (starting_node->west != nullptr) {
        starting_node->west->type = 4;
        starting_node->west->prev = starting_node;
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
                Node* curr_ = curr;
                while (curr_ != starting_node) {
                    curr_->pipe = true;
                    curr_ = curr_->prev;
                }
                Node* other = curr->north;
                while (other != starting_node) {
                    other->pipe = true;
                    other = other->prev;
                }
            }
            curr->north->type = curr->type;
            curr->north->step = curr->step + 1;
            curr->north->prev = curr->north->prev == nullptr ? curr : curr->north->prev;
            q.push(curr->north);
        }

        if (curr->south != nullptr) {
            if (curr->south->type != 0 && curr->south->type != curr->type) {
                found = true;
                total_steps = curr->step + curr->south->step;
                Node* curr_ = curr;
                while (curr_ != starting_node) {
                    // test
                    curr_->pipe = true;
                    curr_ = curr_->prev;
                }
                Node* other = curr->south;
                while (other != starting_node) {
                    other->pipe = true;
                    other = other->prev;
                }
            }
            curr->south->type = curr->type;
            curr->south->step = curr->step + 1;
            curr->south->prev = curr->south->prev == nullptr ? curr : curr->south->prev;
            q.push(curr->south);
        }

        if (curr->east != nullptr) {
            if (curr->east->type != 0 && curr->east->type != curr->type) {
                found = true;
                total_steps = curr->step + curr->east->step;
                Node* curr_ = curr;
                while (curr_ != starting_node) {
                    curr_->pipe=true;
                    curr_ = curr_->prev;
                }
                Node* other = curr->east;
                while (other != starting_node) {
                    other->pipe = true;
                    other = other->prev;
                }
            }
            curr->east->type = curr->type;
            curr->east->step = curr->step + 1;
            curr->east->prev = curr->east->prev == nullptr ? curr : curr->east->prev;
            q.push(curr->east);
        }

        if (curr->west != nullptr) {
            if (curr->west->type != 0 && curr->west->type != curr->type) {
                found = true;
                total_steps = curr->step + curr->west->step;
                Node* curr_ = curr;
                while (curr_ != starting_node) {
                    curr_->pipe=true;
                    curr_ = curr_->prev;
                }
                Node* other = curr->west;
                while (other != starting_node) {
                    other->pipe = true;
                    other = other->prev;
                }
            }
            curr->west->type = curr->type;
            curr->west->step = curr->step + 1;
            curr->west->prev = curr->west->prev == nullptr ? curr : curr->west->prev;

            q.push(curr->west);
        }

        curr->seen = true;
    }

    total_steps += 2;
    int total_half = (total_steps + 1) / 2;

    cout << "The answer for Day 10 Part 1 is: " << total_half << endl;



    // ---------------------------- PART 2 ----------------------------
    
    int bigrows = (rows * 2) - 1;
    int bigcols = (cols * 2) - 1;
    char expanded_grid[bigrows][bigcols];
    
    for (int i = 0; i < bigrows; i++) {
        for (int j = 0; j < bigcols; j++) {
            if (i % 2 == 0 && j % 2 == 0) {
                expanded_grid[i][j] = node_matrix[i/2][j/2]->pipe ? node_matrix[i/2][j/2]->c : '.';
            } else {
                expanded_grid[i][j] = '?';
            }
        }
    }


    // Close gaps
    for (int i = 0; i < bigrows; i++) {
        for (int j = 0; j < bigcols; j++) {
            if (expanded_grid[i][j] == 'L' || expanded_grid[i][j] == 'S') {
                // Check up
                if (expanded_grid[i-2][j] == '|' || expanded_grid[i-2][j] == 'F' || expanded_grid[i-2][j] == '7') {
                    expanded_grid[i-1][j] = '|';
                }
                // Check right
                if (expanded_grid[i][j+2] == '-' || expanded_grid[i][j+2] == 'J' || expanded_grid[i][j+2] == '7') {
                    expanded_grid[i][j+1] = '-';
                }
            }

            if (expanded_grid[i][j] == 'J' || expanded_grid[i][j] == 'S') {
                // Check up
                if (expanded_grid[i-2][j] == '|' || expanded_grid[i-2][j] == 'F' || expanded_grid[i-2][j] == '7') {
                    expanded_grid[i-1][j] = '|';
                }
                // Check left
                if (expanded_grid[i][j-2] == '-' || expanded_grid[i][j-2] == 'F' || expanded_grid[i][j-2] == 'L') {
                    expanded_grid[i][j-1] = '-';
                }
            }

            if (expanded_grid[i][j] == '7' || expanded_grid[i][j] == 'S') {
                // Check down
                if (expanded_grid[i+2][j] == '|' || expanded_grid[i+2][j] == 'L' || expanded_grid[i+2][j] == 'J') {
                    expanded_grid[i+1][j] = '|';
                }
                // Check left
                if (expanded_grid[i][j-2] == '-' || expanded_grid[i][j-2] == 'F' || expanded_grid[i][j-2] == 'L') {
                    expanded_grid[i][j-1] = '-';
                }
            }

            if (expanded_grid[i][j] == 'F' || expanded_grid[i][j] == 'S') {
                // Check down
                if (expanded_grid[i+2][j] == '|' || expanded_grid[i+2][j] == 'L' || expanded_grid[i+2][j] == 'J') {
                    expanded_grid[i+1][j] = '|';
                }
                // Check right
                if (expanded_grid[i][j+2] == '-' || expanded_grid[i][j+2] == 'J' || expanded_grid[i][j+2] == '7') {
                    expanded_grid[i][j+1] = '-';
                }
            }

            if (expanded_grid[i][j] == '|' || expanded_grid[i][j] == 'S') {
                // Check down
                if (expanded_grid[i+2][j] == '|' || expanded_grid[i+2][j] == 'L' || expanded_grid[i+2][j] == 'J') {
                    expanded_grid[i+1][j] = '|';
                }
                // Check up
                if (expanded_grid[i-2][j] == '|' || expanded_grid[i-2][j] == 'F' || expanded_grid[i-2][j] == '7') {
                    expanded_grid[i-1][j] = '|';
                }
            }

            if (expanded_grid[i][j] == '-' || expanded_grid[i][j] == 'S') {
                // Check right
                if (expanded_grid[i][j+2] == '-' || expanded_grid[i][j+2] == 'J' || expanded_grid[i][j+2] == '7') {
                    expanded_grid[i][j+1] = '-';
                }
                // Check left
                if (expanded_grid[i][j-2] == '-' || expanded_grid[i][j-2] == 'F' || expanded_grid[i][j-2] == 'L') {
                    expanded_grid[i][j-1] = '-';
                }
            }
            
        }
    }

    // Look for enclosed
    int enclosed = 0;
    for (int i = 0; i < bigrows; i++) {
        for (int j = 0; j < bigcols; j++) {
            if (expanded_grid[i][j] == '.') {
                // Up horizontal
                if (i < 1 ) { continue; }
                bool is_enclosed = false;
                for (int k = 0; k < j; k++) {
                    if (expanded_grid[i-1][k] == '|') {
                        is_enclosed = !is_enclosed;
                    }
                }

                if (is_enclosed){
                    enclosed++;
                }
            }
        }
    }

    cout << "The answer for Day 10 Part 2 is: " << enclosed << endl;
    // ----------------------------------------------------------------


    // Free up memory
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            delete node_matrix[i][j];
        }
    }

    return 0;
}