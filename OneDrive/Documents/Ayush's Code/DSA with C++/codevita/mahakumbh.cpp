#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

static inline vector<string> split(const string& s) {
    vector<string> tokens;
    string word;
    stringstream ss(s);
    while (ss >> word) {
        tokens.push_back(word);
    }
    return tokens;
}

static bool canTravel(
    const string& src, const string& dst,
    const unordered_map<string, unordered_set<string>>& adj,
    const unordered_map<string, unordered_set<string>>& restricts
) {
    if (src == dst) return true;

    const unordered_set<string> emptySet;
    auto it = restricts.find(src);
    const unordered_set<string>& blocked_stations = (it != restricts.end()) ? it->second : emptySet;

    queue<string> q;
    q.push(src);
    unordered_set<string> visited;
    visited.insert(src);

    while (!q.empty()) {
        string current_station = q.front();
        q.pop();

        auto adj_it = adj.find(current_station);
        if (adj_it == adj.end()) continue;

        for (const string& neighbor : adj_it->second) {
            if (neighbor == dst) return true;
            if (visited.count(neighbor)) continue;
            if (blocked_stations.count(neighbor)) continue;

            visited.insert(neighbor);
            q.push(neighbor);
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    string dummy;
    getline(cin, dummy);

    unordered_map<string, unordered_set<string>> adj;
    for (int i = 0; i < N; ) {
        string line;
        if (!getline(cin, line) || line.empty()) continue;
        
        vector<string> tokens = split(line);
        const string& source_station = tokens[0];
        for (size_t j = 1; j < tokens.size(); ++j) {
            const string& neighbor = tokens[j];
            adj[source_station].insert(neighbor);
            adj[neighbor].insert(source_station);
        }
        i++;
    }

    int Q;
    cin >> Q;
    getline(cin, dummy);

    struct Query { string station1, operation, station2; };
    vector<Query> queries;
    queries.reserve(Q);

    for (int i = 0; i < Q; ) {
        string line;
        if (!getline(cin, line) || line.empty()) continue;
        
        vector<string> tokens = split(line);
        queries.push_back({tokens[0], tokens[1], tokens[2]});
        i++;
    }

    int R;
    cin >> R;
    getline(cin, dummy);

    unordered_map<string, unordered_set<string>> restricts;
    for (int i = 0; i < R; ) {
        string line;
        if (!getline(cin, line) || line.empty()) continue;
        
        vector<string> tokens = split(line);
        const string& source_station = tokens[0];
        for (size_t j = 1; j < tokens.size(); ++j) {
            restricts[source_station].insert(tokens[j]);
        }
        i++;
    }

    for (const auto& q : queries) {
        if (q.operation == "to") {
            cout << (canTravel(q.station1, q.station2, adj, restricts) ? "yes" : "no") << '\n';
        } else if (q.operation == "connects") {
            adj[q.station1].insert(q.station2);
            adj[q.station2].insert(q.station1);
        } else if (q.operation == "disconnects") {
            adj[q.station1].erase(q.station2);
            adj[q.station2].erase(q.station1);
        }
    }

    return 0;
}