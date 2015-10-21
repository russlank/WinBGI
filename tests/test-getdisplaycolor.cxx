#include <graphics.h>
#include <iostream>
using namespace std;

int main(void)
{
   int r, g, b; // Components of r, g and b for a color.
   int color_request, color_actual;

   /* initialize graphics window */
   initwindow(300, 300);

   /* Get a user-defined color */
   cout << "Please enter amounts of red, green and blue: ";
   cin >> r >> g >> b;

   /* Compute what this color will display as. */
   color_request = COLOR(r, g, b);
   color_actual = getdisplaycolor(color_request);
   if (IS_BGI_COLOR(color_actual))
   {
      cout << "That will display as BGI color number " << color_actual << endl;
   }
   else
   {
       cout << "That color will display on this machine with components:\n"
	    << "Red:   " << RED_VALUE(color_actual)   << '\n'
            << "Green: " << GREEN_VALUE(color_actual) << '\n'
            << "Blue:  " << BLUE_VALUE(color_actual)  << '\n';
   }
}
