// fractal.cxx
// Program to draw the Mandelbrot fractal.

#include <graphics.h> // Provides the winbgim library
#include <cctype>     // Provides toupper function
#include <iostream>   // Provides cin and cout
#include <complex>    // Provides the complex type
using namespace std;

// Constant declarations
const int WINDOW_SIZE = 600; // Width and height of the window in pixels
const double RADIUS = 2.0;   // Radius of the circle that defines the in group
const int MANY_COLORS = 47;  // Number of colors in the table
const int TABLE[MANY_COLORS][3] = {
    {   0,   0,   0},  // Black
    {   0,   0,   0},  // Real Dark Green
    {   0,   0,   0},  // Dark Green
    {  20,  20, 200},  // Blue
    { 130, 130, 235},  // Light Blue
    { 200, 200,  20},  // Yellow
    { 252, 252,  84},  // Yellow
    { 252, 252,  84},  // Yellow
    { 252, 252,  84},  // Yellow
    {   0,   0,   0},  // Black
    { 255,   0,   0},  // Red
    { 255,   0,   0},  // Red
    { 255,   0,   0},  // Red
    { 255,   0,   0},  // Red
    { 255,   0,   0},  // Red
    { 255,   0,   0},  // Red
    { 255,   0,   0},  // Red
    { 255,   0,   0},  // Red
    { 255,   0,   0},  // Red
    { 255,   0,   0},  // Red
    { 255,   0,   0},  // Red
    { 255,  60,   0},  // Orange
    { 255,  60,   0},  // Orange
    { 255,  60,   0},  // Orange
    { 255,  60,   0},  // Orange
    { 255,  60,   0},  // Orange
    { 255,  60,   0},  // Orange
    { 255,  60,   0},  // Orange
    { 255,  60,   0},  // Orange
    { 255,  60,   0},  // Orange
    { 255,  60,   0},  // Orange
    { 255,  60,   0},  // Orange
    {  20,  20, 200},  // Blue
    { 230, 230, 255},  // Light Blue
    {  20,  20, 200},  // Blue
    { 230, 230, 255},  // Light Blue
    {  20,  20, 200},  // Blue
    { 230, 230, 255},  // Light Blue
    {  20,  20, 200},  // Blue
    { 230, 230, 255},  // Light Blue
    {  20,  20, 200},  // Blue
    { 230, 230, 255},  // Light Blue
    {  20,  20, 200},  // Blue
    {  20, 150, 255},  // Light blue
    {  20,  20, 200},  // Blue
    {   0,   0,   0},  // Black
    {   0,   0,   0}   // Black
    //{ 240, 243, 243},  // Near white
    //{ 240, 243, 243}   // Near white
};
void change_controls
(char& command, double& centerx, double& centery, double& half_size);
// Wait for a key stroke or mouse click, and then change the
// values of the four control variables.

void draw_fractal(double cx, double cy, double half_side);
// This draws part of a fractal.  The center is at
// (cx, cy) and half_side is the length of half the side
// of the square that is drawn.
    
int pixel_color(complex<double> p);
// Calculates the color to put at the specified col and row.

    
int main( )
{
    char command;         // A key from the keyboard
    double centerx = 0;   // X cartesian coordinate of center
    double centery = 0;   // Y cartesian coordinate of center
    double half_size = 2; // Half the size of window in cartesian
    
    initwindow(WINDOW_SIZE, WINDOW_SIZE);

    do
    {
	draw_fractal(centerx, centery, half_size);
	change_controls(command, centerx, centery, half_size); 
    }   while (command != 'Q');

    return 0;
}


void change_controls
(char& command, double& centerx, double& centery, double& half_size)
{
    const int WAIT = 100; // Time to delay when there is no keystroke
    int pixelx, pixely;   // Location of the mouse click
    
    // Wait for a key stroke or mouse click
    while (!kbhit( ) && !ismouseclick(WM_LBUTTONUP))
    {
	delay(WAIT);
    }
    
    if (kbhit( ))
    {  // Deal with the key stroke
	command = toupper(getch());
	switch (command)
	{
	case '+': half_size /= 2; break;
	case '-': half_size *= 2; break;
	case '.': cin >> half_size >> centerx >> centery;
	}
    }
    else
    {  // Deal with the mouse click
	getmouseclick(WM_LBUTTONUP, pixelx, pixely);

	centerx = (2*half_size/WINDOW_SIZE) * pixelx
	        + (centerx - half_size);

    	centery = -(2*half_size/WINDOW_SIZE) * pixely
	        + (centery + half_size);
    }
    cout << half_size << ' ' << centerx << ' ' << centery << endl;
}

void draw_fractal(double cx, double cy, double half_side)
{
    int row, col; // The pixel numbers of the row and column
    double realx, realy; // The coordinates in the complex plane
    complex<double> p;    // The point as a complex number

    setrefreshingbgi(false);
    row = 0;
    while (row < WINDOW_SIZE)
    {
	// Color all the pixels in this row...
        col = 0;
	while (col < WINDOW_SIZE)
	{
	    // Color the pixel at location (col, row)
            realx =
		(2.0*half_side/WINDOW_SIZE)*col
		+
		(cx-half_side);
            realy =
		-(2.0*half_side/WINDOW_SIZE)*row
		+
		(cy+half_side);
            p = complex<double>(realx, realy);

	    putpixel(col, row, pixel_color(p));
	    col++;
	}
	//refresh(0, row, WINDOW_SIZE-1, row);
	row++;
    }
    refreshallbgi( );
    setrefreshingbgi(true);
}

int pixel_color(complex<double> p)
{
    const int LIMIT = (MANY_COLORS-1) * 10 - 1;
    complex<double> start = p;
    int count = 0;
    int lower, upper, tenths;
    int answer;

    while (count < LIMIT && abs(p) < RADIUS)
    {
	p = p*p + start;
	count++;
    }

    // Create a color that depends on the number of jumps taken.
    // Example: If 123 jumps were taken, then the color created is 3/10ths
    // of the way between color 12 and color 13.
    lower = count / 10;  // A color from 0 to MANY_COLORS-2
    upper = lower + 1             ;   // The next color up
    tenths = count % 10; // How far are we between lower and upper?
    answer = COLOR(
	TABLE[lower][0] + tenths * (TABLE[upper][0] - TABLE[lower][0]) / 10,
	TABLE[lower][1] + tenths * (TABLE[upper][1] - TABLE[lower][1]) / 10,
	TABLE[lower][2] + tenths * (TABLE[upper][2] - TABLE[lower][2]) / 10
	);
    return answer;
}

