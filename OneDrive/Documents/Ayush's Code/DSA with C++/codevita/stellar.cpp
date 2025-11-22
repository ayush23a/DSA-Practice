#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

// Point structure
struct Point {
    int x, y;
    Point(int xx = 0, int yy = 0): x(xx), y(yy) {}
    bool operator<(const Point& b) const { return x < b.x || (x == b.x && y < b.y); }
    bool operator==(const Point& b) const { return x == b.x && y == b.y; }
};

// Check if point p lies on segment ab
bool onSegment(const Point& p, const Point& a, const Point& b) {
    int dx1 = b.x - a.x, dy1 = b.y - a.y;
    int dx2 = p.x - a.x, dy2 = p.y - a.y;
    if (dx1 * dy2 != dy1 * dx2) return false; // colinear check
    int minx = min(a.x, b.x), maxx = max(a.x, b.x);
    int miny = min(a.y, b.y), maxy = max(a.y, b.y);
    return minx <= p.x && p.x <= maxx && miny <= p.y && p.y <= maxy;
}

// Find intersection point of segments ab and cd, returns true if found
bool getIntersection(const Point& a, const Point& b, const Point& c, const Point& d, Point& res) {
    int a1 = b.y - a.y, b1 = a.x - b.x, c1 = a1 * a.x + b1 * a.y;
    int a2 = d.y - c.y, b2 = c.x - d.x, c2 = a2 * c.x + b2 * c.y;
    int det = a1 * b2 - a2 * b1;
    if (det == 0) return false; // parallel
    int x = (b2 * c1 - b1 * c2) / det;
    int y = (a1 * c2 - a2 * c1) / det;
    Point inter(x, y);
    if (onSegment(inter, a, b) && onSegment(inter, c, d)) {
        res = inter;
        return true;
    }
    return false;
}

int main() {
    int N;
    cin >> N;
    vector<pair<Point, Point>> segments(N);
    set<Point> stars;

    // Read segments and record endpoints as stars
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        segments[i] = {Point(x1, y1), Point(x2, y2)};
        stars.insert(Point(x1, y1));
        stars.insert(Point(x2, y2));
    }
    // Find all intersections as stars
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            Point inter;
            if (getIntersection(segments[i].first, segments[i].second,
                                segments[j].first, segments[j].second, inter)) {
                stars.insert(inter);
            }
        }
    }

    // Build star graph: connect stars that lie on the same segment
    map<Point, vector<Point>> graph;
    vector<Point> starvec(stars.begin(), stars.end());
    for (const auto& seg : segments) {
        vector<Point> pts;
        for (const auto& star : starvec) {
            if (onSegment(star, seg.first, seg.second)) pts.push_back(star);
        }
        for (size_t i = 0; i < pts.size(); ++i)
            for (size_t j = i + 1; j < pts.size(); ++j) {
                graph[pts[i]].push_back(pts[j]);
                graph[pts[j]].push_back(pts[i]);
            }
    }

    int sx, sy, dx, dy;
    cin >> sx >> sy >> dx >> dy;
    Point src(sx, sy), dst(dx, dy);

    if (!stars.count(src) || !stars.count(dst)) {
        cout << "Impossible" << endl;
        return 0;
    }

    // BFS from src to dst
    queue<Point> q;
    map<Point, int> dist;
    q.push(src);
    dist[src] = 1;
    while (!q.empty()) {
        Point cur = q.front(); q.pop();
        if (cur == dst) {
            cout << dist[cur] << endl;
            return 0;
        }
        for (const auto& nb : graph[cur]) {
            if (!dist.count(nb)) {
                dist[nb] = dist[cur] + 1;
                q.push(nb);
            }
        }
    }
    cout << "Impossible" << endl;
    return 0;
}
