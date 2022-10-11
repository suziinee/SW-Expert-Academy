#include <iostream>
#include <queue>
using namespace std;

#define MAXN 50
int N, M, R, C, L;
int map[MAXN][MAXN];
bool chk[MAXN][MAXN];

int pipe_lut[8][4];
int dir_pipe[4][8];

struct STATUS { int y, x, time; };
queue<STATUS> q;


void init()
{
	pipe_lut[1][0] = 1;
	pipe_lut[1][1] = 1;
	pipe_lut[1][2] = 1;
	pipe_lut[1][3] = 1;
	pipe_lut[2][0] = 1;
	pipe_lut[2][2] = 1;
	pipe_lut[3][1] = 1;
	pipe_lut[3][3] = 1;
	pipe_lut[4][0] = 1;
	pipe_lut[4][1] = 1;
	pipe_lut[5][1] = 1;
	pipe_lut[5][2] = 1;
	pipe_lut[6][2] = 1;
	pipe_lut[6][3] = 1;
	pipe_lut[7][0] = 1;
	pipe_lut[7][3] = 1;

	dir_pipe[0][1] = 1;
	dir_pipe[0][2] = 1;
	dir_pipe[0][5] = 1;
	dir_pipe[0][6] = 1;
	dir_pipe[1][1] = 1;
	dir_pipe[1][3] = 1;
	dir_pipe[1][6] = 1;
	dir_pipe[1][7] = 1;
	dir_pipe[2][1] = 1;
	dir_pipe[2][2] = 1;
	dir_pipe[2][4] = 1;
	dir_pipe[2][7] = 1;
	dir_pipe[3][1] = 1;
	dir_pipe[3][3] = 1;
	dir_pipe[3][4] = 1;
	dir_pipe[3][5] = 1;
}

int bfs()
{
	static int dx[] = { 0, 1, 0, -1 };
	static int dy[] = { -1, 0, 1, 0 };

	int ret = 0;
	q.push({ R, C, 1 }); //좌표, time
	chk[R][C] = true;
	ret++;

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();
		if (cur.time == L) continue;

		for (int d = 0; d < 4; d++) {
			int nx = cur.x + dx[d];
			int ny = cur.y + dy[d];
			if (nx < 0 || ny < 0 || nx >= M || ny >= N) continue;
			if (map[ny][nx] == 0 || chk[ny][nx]) continue;
			if (pipe_lut[map[cur.y][cur.x]][d] && dir_pipe[d][map[ny][nx]]) {
				q.push({ ny, nx, cur.time + 1 });
				chk[ny][nx] = true;
				ret++;
			}
		}
	}

	return ret;
}

void input()
{
	int T;
	cin >> T;
	init();
	for (int t = 1; t <= T; t++) {
		cin >> N >> M >> R >> C >> L;
		fill(&map[0][0], &map[MAXN - 1][MAXN], 0);
		fill(&chk[0][0], &chk[MAXN - 1][MAXN], false);
		q = {};

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) {
				cin >> map[y][x];
			}
		}
		
		cout << "#" << t << " " << bfs() << "\n";
	}
}


int main()
{
	input();
	return 0;
}