#include <iostream>
#include <cstdio>
#include <memory.h>
 
using namespace std;
 
// 城市数
int citiesNum = 0;
 
int indexs = 1;
 
// 城市是否重要
bool cut[100]; // 是否为切点
 
// 图储存
int line[100]; // 节点的最后一条线段
int nextl[10000]; // 线段的邻线段
int to[10000]; // 线段目标节点
 
// 搜索相关
int dfn[100] = {0};// 搜索ID
int tag[100] = {0}; // 强连通标签
bool alive[10000]; // 线段是否可用（未访问过）
 
int rootSingle = -1;
 
// 函数声明
int dfs (int);
 
int main () {
 
	// 重定向IO
	freopen("gd.in", "r", stdin);
	freopen("gd.out", "w", stdout);
 
	cin >> citiesNum;
 
	// 元素初始化 -1为空
	memset(line, -1, sizeof(line));
	memset(dfn, 0, sizeof(dfn));
	memset(to, -1, sizeof(to));
	memset(nextl, -1, sizeof(nextl));
 
	// 构图
	int ca, cb;
	for (int i = 0; !cin.eof(); i += 2) {
		// 双（无）向边存储存图
 
		cin >> ca >> cb;
		// cout << "Get " << ca << " " << cb << endl;
		ca--;cb--;
		if(line[ca] != -1)
			nextl[i] = line[ca];
		line[ca] = i;
		to[i] = cb;
		if(line[cb] != -1)
			nextl[i+1] = line[cb];
		line[cb] = i+1;
		to[i+1] = ca;
		alive[i] = true;
		alive[i+1] = true;
		if (ca == 0 || cb == 0) {
			// cout << "RootSingle++" << endl;
			rootSingle++;
		}
	}
 
	// for (int i = 0; i < 10000; i++) {
	// 	cout << i << "\t" << to[i] << "\t" << nextl[i] << endl;
	// }
 
	dfs(0);
 
	// for (int i = 0; i < citiesNum; i++) {
	// 	cout << i+1 << "\t" << dfn[i] << "\t" << tag[i] << endl;
	// }
 
	// cout << rootSingle << " ";
 
	int counter = 0;
	string listing;
	for (int i = 0; i < citiesNum; i++) {
		if (cut[i] == true) {
			counter++;
		}
	}
	cout << counter << endl;
	for (int i = 0; i < citiesNum; i++) {
		if (cut[i] == true) {
			cout << i + 1 << endl;
		}
	}
	
	return 0;
}
 
// tarjan搜索主循环
int dfs (int node) {
 
	// cout << "Enter " << node + 1 << endl;
	if(dfn[node] == 0) {
 
		dfn[node] = indexs;
		tag[node] = indexs;
		indexs++;
 
		// cout << " - entered" << " indexd " << dfn[node] << endl;
		int l;
		while ((l = line[node]) != -1) {
			line[node] = nextl[l];
			if (alive[l]) {
				alive[l] = false;
				if (to[l+1] == node)
					alive[l+1] = false;
				else
					alive[l-1] = false;
				// cout << " - Goto " << to[l] + 1 << endl;
				int childTag = dfs(to[l]);
				if (tag[node] > childTag)
					tag[node] = childTag;
				if (childTag >= dfn[node]) {
					if (node != 0) {
						cut[node] = true;
					} else {
						if (rootSingle > 0) {
							if (childTag > dfn[0])
							cut[0] = true;
						}
					}
				}
			}
		}
	}
 
	// cout << "left " << node + 1 << "return" << tag[node] << endl;
 
	return tag[node];
 
}