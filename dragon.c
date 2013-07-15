#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ANGLE_STEP 72
#define INITIAL_ANGLE -36 
#define INITIAL_X 0.0
#define INITIAL_Y 0.0
#define JUMP_SIZE 1
#define ERROR 0.0001

// Point model
typedef struct {
  float x;
  float y;
  int alfa; // In this case we don't need real numbers, (72 degrees each step)
} pto;

// Return an angle between 0 and 360. 
int normalize_angle(int beta){
   while(beta<0){
     beta=360+beta;
   }
   while(beta>=360){
     beta=beta-360;
   }
   return beta;
}

// Move point to the left
pto *l(pto *current){
   pto *next;
   
   next=(pto *)malloc(sizeof(pto));
   
   // Calculating new positions
   next->alfa=current->alfa-ANGLE_STEP;
   next->x=current->x+JUMP_SIZE*sin(current->alfa*M_PI/180);
   next->y=current->y+JUMP_SIZE*cos(current->alfa*M_PI/180);
   
   return next;
}

// Move point to the right
pto *r(pto *current){
   pto *next;
   
   next=(pto *)malloc(sizeof(pto));
   
   // Calculating new positions
   next->alfa=current->alfa+ANGLE_STEP;
   next->x=current->x+JUMP_SIZE*sin(current->alfa*M_PI/180);
   next->y=current->y+JUMP_SIZE*cos(current->alfa*M_PI/180);
   
   return next;
 }
 
// Comparation between reals assuming a small error
int real_equal(float real, float obj, float error){
   if(real<obj+error && real>obj-error){
      return 1;
   }else{
      return 0;
   }
}

// Recursive function that return the number of valid paths from a point in N steps
int npaths(int steps, pto *point){
   pto *left, *right;
   
   // We finish this path. Check if it is a solution
   if(steps==0){
      if(real_equal(point->x,INITIAL_X,ERROR) && real_equal(point->y, INITIAL_Y, ERROR) && normalize_angle(INITIAL_ANGLE)==normalize_angle(point->alfa)){ // is valid solution?
         free(point);
	 return 1;
      }else{
         free(point);
         return 0;
      }
   }
   
   // Pruning test: check if we can walk to the origin or origin is so far (Euclidean distance)
   if( sqrt( pow((point->x-INITIAL_X),2) + pow((point->y-INITIAL_Y),2))>(steps+ERROR)*JUMP_SIZE ){
      free(point);
      return 0;
   }

   // Next step
   left=l(point);
   right=r(point);
   free(point);   
   
   // The total number of solutions are solutions to the right plus solutions the left 
   return npaths(steps-1, left)+npaths(steps-1,right);
}
   

int main (int argc, char **argv){
   pto *current, *next;

   // Initialize
   current=(pto *)malloc(sizeof(pto));
   current->x=INITIAL_X;
   current->y=INITIAL_Y;
   current->alfa=INITIAL_ANGLE; // Initially it is looking to nord

   // We force the first step and then the number of solutions will be double
   next=l(current);
   free(current);
   current=next;  
   printf(" Number of posible solutions: %d\n", npaths(atoi(argv[1])-1, current)*2);
   
   return 0;
}
