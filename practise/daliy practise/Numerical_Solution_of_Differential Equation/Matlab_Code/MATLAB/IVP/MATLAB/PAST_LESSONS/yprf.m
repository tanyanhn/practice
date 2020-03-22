function yprf =yprf(t,y)
	yprf(1) =-.5*y(1) + .01*y(1)*y(2) -1;
	yprf(2) = .5*y(2) -.01*y(1)*y(2);
   yprf = [yprf(1) yprf(2)]';