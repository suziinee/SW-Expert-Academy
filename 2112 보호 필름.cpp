#include <iostream>
#include <algorithm>
using namespace std;
 
#define MAXD 13
#define MAXW 20
int D, W, K;
int map[MAXD][MAXW];
int back[MAXD][MAXW];
int ans;
 
 
bool check()
{
    if (K == 1) return true;
    for (int x = 0; x < W; x++) {
        int tmp = map[0][x];
        int cnt = 1;
        bool flag = false;
        for (int y = 1; y < D; y++) {
            if (tmp == map[y][x]) cnt++;
            else {
                tmp = map[y][x];
                cnt = 1;
            }
            if (cnt >= K) { flag = true; break; }
        }
        if (!flag) return false;
    }
    return true;
}
 
void fill(int row, int med)
{
    for (int x = 0; x < W; x++) {
        map[row][x] = med;
    }
}
 
void unfill(int row)
{
    for (int x = 0; x < W; x++) {
        map[row][x] = back[row][x];
    }
}

void dfs(int s, int cnt)
{
    if (cnt > ans) return;
    if (cnt < ans && check()) {
        ans = cnt;
    }
    if (s == D) return;
 
    for (int i = s; i < D; i++) {
        for (int med = 0; med < 2; med++) {
            fill(i, med);
            dfs(i + 1, cnt + 1);
            unfill(i);
        }
    }
}
 
void input()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> D >> W >> K;
        fill(&map[0][0], &map[MAXD - 1][MAXW], 0);
        fill(&back[0][0], &back[MAXD - 1][MAXW], 0);
        ans = 0x7fffffff;
        for (int y = 0; y < D; y++) {
            for (int x = 0; x < W; x++) {
                cin >> map[y][x];
                back[y][x] = map[y][x];
            }
        }
        dfs(0, 0);
        cout << "#" << t << " " << ans << "\n";
    }
}
 
 
int main()
{
    input();
    return 0;
}