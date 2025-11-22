#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 1000
#define MAX_BRICKS 10000

typedef struct {
    int neighbors[100];
    int count;
} AdjList;

char idToType[MAX_BRICKS];
AdjList graph[MAX_BRICKS];
int dp[MAX_BRICKS];
int visited[MAX_BRICKS];
int endId;

int min(int a, int b) {
    return (a < b) ? a : b;
}

int dfs(int curId) {
    if (curId == endId) {
        return 0;
    }
    
    if (visited[curId]) {
        return dp[curId];
    }
    
    visited[curId] = 1;
    dp[curId] = INT_MAX;
    
    for (int i = 0; i < graph[curId].count; i++) {
        int neighbor = graph[curId].neighbors[i];
        char neighborType = idToType[neighbor];
        
        if (neighborType == 'R') continue;
        
        int result = dfs(neighbor);
        if (result != INT_MAX) {
            int cost = (neighborType == 'G') ? 1 : 0;
            dp[curId] = min(dp[curId], result + cost);
        }
    }
    
    return dp[curId];
}

int main() {
    int N;
    scanf("%d", &N);
    
    int brickId[MAX_N][MAX_N];
    int start = -1;
    int idCounter = 0;
    
    for (int i = 0; i < MAX_BRICKS; i++) {
        graph[i].count = 0;
        dp[i] = INT_MAX;
        visited[i] = 0;
    }
    
    getchar();
    
    for (int row = 0; row < N; row++) {
        char line[MAX_N * 2 + 10];
        fgets(line, sizeof(line), stdin);
        int col = 0;
        
        for (size_t j = 0; j < strlen(line) && line[j] != '\n'; j += 2) {
            int len = line[j] - '0';
            char type = line[j + 1];
            idToType[idCounter] = type;
            
            if (type == 'S') start = idCounter;
            if (type == 'D') endId = idCounter;
            
            for (int k = 0; k < len; k++) {
                if (col + k < N) {
                    brickId[row][col + k] = idCounter;
                }
            }
            col += len;
            idCounter++;
        }
    }
    
    // Build adjacency list
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            int curId = brickId[r][c];
            
            // Right neighbor
            if (c + 1 < N && brickId[r][c + 1] != curId) {
                int neighbor = brickId[r][c + 1];
                int exists = 0;
                for (int i = 0; i < graph[curId].count; i++) {
                    if (graph[curId].neighbors[i] == neighbor) {
                        exists = 1;
                        break;
                    }
                }
                if (!exists) {
                    graph[curId].neighbors[graph[curId].count++] = neighbor;
                }
            }
            
            // Bottom neighbor
            if (r + 1 < N && brickId[r + 1][c] != curId) {
                int neighbor = brickId[r + 1][c];
                int exists = 0;
                for (int i = 0; i < graph[curId].count; i++) {
                    if (graph[curId].neighbors[i] == neighbor) {
                        exists = 1;
                        break;
                    }
                }
                if (!exists) {
                    graph[curId].neighbors[graph[curId].count++] = neighbor;
                }
            }
            
            // Left neighbor
            if (c - 1 >= 0 && brickId[r][c - 1] != curId) {
                int neighbor = brickId[r][c - 1];
                int exists = 0;
                for (int i = 0; i < graph[curId].count; i++) {
                    if (graph[curId].neighbors[i] == neighbor) {
                        exists = 1;
                        break;
                    }
                }
                if (!exists) {
                    graph[curId].neighbors[graph[curId].count++] = neighbor;
                }
            }
            
            // Top neighbor
            if (r - 1 >= 0 && brickId[r - 1][c] != curId) {
                int neighbor = brickId[r - 1][c];
                int exists = 0;
                for (int i = 0; i < graph[curId].count; i++) {
                    if (graph[curId].neighbors[i] == neighbor) {
                        exists = 1;
                        break;
                    }
                }
                if (!exists) {
                    graph[curId].neighbors[graph[curId].count++] = neighbor;
                }
            }
        }
    }
    
    if (start == -1) {
        printf("Impossible\n");
        return 0;
    }
    
    int result = dfs(start);
    
    if (result == INT_MAX) {
        printf("Impossible\n");
    } else {
        printf("%d\n", result);
    }
    
    return 0;
}