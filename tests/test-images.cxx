#include <graphics.h>

int main( )
{
    initwindow(400,600,"Podkayne of Mars");
    readimagefile("fries.gif", 40, 100, 340, 576);
    writeimagefile("copy.gif", 40, 100, 340, 576);
    writeimagefile( );
    printimage("Testing", 1.0);
    getch( );
}
