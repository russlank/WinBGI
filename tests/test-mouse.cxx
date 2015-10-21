/* mouse example */ 
#include <iostream>
#include "winbgim.h"
using namespace std;

int main(void)
{
    int maxx, maxy;  // Maximum x and y pixel coordinates
    int x, y;        // Coordinates of the mouse click
    int divisor;     // Divisor for the length of a triangle side

    // Put the machine into graphics mode and get the maximum coordinates:
    initwindow(450, 300);         
    setmousequeuestatus(WM_LBUTTONDOWN);
    maxx = getmaxx( );
    maxy = getmaxy( );

    // Draw a white circle with red inside and a radius of 50 pixels:
    setfillstyle(SOLID_FILL, RED);
    setcolor(WHITE);
    fillellipse(maxx/2, maxy/2, 50, 50);
    
    // Print a message and wait for a red pixel to be double clicked:
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(20, 20, "Left click several times!");
    setcolor(BLUE);
    divisor = 2;
    while (!ismouseclick(WM_LBUTTONDOWN))
    {
        delay(5000); // Five second delay, so there might be a several clicks
    }

    while (ismouseclick(WM_LBUTTONDOWN))
    {
        getmouseclick(WM_LBUTTONDOWN, x, y);
        cout << "The mouse was clicked at: ";
        cout << "x=" << x;
        cout << " y=" << y << endl;
    }
    
    // Switch back to text mode:
    closegraph( );
}
