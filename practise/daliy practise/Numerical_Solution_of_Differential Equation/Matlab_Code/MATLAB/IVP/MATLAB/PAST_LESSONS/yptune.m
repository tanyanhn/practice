function yptune = yptune(t,y)
  yptune(1) = y(2);
  yptune(2) = (100*sin(63.*t)*sin(710.*t)-400*y(2) - (10^6)*y(1))/2;
  yptune = [yptune(1) yptune(2)]';