#include<SPI.h>
#include<USCL.h>
// Use this as template to create new animation
float animtime = 60000; // global duration of animations

 USCL cube(CUBE_SIZE_4x4x4, RGB_CUBE , D4, D3,  60 , 3, SPI_speed_8); // uncomment this if you are building for Wemos D1 mini
//USCL cube(CUBE_SIZE_8x8x8, RGB_CUBE , PA0, PA0,  30 , 2, SPI_speed_4); // change it to mach your cube - BLUEPILL
//USCL cube(CUBE_SIZE_4x4x4, RGB_CUBE , PA0, PA1,  60 , 6, SPI_speed_2); // BLUEPILL


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------




void plasma6(float time, USCL & cube, uint16_t shiftDelay)
{
  /* plasma1 parameters   ***   ***
    - time:                 Define the length of time that the animation should be executed.
    - cube:            Define the instance of the 'USCL' class that you made in your main program.
    - shiftDelay :        Define the delay (in ms) . Normally a value of  0 - 100 ms will suffice.
  */
  // Declare and initialize other variables needed for the animation
  //  float omega = (2.0 * PI) / (2 * cube.getCubeSize()); // Calculate the radial frequency omega
  byte cubesize = cube.getCubeSize();
  int FPS = cube.getFPS() / 2;
  int delay_FPS = 1000 / FPS;
  int max_brightness = cube.getMaxBrightness();

  // Other variables
  float step_offset = 180.00;
  float xoffset = float(PI / (((step_offset) + random(step_offset)) / float(cubesize))); //19//24
  float yoffset = float(PI / (((step_offset) + random(step_offset)) / float(cubesize))); //37//37
  float zoffset = float(PI / (((step_offset) + random(step_offset)) / float(cubesize))); //24//19

  float xx;
  float yy;
  float zz;


  float plasma;
  float hue;
  int int_hue;

  float xmap[cubesize];
  //  float ymap[cubesize];
  //  float zmap[cubesize];
  for ( int cc = 0 ; cc < cubesize; cc++)
  {
    xmap[cc] = map(cc, 0, cubesize - 1, 0.0, 1000.0 * ((float(1.0 / float(1.0 * float(cubesize))) * PI)) );
    //    ymap[cc] = map(cc, 0, cubesize - 1, 0, 2 * PI);
    //    zmap[cc] = map(cc, 0, cubesize - 1, 0, 2 * PI);
  }

  float fx;
  float fy;
  float fz;


  float  startTime = millis();
  while (millis() - startTime < time)
  {
    ///////////////////

    for ( int x = 0; x < cubesize ; x++)
    {
      //fx = float(sin(xx + xmap[x])) ;
      fx = sin(xx + (xmap[x] / 1000.0));
      fxV = cos(xx + (xmap[x] / 1000.0));
      for (int   z = 0; z < cubesize; z++)
      {
        fz = sin(zz + (xmap[z]) / 1000.0) ;
        fzV=sin(zz + (xmap[z]) / 1000.0) *sin(zz + (xmap[z]) / 1000.0) ;
        for ( int  y = 0 ; y < cubesize ; y++ )
        {
          fy = cos(yy + (xmap[y] / 1000.0));
          fyV=abs(cos(yy + (xmap[y] / 1000.0))+sin(yy + (xmap[y] / 1000.0)))/2;
          plasma = 180 + 70 * (fx + fz + fy) ; // *max=3
          if (plasma >= 0.0) {
            if (plasma <= 360.0 ) {
              cube.HSV( z, x, y, plasma   , 1.0, 0.1);
            }
          }
        }//  y
      }  //  z
    }    //  x
    xx = xx + xoffset;
    if (xx > 2.0 * PI)
    {
      xx = 0;
      yy = yy + yoffset;
      if (yy > 2.0 * PI)
      {
        yy = 0;

      }
    }

    zz = zz + zoffset;
    if (zz > 2.0 * PI)
    {
      zz = 0;
    }





    cube.drawVoxels();
    if (shiftDelay > 0) {
      delay(shiftDelay);
    }


    // hue
  } // while

  // ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------




void setup()
{
  //Start the cube
  cube.begin();
}
void loop()
{
  plasma6(animtime, cube ,  0 ); // animation time lenght, cube, delay in frames (if it's too fast)
}
