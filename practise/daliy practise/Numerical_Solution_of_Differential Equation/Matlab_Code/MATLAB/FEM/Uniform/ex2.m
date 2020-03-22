
clear
clf

n=3;
h=1/(n+1);

x=0:h:1;
a=zeros(n,n);         % initialize the stiffness matrix.
b=zeros(n,1);	      % initialize the load vector.
uexact=zeros(n,1);    % initialize the exact solution.

for i=1:n-1,
  a(i,i)= 2/h;
  a(i+1,i) = -1/h;
  a(i,i+1) = -1/h;
end

  a(n,n) = 2/h;

% Computer the load vector: Regular problem, need function f.m.

for i=1:n
  xhalf = x(i)+0.5*h;
  b(i)= h*( 2*f(xhalf) + 2*f(xhalf+h) +2* f(x(i+1)) )/6;
  uexact(i) = (-x(i+1)^2 + x(i+1))/2;
  x1(i) = x(i+1);
end


y = a\b;			% Solve the linear system of equations.
norm(y-uexact,inf)		% Estimate the error in the infinity norm.
plot(x1,y,'o')
hold

x2=0:0.01:1; 			% Get the exact solution at many points
nn = length(x2);		% to plot the exact solution.

for i=1:nn
%y2(i)=(-x2(i)^2 + x2(i))/2;	% Problem (a).
   if x2(i) <= 0.5
      y2(i) =  x2(i)/2;
   else
      y2(i) = (1-x2(i))/2;
   end
end

%y2(i)=(-x2(i)^2 + x2(i))/2;

plot(x2,y2)

