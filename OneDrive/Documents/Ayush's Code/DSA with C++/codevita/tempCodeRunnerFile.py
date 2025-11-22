from collections import defaultdict, deque

def bfs(graph, start, end, restricted):
    q, visited = deque([start]), {start}
    while q:
        node = q.popleft()
        if node == end:
            return True
        for nei in graph[node]:
            if nei not in visited and nei not in restricted:
                visited.add(nei)
                q.append(nei)
    return False

def main():
    import sys
    input = sys.stdin.readline

    n = int(input())
    graph = defaultdict(list)
    for _ in range(n):
        line = input().split()
        u = line[0]
        for v in line[1:]:
            graph[u].append(v)
            graph[v].append(u)

    q = int(input())
    queries = [input().strip() for _ in range(q)]
    r = int(input())
    restrictions = {}
    for _ in range(r):
        line = input().split()
        restrictions[line[0]] = set(line[1:])

    results = []
    for query in queries:
        parts = query.split()
        if parts[1] == "to":
            src, dest = parts[0], parts[2]
            restrict = restrictions.get(src, set())
            results.append("YES" if bfs(graph, src, dest, restrict) else "NO")
        elif parts[1] == "connects":
            a, b = parts[0], parts[2]
            if b not in graph[a]: graph[a].append(b)
            if a not in graph[b]: graph[b].append(a)
        elif parts[1] == "disconnects":
            a, b = parts[0], parts[2]
            if b in graph[a]: graph[a].remove(b)
            if a in graph[b]: graph[b].remove(a)
    for res in results:
        print(res)

if __name__ == "__main__":
    main()