#include <graphics.h>
#include <iostream>
using namespace std;

int main( )
{
    initwindow(400, 300);
    setbkcolor(YELLOW);
    setfillstyle(EMPTY_FILL, RED);
    fillellipse(200, 150, 50, 90);
    while (!ismouseclick(WM_LBUTTONUP))
    {
	cout << mousex( ) << " " << mousey( ) << endl;
	delay(300);
    }
    return 0;
}
