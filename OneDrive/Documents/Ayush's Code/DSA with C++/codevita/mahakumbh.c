#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATIONS 15
#define MAX_NAME_LEN 30

typedef struct {
    char names[MAX_STATIONS][MAX_NAME_LEN];
    int count;
} StationList;

int get_station_idx(StationList *list, const char *name) {
    for (int i = 0; i < list->count; i++)
        if (strcmp(list->names[i], name) == 0)
            return i;
    strcpy(list->names[list->count], name);
    return list->count++;
}

int graph[MAX_STATIONS][MAX_STATIONS];
int restricts[MAX_STATIONS][MAX_STATIONS];

int dfs(int src, int dst, int N, int *visited, int *restricted) {
    if (src == dst) return 1;
    visited[src] = 1;
    for (int i = 0; i < N; i++) {
        if (graph[src][i] && !visited[i] && !restricted[i]) {
            if (dfs(i, dst, N, visited, restricted))
                return 1;
        }
    }
    return 0;
}

int main() {
    StationList stations = { .count = 0 };
    memset(graph, 0, sizeof(graph));
    memset(restricts, 0, sizeof(restricts));
    int N;
    scanf("%d", &N);
    char line[500];
    getchar();

    for (int ni = 0; ni < N; ni++) {
        fgets(line, sizeof(line), stdin);
        char* token = strtok(line, " \n");
        int src = get_station_idx(&stations, token);
        while ((token = strtok(NULL, " \n"))) {
            int dst = get_station_idx(&stations, token);
            graph[src][dst] = 1;
            graph[dst][src] = 1;
        }
    }

    int Q;
    scanf("%d", &Q);
    getchar();
    char queries[Q][100];
    for (int qi = 0; qi < Q; qi++) {
        fgets(queries[qi], sizeof(queries[qi]), stdin);
    }
    int R;
    scanf("%d", &R);
    getchar();
    for (int ri = 0; ri < R; ri++) {
        fgets(line, sizeof(line), stdin);
        char* token = strtok(line, " \n");
        int src = get_station_idx(&stations, token);
        while ((token = strtok(NULL, " \n"))) {
            int rest = get_station_idx(&stations, token);
            restricts[src][rest] = 1;
        }
    }

    for (int qi = 0; qi < Q; qi++) {
        char* statement = queries[qi];
        char w1[MAX_NAME_LEN], w2[MAX_NAME_LEN];
        if (strstr(statement, " to ")) {
            sscanf(statement, "%s to %s", w1, w2);
            int src = get_station_idx(&stations, w1);
            int dst = get_station_idx(&stations, w2);
            int visited[MAX_STATIONS] = {0};
            int restricted[MAX_STATIONS] = {0};
            for (int i = 0; i < stations.count; i++)
                if (restricts[src][i]) restricted[i] = 1;
            printf(dfs(src, dst, stations.count, visited, restricted) ? "yes\n" : "no\n");
        } else if (strstr(statement, " connects ")) {
            sscanf(statement, "%s connects %s", w1, w2);
            int idx1 = get_station_idx(&stations, w1);
            int idx2 = get_station_idx(&stations, w2);
            graph[idx1][idx2] = 1;
            graph[idx2][idx1] = 1;
        } else if (strstr(statement, " disconnects ")) {
            sscanf(statement, "%s disconnects %s", w1, w2);
            int idx1 = get_station_idx(&stations, w1);
            int idx2 = get_station_idx(&stations, w2);
            graph[idx1][idx2] = 0;
            graph[idx2][idx1] = 0;
        }
    }
    return 0;
}
