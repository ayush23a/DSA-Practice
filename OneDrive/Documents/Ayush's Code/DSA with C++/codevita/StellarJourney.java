import java.util.*;

public class StellarJourney {

    static class Point {
        int x, y;
        Point(int a, int b) { x = a; y = b; }
        public boolean equals(Object o) {
            if (this == o) return true;
            if (!(o instanceof Point)) return false;
            Point p = (Point)o;
            return x == p.x && y == p.y;
        }
        public int hashCode() { return Objects.hash(x, y); }
        public String toString() { return "(" + x + "," + y + ")"; }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = Integer.parseInt(sc.nextLine().trim());
        int[][] segments = new int[N][4];
        for (int i = 0; i < N; i++) {
            String[] arr = sc.nextLine().split(" ");
            for (int j = 0; j < 4; j++) segments[i][j] = Integer.parseInt(arr[j]);
        }
        String[] ssrc = sc.nextLine().split(" ");
        String[] sdst = sc.nextLine().split(" ");
        Point src = new Point(Integer.parseInt(ssrc[0]), Integer.parseInt(ssrc[1]));
        Point dst = new Point(Integer.parseInt(sdst[0]), Integer.parseInt(sdst[1]));

        // Map points to a set of segment indexes each point belongs to (star arms)
        Map<Point, Set<Integer>> starSegments = new HashMap<Point, Set<Integer>>();
        // Collect all star centers: all endpoints + intersections
        Set<Point> allStars = new HashSet<Point>();
        for (int i = 0; i < N; i++) {
            Point p1 = new Point(segments[i][0], segments[i][1]);
            Point p2 = new Point(segments[i][2], segments[i][3]);
            allStars.add(p1); allStars.add(p2);
            addToMap(starSegments, p1, i); addToMap(starSegments, p2, i);
        }
        // Add intersections
        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {
                Point inter = getIntersection(segments[i], segments[j]);
                if (inter != null) {
                    allStars.add(inter);
                    addToMap(starSegments, inter, i);
                    addToMap(starSegments, inter, j);
                }
            }
        }
        // Build adjacency graph: star to star, if share a segment
        Map<Point, List<Point>> graph = new HashMap<Point, List<Point>>();
        for (Point p1 : allStars) graph.put(p1, new ArrayList<Point>());
        for (int i = 0; i < N; i++) {
            // collect all stars on the segment
            List<Point> pointsOnSeg = new ArrayList<Point>();
            for (Point s : allStars) {
                if (onSegment(s, segments[i])) pointsOnSeg.add(s);
            }
            for (Point a : pointsOnSeg) {
                for (Point b : pointsOnSeg) {
                    if (!a.equals(b)) graph.get(a).add(b);
                }
            }
        }

        // Get the star center that contains src/dest (must be exactly at a star center)
        if (!allStars.contains(src) || !allStars.contains(dst)) {
            System.out.println("Impossible");
            return;
        }

        // BFS: find min number of stars from src to dst
        Queue<Point> q = new LinkedList<Point>();
        Map<Point, Integer> dists = new HashMap<Point, Integer>();
        q.add(src);
        dists.put(src, 1); // including starting star
        boolean found = false;
        while (!q.isEmpty()) {
            Point cur = q.poll();
            int dist = dists.get(cur);
            if (cur.equals(dst)) {
                System.out.println(dist);
                found = true;
                break;
            }
            for (Point nxt : graph.get(cur)) {
                if (!dists.containsKey(nxt)) {
                    dists.put(nxt, dist + 1);
                    q.add(nxt);
                }
            }
        }
        if (!found) System.out.println("Impossible");
    }

    static void addToMap(Map<Point, Set<Integer>> map, Point pt, int segIdx) {
        if (!map.containsKey(pt)) map.put(pt, new HashSet<Integer>());
        map.get(pt).add(segIdx);
    }

    static boolean onSegment(Point p, int[] seg) {
        int x1 = seg[0], y1 = seg[1], x2 = seg[2], y2 = seg[3];
        int minX = Math.min(x1,x2), maxX = Math.max(x1,x2), minY = Math.min(y1,y2), maxY = Math.max(y1,y2);
        if (p.x < minX || p.x > maxX || p.y < minY || p.y > maxY) return false;
        int dx = x2-x1, dy = y2-y1;
        int px = p.x-x1, py = p.y-y1;
        // for vertical, horizontal or diagonal only
        return dx==0? px==0 : dy==0? py==0 : Math.abs(px*dy-py*dx)==0;
    }

    static Point getIntersection(int[] a, int[] b) {
        int x1 = a[0], y1 = a[1], x2 = a[2], y2 = a[3];
        int x3 = b[0], y3 = b[1], x4 = b[2], y4 = b[3];
        int denom = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);
        if (denom == 0) return null;
        int xi = ((x1*y2-y1*x2)*(x3-x4)-(x1-x2)*(x3*y4-y3*x4))/denom;
        int yi = ((x1*y2-y1*x2)*(y3-y4)-(y1-y2)*(x3*y4-y3*x4))/denom;
        if (onSegment(new Point(xi,yi), a) && onSegment(new Point(xi,yi), b))
            return new Point(xi,yi);
        return null;
    }
}
