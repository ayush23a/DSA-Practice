import java.util.*;

public class MahaKumbh2K25 {
    static Map<String, HashSet<String>> graph = new HashMap<String, HashSet<String>>();
    static Map<String, HashSet<String>> restrictions = new HashMap<String, HashSet<String>>();

    public static boolean canTravel(String src, String dst, HashSet<String> restricted) {
        Queue<String> queue = new LinkedList<String>();
        HashSet<String> visited = new HashSet<String>();
        queue.add(src);
        visited.add(src);
        while (!queue.isEmpty()) {
            String current = queue.poll();
            if (current.equals(dst)) return true;
            HashSet<String> neighbors = graph.containsKey(current) ? graph.get(current) : new HashSet<String>();
            for (String neighbor : neighbors) {
                if (!visited.contains(neighbor) && !restricted.contains(neighbor)) {
                    visited.add(neighbor);
                    queue.add(neighbor);
                }
            }
        }
        return false;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = Integer.parseInt(sc.nextLine().trim());
        for (int i = 0; i < N; i++) {
            String[] tokens = sc.nextLine().trim().split("\\s+");
            String src = tokens[0];
            if (!graph.containsKey(src)) graph.put(src, new HashSet<String>());
            for (int j = 1; j < tokens.length; j++) {
                String dst = tokens[j];
                if (!graph.containsKey(dst)) graph.put(dst, new HashSet<String>());
                graph.get(src).add(dst);
                graph.get(dst).add(src);
            }
        }

        int Q = Integer.parseInt(sc.nextLine().trim());
        String[] queries = new String[Q];
        for (int i = 0; i < Q; i++)
            queries[i] = sc.nextLine().trim();

        int R = Integer.parseInt(sc.nextLine().trim());
        for (int i = 0; i < R; i++) {
            String[] restTokens = sc.nextLine().trim().split("\\s+");
            String src = restTokens[0];
            if (!restrictions.containsKey(src)) restrictions.put(src, new HashSet<String>());
            for (int j = 1; j < restTokens.length; j++)
                restrictions.get(src).add(restTokens[j]);
        }

        for (int i = 0; i < queries.length; i++) {
            String q = queries[i];
            if (q.contains(" to ")) {
                String[] parts = q.split(" to ");
                String src = parts[0];
                String dst = parts[1];
                HashSet<String> restricted = restrictions.containsKey(src) ? restrictions.get(src) : new HashSet<String>();
                System.out.println(canTravel(src, dst, restricted) ? "yes" : "no");
            } else if (q.contains(" connects ")) {
                String[] parts = q.split(" connects ");
                String s1 = parts[0];
                String s2 = parts[1];
                if (!graph.containsKey(s1)) graph.put(s1, new HashSet<String>());
                if (!graph.containsKey(s2)) graph.put(s2, new HashSet<String>());
                graph.get(s1).add(s2);
                graph.get(s2).add(s1);
            } else if (q.contains(" disconnects ")) {
                String[] parts = q.split(" disconnects ");
                String s1 = parts[0];
                String s2 = parts[1];
                if (graph.containsKey(s1)) graph.get(s1).remove(s2);
                if (graph.containsKey(s2)) graph.get(s2).remove(s1);
            }
        }
        sc.close();
    }
}
