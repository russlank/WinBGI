#include <winbgim.h>
#include <iostream>

void flood(int x, int y, int color);

int main( )
{
    int WSIZE = 1000;
    initwindow(WSIZE, WSIZE);
    for (int k = 1; k < 1000000; k++)
    {
	for (int i = 0; i < WSIZE; ++i)
	{
	    for (int j = 0; j < WSIZE; ++j)
	    {
		putpixel(j, i, (k % 16));
	    }
	}
	std::cout << k << std::endl;
    }
    // flood(150, 150, WHITE);
    delay(20000);
}

void flood(int x, int y, int color)
{
    if (x < 0 || x > getmaxx() || y < 0 || y > getmaxy())
	return;

    if (getpixel(x,y) != color)
    {
	putpixel(x, y, color);
	flood(x+1, y, color);
	flood(x-1, y, color);
	flood(x, y+1, color);
	flood(x, y-1, color);
    }
}
