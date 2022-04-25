#include <iostream>
#include <cstring>
#include <graphics.h>
#include <windows.h>
#include <stdio.h>
using namespace std;

int n = 8, mat[8][8], moves[63];
int korI[8]={2,1,-1,-2,-2,-1,1,2};
int korJ[8]={1,2,2,1,-1,-2,-2,-1};
//int korI[8]={-2,-2,2,2,-1,-1,1,1};
//int korJ[8]={-1,1,-1,1,-2,2,-2,2};


void drawline(float x, float y, float x1, float y1) {
    line(150+(800.0/n)*x, 150+(800.0/n)*y, 150+(800.0/n)*x1, 150+(800.0/n)*y1);
}

void flood(float x, float y) {
    setfillstyle(SOLID_FILL, 3);
    floodfill(150+(800.0/n)*x, 150+(800.0/n)*y, 4);
}

bool validMove(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n && mat[x][y] == -1;
}

bool solve(int ii, int jj, int currIdx) {
    if(currIdx == 64)
        return true;
    for(int rr = 0; rr < 8; rr++) {
        int i = ii + korI[rr], j = jj + korJ[rr];
        if (validMove(i, j)) {
            mat[i][j] = currIdx;
            moves[currIdx] = rr;
            if(solve(i, j, currIdx+1))
                return true;
            mat[i][j]=-1;
        }
    }
    return false;
}

int main() {
    //ios_base::sync_with_stdio(0);
    memset(mat,-1,sizeof(mat));

    int i, j;
    DWORD weight = GetSystemMetrics(SM_CXSCREEN);
    DWORD height = GetSystemMetrics(SM_CYSCREEN);
    initwindow(1000, 1000, "KNIGHT'S TOUR", weight/2-500, 0);

    // table
	setcolor(4);
	for(i = 0; i < n+1; i++) {
		drawline(i-0.5, -0.5, i-0.5, n-0.5);
		drawline(-0.5, i-0.5, n-0.5, i-0.5);
	}

	for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            flood(i, j);

        }
	}

    int ii,jj;
    cin>>ii>>jj;
    mat[ii][jj]=0;
    if (solve(ii,jj,1)) {
        for(int i = 0;i < n; i++) {
            for(int j = 0; j < n; j++)
                cout<<mat[i][j]+1<<"\t";
            cout<<"\n";
        }
    }
    else
        cout<<"Impossible\n";

    setcolor(14);
    int xx = ii, yy = jj;
    for(i = 1; i < 64; i++) {
        setcolor(14);
        int x = xx + korI[moves[i]], y = yy + korJ[moves[i]];

        drawline(yy, xx, y, x);

        char step1[2];
        sprintf(step1, "%d", i);
        setcolor(12);
        outtextxy(150+(800.0/n)*yy, 150+(800.0/n)*xx, step1);

        xx = x; yy = y;
        char step2[2];
        sprintf(step2, "%d", i+1);
        setcolor(12);
        outtextxy(150+(800.0/n)*yy, 150+(800.0/n)*xx, step2);

        delay(500);
    }

    setcolor(12);
    outtextxy(150+(800.0/n)*yy, 150+(800.0/n)*xx, "64");

    getch();
    closegraph();

    return 0;
}
