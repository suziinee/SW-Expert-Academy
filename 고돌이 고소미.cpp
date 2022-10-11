#include <iostream>
#include <queue>
using namespace std;

#define MAXN 25
int N;
int map[MAXN][MAXN];
bool chk[MAXN][MAXN][MAXN][MAXN]; //고돌이 위치, 고소미 위치

struct AXIS { int y, x; };
AXIS pos[4]; //고돌이 위치(0), 고돌이 집(1), 고소미 위치(2), 고소미 집(3)

struct STATUS {
	int by, bx, gy, gx, time;
};
queue<STATUS> q;


void input()
{
	cin >> N;
	int y, x;
	for (int i = 0; i < 4; i++) {
		cin >> y >> x;
		--y; --x;
		pos[i].y = y;
		pos[i].x = x;
	}
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
		}
	}
}

int bfs()
{
	static int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1, 0 }; //마지막은 움직이지 않는 것
	static int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1, 0 };

	if (pos[0].y == pos[1].y && pos[0].x == pos[1].x && pos[2].y == pos[3].y && pos[2].x == pos[3].x) return 0;
	q.push({ pos[0].y, pos[0].x, pos[2].y, pos[2].x, 0 });
	chk[pos[0].y][pos[0].x][pos[2].y][pos[2].x] = true;

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();

		for (int bd = 0; bd < 9; bd++) {
			for (int gd = 0; gd < 9; gd++) {
				int nby = cur.by + dy[bd];
				int nbx = cur.bx + dx[bd];
				int ngy = cur.gy + dy[gd];
				int ngx = cur.gx + dx[gd];

				//인덱스 확인
				if (nby < 0 || nbx < 0 || nby >= N || nbx >= N) continue;
				if (ngy < 0 || ngx < 0 || ngy >= N || ngx >= N) continue;
				//갔던 곳인지 확인
				if (chk[nby][nbx][ngy][ngx]) continue;
				//웅덩이 확인
				if (map[nby][nbx] || map[ngy][ngx]) continue;
				//가시 확인
				if (abs(nby - ngy) <= 1 && abs(nbx - ngx) <= 1) continue;
				//종료조건
				if (nby == pos[1].y && nbx == pos[1].x && ngy == pos[3].y && ngx == pos[3].x) return cur.time + 1;

				q.push({ nby, nbx, ngy, ngx, cur.time + 1 });
				chk[nby][nbx][ngy][ngx] = true;
			}
		}
	}
	return -1;
}

void solve()
{
	cout << bfs();
}


int main()
{
	input();
	solve();
	return 0;
}