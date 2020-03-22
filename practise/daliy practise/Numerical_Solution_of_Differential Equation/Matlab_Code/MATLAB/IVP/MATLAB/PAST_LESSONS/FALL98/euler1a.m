function [x,y] = euler1a(x0,xfinal,yfun,y0,n)

h=(xfinal-x0)/n;

mdim=length(y0);	 % Find how many dependent variables, y's.

y=zeros(n+1,mdim);	 % Open a space for the solution.
x = zeros(n+1,1);        % Return x as a column vector.

for j=1:mdim
  y(1,j)=y0(j);               % First row is the initial value at x0. 
end

x(1)=x0; 

for i=1:n                % Big loop from one x to the another.

    for j=1:mdim
      yt(j) = y(i,j);              % New  y0 for the next step
    end
   
    ft = feval(yfun,x(i),yt);      % f(x,yt)

    for j=1:mdim   
      y(i+1,j)=y(i,j)+h*ft(j);     % Euler's method for each function !
    end

    x(i+1) = x(i) + h;
end
