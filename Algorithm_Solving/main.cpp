#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;
typedef struct _NODE { int x, y; } NODE;

int N, tsum = 0, A[21][21];
int dx[4] = { -1, 1, 1, -1 };
int dy[4] = { 1, 1, -1, -1 };
int rev[4] = { 2, 3, 0, 1 };
NODE U, R, L, D;
void calc()
{
	int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5;
	sum5 = tsum - sum1 - sum2 - sum3 - sum4;
}
void find_rect(int x, int y, int dir)
{
	int tx, ty;
	if (tx < 0 || tx > N - 1 || ty < 0 || ty > N - 1) return;
	if (x == U.x && y == U.y) {
		return;
	}
	tx = x + dx[dir], ty = y + dy[dir];
	find_rect(tx, ty, 2), L.x = tx, L.y = ty;
	find_rect(tx, ty, 1), D.x = tx, D.y = ty;
	find_rect(tx, ty, 0), R.x = tx, R.y = ty;
	find_rect(tx, ty, 3);
}
int main()
{
	int val;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", val);
			A[i][j] = val, tsum += val;
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			U.x = i, U.y = j, find_rect(i, j, 2);
		}
	}
	return 0;
}