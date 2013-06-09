#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "gmath.h"



/*======== void add_polygon() ==========
Inputs:   struct matrix *surfaces
         double x0
         double y0
         double z0
         double x1
         double y1
         double z1
         double x2
         double y2
         double z2  
Returns: 
Adds the vertices (x0, y0, z0), (x1, y1, z1)
and (x2, y2, z2) to the polygon matrix. They
define a single triangle surface.

04/16/13 13:05:59
jdyrlandweaver
====================*/
void add_polygon( struct matrix *polygons, 
		  double x0, double y0, double z0, 
		  double x1, double y1, double z1, 
		  double x2, double y2, double z2 ) {

  add_point(polygons, x0, y0, z0);
  add_point(polygons, x1, y1, z1);
  add_point(polygons, x2, y2, z2);
}

/*======== void draw_polygons() ==========
Inputs:   struct matrix *polygons
         screen s
         color c  
Returns: 


04/16/13 13:13:27
jdyrlandweaver
====================*/
void draw_polygons( struct matrix *polygons, screen s, color c ) {
  int i;
  
  if ( polygons->lastcol < 3 ) {
    printf("Need at least 3 points to draw a polygon!\n");
    return;
  }
  //printf("\n\n");
  for( i=0; i < polygons->lastcol-2; i+=3 ) {
    
    if ( calculate_dot( polygons, i ) >= 0 ) {
    //      printf("drawing polygon %d\n", i/3);    

  c.red = (c.red + 51)%255;
  c.green =(c.green + 51)%255;
  c.blue = (c.blue + 51)%255;

      draw_line( polygons->m[0][i],
		 polygons->m[1][i],
		 polygons->m[0][i+1],
		 polygons->m[1][i+1],
		 s, c,
		polygons->m[2][i],
		 polygons->m[2][i+1]);
      draw_line( polygons->m[0][i+1],
		 polygons->m[1][i+1],
		 polygons->m[0][i+2],
		 polygons->m[1][i+2],
		 s, c,
		polygons->m[2][i+1],
		 polygons->m[2][i+2]);
      draw_line( polygons->m[0][i+2],
		 polygons->m[1][i+2],
		 polygons->m[0][i],
		 polygons->m[1][i],
		 s, c,
		polygons->m[2][i+2],
		 polygons->m[2][i]);
double b, m, t;
double uo, ut, ur;
int oo, ot, or,ob, ott, om;
oo = 0;
ot = 0;
or = 0;
ob = 0;
om = 0;
ott = 0;
uo = polygons->m[1][i];
ut = polygons->m[1][i+1];
ur = polygons->m[1][i+2];
double x1, x2, x3;
double z1, z2, z3;
///*
x1 = polygons->m[0][i];
x2 = polygons->m[0][i+1];
x3 = polygons->m[0][i+2];
z1 = polygons->m[2][i];
z2 = polygons->m[2][i+1];
z3 = polygons->m[2][i+2];
//printf("points->(%lf,%lf,%lf);(%lf,%lf,%lf);(%lf,%lf,%lf)\n",x1,uo,z1,x2,ut,z2,x3,ur,z3);
//*/
if(ott == 0 && uo >= ut && uo>= ur){
t = uo;
oo++;
ott++;
x3 = polygons->m[0][i];
z3 = polygons->m[2][i];
}
if(ott == 0 && ut >= uo && ut>= ur){
t = ut;
ot++;
ott++;
x3 = polygons->m[0][i+1];
z3 = polygons->m[2][i+1];
}
if(ott == 0 && ur >= ut && ur>= uo){
t = ur;
or++;
ott++;
x3 = polygons->m[0][i+2];
z3 = polygons->m[2][i+2];
}

if(ob == 0 && oo == 0 && uo <= ut && uo<= ur){
b = uo;
oo++;
ob++;
x1 = polygons->m[0][i];
z1 = polygons->m[2][i];
}
if(ob == 0 && ot == 0 && ut <= uo && ut<= ur){
b = ut;
ot++;
ob++;
x1 = polygons->m[0][i+1];
z1 = polygons->m[2][i+1];
}
if(ob == 0 && or == 0 && ur <= ut && ur<= uo){
b = ur;
or++;
ob++;
x1 = polygons->m[0][i+2];
z1 = polygons->m[2][i+2];
}

if (om == 0 && oo == 0){
m = uo;
om++;
x2 = polygons->m[0][i];
z2 = polygons->m[2][i];
}
if (om == 0 && ot == 0){
m = ut;
om++;
x2 = polygons->m[0][i+1];
z2 = polygons->m[2][i+1];
}
else{
m = ur;
om++;
x2 = polygons->m[0][i+2];
z2 = polygons->m[2][i+2];
}
//printf("bmt -> (%lf,%lf,%lf);(%lf,%lf,%lf);(%lf,%lf,%lf)\n\n",x1,b,z1,x2,m,z2,x3,t,z3);
double bt, bm, mt;
if (t == b){
bt = DBL_MAX;//9999999;//DBL_MAX;//
if (x3 < x1){
bt = -DBL_MAX;//-9999999;//-DBL_MAX;//
}
}
else{
bt = 1.0 * (x3 - x1)/(t - b);
}
if (m == b){
bm = DBL_MAX;//9999999;//DBL_MAX;//
if (x2 < x1){
bm = -DBL_MAX;//-9999999;//-DBL_MAX;//
}
}
else{
bm = 1.0 * (x2 - x1)/(m - b);
}
if (t == m){
mt = DBL_MAX;//9999999;//DBL_MAX;//
if (x3 < x2){
mt = -DBL_MAX;//-9999999;//-DBL_MAX;//
}
}
else{
mt = 1.0 * (x3 - x2)/(t - m);
}
//////zzzzzzzz
double btz, bmz, mtz;
if (t == b){
btz = DBL_MAX;//9999999;//DBL_MAX;//
if (z3 < z1){
btz = -DBL_MAX;//-9999999;//-DBL_MAX;//
}
}
else{
btz = 1.0 * (z3 - z1)/(t - b);
}
if (m == b){
bmz = DBL_MAX;//9999999;//DBL_MAX;//
if (z2 < z1){
bmz = -DBL_MAX;//-9999999;//-DBL_MAX;//
}
}
else{
bmz = 1.0 * (z2 - z1)/(m - b);
}
if (t == m){
mtz = DBL_MAX;//9999999;//DBL_MAX;//
if (z3 < z2){
mtz = -DBL_MAX;//-9999999;//-DBL_MAX;//
}
}
else{
mtz = 1.0 * (z3 - z2)/(t - m);
}
//printf("inv slopes %lf %lf %lf\n",bt,bm,mt);
//printf("inv z slopes %lf %lf %lf\n",btz,bmz,mtz);
double m2 = bm;
double mz2 = bmz;
double drx, drx2, drx3;
double drz, drz2, drz3;
drx2 = x1;
drx = x1;
drx3 = x2;
drz2 = z1;
drz = z1;
drz3 = z2;
int abcdef = 0;
while(b <= t){
if (abcdef == 0 && b >= m){
m2 = mt;
mz2 = mtz;
drx2 = x2;
drx3 = x3;
drz2 = z2;
drz3 = z3;
abcdef++;
}
drx += bt;
drx2 += m2;
drz += btz;
drz2 += mz2;
if ((bt < 0 && drx < x3) || (bt >= 0 && drx > x3)){
drx = x3;
}
if ((m2 < 0 && drx2 < drx3) || (m2 >= 0 && drx2 > drx3)){
drx2 = drx3;
}
if ((btz < 0 && drz < z3) || (btz >= 0 && drz > z3)){
drz = z3;
}
if ((mz2 < 0 && drz2 < drz3) || (mz2 >= 0 && drz2 > drz3)){
drz2 = drz3;
}
//printf("drawing (%lf,%lf,%lf) to (%lf,%lf,%lf)\n",drx,b,drz,drx2,b,drz2);
//printf("\tbmt -> (%lf,%lf,%lf);(%lf,%lf,%lf);(%lf,%lf,%lf)\n",x1,b,z1,x2,m,z2,x3,t,z3);
draw_line(drx,b,drx2,b,s,c, drz, drz2);
b++;
}
    }
  }
}

/*======== void add_box() ==========
  Inputs:   struct matrix * points
            double x
	    double y
	    double z
	    double width
	    double height
	    double depth
  Returns: 

  add the points for a rectagular prism whose 
  upper-left corner is (x, y, z) with width, 
  height and depth dimensions.

  jdyrlandweaver
  ====================*/
void add_box( struct matrix * polygons,
	      double x, double y, double z,
	      double width, double height, double depth ) {

  double x2, y2, z2;
  x2 = x + width;
  y2 = y - height;
  z2 = z - depth;


if (width < 0){//shows backends only otherwise
add_box(polygons,x2,y,z,-1 * width, height, depth);
return;
}
if (depth < 0){
add_box(polygons,x,y,z2,width, height, -1 * depth);
return;
}
if (height < 0){
add_box(polygons,x,y2,z,width, -1 * height, depth);
return;
}



  //front
  add_polygon( polygons, 
	       x, y, z, 
	       x, y2, z,
	       x2, y2, z);
  add_polygon( polygons, 
	       x2, y2, z, 
	       x2, y, z,
	       x, y, z);
  //back
  add_polygon( polygons, 
	       x2, y, z2, 
	       x2, y2, z2,
	       x, y2, z2);
  add_polygon( polygons, 
	       x, y2, z2, 
	       x, y, z2,
	       x2, y, z2);
  //top
  add_polygon( polygons, 
	       x, y, z2, 
	       x, y, z,
	       x2, y, z);
  add_polygon( polygons, 
	       x2, y, z, 
	       x2, y, z2,
	       x, y, z2);
  //bottom
  add_polygon( polygons, 
	       x2, y2, z2, 
	       x2, y2, z,
	       x, y2, z);
  add_polygon( polygons, 
	       x, y2, z, 
	       x, y2, z2,
	       x2, y2, z2);
  //right side
  add_polygon( polygons, 
	       x2, y, z, 
	       x2, y2, z,
	       x2, y2, z2);
  add_polygon( polygons, 
	       x2, y2, z2, 
	       x2, y, z2,
	       x2, y, z);
  //left side
  add_polygon( polygons, 
	       x, y, z2, 
	       x, y2, z2,
	       x, y2, z);
  add_polygon( polygons, 
	       x, y2, z, 
	       x, y, z,
	       x, y, z2); 
}


/*======== void add_sphere() ==========
  Inputs:   struct matrix * points
            double cx
	    double cy
	    double r
	    double step  
  Returns: 

  adds all the points for a sphere with center 
  (cx, cy) and radius r.

  should call generate_sphere to create the
  necessary points

  jdyrlandweaver
  ====================*/
void add_sphere( struct matrix * points, 
		 double cx, double cy, double cz, double r, 
		 double step ) {

  struct matrix * temp;
  int lat, longt;
  int index;
  double ns;
  int num_steps;
 
  ns = 1.0 / step;
  num_steps = (int)ns;

  temp = new_matrix( 4, num_steps * (num_steps+1) );
  //generate the points on the sphere
  generate_sphere( temp, cx, cy, cz, r, step );
  num_steps++;
  int latStop, longStop, latStart, longStart;
  latStart = 0;
  latStop = num_steps-1;
  longStart = 0;
  longStop = num_steps-1;
  
  for ( lat = latStart; lat < latStop; lat++ ) {
    for ( longt = longStart; longt < longStop; longt++ ) {
      
      index = lat * (num_steps) + longt;

      if ( lat == num_steps - 2) {
	add_polygon( points, temp->m[0][index],
		     temp->m[1][index],
		     temp->m[2][index],
		     temp->m[0][longt],
		     temp->m[1][longt],
		     temp->m[2][longt],
		     temp->m[0][longt+1],
		     temp->m[1][longt+1],
		     temp->m[2][longt+1]);
	if ( longt != num_steps - 2 ) {
	  add_polygon( points, 
		       temp->m[0][longt+1],
		       temp->m[1][longt+1],
		       temp->m[2][longt+1],
		       temp->m[0][index+1],
		       temp->m[1][index+1],
		       temp->m[2][index+1],
		       temp->m[0][index],
		       temp->m[1][index],
		       temp->m[2][index]);
	}
      }//end edge case
      else {	
	add_polygon( points, temp->m[0][index],
		     temp->m[1][index],
		     temp->m[2][index],
		     temp->m[0][index+num_steps],
		     temp->m[1][index+num_steps],
		     temp->m[2][index+num_steps],
		     temp->m[0][index+num_steps+1],
		     temp->m[1][index+num_steps+1],
		     temp->m[2][index+num_steps+1]);
	if ( longt != num_steps - 2 ) {
	  add_polygon( points, 
		       temp->m[0][index+num_steps+1],
		       temp->m[1][index+num_steps+1],
		       temp->m[2][index+num_steps+1],
		       temp->m[0][index+1],
		       temp->m[1][index+1],
		       temp->m[2][index+1],
		       temp->m[0][index],
		       temp->m[1][index],
		       temp->m[2][index]);
	}
      }//end not last full rotation
    }
  }
}

/*======== void generate_sphere() ==========
  Inputs:   struct matrix * points
            double cx
	    double cy
	    double r
	    double step  
  Returns: 

  Generates all the points along the surface of a 
  sphere with center (cx, cy) and radius r

  Adds these points to the matrix parameter

  03/22/12 11:30:26
  jdyrlandweaver
  ====================*/
void generate_sphere( struct matrix * points, 
		      double cx, double cy, double cz, double r, 
		      double step ) {

  double x, y, z, circle, rotation;

  double rotStart = step * 0;
  double rotStop = 1;

  for ( rotation = rotStart; rotation <= rotStop; rotation += step ) {
    for ( circle = 0; circle <= 1.01; circle+= step ) {
      
      x = r * cos( M_PI * circle ) + cx;
      y = r * sin( M_PI * circle ) *
	cos( 2 * M_PI * rotation ) + cy;
      z = r * sin( M_PI * circle ) *
	sin( 2 * M_PI * rotation ) + cz;
   
      add_point( points, x, y, z );
    }
  }
}    

/*======== void add_torus() ==========
  Inputs:   struct matrix * points
            double cx
	    double cy
	    double r1
	    double r2
	    double step  
  Returns: 

  adds all the points required to make a torus
  with center (cx, cy) and radii r1 and r2.

  should call generate_torus to create the
  necessary points

  03/22/12 13:34:03
  jdyrlandweaver
  ====================*/
void add_torus( struct matrix * points, 
		double cx, double cy, double cz,
		double r1, double r2, 
		double step ) {

  struct matrix * temp;
  int lat, longt;
  int index;
  double ns;
  int num_steps;
  
  ns = 1.0 / step;
  num_steps = (int)ns;

  temp = new_matrix( 4, num_steps * num_steps );
  //generate the points on the torus
  generate_torus( temp, cx, cy, cz, r1, r2, step );

  int num_points = temp->lastcol;

  int latStop, longStop, latStart, longStart;
  latStart = 0;
  longStart = 0;
  latStop = num_steps;
  longStop = num_steps;

  for ( lat = 0; lat < latStop; lat++ )
    for ( longt = 0; longt < longStop; longt++ ) {
      
      index = lat * num_steps + longt;
      
      if ( longt != num_steps-1) {
	add_polygon( points, temp->m[0][index],
		     temp->m[1][index],
		     temp->m[2][index],
		     temp->m[0][(index+num_steps+1) % num_points],
		     temp->m[1][(index+num_steps+1) % num_points],
		     temp->m[2][(index+num_steps+1) % num_points],
		     temp->m[0][index+1],
		     temp->m[1][index+1],
		     temp->m[2][index+1] );
	add_polygon( points, temp->m[0][index],
		     temp->m[1][index],
		     temp->m[2][index],
		     temp->m[0][(index+num_steps) % num_points],
		     temp->m[1][(index+num_steps) % num_points],
		     temp->m[2][(index+num_steps) % num_points],
		     temp->m[0][(index+num_steps) % num_points + 1],
		     temp->m[1][(index+num_steps) % num_points + 1],
		     temp->m[2][(index+num_steps) % num_points + 1]);
      }
      else {
	add_polygon( points, temp->m[0][index],
		     temp->m[1][index],
		     temp->m[2][index],
		     temp->m[0][(index+1) % num_points],
		     temp->m[1][(index+1) % num_points],
		     temp->m[2][(index+1) % num_points],
		     temp->m[0][index+1-num_steps],
		     temp->m[1][index+1-num_steps],
		     temp->m[2][index+1-num_steps] );
	add_polygon( points, temp->m[0][index],
		     temp->m[1][index],
		     temp->m[2][index],
		     temp->m[0][(index+num_steps) % num_points],
		     temp->m[1][(index+num_steps) % num_points],
		     temp->m[2][(index+num_steps) % num_points],
		     temp->m[0][(index+1) % num_points],
		     temp->m[1][(index+1) % num_points],
		     temp->m[2][(index+1) % num_points]);
      }

    }//end points only
}

/*======== void generate_torus() ==========
  Inputs:   struct matrix * points
            double cx
	    double cy
	    double r
	    double step  
  Returns: 

  Generates all the points along the surface of a 
  tarus with center (cx, cy) and radii r1 and r2

  Adds these points to the matrix parameter

  03/22/12 11:30:26
  jdyrlandweaver
  ====================*/
void generate_torus( struct matrix * points, 
		     double cx, double cy, double cz,
		     double r1, double r2, 
		     double step ) {
  double x, y, z, circle, rotation;

  double rotStart = step * 0;
  double rotStop = 1;


  for ( rotation = rotStart; rotation <= rotStop; rotation += step ) {
    for ( circle = 0; circle <= 1; circle+= step ) {

      x = cos( 2 * M_PI * rotation ) *
	( r1 * cos( 2 * M_PI * circle ) + r2 ) + cx;
      y = r1 * sin( 2 * M_PI * circle ) + cy;
      z = sin( 2 * M_PI * rotation ) *
	( r1 * cos( 2 * M_PI * circle ) + r2 ) + cz;

      add_point( points, x, y, z );
    }
  }

}

  
/*======== void add_circle() ==========
  Inputs:   struct matrix * points
            double cx
	    double cy
	    double y
	    double step  
  Returns: 


  03/16/12 19:53:52
  jdyrlandweaver
  ====================*/
void add_circle( struct matrix * points, 
		 double cx, double cy, 
		 double r, double step ) {
  
  double x0, y0, x, y, t;
  
  x0 = cx + r;
  y0 = cy;

  for ( t = step; t <= 1; t+= step ) {
    
    x = r * cos( 2 * M_PI * t ) + cx;
    y = r * sin( 2 * M_PI * t ) + cy;
    
    add_edge( points, x0, y0, 0, x, y, 0 );
    x0 = x;
    y0 = y;
  }

  add_edge( points, x0, y0, 0, cx + r, cy, 0 );
}

/*======== void add_curve() ==========
Inputs:   struct matrix *points
         double x0
         double y0
         double x1
         double y1
         double x2
         double y2
         double x3
         double y3
         double step
         int type  
Returns: 

Adds the curve bounded by the 4 points passsed as parameters
of type specified in type (see matrix.h for curve type constants)
to the matrix points

03/16/12 15:24:25
jdyrlandweaver
====================*/
void add_curve( struct matrix *points, 
		double x0, double y0, 
		double x1, double y1, 
		double x2, double y2, 
		double x3, double y3, 
		double step, int type ) {

  double x, y, t;
  struct matrix * xcoefs;
  struct matrix * ycoefs;
  
  //generate the coeficients
  if ( type == BEZIER_MODE ) {
    ycoefs = generate_curve_coefs(y0, y1, y2, y3, BEZIER_MODE);
    xcoefs = generate_curve_coefs(x0, x1, x2, x3, BEZIER_MODE);
  }

  else {
    xcoefs = generate_curve_coefs(x0, x1, x2, x3, HERMITE_MODE);
    ycoefs = generate_curve_coefs(y0, y1, y2, y3, HERMITE_MODE);
  }

  /*
  printf("a = %lf b = %lf c = %lf d = %lf\n", xcoefs->m[0][0],
         xcoefs->m[1][0], xcoefs->m[2][0], xcoefs->m[3][0]);
  */

  for (t=step; t <= 1; t+= step) {
    
    x = xcoefs->m[0][0] * t * t * t + xcoefs->m[1][0] * t * t
      + xcoefs->m[2][0] * t + xcoefs->m[3][0];

    y = ycoefs->m[0][0] * t * t * t + ycoefs->m[1][0] * t * t
      + ycoefs->m[2][0] * t + ycoefs->m[3][0];

    add_edge(points, x0, y0, 0, x, y, 0);
    x0 = x;
    y0 = y;
  }

  free_matrix(xcoefs);
  free_matrix(ycoefs);
}

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
  
  if ( points->lastcol == points->cols )
    grow_matrix( points, points->lastcol + 100 );

  points->m[0][points->lastcol] = x;
  points->m[1][points->lastcol] = y;
  points->m[2][points->lastcol] = z;
  points->m[3][points->lastcol] = 1;

  points->lastcol++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
  add_point( points, x0, y0, z0 );
  add_point( points, x1, y1, z1 );
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {

  int i;
 
  if ( points->lastcol < 2 ) {
    
    printf("Need at least 2 points to draw a line!\n");
    return;
  }

  for ( i = 0; i < points->lastcol - 1; i+=2 ) {

    draw_line( points->m[0][i], points->m[1][i], 
	       points->m[0][i+1], points->m[1][i+1], s, c,
		points->m[2][i], points->m[2][i]);
  } 	       
}


void draw_line(int x0, int y0, int x1, int y1, screen s, color c, double z1, double z2) {
 /*
if (x >= 0 && y >= 0 && x < 500 && y < 500 && zbuf[x][y] <= z){
plot(s, c, x, y);
zbuf[x][y] = z;
}
 z += dz;
*/
  int x, y, d, dx, dy;
double z, dz;

  x = x0;
  y = y0;
z = z1;
  
  //swap points so we're always draing left to right
  if ( x0 > x1 ) {
    x = x1;
    y = y1;
    x1 = x0;
    y1 = y0;
z = z2;
z2 = z1;
  }

  //need to know dx and dy for this version
  dx = (x1 - x) * 2;
  dy = (y1 - y) * 2;
  dz = (z2 - z1) * 2;

  //positive slope: Octants 1, 2 (5 and 6)
  if ( dy > 0 ) {

    //slope < 1: Octant 1 (5)
    if ( dx > dy ) {
      d = dy - ( dx / 2 );
  
      while ( x <= x1 ) {
	if (x >= 0 && y >= 0 && x < 500 && y < 500 && zbuf[x][y] < z){
plot(s, c, x, y);
zbuf[x][y] = z;
}
 z += dz;

	if ( d < 0 ) {
	  x = x + 1;
	  d = d + dy;
	}
	else {
	  x = x + 1;
	  y = y + 1;
	  d = d + dy - dx;
	}
      }
    }

    //slope > 1: Octant 2 (6)
    else {
      d = ( dy / 2 ) - dx;
      while ( y <= y1 ) {

	plot(s, c, x, y );
	if ( d > 0 ) {
	  y = y + 1;
	  d = d - dx;
	}
	else {
	  y = y + 1;
	  x = x + 1;
	  d = d + dy - dx;
	}
      }
    }
  }

  //negative slope: Octants 7, 8 (3 and 4)
  else { 

    //slope > -1: Octant 8 (4)
    if ( dx > abs(dy) ) {

      d = dy + ( dx / 2 );
  
      while ( x <= x1 ) {

	if (x >= 0 && y >= 0 && x < 500 && y < 500 && zbuf[x][y] <= z){
plot(s, c, x, y);
zbuf[x][y] = z;
}
 z += dz;

	if ( d > 0 ) {
	  x = x + 1;
	  d = d + dy;
	}
	else {
	  x = x + 1;
	  y = y - 1;
	  d = d + dy + dx;
	}
      }
    }

    //slope < -1: Octant 7 (3)
    else {

      d =  (dy / 2) + dx;

      while ( y >= y1 ) {
	
	plot(s, c, x, y );
	if ( d < 0 ) {
	  y = y - 1;
	  d = d + dx;
	}
	else {
	  y = y - 1;
	  x = x + 1;
	  d = d + dy + dx;
	}
      }
    }
  }
}

