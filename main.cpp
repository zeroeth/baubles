//// HEADER ///////////////////////////////////////////////////////////////
//
//  Johnny SDL Test
//  Recursive Functions, Matrix Stacks, and Dot/Cross Products
//

#include "main.h"



int main(int argc, char *argv[]){


//// VARS /////////////////////////////////////////////////////////////////

  int width  = 1024;                      /* Screen Dimensions           */
  int height = 768;

  SDL_Event event;                        /* SDL Event Holder            */
  SDL_Surface *screen;                    /* SDL Screen Surface          */

  GLfloat theta = 0.0f;                   /* Rotation Var                */
  GLfloat rotspeed = 0.0f;                /* Rotation Speed              */

  struct {                                /* Mouse Coord Var             */
      int x;
      int y;
  } mouse;

  TwBar *guiBar;                          /* GUI Bar Pointer             */


  GLint        blobFunc;                  /* Holds Pointer to DispList   */
  GLUquadric  *blobShape;                 /* GLU Shape Holder            */

  // make a struct.. and vector of blobs with struct
  // hmm gravity and collisions (should try both out)


  GLint        blobRes      = 35;         /* Number of Points Around     */
  GLint        blobChanged  = 0;          /* Boolean                     */
  GLint        blobLine     = 20;         /* Line Thickness              */
  GLint        blobCount    = 20;         /* start count.. can add/rem   */
  GLfloat      blobMinSize  = 0;          /* How small                   */
  GLfloat      blobMaxSize  = 175;        /* How big                     */
  GLfloat      blobMinSpeed = 0;          /* Limit Slowest Speed         */
  GLfloat      blobMaxSpeed = 3;          /* Limit Top Speed             */

  GLfloat bCol[] = { 0.3f, 0.35f, 0.0f }; /* 3 Ajustable colors          */
  GLfloat fCol[] = { 1.0f, 1.00f, 1.0f };
  GLfloat lCol[] = { 0.0f, 0.00f, 0.0f };

  std::vector <jBlob> blobList;           /* My Container of Blobs       */
  std::vector <jBlob> ::iterator bi;      /* To Run through the list     */


//// SDL/GL INIT //////////////////////////////////////////////////////////

  SDL_Init        ( SDL_INIT_VIDEO );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

  if(true) {
    screen = SDL_SetVideoMode( 0, 0, 0, SDL_OPENGL | SDL_FULLSCREEN | SDL_HWSURFACE );
    height = screen->h;
    width  = screen->w;
  }
  else {
    screen = SDL_SetVideoMode( width, height, 0, SDL_OPENGL | SDL_FULLSCREEN | SDL_HWSURFACE );
  }

  //SDL_ShowCursor  ( SDL_DISABLE );
  glViewport  ( 0, 0, width, height    ); /* screen <-> windows coords   */


  glClearDepth( 1.0           );          /* Clears Depth Buffer upto X  */
  glDepthFunc ( GL_LEQUAL     );          /* How openGL handles Depth    */
  glEnable    ( GL_DEPTH_TEST );          /* Turn Depth On               */

  glShadeModel( GL_SMOOTH     );          /* Shading: FLAT or SMOOTH     */


  TwInit      ( TW_OPENGL, NULL );        /* Ant Tweak Bar               */
  TwWindowSize( width, height   );



//// DISPLAY LIST /////////////////////////////////////////////////////////

  blobFunc  = glGenLists   ( 1 );         /* Integer ID of displayList   */
  blobShape = gluNewQuadric(   );         /* Holds GLU Primitive Disc    */

  jDisc(blobFunc, blobShape, blobRes);    /* Compile a displayList       */


  jBlob newBlob;

  // Move to shared function
  // TODO why don't we need to construct here each time?
  for(int i = 0; i < blobCount; i++)
  {

             newBlob.pos.x = rand() % width;
             newBlob.pos.y = rand() % height;

             newBlob.vec.x = (float)rand() / RAND_MAX;
             newBlob.vec.y = (float)rand() / RAND_MAX;

             newBlob.size  = (float)rand() / RAND_MAX;

             newBlob.dir   = rand() % 2;
             newBlob.rot   = (float)rand() / RAND_MAX;

          blobList.push_back(newBlob);
  }



//// CREATE BLOBS /////////////////////////////////////////////////////////

// create initial position and vectors


//// TWEAK BAR ////////////////////////////////////////////////////////////

  guiBar = TwNewBar( "Blob List SDL" );      /* Build the TweakBar Menu     */

  TwAddVarRW( guiBar, "Blob Count", TW_TYPE_INT32, &blobCount, "min=0");
  TwAddVarRW( guiBar, "Rot Speed",  TW_TYPE_FLOAT, &rotspeed,
                                             "min=0.0 max=5.0 step=0.01" );
  TwAddVarRW( guiBar, "Min Speed",  TW_TYPE_FLOAT, &blobMinSpeed, "min=0.0 step=0.1");
  TwAddVarRW( guiBar, "Max Speed",  TW_TYPE_FLOAT, &blobMaxSpeed, "min=0.0 step=0.1");
  TwAddVarRW( guiBar, "Min Size",   TW_TYPE_FLOAT, &blobMinSize, "min=1.0 step=0.1");
  TwAddVarRW( guiBar, "Max Size",   TW_TYPE_FLOAT, &blobMaxSize, "min=1.0 step=0.1");
  TwAddVarRW( guiBar, "Line size",  TW_TYPE_INT32, &blobLine, ""     );
  TwAddVarRW( guiBar, "Resolution", TW_TYPE_INT32, &blobRes, "min=3"     );
  TwAddVarRW( guiBar, "Set Res",    TW_TYPE_BOOL32, &blobChanged, "" );
  TwAddVarRW( guiBar, "Back Color", TW_TYPE_COLOR3F, &bCol, "");
  TwAddVarRW( guiBar, "Fore Color", TW_TYPE_COLOR3F, &fCol, "");
  TwAddVarRW( guiBar, "Line Color", TW_TYPE_COLOR3F, &lCol, "");
  // add blob
  // remove blob

//// (RE)SIZE /////////////////////////////////////////////////////////////

/* TODO: Add this to a function that handles window resizing             */
  glMatrixMode  (GL_PROJECTION);          /* Determine the Camera        */
  glLoadIdentity( );                      /* Reset the Transform Matrix  */

  glOrtho( 0, width, 0, height, -100, 100 );
                                          /* Set a Pixel Perfect Screen  */
                                          /* With 200 Layers for sprites */


  glMatrixMode  ( GL_MODELVIEW );         /* Object Mode                 */
  glLoadIdentity( );                      /* Reset Trans.                */



//// LOOP /////////////////////////////////////////////////////////////////

  int done;
  for( done = 0; !done; )
  {



//// SDL EVENT ////////////////////////////////////////////////////////////

    while( SDL_PollEvent(&event) )
    {
                                          /* Pass if not used by Ant     */
      if( !TwEventSDL(&event, SDL_MAJOR_VERSION, SDL_MINOR_VERSION) )
      {
        switch( event.type )
        {
            case SDL_QUIT:                /* Clicked the X Button        */

               done = true;
               break;

            case SDL_KEYDOWN:             /* Pressed a Key               */

               if(event.key.keysym.sym == SDLK_ESCAPE)
                  done = 1;
               break;

            case SDL_MOUSEMOTION:         /* Update Mouse XY vars        */

               mouse.x = event.motion.x;
               mouse.y = event.motion.y;

               break;

        } /* switch */
      }  /* if !handled */
     } /* while */



//// RESHAPE //////////////////////////////////////////////////////////////

  if(blobChanged)
  {
    jDisc(blobFunc, blobShape, blobRes);

    blobList.clear();
    for(int i = 0; i < blobCount; i++)
    {

               newBlob.pos.x = rand() % width;
               newBlob.pos.y = rand() % height;

               newBlob.vec.x = (float)rand() / RAND_MAX;
               newBlob.vec.y = (float)rand() / RAND_MAX;

               newBlob.size  = (float)rand() / RAND_MAX;

               newBlob.dir   = rand() % 2;
               newBlob.rot   = (float)rand() / RAND_MAX;

            blobList.push_back(newBlob);
    }

    blobChanged = 0;
  }



//// DRAW /////////////////////////////////////////////////////////////////

                                          /* Screen Clear Color          */
    glClearColor( bCol[0], bCol[1], bCol[2], 1.0f );
    glClear( GL_COLOR_BUFFER_BIT          /* What to Clear each Frame    */
           | GL_DEPTH_BUFFER_BIT );

    glLoadIdentity ( );                   /* Reset openGL World          */

    for(bi  = blobList.begin( );
        bi != blobList.end  ( );
        bi++ )
    {

//// RENDER BLOBS /////////////////////////////////////////////////////////

      glPushMatrix( );

        glPushMatrix( );

          GLfloat bSize = blobMinSize + (bi->size * (blobMaxSize - blobMinSize));

          glTranslated( bi->pos.x, bi->pos.y, 0 );

          if( bi->dir )
            glRotatef  ( theta * bi->rot, 0.0f, 0.0f, 1.0f );
          else
            glRotatef  ( -(theta * bi->rot), 0.0f, 0.0f, 1.0f );

          glScalef    ( bSize, bSize, 0.0 );

          glColor3fv  ( fCol     );
          glCallList  ( blobFunc );

        glPopMatrix( );

          glTranslated( bi->pos.x, bi->pos.y, -1 );

          if( bi->dir )
            glRotatef  ( theta * bi->rot, 0.0f, 0.0f, 1.0f );
          else
            glRotatef  ( -(theta * bi->rot), 0.0f, 0.0f, 1.0f );

          glScalef    ( bSize+blobLine, bSize+blobLine, 0.0 );

          glColor3fv( lCol     );
          glCallList( blobFunc );

      glPopMatrix ( );



//// MOVE BLOBS ///////////////////////////////////////////////////////////


      if(bi->vec.x > 0)
        bi->pos.x += blobMinSpeed + (bi->vec.x * (blobMaxSpeed-blobMinSpeed));
      else
        bi->pos.x += -blobMinSpeed + (bi->vec.x * (blobMaxSpeed-blobMinSpeed));

      if(bi->vec.y > 0)
        bi->pos.y += blobMinSpeed + (bi->vec.y * (blobMaxSpeed-blobMinSpeed));
      else
        bi->pos.y += -blobMinSpeed + (bi->vec.y * (blobMaxSpeed-blobMinSpeed));

      if( bi->pos.x > width )             /* Bounce                      */
      {
        bi->vec.x = -bi->vec.x;
        bi->pos.x = width;
      }

      if( bi->pos.x < 0 )
      {
        bi->vec.x = -bi->vec.x;
        bi->pos.x = 0;
      }

      if( bi->pos.y > height )
      {
        bi->vec.y = -bi->vec.y;
        bi->pos.y = height;
      }

      if( bi->pos.y < 0 )
      {
        bi->vec.y = -bi->vec.y;
        bi->pos.y = 0;
      }

    } /* for blobRun */


    theta += rotspeed;                    /* Update Rotation Angle       */

    TwDraw();                             /* Draw the Ant Tweak Bar      */

    SDL_GL_SwapBuffers();                 /* SDL's Screen Swap Func      */

  } /* for */

  SDL_Quit();
  return(0);
}
