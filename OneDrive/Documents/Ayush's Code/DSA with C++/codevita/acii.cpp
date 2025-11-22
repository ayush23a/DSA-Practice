#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Function to generate the grid for a single house
vector<string> buildHouse(int width, int wall_height, char direction) {
    vector<string> house_grid;
    
    // 1. Build the Roof
    // Roof height is half the width
    int roof_height = width / 2;
    
    for (int i = 0; i < roof_height; ++i) {
        int outer_spaces = (width / 2) - 1 - i;
        int inner_spaces = 2 * i;
        
        string line = "";
        line += string(outer_spaces, ' ');
        line += "/";
        line += string(inner_spaces, ' ');
        line += "\\";
        line += string(outer_spaces, ' ');
        
        // Ensure the string length matches the width strictly
        while (line.length() < width) {
            line += " ";
        }
        house_grid.push_back(line);
    }
    
    // 2. Build the Walls and Base
    // Determine wall characters (handle Mirroring L/R)
    char left_char = '@';
    char right_char = '&';
    
    if (direction == 'L' || direction == 'R') {
        swap(left_char, right_char);
    }
    
    // Wall section height includes the base row.
    // So actual wall rows = wall_height - 1
    for (int i = 0; i < wall_height - 1; ++i) {
        string line = "";
        line += left_char;
        if (width > 2) {
            line += string(width - 2, ' ');
        }
        line += right_char;
        house_grid.push_back(line);
    }
    
    // Add Base row
    house_grid.push_back(string(width, '#'));
    
    // 3. Handle Inversion (Direction 'D')
    // If direction is Down, reverse the entire grid vertically
    if (direction == 'D') {
        reverse(house_grid.begin(), house_grid.end());
    }
    
    return house_grid;
}

int main() {
    // Optimize I/O operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string input_line;
    if (!getline(cin, input_line) || input_line.empty()) {
        return 0;
    }

    stringstream ss(input_line);
    string segment;
    
    // Store all houses as 2D grids (vector of strings)
    vector<vector<string>> all_houses;
    int max_total_height = 0;

    // Parse inputs
    while (ss >> segment) {
        // Format: width<x>height<direction> (e.g., 2x4H)
        size_t x_pos = segment.find('x');
        
        // Parse width
        int width = stoi(segment.substr(0, x_pos));
        
        // Parse height (between 'x' and last char)
        // Length of height substring = (Total Len) - (x_pos + 1) - (1 for direction)
        int height_len = segment.length() - x_pos - 2;
        int height = stoi(segment.substr(x_pos + 1, height_len));
        
        // Parse direction (last char)
        char direction = segment.back();
        
        // Build and store
        vector<string> house = buildHouse(width, height, direction);
        
        if (house.size() > max_total_height) {
            max_total_height = house.size();
        }
        
        all_houses.push_back(house);
    }

    // Print aligned output
    // We iterate from row 0 (top) to max_total_height (bottom)
    for (int r = 0; r < max_total_height; ++r) {
        for (const auto& house : all_houses) {
            int h_height = house.size();
            
            // Calculate padding needed to push this house to the bottom
            int padding_top = max_total_height - h_height;
            
            if (r < padding_top) {
                // Print spaces equivalent to the house's width
                // house[0].length() gives the width
                if (!house.empty()) {
                    cout << string(house[0].length(), ' ');
                }
            } else {
                // Print the actual house row
                // Calculate relative index inside the house grid
                int inner_row = r - padding_top;
                cout << house[inner_row];
            }
        }
        // Move to next line after printing slice of all houses
        cout << endl;
    }

    return 0;
}