#include <iostream>
using namespace std;

void print(int *c, int n) {
    printf("Solution of %d queen:\n", n);
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (col != 0) putchar(' ');
            cout << (col == c[row] ?"*" : "-");
        }
        cout << endl;
    }
    cout << endl;
}

bool canPlaceQueen(int *c, int n, int row, int col) {
    for (int i = 0; i < row; i++) {       
        if (c[i] == col) return false;        
        if (col - c[i] == row - i) return false;
        if (col - c[i] == i - row) return false;
    }
    return true;
}

void queen(int *c, int n, int row) {
    if (row == n) {
        print(c, n);
        return;
    }
    for (int col = 0; col < n; col++) {
        if (canPlaceQueen(c, n, row, col)) {
            c[row] = col;
            queen(c, n, row + 1);
        }
    }
}


void n_queen(int n) {
    int * c = new int[n];
    queen(c, n, 0);
    free(c);
}

int main()
{
    int n;
    while (cin >> n) {
        if (n == 0) break;
        n_queen(n);
    }
    return 0;
}
