#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAX 400
int N, M, K;
bool chk[MAX + 1][MAX + 1];

struct CELL {
	int y, x;
	int life, wait, turn;
	bool active;
	bool operator<(const CELL& c) const { //turn 오름차순, life 내림차순
		if (turn == c.turn) return life < c.life;
		return turn > c.turn;
	}
};
priority_queue<CELL> pq;


int solve()
{
	static int dx[] = { 0, 1, 0, -1 };
	static int dy[] = { -1, 0, 1, 0 };
	
	while (!pq.empty()) {
		CELL cur = pq.top(); pq.pop();

		if (cur.turn == K) {
			pq.push(cur);
			return pq.size();
		}

		//사방으로 번식 + cur의 생명력 줄어듦
		if (cur.active) {
			for (int d = 0; d < 4; d++) {
				int nx = cur.x + dx[d];
				int ny = cur.y + dy[d];
				if (chk[ny][nx]) continue;
				pq.push({ ny, nx, cur.life, cur.life, cur.turn + 1, false });
				chk[ny][nx] = true;
			}
			if (--cur.life > 0) { //생명력이 0이 아니면 사망한게 아니므로 다시 pq에 넣어줌
				cur.turn++;
				pq.push(cur);
			}
		}
		//대기시간 줄어듦
		else {
			if (--cur.wait == 0) {
				cur.active = true;
			}
			cur.turn++;
			pq.push(cur);
		}
	}
}

void input()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N >> M >> K;
		fill(&chk[0][0], &chk[MAX - 1][MAX], false);
		pq = {};
		int n;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) {
				cin >> n;
				if (n) {
					chk[y + MAX / 2][x + MAX / 2] = true;
					pq.push({ y + MAX / 2, x + MAX / 2, n, n, 0, false });
				}
			}
		}
		cout << "#" << t << " " << solve() << "\n";
	}
}


int main()
{
	input();
	return 0;
}