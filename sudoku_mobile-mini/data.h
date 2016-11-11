  #ifndef DATA_H
#define DATA_H

#include <ctime>
#include <cstring>
#include <algorithm>
using namespace std;

class Data {
public:
	Data();
	void newPuzzle(int blank);//挖掉空的数量为blank。
	int getPuzzle(int r, int c);//row,column,number,范围：从1到9,注意，挖掉的空返回值为0
	void setUserAns(int r, int c, int n);
	bool checkUserAns(void);//使用之前先setUserAns
	int getAns(int r, int c);

private:
	bool isexist(int(*a)[10], int r, int c, int n);
	bool fillnum(int(*a)[10], int r, int c);
	void randomrow(int(*a)[10], int r);
	void randomSwapPuzzle(int(*a)[10]);
	void swapColumn(int(*a)[10], int m, int n);


	int a[10][10];//newPuzzleData
	int b[10][10];//newPuzzleData（挖掉空的）
	int c[10][10];//userData


};

#endif // DATA_H
