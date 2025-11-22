#include <bits/stdc++.h>
using namespace std;

struct Command {
    int existing;
    int newCube;
    string direction;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<Command> commands(n);
    
    for (int i = 0; i < n; i++) {
        cin >> commands[i].existing >> commands[i].newCube >> commands[i].direction;
    }
    
    int queryNum;
    cin >> queryNum;
    
    sort(commands.begin(), commands.end(), [](const Command& a, const Command& b) {
        if (a.existing != b.existing) {
            return a.existing < b.existing;
        }
        return a.newCube < b.newCube;
    });
    
    map<int, pair<int, int>> positions;
    
    map<pair<int, int>, int> grid;
    
    positions[1] = make_pair(0, 0);
    grid[make_pair(0, 0)] = 1;
    
    map<string, pair<int, int>> directionMap;
    directionMap["up"] = make_pair(0, 1);
    directionMap["top"] = make_pair(0, 1);
    directionMap["down"] = make_pair(0, -1);
    directionMap["left"] = make_pair(-1, 0);
    directionMap["right"] = make_pair(1, 0);
    
    for (int i = 0; i < n; i++) {
        int existing = commands[i].existing;
        int newCube = commands[i].newCube;
        string dir = commands[i].direction;
        
        
        if (positions.find(existing) == positions.end()) {
            continue; 
        }
        
        pair<int, int> existingPos = positions[existing];
        pair<int, int> delta = directionMap[dir];
        
        pair<int, int> newPos = make_pair(existingPos.first + delta.first,
                                          existingPos.second + delta.second);
        
        if (grid.find(newPos) != grid.end()) {
            int oldCube = grid[newPos];
            positions.erase(oldCube);
            grid.erase(newPos);
        }
        
        positions[newCube] = newPos;
        grid[newPos] = newCube;
    }
    
    if (positions.find(queryNum) == positions.end()) {
        cout << "-1 -1 -1 -1" << endl;
        return 0;
    }
    
    pair<int, int> queryPos = positions[queryNum];
    
    vector<pair<int, int>> neighbors;
    neighbors.push_back(make_pair(queryPos.first, queryPos.second + 1));      // UP
    neighbors.push_back(make_pair(queryPos.first, queryPos.second - 1));      // DOWN
    neighbors.push_back(make_pair(queryPos.first - 1, queryPos.second));      // LEFT
    neighbors.push_back(make_pair(queryPos.first + 1, queryPos.second));      // RIGHT
    
    vector<int> result;
    for (int i = 0; i < 4; i++) {
        if (grid.find(neighbors[i]) != grid.end()) {
            result.push_back(grid[neighbors[i]]);
        } else {
            result.push_back(-1);
        }
    }
    
    cout << result[0] << " " << result[1] << " " 
         << result[2] << " " << result[3] << endl;
    
    return 0;
}