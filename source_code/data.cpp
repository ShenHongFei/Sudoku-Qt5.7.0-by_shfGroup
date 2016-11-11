#include "data.h"

Data::Data() {
	srand(static_cast<unsigned int>(time(0)));
}

bool Data::isexist(int(*a)[10], int r, int c, int n) {
	bool e = 0;
	for (int i = 1; i < c; ++i) {
		if (a[r][i] == n) {
			e = 1;
			break;
		}
	}
	if (e == 0) {
		for (int i = 1; i < r; ++i) {
			if (a[i][c] == n) {
				e = 1;
				break;
			}
		}
	}
	if (e == 0) {
		int gmr = (r - 1) / 3 * 3 + 1;//gong minimum row
		int gmc = (c - 1) / 3 * 3 + 1;//gong minimum column
		for (int i = gmr; i < gmr + 3; ++i) {
			for (int j = gmc; j < gmc + 3; ++j) {
				if (!(i==r&&j==c)&&a[i][j] == n) {
					e = 1;
				}
			}
		}
	}
	return e;
}

bool Data::fillnum(int(*a)[10], int r, int c) {
	if (r > 9 || c > 9) {
		return 1;
	}
	for (int i = 1; i <= 9; ++i) {
		int e = isexist(a, r, c, i);
		if (e) {
			continue;
		} else {
			a[r][c] = i;
			if (c == 9) {
				if (fillnum(a, r + 1, 1)) {
					return 1;
				} else {
					a[r][c] = 0;
					continue;
				}
			} else {
				if (fillnum(a, r, c + 1)) {
					return 1;
				} else {
					a[r][c] = 0;
					continue;
				}
			}
		}
	}
	return 0;
}

void Data::randomrow(int(*a)[10], int r) {
	for (int i = 1; i <= 9; ++i) {
		a[r][i] = i;
	}
	random_shuffle(&a[r][1], &a[r][10]);
}

void Data::newPuzzle(int blank) {
	memset(a, 0, sizeof(int) * 100);
	randomrow(a, 1);
	fillnum(a, 2, 1);
	randomSwapPuzzle(a);
	memcpy(b, a, sizeof(int) * 100);
	for (int i = 0; i < blank; i++) {
		b[rand() % 9 + 1][rand() % 9 + 1] = 0;
	}
}

int Data::getPuzzle(int r, int c) {
	return b[r][c];
}

void Data::setUserAns(int r, int c, int n) {
    Data::c[r][c] = n;
}

bool Data::checkUserAns(void) {
	bool ok = 1;
	for (int i = 1; i <= 9; ++i) {
		for (int j = 1; j <= 9; ++j) {
			if (isexist(c, i, j, c[i][j]) == 1) ok = 0;
            if (c[i][j] == 0) ok = 0;
		}
	}
	return ok;
}

int Data::getAns(int r, int c) {
	return a[r][c];
}

void Data::randomSwapPuzzle(int(*a)[10]) {
	const int swapColumnTimes = 10;
	//swap column
	for (int c = 0; c < swapColumnTimes; ++c) {
		int p = rand() % 3 * 3 + 1;
		int m = p + rand() % 3;
		int n = p + rand() % 3;
        swapColumn(a, m, n);
	}
	//swap blocks
	int p = rand() % 3 * 3 + 1;
	if (p == 1 || p == 4) {
		swapColumn(a, p, p + 3);
		swapColumn(a, p + 1, p + 4);
		swapColumn(a, p + 2, p + 5);
	} else {
		swapColumn(a, p, p -6);
		swapColumn(a, p + 1, p -5);
		swapColumn(a, p + 2, p -4);
	}
}

void Data::swapColumn(int(*a)[10], int m, int n) {
	int t[10];
	for (int i = 1; i <= 9; ++i) {
		t[i] = a[i][m];
	}
	for (int i = 1; i <= 9; ++i) {
		a[i][m] = a[i][n];
	}
	for (int i = 1; i <= 9; ++i) {
		a[i][n] = t[i];
	}

}
