#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
//#include <ccytype>

using namespace std;

int main(void)
{
    int n, nn,  x, y;
    initwindow (1000, 1000);
    void setcolor(int color);

    while (true)
    {
	delay(500);
	cleardevice( );
	for (nn = 1; nn  < 1000; nn  = nn + 200){
	    for (n = 2; n < 1000; n = n + 10) {
		circle(n, nn, 200);
		//delay (1);
	    }
	}
    }

    while (!kbhit())
	delay (100);
}

