
	function [x,y] = euler_simple2(x0,y0,xfinal,n)

	h = (xfinal - x0)/n;
	x(1) = x0;
	y(1) = y0;
	
	for i=1:n,
	   y(i+1) = y(i) + h*f2(x(i),y(i));
           x(i+1) = x(i) + h;
	end


