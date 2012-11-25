#version 3.7;

global_settings {
  assumed_gamma  1.0
}

#declare csSize = 3;

#declare planeCameraDist = 15;

/*
     the Camera and the Light
*/

camera{
  location <1 + planeCameraDist * cos(2 * pi * clock), 2.5, 1 - planeCameraDist * sin(2 * pi * clock)>
  look_at <1,1,1>
  angle 30
}

light_source{
  <5,5,10>
  color<1,1,1>
}

/*
     the coordinate system
*/

cylinder{
  <-0.3, 0, 0> * csSize
  < 1, 0, 0> * csSize
  0.05
  pigment{
    color<1,0,0>
  }
}

cylinder{
  <0, 0, -0.3> * csSize
  <0, 0,  1.0> * csSize
  0.05
  pigment{
    color<0,1,0>
  }
}

cylinder{
  < 0, -0.3, 0> * csSize
  < 0, 1, 0> * csSize
  0.05
  pigment{
    color<0,0,1>
  }
}

/*
    spheres using cycle and vector arithmetic
*/


#for(ind, 0, 10) 
  #declare shift = <0.0, 0.0, 0.1>;
  #declare initialPosition = <0.5, 0.5, 0.5>;
  #declare position = initialPosition + shift * ind;

  sphere{
    position,
    0.05
    pigment {
      color<1,1,0>
    }
  }
#end