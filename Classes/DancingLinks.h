#ifndef __DANCINGLINKS_H__
#define __DANCINGLINKS_H__

#include <iostream>
#include <ctime>
using namespace std;

const int N = 5000;

class DLX {
private:
	//-------------------- Dancing links Start ----------------------------
	int n, m;
	int to[800][3];
	int L[N], R[N], U[N], D[N]; //左右上下
	int C[N], H[N]; //C[i],H[i]表示i对应的哪一列,哪一行
	int row[N];
	int S[N]; //列链表中节点的总数
	int O[N]; //记录答案
	int head, num; //head, num为总节点数(即1的总个数)
	void remove(int c) { //删除第c列
		L[R[c]] = L[c]; R[L[c]] = R[c];
		for (int i = D[c]; i != c; i = D[i]) { //删除对应c列有1的行
			for (int j = R[i]; j != i; j = R[j]) {
				U[D[j]] = U[j]; D[U[j]] = D[j];
				S[C[j]]--;
			}
		}
	}
	void resume(int c) { //恢复第c列
		for (int i = U[c]; i != c; i = U[i]) { //恢复c对应的有1的行
			for (int j = L[i]; j != i; j = L[j]) {
				U[D[j]] = j; D[U[j]] = j;
				S[C[j]]++;
			}
		}
		L[R[c]] = c; R[L[c]] = c;
	}
	bool dfs(int k)  {
		if (R[head] == head) { //全部填完 , 找到一个解
			if (++cnt > 1) return 1; //多解
			//记录数独的一个解
			for (int i = 1; i <= 9; i++)
			for (int j = 1; j <= 9; j++) ans[i][j] = g[i][j];
			return 0;
		}
		int s = 99999999, c; //找1最少的列对应的第一个1的位置i
		for (int i = R[head]; i != head; i = R[i])
		if (S[i] < s) s = S[i], c = i;

		remove(c); //删除c对应的列
		for (int i = D[c]; i != c; i = D[i]) {
			//O[k]=i;
			int x = to[row[i]][0], y = to[row[i]][1], z = to[row[i]][2];
			g[x][y] = z;
			for (int j = R[i]; j != i; j = R[j]) remove(C[j]); //删除那一行有1的列
			if (dfs(k + 1)) return 1;
			for (int j = L[i]; j != i; j = L[j]) resume(C[j]); //恢复那一行有1的列
		}
		resume(c); //恢复c对应的列
		return 0;
	}
	void addedge(int r, int c) {
		num++;
		U[num] = U[c]; D[U[c]] = num;  //老的最后行指向新的最后行
		U[c] = num; D[num] = c;   //新的最后行指向列首

		if (H[r] == -1) H[r] = L[num] = R[num] = num; //行的第一个1
		else { //插入到行列表中
			L[num] = L[H[r]]; R[num] = H[r];
			R[L[H[r]]] = num; L[H[r]] = num;
		}
		C[num] = c;   //列指针,表示num所在的列
		row[num] = r;   //行指针,表示num所在的行
		S[c]++;     //相应的列1的个数++
	}
	void init() {
		head = 0;
		memset(H, -1, sizeof(int)*(n + 1));
		for (int i = 0; i <= m; i++) {
			U[i] = i; D[i] = i;
			L[i + 1] = i; R[i] = i + 1;
			S[i] = 0; C[i] = i;
		}
		L[0] = m; R[m] = 0;
		num = m;
	}
	//-------------------- Dancing links End ----------------------------

public:
	DLX() {
		int t = 0;
		n = 9 * 9 * 9;
		m = (9 + 9 + 9) * 9 + 81;
		for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++)
		for (int k = 1; k <= 9; k++)
			to[++t][0] = i, to[t][1] = j, to[t][2] = k;
	}

	int g[10][10]; //初始盘面
	int ans[10][10]; //数独解
	int cnt; //记录解的个数

	//建立数独DLX
	void build(int _g[10][10]) {
		cnt = 0; //初始化解的个数
		init();

		for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++) g[i][j] = _g[i][j];

		int nn = 0;
		for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++) {
			for (int k = 1; k <= 9; k++) {
				nn++;
				if (g[i][j] == 0 || g[i][j] == k) { //未确定 或是 确定的数字
					addedge(nn, (i - 1) * 9 + k);
					addedge(nn, 9 * 9 + (j - 1) * 9 + k);
					addedge(nn, 9 * 9 + 9 * 9 + ((i - 1) / 3 * 3 + (j - 1) / 3) * 9 + k);
					addedge(nn, 9 * 9 + 9 * 9 + 9 * 9 + (i - 1) * 9 + j);
				}
			}
		}
	}

	//解数独
	void solve(int _g[10][10]) {
		build(_g);
		dfs(0);
	}
};


#endif // __DANCINGLINKS_H__
