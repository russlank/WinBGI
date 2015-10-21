#include "graphics.h"
#include <iostream>
using namespace std;

int main(void)
{
   int wid1, wid2, wid3;

   /* initialize graphics windows */
   wid1 = initwindow(400, 300, " ");
   wid2 = initwindow(300, 400, "Second Window", 410, 100, false, false);
   wid3 = initwindow(300, 400, "", 600, 200, false, false);
   int x,y;
   
   /* draw pixels */
   setcurrentwindow(wid1);
   do {
       cin >> x >> y;
       clearviewport( );
       putpixel(x, y, WHITE);
   }   while (x);
   setcurrentwindow(wid2);
   do {
       cin >> x >> y;
       clearviewport( );
       putpixel(x, y, WHITE);
   }   while (x);
   setcurrentwindow(wid3);
   do {
       cin >> x >> y;
       clearviewport( );
       putpixel(x, y, WHITE);
   }   while (x);

   /* clean up */
   getch();
   while (!ismouseclick(WM_LBUTTONDOWN) || !ismouseclick(WM_LBUTTONUP))
       delay(100);
   getmouseclick(WM_LBUTTONUP, x, y);
   bgiout << x << " " << y;
   outstreamxy(20,20);
   delay(4000);
   closegraph();
   return 0;
}
