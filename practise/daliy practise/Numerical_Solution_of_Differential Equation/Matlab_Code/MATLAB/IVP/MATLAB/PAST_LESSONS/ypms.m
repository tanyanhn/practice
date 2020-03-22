function ypms = ypms(t,y)
  ypms(1) = y(2);
  ypms(2) = cos(1.2*t) - y(1) - 0.0*y(2);
  ypms = [ypms(1) ypms(2)]';