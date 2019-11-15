#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define INF 2e9
#pragma warning(disable:4996)
using namespace std;
typedef struct _NODE { int x, y; } NODE;
int N, total_sum = 0, ans = INF;
int A[101][101];
int dx[2] = { 1, 1 };
int dy[2] = { -1, 1 };
bool v[101][101];
NODE U, R, L, D;
bool is_out(int x, int y) { return x < 1 || x > N || y < 1 || y > N; }
void solve()
{
	int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0;
	int gmax = -INF, gmin = INF;
	for (int i = 1; i < L.x; i++) {
		for (int j = 1; j <= (i < U.x ? U.y : U.y - (i - U.x) - 1); j++) sum1 += A[i][j];
	}
	gmax = max(gmax, sum1), gmin = min(gmin, sum1);

	for (int i = 1; i <= R.x; i++) {
		for (int j = (i <= U.x ? U.y + 1 : U.y + 1 + (i - U.x)); j <= N; j++) sum2 += A[i][j];
	}
	gmax = max(gmax, sum2), gmin = min(gmin, sum2);

	for (int i = L.x; i <= N; i++) {
		for (int j = 1; j < (i >= D.x ? D.y : L.y + i - L.x); j++) sum3 += A[i][j];
	}
	gmax = max(gmax, sum3), gmin = min(gmin, sum3);
	
	for (int i = R.x + 1; i <= N; i++) {
		for (int j = (i > D.x ? D.y : R.y - (i - R.x) + 1); j <= N; j++) sum4 += A[i][j];
	}
	gmax = max(gmax, sum4), gmin = min(gmin, sum4);

	sum5 = total_sum - sum1 - sum2 - sum3 - sum4;
	gmax = max(gmax, sum5), gmin = min(gmin, sum5);
	ans = min(ans, gmax - gmin);
}
int main()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &A[i][j]);
			total_sum += A[i][j];
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			U.x = i, U.y = j;
			for (int l = 1; l <= N; l++) {
				for (int r = 1; r <= N; r++) {
					if (i + l + r > N) continue;
					L.x = U.x + (l * dx[0]), L.y = U.y + (l * dy[0]);
					R.x = U.x + (r * dx[1]), R.y = U.y + (r * dy[1]);
					D.x = L.x + (r * dx[1]), D.y = L.y + (r * dy[1]);
					if (is_out(R.x, R.y) || is_out(L.x, L.y) || is_out(D.x, D.y)) continue;
					solve();
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}