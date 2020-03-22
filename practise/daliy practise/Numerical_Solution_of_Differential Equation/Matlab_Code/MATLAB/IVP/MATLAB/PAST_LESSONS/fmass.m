function fmass= fmass(t,y)
   fmass = -32 + .1*abs(y) + .001*y*y;