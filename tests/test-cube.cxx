// File: cube.cpp
// Written by Grant Macklem
// 		Grant.Macklem@Colorado.EDU
//			2:00 PM Recitation
// Displays a cube in perspective projection which the user can then rotate.  The
// cube is drawn so that it's center is at the origin of the axes.  The length of
// each side is given by the variable in the main function.  The program calculates
// the perspective projection of the cube onto a plane by using 3-dimentional vector
// equations for lines and planes.  A projection point located below the cube is
// where all rays begin, travelling through each vertex of the cube, and finally
// intersecting the plane which is above the axes.  Because of this method, the
// sides of the cube closest to to the projection point are drawn larger than
// the sides further away, even though the sides further away are actually closer
// to the projection plane (the computer screen).
// The projection plane has the z-axis coming out of the screen towards us.
// The perspective projection was created using the following equations where
// P_0 means "P sub 0":
// P_0 = <P_0x, P_0y, P_0z>
// P_i = point of a vertex = <P_ix, P_iy, P_iz>
// V = P_i - P_0 = <P_ix - P_0x, P_iy - P_0y, P_iz - P_0z> = <A, B, C>
// The equations for a line are
// r = r_0 + tv where r = <x, y, z> ; r_0 = <x_0, y_0, z_0>, and v = <a, b, c>
// In this program, r_0 = P_0, v = V
// So, <x, y, z> = <x_0, y_0, z_0> + <tA, tB, tC>
// or
// x = x_0 + tA;  y = y_0 + tB;  z = z_0 + tC
// which can be represented as (x - x_0) / A = (y - y_0) / B = (z - z_0) / C
// Thus, to find the corresponding points where the line intersects the plane
// with a given z_0, I used only that component and set it equal to the last term.
// x component:  x = [A * (z - z_0)] / C + x_0
// or x = { [ (P_ix - P_0x) * (z - z_0) ] / (P_iz - P_0z) } + x_0
// A similar calculation results in the y value.

/*******************************************************************************
* cube.exe  A program to manipulate a perspective cube projection.
* Copyright (C) 1998 Grant Macklem
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software Foundation,
* Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*
* You may contact me, the author by emailing Grant.Macklem@Colorado.EDU
*******************************************************************************/

#include <graphics.h>    // Provides init_window
#include <iostream.h>	 // Provides cin, cout
#include <math.h>	 // Provides sqrt, sin, cos

const double PI = 3.141592653589;

// Sets the initial points of the cube verticies
void set_initial(double cube [][3], double length);

// Rotate the verticies of the cube corresponding to each angle xa, ya, and za
void rotate_cube
	(double cube[][3],			// Cube verticies in 3-space
    int xa,							// Angle of rotation w/r/t x-axis
    int ya,
    int za);

// Draw the cube projection onto the plane
void draw_cube
	(double cube[][3],			// Cube verticies in 3-space
    double point[][2],			// Cube verticies in perspective 2-space
    double plane[],				// Coordinates of viewing plane
    double pro[]);				// Coordinates of projection point

// Returns the ascii value of a key pressed
int GetKey();

// Actually works with the user interaction and moves the cube.  The main funciton
// calls this function every time it is to work.  Return value is whether or not
// to keep running the program.
bool user
	(double cube[][3],			// Cube verticies in 3-space
    double point[][2],			// Cube verticies in perspective 2-space
	 double plane[],				// Coordinates of viewing plane
    double pro[],					// Coordinates of projection point
    double length,				// Length of cube side
    double scale,					// Scale factor used when zooming.
    double pro_z,					// Z-coordinate of projection point.
    double plane_z);				// Z-coordinate of projection plane.


int APIENTRY WinMain
( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    const double pro_z = -50;		// Z-coordinate of projection point.
	const double plane_z = 120;	// Z-coordinate of projection plane.
	double cube[8][3];				// Array to hold cube points.  First index is the
   										// vertex point, second is the x,y,z coordinates.
   double length = 20;				// Length of cube side
   double scale = 1.1;				// Scale factor used when zooming.
   double pro[3] = {0, 0, pro_z}; 		// x,y,z coordinates of the projection point
   double plane[3] = {0, 0, plane_z};	// Coordinates of the plane projected onto.
   double point [8][2];				// Coordinates where ray intersects projection plane
   bool run;							// Value to keep running the program.

	initwindow (400,400);			// Initialize graphics window

   set_initial(cube, length);		// Set initial cube verticies

   draw_cube(cube, point, plane, pro);	// Draw the cube

	cout << "Rotating Cube, Copyright (C) 1998 Grant Macklem.\n" << endl;
   cout << "Press " << char(34) << "Q" << char(34) << " at any time to quit." << endl;
   cout << "Press " << char(34) << "R" << char(34) << " to reset the cube to"
        << " the initial position." << endl;
	cout << "Press (up) to move the viewpoint above the cube." << endl;
   cout << "Press (down) to move the viewpoint below the cube." << endl;
   cout << "Press (left) to move the viewpoint to the left of the cube" << endl;
   cout << "Press (right) to move the viewpoint to the right of the cube" << endl;
	cout << "Press " << char(34) << "\\" << char(34) << " to rotate"
   	  << " counterclockwise." << endl;
   cout << "Press " << char(34) << "/" << char(34) << " to rotate"
   	  << " clockwise." << endl;
   cout << "Press " << char(34) << "z" << char(34) << " to zoom out." << endl;
   cout << "Press " << char(34) << "Z" << char(34) << " to zoom in." << endl;

   do
   {
		run = user (cube, point, plane, pro, length, scale, pro_z, plane_z);
   }  while(run == true);

}


void set_initial(double cube [][3], double length)
{
	double side = length / 2.0;
	// Point 1
	cube[0][0]=-side;
  	cube[0][1]=-side;
	cube[0][2]=side;

	// Point 2
	cube[1][0]=-side;
  	cube[1][1]=side;
	cube[1][2]=side;

	// Point 3
	cube[2][0]=side;
  	cube[2][1]=-side;
	cube[2][2]=side;

	// Point 4
	cube[3][0]=side;
  	cube[3][1]=side;
	cube[3][2]=side;

	// Point 5
	cube[4][0]=-side;
  	cube[4][1]=-side;
	cube[4][2]=-side;

	// Point 6
	cube[5][0]=-side;
  	cube[5][1]=side;
	cube[5][2]=-side;

	// Point 7
	cube[6][0]=side;
  	cube[6][1]=-side;
	cube[6][2]=-side;

	// Point 8
	cube[7][0]=side;
  	cube[7][1]=side;
	cube[7][2]=-side;
}


// Draws the cube projection onto the plane.
void draw_cube
	(double cube[][3],			// Cube verticies in 3-space
    double point[][2],			// Cube verticies in perspective 2-space
    double plane[],				// Coordinates of viewing plane
    double pro[])					// Coordinates of projection point
{

	// Calculate two-dimentional projections of the points.
	for (int i=0; i<8; i++)
   {
   	for (int j=0; j<2; j++)
      {
			point[i][j] = (plane[2]-cube[i][2]) / (cube[i][2]-pro[2]) * (cube[i][j]-pro[j]) + cube[i][j];
      }
   }

   // put coordinates in center of window
   for (int i=0; i<8; i++)
   {
   	for (int j=0; j<2; j++)
      	point[i][j]+=200;
   }

   line(point[6][0],point[6][1],point[4][0],point[4][1]);	// bottom left
   line(point[6][0],point[6][1],point[7][0],point[7][1]);	// bottom front
   line(point[6][0],point[6][1],point[2][0],point[2][1]);	// front left
   line(point[0][0],point[0][1],point[2][0],point[2][1]);	// top left
   line(point[0][0],point[0][1],point[4][0],point[4][1]);	// back left
   line(point[0][0],point[0][1],point[1][0],point[1][1]);	// top back
   line(point[3][0],point[3][1],point[2][0],point[2][1]);	// top front
   line(point[3][0],point[3][1],point[1][0],point[1][1]);	// top right
   line(point[3][0],point[3][1],point[7][0],point[7][1]);	// front right
   line(point[5][0],point[5][1],point[4][0],point[4][1]);	// bottom back
   line(point[5][0],point[5][1],point[1][0],point[1][1]);	// back right
   line(point[5][0],point[5][1],point[7][0],point[7][1]);	// bottom right

}


void rotate_cube
	(double cube[][3],			// Cube verticies in 3-space
    int xa,							// Angle of rotation w/r/t x-axis
    int ya,
    int za)
{
	double rad = PI / 180.0;

	double txa, tya, tza;
   double tSin, tCos;
   double tx, ty, tz;

   txa = xa * rad;
   tya = ya * rad;
   tza = za * rad;


   // Rotate along Z-axis
   tSin = sin(tza);
   tCos = cos(tza);

	for (int i = 0; i < 8; i++)
   {
   	tx = cube[i][0] * tCos - cube[i][1] * tSin;
	   ty = cube[i][0] * tSin + cube[i][1] * tCos;
	   cube[i][0] = tx;
	   cube[i][1] = ty;
   }

   // Rotate along Y-axis
   tSin = sin(tya);
   tCos = cos(tya);

	for (int i = 0; i < 8; i++)
   {
   	tx = cube[i][0] * tCos + cube[i][2] * tSin;
	   tz = -cube[i][0] * tSin + cube[i][2] * tCos;
	   cube[i][0] = tx;
	   cube[i][2] = tz;
   }

   // Rotate along X-axis
   tSin = sin(txa);
   tCos = cos(txa);

	for (int i = 0; i < 8; i++)
   {
	   ty = cube[i][1] * tCos - cube[i][2] * tSin;
	   tz = cube[i][1] * tSin + cube[i][2] * tCos;
	   cube[i][1] = ty;
	   cube[i][2] = tz;
   }

}


int GetKey( void )
{
   int c;
	c = getch();

   if(c == 0)
   {
   	c = getch();
      c += 300;
   }

   return c;
}


bool user
	(double cube[][3],			// Cube verticies in 3-space
    double point[][2],			// Cube verticies in perspective 2-space
	 double plane[],				// Coordinates of viewing plane
    double pro[],					// Coordinates of projection point
    double length,				// Length of cube side
    double scale,					// Scale factor used when zooming.
    double pro_z,					// Z-coordinate of projection point.
    double plane_z)				// Z-coordinate of projection plane.

{

   int command;						// Key pressed for next action
   int za=0;							// Angle that the cube has rotated around the
   										// z-axis ([counter]clockwise motion)
   int ya=0;							// Angle that the cube has rotated around the
   										// y-axis (left and right motion)
   int xa=0;							// Angle that the cube has rotated arond the
   										// x-axis (up and down motion)


	command = getch();
   if (command == 0)
   	command = getch();


   switch (command)
   {
     	case int('4'):	case KEY_LEFT:		//Observer moves to left, rotate cube to right
        										//Actually rotate cube forward (ya)
      	ya=-5;
     	   rotate_cube(cube, xa, ya, za);
         break;

     	case int('6'):	case KEY_RIGHT:		//Observer moves to right, rotate cube to left
        										//Acutally rotate cube back (ya)
      	ya=5;
     	   rotate_cube(cube, xa, ya, za);
	      break;

      case int('8'):	case KEY_UP:	  	// Observer moves up, rotate cube down
        									  	// Actually rotate cube clockwise (xa)
      	xa=5;
     	   rotate_cube(cube, xa, ya, za);
	      break;

      case int('2'): case KEY_DOWN:		// Observer moves down, rotate cube up
        										// Actually rotate cube counterclockwise (xa)
      	xa=-5;
     	   rotate_cube(cube, xa, ya, za);
	      break;

      case int('/'):			// Observer tilts left, rotate cube clockwise
        							// Actually rotate cube along z-azis (za)
      	za=5;
     	   rotate_cube(cube, xa, ya, za);
         break;

      case int('\\'):		// Observer tilts right, rotate cube counterclockwise
      							// Actually rotate cube along z-axis (za)
      	za=-5;
         rotate_cube(cube, xa, ya, za);
         break;

      case int('Z'):			// Zoom in.  Actually move the projection point closer
      							// until it is at its default value.  Then start moving
                           // the plane further away so the image is larger.
			// Since pro and pro_z are double numbers, see if the projection point
         // is very close to the original number.
			// Will move the plane up 10% further than it was previously.
         // If the plane is up so far that no more zooming will occur, do nothing.
			// Constant 5.7 MAY need adjusting if pro_z and plane_z are changed..
         if (  plane[2] > ( (abs(pro_z * plane_z)) / 5.7 )  )
           	break;

         if (abs(pro[2] - pro_z) > .01)
			{
         	pro[2] /= scale;
         }
         else
         {
         	plane[2] *= scale;
         }
         break;

      case int ('z'): 		// Zoom out.  Acutally move the projection plane closer
      							// until it is at its default value.  Then start moving
      							// the projection point further away so the image is smaller.
			// Since plane and plane_z are double numbers, see if the projection plane
         // is very close to the original number.
         // Will move the point back 10% further than it was before.
         // If the point is back so that hardly any more zooming out will occur,
         // do nothing.
         // Constant 4.5 MAY need adjusting if pro_z and plane_z are changed.
			if ( pro[2] < ((pro_z * plane_z) / 4.5) )
         	break;

			if (abs(plane[2] - plane_z) > .01)
         {
            plane[2] /= scale;
         }
         else
         {
            pro[2] *= scale;
         }
         break;


		// Quit the program
      case int ('Q'): case int ('q'):
        	return false;

		// Reset the initial values of the program
      case int ('R'): case int('r'):
			pro[0] = 0;
         pro[1] = 0;
         pro[2] = pro_z;
         plane[0] = 0;
         plane[1] = 0;
         plane[2] = plane_z;

      	set_initial (cube, length);
         break;

		default:
        	return true;
   }	// end switch

   cleardevice();

   draw_cube(cube, point, plane, pro);
   return true;
}
