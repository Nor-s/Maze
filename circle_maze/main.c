#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void trimCircle(int **map, int d)
{
    int i, j;
    int  rr = d/2;
     
    for(i = 1; i < d-1; i++){
        for(j = 1; j < d-1; j++){
            if( (i-rr) < 0) {
                if ( map[i][j] == 1 && map[i-1][j] ==1 && ( map[i][j+1] == 1 || map[i][j-1] == 1))
                    map[i][j] = 0;
            } else  if ( map[i][j] == 1 && map[i+1][j] ==1 && ( map[i][j-1] == 1 || map[i][j+1] == 1))
                    map[i][j] = 0;
            }
       }
    
    return;
}
void drawCircle(int **map, int rr, int rd)
{
    int i, j;
    for(i =  rd - rr; i < rd + rr + 1; i++) {
       for(j = rd - rr; j < rd + rr + 1; j++) {
          if ((double)sqrt((i - rd)*(i - rd) +(j - rd)*(j - rd)) >= rr -0.5 && (double)sqrt((i - rd)*(i - rd) +(j - rd)*(j - rd)) <= rr +0.5){
              map[i][j] = 1;
           }
      }
   }
  // if(rr + 3  <  rd)
     //  drawCircle(map, rr+3, rd);
    if(rr + 3  <  rd)
       drawCircle(map, rr+3, rd);
}
int main(void)
{
    int d, i, j;
    int **map;

    printf("Diameter(odd num): ");
    scanf("%d", &d);

    map = (int **)malloc(d * sizeof(int *));
    for (i = 0; i < d; i++)
        map[i] = (int *)malloc(d* sizeof(int));
   
   //initialArray(map);

   //drawCircle(map, 2, d/2);
   drawCircle(map, 1, d/2);
   trimCircle(map, d);

   for(i = 0; i < d; i++) {
      for(j = 0; j < d; j++) {
          if(map[i][j] == 1)
             printf("[]");
          else 
             printf("  ");
      }
      putchar('\n');
   }
   
   for(i = 0; i < d; i++)
      free(map[i]);
   free(map);

   return 0;
}