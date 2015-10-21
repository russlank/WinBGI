#include <graphics.h>

int main(void)
{
   int big;
   int w, w_right, w_below ;
   int width, height; // Total width and height of w_left;
   
   big = initwindow(getmaxwidth( ), getmaxheight( ), "Big");   
   w = initwindow(300, 200, "Top/Left Corner");
   width = getwindowwidth( );
   height = getwindowheight( );
   w_right = initwindow(300, 200, "Right", width, 0);
   w_below = initwindow(300, 200, "Below", 0, height);

   /* clean up */
   getch();
   closegraph();
   return 0;
}
