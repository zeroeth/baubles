   /***********************
   **   Shape Functions   **
    ***********************/

#include "Shapes.h"

/** JSQUARE ** A Centered Square without glBegin/End ************************/

void jSquare( int size )
{
   
 glPushMatrix( );                                /* So Offset doesnt messup */
                                                 /* ... other shapes        */

   int half = -(size/2);                         /* Draw from center        */                                                 
   glTranslated( half, half, 0);
      
   glBegin(GL_QUADS);
   {
     //glColor4ub( 0, 255, 0, 255 );   
     glColor4f(1.0f,1.0f,1.0f,1.0f);
     
     // couldnt this have used a 'scale' inconjunction with a size of 1.0
     // ... hmmmm
     glTexCoord2i( 0, 1 ); //1
     glVertex2i  ( 0, 0 );
  
     glTexCoord2i( 1, 1 ); //2
     glVertex2i  ( size, 0 );
     
  
     glTexCoord2i( 1, 0 ); //3
     glVertex2i  ( size, size );      
     
     glTexCoord2i( 0, 0 ); //4
     glVertex2i  ( 0, size );
   }  
   glEnd();
   
  glPopMatrix( );                                /* Restore for next cmd    */
}



void jTree(     int nodes,
                int size,
            GLfloat smulti,
                int spacing,
            GLfloat multi,
                int depth,
            GLfloat rmulti,
            GLfloat theta )
{
  if( depth <= 0 ) return;

  int degspace = 360/nodes;
  
  for(int i = 0; i < nodes; i++)
  {
    glPushMatrix( );
    
    glRotatef   ( theta + (i*degspace), 0.0f, 0.0f, 1.0f );         
    glTranslated( spacing, spacing, 0 );           
    
    glRotatef   ( theta * rmulti + (i*degspace), 0.0f, 0.0f, 1.0f );
    jSquare     ( size );
    
    jTree( nodes,
          (int) (size * smulti),
           smulti,
          (int) (spacing * multi),
           multi,
           depth - 1,
           rmulti,
           theta * rmulti);
    
    glPopMatrix( );
    
  }
}



void jDisc( GLint List, GLUquadric *Shape, int Resolution )
{
  glNewList( List, GL_COMPILE );
  
    gluDisk( Shape, 0.0, 1.0, Resolution, 4);
  
  glEndList( );  
}
