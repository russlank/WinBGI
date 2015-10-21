#include <graphics.h>
#include <iostream>
using namespace std;

int main( )
{
    initwindow(300,300);
    
    setcolor(BLUE);             // Change drawing color to BLUE.
    setcolor(COLOR(255,120,0)); // Change drawing color to reddish-green.
    setpalette(4, BLUE);        // Change palette entry 4 to BLUE.
    setpalette(4, COLOR(9,9,9));// Change palette entry 4 to nearly black.
     
    int current = getcolor( );  // Set current to current drawing color.
    
    if (IS_BGI_COLOR(current))  // Check whether it is a BGI color.
       cout << "Current BGI drawing color is: " << current << endl;

    if (IS_RGB_COLOR(current))  // Check whether it is an RGB color.
       cout << "Current RGB drawing color has these components:\n"
            << "Red:   " << RED_VALUE(current)   << '\n'
            << "Green: " << GREEN_VALUE(current) << '\n'
            << "Blue:  " << BLUE_VALUE(current)  << '\n';

    cout << "The usual Windows RGB color int value is:\n"
         << converttorgb(current) << endl;

    return 0;
}
