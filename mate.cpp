#include<iostream>
#include<vector>
using namespace std;

vector<vector<int> > mate;
vector<vector<int>> tmp_path;
vector<vector<int>> best_path;
int M, N;
void backtrace(int x,int y) {
	mate[x][y] = 0;            //走的路将不再重复去走
	tmp_path.push_back({ x,y });
	if(x==M-1 && y==N-1)                  //走出了迷宫
		if (best_path.empty() || tmp_path.size() < best_path.size())          //判断是否为最佳方案，也就是所走的步数最少
			best_path = tmp_path;
	if (x - 1 >= 0 && mate[x - 1][y] == 1)              //向上走
		backtrace(x - 1, y);
	if (x + 1 < M && mate[x + 1][y] == 1)        //向下走
		backtrace(x + 1, y);
	if (y - 1 >= 0 && mate[x][y - 1] == 1)           //向左走
		backtrace(x, y - 1);
	if (y + 1 < N && mate[x][y + 1] == 1)                //向右走
		backtrace(x, y + 1);
	mate[x][y] = 1;                      //恢复现场
	tmp_path.pop_back();           //弹出不能走的结点
}

int main() {
	cout << "please input row and col in mate: ";
	while (cin >> M >> N) {
		int i, j;
		cout << "please input the access and obstacle in mate: " << endl;
		mate = vector<vector<int>>(M, vector<int>(N, 0));
		for (i = 0; i < M; i++)
			for (j = 0; j < N; j++)
				cin >> mate[i][j];

		backtrace(0, 0);
		cout << "The best route is:  " << endl;
		for (int i = 0; i < best_path.size(); i++)
			cout << "(" << best_path[i][0] << "," << best_path[i][1] << ")" << endl;
		mate.clear();
		tmp_path.clear();
		best_path.clear();
		cout << "please input row and col in mate: ";
	}
	system("pause");
	return 0;
}