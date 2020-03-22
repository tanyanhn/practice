
	function yp = yfun_mol(t,y);
	global n h x

	k = length(y);
	yp = zeros(k,1);

	
	h1 = h*h;  et = exp(-t);
	yp(1) = (-2*y(1) + y(2) )/h1  ;
 	yp(n-1) = (y(n-2) - 2*y(n-1) )/h1;
          
	for i=2:n-2
	   yp(i) = (y(i-1) - 2*y(i) + y(i+1))/h1;
	end 

	for i=1:n-1,
          yp(i) = yp(i) + et*sin(pi*x(i))* (pi*pi-1);
	end

