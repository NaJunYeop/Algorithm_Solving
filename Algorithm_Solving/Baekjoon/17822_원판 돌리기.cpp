#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;
int N, M, T, tsum = 0, tnum = 0, disk[51][51];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
void revision()
{
	if (tnum == 0) return;
	double num, mean = tsum / (double)tnum;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			if (disk[i][j] > 0) {
				num = (double)disk[i][j];
				if (num < mean) disk[i][j]++, tsum++;
				else if (num > mean) disk[i][j]--, tsum--;
			}
		}
	}
}
bool elimination()
{
	int x, y, tx, ty, num, cnt;
	bool ret = false;
	queue< pair< int, int > > q;

	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			num = disk[i][j];
			if (num > 0) {
				cnt = 1, disk[i][j] = 0, q.push({ i, j });
				while (!q.empty()) {
					x = q.front().first, y = q.front().second, q.pop();
					for (int d = 0; d < 4; d++) {
						tx = x + dx[d], ty = y + dy[d];
						if (tx < 1 || tx > N) continue;
						if (ty > M - 1) ty = 0;
						else if (ty < 0) ty = M - 1;
						if (disk[tx][ty] != num) continue;
						cnt++, disk[tx][ty] = 0, q.push({ tx, ty });
					}
				}
				if (cnt > 1) ret = true, tsum -= (cnt * num), tnum -= cnt;
				else disk[i][j] = num;
			}
		}
	}
	return ret;
}
void rotate(int idx, int dir, int k)
{
	int tmp;
	
	if (dir == 0) {
		for (int t = 1; t <= N; t++) {
			if (t % idx == 0) {
				for (int i = 0; i < k; i++) {
					tmp = disk[t][M - 1];
					for (int j = M - 1; j > 0; j--) disk[t][j] = disk[t][j - 1];
					disk[t][0] = tmp;
				}
			}
		}
	}
	else {
		for (int t = 1; t <= N; t++) {
			if (t % idx == 0) {
				for (int i = 0; i < k; i++) {
					tmp = disk[t][0];
					for (int j = 0; j < M - 1; j++) disk[t][j] = disk[t][j + 1];
					disk[t][M - 1] = tmp;
				}
			}
		}
	}
	if (!elimination()) revision();
}
int main()
{
	int idx, dir, k;

	scanf("%d %d %d", &N, &M, &T);
	tnum = N * M;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &disk[i][j]);
			tsum += disk[i][j];
		}
	}
	for (int t = 1; t <= T; t++) {
		scanf("%d %d %d", &idx, &dir, &k);
		rotate(idx, dir, k % M);
		if (tsum == 0) break;
	}
	printf("%d\n", tsum);
	return 0;
}