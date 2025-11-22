#include <bits/stdc++.h>
using namespace std;

struct Node {
    int l, r, c, d;
    Node(int _l=0,int _r=0,int _c=0,int _d=0):l(_l),r(_r),c(_c),d(_d){}
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int S;
    if(!(cin>>S)) return 0;

    // grid[layer][row][col]
    vector<vector<string>> grid(S, vector<string>(S));
    for(int layer=0; layer<S; ++layer){
        for(int row=0; row<S; ++row){
            string s; cin >> s;
            if((int)s.size() != S){
                // if input has spaces or stray chars, try to handle but assume judge input is correct
            }
            grid[layer][row] = s;
        }
    }

    int sl,sr,sc;
    int gl,gr,gc;
    cin >> sl >> sr >> sc;
    cin >> gl >> gr >> gc;

    auto in_bounds = [&](int l,int r,int c){
        return l>=0 && l<S && r>=0 && r<S && c>=0 && c<S;
    };
    auto walkable = [&](int l,int r,int c){
        return grid[l][r][c] != 'E';
    };

    // If start or goal out of bounds -> unreachable
    if(!in_bounds(sl,sr,sc) || !in_bounds(gl,gr,gc)){
        cout << -1 << '\n';
        return 0;
    }

    // If start not walkable -> unreachable
    if(!walkable(sl,sr,sc)){
        cout << -1 << '\n';
        return 0;
    }

    // visited
    vector<vector<vector<char>>> vis(S, vector<vector<char>>(S, vector<char>(S,0)));
    queue<Node> q;
    vis[sl][sr][sc] = 1;
    q.push(Node(sl,sr,sc,0));

    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};

    int answer = -1;
    while(!q.empty()){
        Node cur = q.front(); q.pop();
        int l = cur.l, r = cur.r, c = cur.c, d = cur.d;

        if(l==gl && r==gr && c==gc){
            answer = d;
            break;
        }

        // 4-directional moves within same layer (only to walkable cells)
        for(int k=0;k<4;++k){
            int nr = r + dr[k];
            int nc = c + dc[k];
            int nl = l;
            if(!in_bounds(nl,nr,nc)) continue;
            if(!walkable(nl,nr,nc)) continue;
            if(!vis[nl][nr][nc]){
                vis[nl][nr][nc] = 1;
                q.push(Node(nl,nr,nc,d+1));
            }
        }

        // special ramp moves depending on current cell
        char ch = grid[l][r][c];
        if(ch == 'R'){
            int nl = l+1, nr = r, nc = c+1;
            if(in_bounds(nl,nr,nc) && walkable(nl,nr,nc) && !vis[nl][nr][nc]){
                vis[nl][nr][nc] = 1;
                q.push(Node(nl,nr,nc,d+1));
            }
        } else if(ch == 'L'){
            int nl = l+1, nr = r, nc = c-1;
            if(in_bounds(nl,nr,nc) && walkable(nl,nr,nc) && !vis[nl][nr][nc]){
                vis[nl][nr][nc] = 1;
                q.push(Node(nl,nr,nc,d+1));
            }
        } else if(ch == 'B'){
            int nl = l+1, nr = r, nc = c;
            if(in_bounds(nl,nr,nc) && walkable(nl,nr,nc) && !vis[nl][nr][nc]){
                vis[nl][nr][nc] = 1;
                q.push(Node(nl,nr,nc,d+1));
            }
        } else if(ch == 'F'){
            int nl = l-1, nr = r, nc = c;
            if(in_bounds(nl,nr,nc) && walkable(nl,nr,nc) && !vis[nl][nr][nc]){
                vis[nl][nr][nc] = 1;
                q.push(Node(nl,nr,nc,d+1));
            }
        }
        // Note: 'D' has no vertical ramp by itself
    }

    cout << answer << '\n';
    return 0;
}
