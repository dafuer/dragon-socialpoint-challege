#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ANGLE_STEP 72
#define INITIAL_ANGLE -36 
#define INITIAL_X 0.0
#define INITIAL_Y 0.0
#define JUMP_SIZE 1
#define ERROR 0.0001

typedef struct {
  float x;
  float y;
  int alfa; // en este caso no seran necesarios numeros decimales, de 72 en 72.
} pto;

int normalize_angle(int beta){
   while(beta<0){
     beta=360+beta;
   }
   while(beta>=360){
     beta=beta-360;
   }
   return beta;
}

pto *l(pto *current){
   pto *next;
   
   next=(pto *)malloc(sizeof(pto));
   
   // Calculating new positions
   next->alfa=current->alfa-ANGLE_STEP;
   next->x=current->x+JUMP_SIZE*sin(current->alfa*M_PI/180);
   next->y=current->y+JUMP_SIZE*cos(current->alfa*M_PI/180);
   
   return next;
 }

pto *r(pto *current){
   pto *next;
   
   next=(pto *)malloc(sizeof(pto));
   
   // Calculating new positions
   next->alfa=current->alfa+ANGLE_STEP;
   next->x=current->x+JUMP_SIZE*sin(current->alfa*M_PI/180);
   next->y=current->y+JUMP_SIZE*cos(current->alfa*M_PI/180);
   
   return next;
 }
 
 int real_equal(float real, float obj, float error){
   if(real<obj+error && real>obj-error){
      return 1;
   }else{
      return 0;
   }
}

int npaths(int steps, pto *point){
   pto *left, *right;
   
   if(steps==0){
      if(real_equal(point->x,INITIAL_X,ERROR) && real_equal(point->y, INITIAL_Y, ERROR) && normalize_angle(INITIAL_ANGLE)==normalize_angle(point->alfa)){ // is valid solution?
         free(point);
	 return 1;
      }else{
         free(point);
         return 0;
      }
   }
   
   if( sqrt( pow((point->x-INITIAL_X),2) + pow((point->y-INITIAL_Y),2))>(steps+2)*JUMP_SIZE ){
      free(point);
      return 0;
   }


   left=l(point);
   right=r(point);
   free(point);   
   return npaths(steps-1, left)+npaths(steps-1,right);
}
   
int main (int argc, char **argv){
   pto *current, *next;

   // Initialize
   current=(pto *)malloc(sizeof(pto));
   current->x=INITIAL_X;
   current->y=INITIAL_Y;
   current->alfa=INITIAL_ANGLE; // Initially it is looking to nord
/*   
   next=l(current);
   free(current);
   current=next;   
   printf(" %f %f %d\n", current->x, current->y,normalize_angle( current->alfa));
   next=l(current);
   free(current);
   current=next;   
   printf(" %f %f %d\n", current->x, current->y, normalize_angle(current->alfa));
   next=l(current);
   free(current);
   current=next;   
   printf(" %f %f %d\n", current->x, current->y, normalize_angle(current->alfa));
   next=l(current);
   free(current);
   current=next;   
   printf(" %f %f %d\n", current->x, current->y, normalize_angle(current->alfa));
   next=l(current);
   free(current);
   current=next;
   printf(" %f %f %d\n", current->x, current->y, normalize_angle(current->alfa));
*/   
   next=l(current);
   free(current);
   current=next;  
   printf(" Number of posible solutions: %d\n", npaths(atoi(argv[1])-1, current)*2);
   
   return 0;
}
