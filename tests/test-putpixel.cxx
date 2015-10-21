#include <graphics.h>
#include <iostream>
using namespace std;

const int WINSIZE=1000;

int main( )
{
    int i,j;
    
    initwindow(WINSIZE, WINSIZE);
    bgiout << "What's up?" << endl;
    bgiout << "Hello " << 42000;
    outstreamxy(30, 30);
    bgiout << "Bye." << endl;
    outstreamxy(150, 150);
    while (!kbhit())
	delay(1000);
    getch( );

    for (i = 0; i < WINSIZE; ++i)
	for (j = 0; j < WINSIZE; ++j)
	    putpixel(i,j,(i+j)%16);
    while (!kbhit())
	delay(1000);
    
    return 0;
}
