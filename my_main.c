/*========== my_main.c ==========

  This is the only file you need to modify in order
  to get a working mdl project (for now).

  my_main.c will serve as the interpreter for mdl.
  When an mdl script goes through a lexer and parser, 
  the resulting operations will be in the array op[].

  Your job is to go through each entry in op and perform
  the required action from the list below:

  frames: set num_frames (in misc_headers.h) for animation

  basename: set name (in misc_headers.h) for animation

  vary: manipluate knob values between two given frames
        over a specified interval

  set: set a knob to a given value
  
  setknobs: set all knobs to a given value

  push: push a new origin matrix onto the origin stack
  
  pop: remove the top matrix on the origin stack

  move/scale/rotate: create a transformation matrix 
                     based on the provided values, then 
		     multiply the current top of the
		     origins stack by it.

  box/sphere/torus: create a solid object based on the
                    provided values. Store that in a 
		    temporary matrix, multiply it by the
		    current top of the origins stack, then
		    call draw_polygons.

  line: create a line based on the provided values. Store 
        that in a temporary matrix, multiply it by the
	current top of the origins stack, then call draw_lines.

  save: call save_extension with the provided filename

  display: view the image live
  
  jdyrlandweaver
  =========================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "parser.h"
#include "symtab.h"
#include "y.tab.h"

#include "misc_headers.h"
#include "matrix.h"
#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "stack.h"

/*======== void first_pass()) ==========
  Inputs:   
  Returns: 

  Checks the op array for any animation commands
  (frames, basename, vary)
  
  Should set num_frames and basename if the frames 
  or basename commands are present

  If vary is found, but frames is not, the entire
  program should exit.

  If frames is found, but basename is not, set name
  to some default value, and print out a message
  with the name being used.
  
  05/17/12 09:27:02
  jdyrlandweaver
  ====================*/
void first_pass() {

  int i, f, j;
  char q;
f = 0;
  num_frames = 1;
int n = 0;
strcpy(name, "PIC");
  for (i=0;i<lastop;i++) {
  
    switch (op[i].opcode) {
case FRAMES:
      num_frames =  op[i].op.frames.num_frames;
      break;
case VARY:
f++;
break;
case BASENAME:
n++;
strcpy(name, op[i].op.basename.p->name);
break;
}
}
if (n == 0 && num_frames == 1){
printf("Basename set to default (PIC).\n");
}
if (f > 0 && num_frames == 1){
num_frames = -1;
}
//printf("nf = %d\n", num_frames);
}

/*======== struct vary_node ** second_pass()) ==========
  Inputs:   
  Returns: An array of vary_node linked lists

  In order to set the knobs for animation, we need to keep
  a seaprate value for each knob for each frame. We can do
  this by using an array of linked lists. Each array index
  will correspond to a frame (eg. knobs[0] would be the first
  frame, knobs[2] would be the 3rd frame and so on).

  Each index should contain a linked list of vary_nodes, each
  node contains a knob name, a value, and a pointer to the
  next node.

  Go through the opcode array, and when you find vary, go 
  from knobs[0] to knobs[frames-1] and add (or modify) the
  vary_node corresponding to the given knob with the
  appropirate value. 

  05/17/12 09:29:31
  jdyrlandweaver
  ====================*/
struct vary_node ** second_pass() {
int i,  j;
  char q[256];
double start, end, b;
double inc;
j = 0;
struct vary_node * s;
struct vary_node ** klist = (struct vary_node **)malloc(num_frames * sizeof(struct vary_node *));
for (i = 0; i < num_frames; i++){
klist[i] = NULL;
}
if ((klist[0] != NULL) && (klist[0]->next != NULL)){
//printf("node 00 has next?\n");
}
  //num_frames = 1;
  for (i=0;i<lastop;i++) {
  
    switch (op[i].opcode) {
case VARY:
strcpy(q, op[i].op.vary.p->name);
start = op[i].op.vary.start_frame;
end = op[i].op.vary.end_frame;
b = op[i].op.vary.start_val;
inc = 1.0 * (op[i].op.vary.end_val - b)/(end - start);
//printf("setting %s, %lf to %lf by %lf\n",q, start, end, inc);



for (j = start; j <= end; j++){
s = klist[j];
struct vary_node * s2 = klist[j];
int f = 0;
int f1 = 0;
if (s != NULL){
s2 = s->next;
//printf(" not null\n");
f1++;
}
else{
//printf("null\n");
}
while (f == 0 && s2  != NULL){
//printf("going...%d\n",f1);
if (strcmp(s2->name, q) == 0){
f++;
}
else{
s2 = s2->next;
s = s->next;
f1++;
}
}
if (f == 0){
s2 = (struct vary_node * )malloc(sizeof(struct vary_node));
strcpy(s2->name, q);
//printf("set name to %s\n",s2->name);
}
s2->value = b + inc * (j - start); 
s2->next = NULL;
if (f1 > 0){
//printf("after %s\n",s->name);
s->next = s2;
}
else{
klist[j] = s2;
}
//printf("set %s at frame %d to %lf;; f = %d f1 = %d\n",s2->name, j, s2->value, f,f1);
}
break;
}
}


for ( i=0; i < lastsym; i++ ) {
    if ( symtab[i].type == SYM_VALUE ) {
int done = 0;
int f = 0;
for (f = 0; f < num_frames && done == 0; f++){
struct vary_node* v = klist[f];
while ( v  != NULL && done == 0){
//printf("set %s %lf \n",v->name, v->value );
if(strcmp(v->name, symtab[i].name) == 0){
set_value(lookup_symbol(v->name), v->value);
done++;
}
v = v->next;
}
}
if (done == 0){
set_value(lookup_symbol(symtab[i].name), 1);
}
    }
}


return klist;
}

/*======== void print_knobs()) ==========
  Inputs:   
  Returns: 

  Goes through the symbol table and prints
  the values of all the knobs.

  05/15/13 09:29:17
  jdyrlandweaver
====================*/
void print_knobs() {
  
  int i;

  printf( "ID\tNAME\t\tTYPE\t\tVALUE\n" );
  for ( i=0; i < lastsym; i++ ) {

    if ( symtab[i].type == SYM_VALUE ) {
      printf( "%d\t%s\t\t", i, symtab[i].name );

      printf( "SYM_VALUE\t");
      printf( "%6.2f\n", symtab[i].s.value);
    }
  }
}

/*======== void my_main() ==========
  Inputs:   int polygons  
  Returns: 

  This is the main engine of the interpreter, it should
  handle most of the commadns in mdl.

  If frames is not present in the source (and therefore 
  num_frames is 1, then process_knobs should be called.

  If frames is present, the enitre op array must be
  applied frames time. At the end of each frame iteration
  save the current screen to a file named the
  provided basename plus a numeric string such that the
  files will be listed in order, then clear the screen and
  reset any other data structures that need it.

  Important note: you cannot just name your files in 
  regular sequence, like pic0, pic1, pic2, pic3... if that
  is done, then pic1, pic10, pic11... will come before pic2
  and so on. In order to keep things clear, add leading 0s
  to the numeric portion of the name. If you use sprintf, 
  you can use "%0xd" for this purpose. It will add at most
  x 0s in front of a number, if needed, so if used correctly,
  and x = 4, you would get numbers like 0001, 0002, 0011,
  0487

  05/17/12 09:41:35
  jdyrlandweaver
  ====================*/
void my_main( int polygons ) {
int i, j;
zbuf = (double **)malloc(500 * sizeof(double*));
for(i = 0; i < 500; i++){
zbuf[i] = (double*)malloc(500 * sizeof(double));
for (j = 0; j < 500; j++){
zbuf[i][j] = -DBL_MAX;
}
}
i = 0;
j = 0;
  int f;
  double step;
  double xval, yval, zval, knob_value;
  struct matrix *transform;
  struct matrix *tmp;
  struct stack *s;
  screen t;
  color g;
  char q;

  clear_screen( t );
  num_frames = 1;
  step = 0.05;
 
  g.red = 0;
  g.green = 125;
  g.blue = 255;

  s = new_stack();
  tmp = new_matrix(4, 1000);

first_pass();
if (num_frames < 0){
printf("ERROR- can't vary knobs when there's only 1 frame.\n");
}
if (num_frames >= 1){
struct vary_node ** klist = second_pass();
for (f = 0; f < num_frames; f++){
for ( i = 0; i < 500; i++){
for (j = 0; j < 500; j++){
zbuf[i][j] = -DBL_MAX;
}
}
  for (i=0;i<lastop;i++) {



struct vary_node* v = klist[f];
SYMTAB * vvv;
while ( v  != NULL){
//printf("set %s %lf \n",v->name, v->value );
vvv = lookup_symbol(v->name);
if (vvv != NULL){
set_value(vvv, v->value);
}
else{
add_symbol(v->name,SYM_VALUE,(void *)&(v->value));
}
v = v->next;
}


  //print_knobs();
    switch (op[i].opcode) {
case SETKNOBS:
xval = 0;
	double abcdef = op[i].op.setknobs.value;
//printf("Setting knobs to %lf.\n",abcdef);
for ( i=0; i < lastsym; i++ ) {

    if ( symtab[i].type == SYM_VALUE ) {
      set_value(&(symtab[i]), abcdef);
    }
  }
break;
    case SPHERE:
      add_sphere( tmp,op[i].op.sphere.d[0], //cx
		  op[i].op.sphere.d[1],  //cy
		  op[i].op.sphere.d[2],  //cz
		  op[i].op.sphere.r,
		  step);
      //apply the current top origin
      matrix_mult( s->data[ s->top ], tmp );
      draw_polygons( tmp, t, g );
      tmp->lastcol = 0;
      break;

    case TORUS:
      add_torus( tmp, op[i].op.torus.d[0], //cx
		 op[i].op.torus.d[1],     //cy
		 op[i].op.torus.d[2],    //cz
		 op[i].op.torus.r0,
		 op[i].op.torus.r1,
		 step);
      matrix_mult( s->data[ s->top ], tmp );
      draw_polygons( tmp, t, g );
      tmp->lastcol = 0;
      break;

    case BOX:
      add_box( tmp, op[i].op.box.d0[0],
	       op[i].op.box.d0[1],
	       op[i].op.box.d0[2],
	       op[i].op.box.d1[0],
	       op[i].op.box.d1[1],
	       op[i].op.box.d1[2]);
      matrix_mult( s->data[ s->top ], tmp );
      draw_polygons( tmp, t, g );
      tmp->lastcol = 0;
      break;

    case LINE:
      add_edge( tmp, op[i].op.line.p0[0],
		op[i].op.line.p0[1],
		op[i].op.line.p0[1],
		op[i].op.line.p1[0],
		op[i].op.line.p1[1],
		op[i].op.line.p1[1]);
      draw_lines( tmp, t, g );
      tmp->lastcol = 0;
      break;

    case MOVE:
      //get the factors
      xval = op[i].op.move.d[0];
      yval =  op[i].op.move.d[1];
      zval = op[i].op.move.d[2];
//printf("MOVE %lf %lf %lf\n",xval,yval,zval);
if (op[i].op.move.p != NULL){
SYMTAB* thing = (lookup_symbol(op[i].op.move.p->name));
xval *= thing->s.value;
yval *= thing->s.value;
zval *= thing->s.value;
//printf("new MOVE %lf %lf %lf\n",xval,yval,zval);
}

      transform = make_translate( xval, yval, zval );
      //multiply by the existing origin
      matrix_mult( s->data[ s->top ], transform );
      //put the new matrix on the top
      copy_matrix( transform, s->data[ s->top ] );
      free_matrix( transform );
      break;

    case SCALE:
      xval = op[i].op.scale.d[0];
      yval = op[i].op.scale.d[1];
      zval = op[i].op.scale.d[2];
      
//printf("scalE %lf %lf %lf\n",xval,yval,zval);
if (op[i].op.scale.p != NULL){
SYMTAB*  thing = (lookup_symbol(op[i].op.scale.p->name));
xval *= thing->s.value;
yval *= thing->s.value;
zval *= thing->s.value;
//printf("new scale %lf %lf %lf\n",xval,yval,zval);
}

      transform = make_scale( xval, yval, zval );
      matrix_mult( s->data[ s->top ], transform );
      //put the new matrix on the top
      copy_matrix( transform, s->data[ s->top ] );
      free_matrix( transform );
      break;

    case ROTATE:
      xval = op[i].op.rotate.degrees * ( M_PI / 180 );
//printf("rotate %lf\n",xval);
if (op[i].op.rotate.p != NULL){
xval *= (lookup_symbol(op[i].op.rotate.p->name))->s.value;
//printf("new rotate%lf\n",xval);
}

      //get the axis
      if ( op[i].op.rotate.axis == 0 ) 
	transform = make_rotX( xval );
      else if ( op[i].op.rotate.axis == 1 ) 
	transform = make_rotY( xval );
      else if ( op[i].op.rotate.axis == 2 ) 
	transform = make_rotZ( xval );

      matrix_mult( s->data[ s->top ], transform );
      //put the new matrix on the top
      copy_matrix( transform, s->data[ s->top ] );
      free_matrix( transform );
      break;

    case PUSH:
      push( s );
      break;
    case POP:
      pop( s );
      break;
    case SAVE:
      save_extension( t, op[i].op.save.p->name );
      break;
    case DISPLAY:
      display( t );
      break;
    }
  }

if (num_frames > 1){
char nopq[256];
char rst[256];
strcpy(nopq,"animations/");
strcat(nopq, name);
sprintf (rst, "%03d", f );
strcat(nopq,rst);
strcat(nopq,".png");
//printf("Saved frame %d to %s\n", (f+1) ,nopq);
save_extension( t, nopq );
  clear_screen( t );
screen t;
  g.red = 0;
  g.green = 255;
  g.blue = 255;


  free_stack( s );
  free_matrix( tmp );

  s = new_stack();
  tmp = new_matrix(4, 1000);
}
//printf("finished frame %d\n",f);
}
  ////////////////////////////////////////////////////////////

for (j = 0; j < num_frames; j++){
struct vary_node * v2 = klist[j];
struct vary_node * v = klist[j];
while (v2  != NULL){
v = v2;
v2 = v2->next;
free(v);
}
}
  free(klist);
}	
////////////////////////////////////////////////
  free_stack( s );
  free_matrix( tmp );
for(i = 0; i < 500; i++){
free(zbuf[i]);
}
free(zbuf);
  //free_matrix( transform );    
}
