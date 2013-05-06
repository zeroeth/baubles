   /***********************
   **   Shape Functions   **
    **    Header File    **
     ********************/
     
     
#include <SDL.h>
#include <gl/gl.h>
#include <gl/glu.h>


void jSquare( int );      /* Guarenteed size, +/- 1 offset error for odd */
void jTree( int, int, GLfloat, int, GLfloat, int, GLfloat, GLfloat );  /* make this 'abstract' for diff shapes */
void jDisc( GLint, GLUquadric *, int ); /* res */



//// STRUCTS //////////////////////////////////////////////////////////////

typedef struct                            /* A 2D point in Space         */
{
   double x;
   double y;
   
} jPt2D;



typedef struct                            /* A blob with position..     */
{                                         /* ..Direction and Size       */
   jPt2D   pos;
   jPt2D   vec;
   GLfloat size;
   GLfloat rot;                           /* How Fast                   */
   GLint   dir;                           /* What Direction             */
        
} jBlob;
