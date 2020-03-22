
%  Change the solution to the rectangular grid
   j = 1;
   for k=1:nnode,
      i = k - (j-1)*(nx+1) ;
      xm(i,j) = x(k); ym(i,j) = y(k);
      sol(i,j) = u(k);
       uexac(i,j) = exp(-pi*y(k))*cos(pi*x(k));	   % Test Problem 1.
%	uexac(i,j) = cos(pi*x(k));		   % Test Problem 2.
      j = fix(k/(nx+1)) + 1;
   end 

   max(max(abs(sol-uexac)))		% Error in the infinity norm.
   mesh(xm,ym,sol)			% Plot the solution.
   figure(2)			        % Get a new graph window.
   mesh(xm,ym,sol-uexac)		% Plot the error.

     
