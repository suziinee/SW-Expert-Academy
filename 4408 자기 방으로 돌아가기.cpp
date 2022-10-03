#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int N;
struct STATUS {
	int st;
	int en;
	bool operator<(const STATUS& s) const {
		if (st == s.st) return en > s.en;
		return st > s.st;
	}
};
priority_queue<STATUS> pq;


int solve()
{
	int cnt = 0; //이동한 학생 수
	int ans = 0;
	vector<STATUS> stor;
	
	while (cnt < N) {
		stor.clear();
		ans++;

		int end = pq.top().en;
		cnt++;
		pq.pop();

		while (!pq.empty()) {
			STATUS cur = pq.top(); pq.pop();

			if (end % 2) { //end, end+1 
				if (cur.st > end + 1) {
					end = cur.en;
					cnt++;
				}
				else { 
					stor.push_back(cur);
				}
			}
			else { //end-1, end 
				if (cur.st > end) { 
					end = cur.en;
					cnt++;
				}
				else { 
					stor.push_back(cur);
				}
			}
		}

		for (STATUS s : stor) pq.push(s);
	}
	
	return ans;
}

void input()
{
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		
		//초기화
		pq = {};

		cin >> N;
		int st, en;
		for (int i = 0; i < N; i++) {
			cin >> st >> en;
			if (st <= en) pq.push({ st, en });
			else pq.push({ en, st });
		}
		
		int ret = solve();
		cout << "#" << t + 1 << " " << ret << "\n";
	}
}


int main()
{
	input();
	return 0;
}
 