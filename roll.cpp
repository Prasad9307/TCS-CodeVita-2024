#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Function to read a line of input and split it into a vector of strings
vector<string> read_input() {
    vector<string> tokens;
    string line;
    getline(cin, line);
    istringstream iss(line);
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));
    return tokens;
}

// Global variables to represent the graph and associated data structures
map<string, vector<string>> adjacency_list;
map<string, ll> mask, color_id;
map<string, string> open_nodes;

ll operations = 0;

// Function to perform the first depth-first search (DFS) for calculating masks
ll calculate_mask(string &node) {
    ll current_mask = color_id.count(node) ? (1LL << color_id[node]) : 0;
    for (string &child : adjacency_list[node]) {
        current_mask |= calculate_mask(child);
    }
    return mask[node] = current_mask;
}

// Function to perform the second DFS to update routing
void update_routing(string &node, int target_bit) {
    if (color_id[node] == target_bit) {
        open_nodes[node] = node;
        return;
    }
    for (string &child : adjacency_list[node]) {
        if (mask[child] >> target_bit & 1) {
            if (open_nodes[node] != child) {
                operations++;
                open_nodes[node] = child;
            }
            return update_routing(child, target_bit);
        }
    }
}

int main() {
    ll num_nodes;
    cin >> num_nodes;
    cin.ignore(); // Ignore the newline character after the integer input

    // Build the graph
    while (num_nodes--) {
        vector<string> children = read_input();
        reverse(children.begin(), children.end());
        string parent = children.back();
        children.pop_back();
        adjacency_list[parent] = children;
    }

    // Assign unique IDs to each color
    ll color_counter = 0;
    vector<string> colors = read_input();
    for (string &color : colors) {
        if (!color_id.count(color)) {
            color_id[color] = ++color_counter;
        }
    }

    // Perform the first DFS from the source node
    string source = "source";
    calculate_mask(source);

    // Perform the second DFS for each color
    for (string &color : colors) {
        update_routing(source, color_id[color]);
    }

    // Output the total number of routing operations
    cout << operations;

    return 0;
}
