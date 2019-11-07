#include <cstdio>
#include <cstring>
#include <vector>
#pragma warning(disable:4996)
using namespace std;
typedef struct _NODE { int x, y, dir; } NODE;
int N, K;
int dx[5] = { 0, 0, 0, -1, 1 };
int dy[5] = { 0, 1, -1, 0, 0 };
int rev[5] = { 0, 2, 1, 4, 3 };
int map[13][13];
vector< int > order[13][13];
NODE horse[11];
bool is_out(int x, int y) { return x < 1 || x > N || y < 1 || y > N; }
int solve()
{
	int x, y, tx, ty, dir, idx, cnt = 0;
	vector< int > vec;
	while (1) {
		cnt++;
		if (cnt > 1000) return -1;
		for (int i = 1; i <= K; i++) {
			vec.clear();
			x = horse[i].x, y = horse[i].y, dir = horse[i].dir;
			tx = x + dx[dir], ty = y + dy[dir];
			for (int j = 0; j < order[x][y].size(); j++) {
				if (order[x][y][j] == i) {
					idx = j;
					break;
				}
			}
			for (int j = idx; j < order[x][y].size(); j++) {
				vec.push_back(order[x][y][j]);
				order[x][y].erase(order[x][y].begin() + j), j--;
			}
			if (is_out(tx, ty) || map[tx][ty] == 2) {
				dir = rev[dir], tx = x + dx[dir], ty = y + dy[dir];
				horse[i].dir = dir;
				if (is_out(tx, ty) || map[tx][ty] == 2) {
					for (int j = 0; j < vec.size(); j++) order[x][y].push_back(vec[j]);
					continue;
				}
			}
			if (map[tx][ty] == 0) {
				for (int j = 0; j < vec.size(); j++) {
					idx = vec[j];
					horse[idx].x = tx, horse[idx].y = ty;
					order[tx][ty].push_back(idx);
				}
			}
			else if (map[tx][ty] == 1) {
				for (int j = vec.size() - 1; j > -1; j--) {
					idx = vec[j];
					horse[idx].x = tx, horse[idx].y = ty;
					order[tx][ty].push_back(idx);
				}
			}
			if (order[tx][ty].size() >= 4) return cnt;
		}
	}
}
int main()
{
	int x, y, dir;
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	for (int i = 1; i <= K; i++) {
		scanf("%d %d %d", &x, &y, &dir), horse[i].x = x, horse[i].y = y, horse[i].dir = dir, order[x][y].push_back(i);
	}
	printf("%d\n", solve());
	return 0;
}