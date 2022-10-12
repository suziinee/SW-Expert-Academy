#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int N, M, K;

struct CELL {
	int y, x, life, time;
	bool operator<(const CELL& c) const {
		return time > c.time;
	}
};
priority_queue<CELL> pq;
priority_queue<int, vector<int>, greater<int>> pq_after; //번식 이후의 세포들 관리(죽는 시간 넣음)

inline long long int get_key(int a, int b) {
	return (long long)a * 100000 + (long long)b;
}
unordered_set<long long int> ht; //해당 좌표 사용되었는지 여부


int solve(int t)
{
	static int dx[] = { 0, 1, 0, -1 };
	static int dy[] = { -1, 0, 1, 0 };
	int die = 0;

	while (true) {
		//현재 time에서 새로 만들어지는 세포들 좌표
		unordered_map<long long int, CELL> born;

		//현재 활성상태 세포 꺼내서 번식하기
		while (!pq.empty() && pq.top().time == t) {
			CELL cur = pq.top(); pq.pop();
			pq_after.push(t + cur.life);

			for (int d = 0; d < 4; d++) {
				int nx = cur.x + dx[d];
				int ny = cur.y + dy[d];
				int key = get_key(ny, nx);
				if (ht.find(key) != ht.end()) continue; //다른 세포가 이미 번식한 자리
				if (born.find(key) == born.end()) {
					born.insert({ key, {ny, nx, cur.life, cur.life + t + 1} });
				}
				else {
					CELL& tmp = born[key];
					if (tmp.life < cur.life) {
						born[key] = { ny, nx, cur.life, cur.life + t + 1 }; //교체
					}
				}
			}
		}

		//번식 끝난 비활성 상태 중 현재 t에 죽은 세포들 꺼내기
		while (!pq_after.empty() && pq_after.top() == t) {
			pq_after.pop();
			die++;
		}

		++t;
		if (t > K) break;

		//새로 생성된 세포를 ht에 추가하기
		if (!born.empty()) {
			for (auto it = born.begin(); it != born.end(); it++) {
				ht.insert(it->first);
				pq.push(it->second);
			}
		}
	}

	return pq.size() + pq_after.size();
}

void input()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N >> M >> K;
		ht.clear();
		pq = {};
		pq_after = {};

		int n;
		int min_time = 11;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) {
				cin >> n;
				if (n) {
					pq.push({ y, x, n, n });
					ht.insert(get_key(y, x));
					if (n < min_time) min_time = n;
				}
			}
		}

		cout << "#" << t << " " << solve(min_time) << "\n";
	}
}


int main()
{
	input();
	return 0;
}