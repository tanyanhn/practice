
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% SOR iteration for  u_xx + u_yy = f(x,y)
% Dirichlet BC on all boundaries.
% Exact solution: u(x,y) = exp(x) sin(pi y)
%                 f(x,y) = (1 - pi^2) sin(pi y) exp(x)
% Files needed for this code: fcn.m for f(x,y), uexact.m for the
% exact solutions, poisson_sor.m is this file.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear;  close all 
n = input('Enter the grid lines in x or y direction ')
region = zeros(1,4);
region = input('Enter the domain as [a b c d] ')
omega = input('Enter relaxation parameter between 1 and 2 ')
tol = input('Enter error tolerance, say 1e-5 ')

a = region(1); b = region(2); c = region(3); d=region(4);
h= (b-a)/n;   h1=h*h;
x = a:h:b;    y = c:h:d;
u2 = zeros(n+1,n+1);              % The solution component
u1 = 100*ones(n+1,n+1); 
f = zeros(n+1,n+1);

for i=1:n+1			% Get f_{ij}
  for j=1:n+1
    f(i,j) = fcn(x(i),y(j));
  end
end

for i=1:n+1
  u2(1,i) = uexact(a,y(i));
  u2(n+1,i) = uexact(b,y(i));
  u2(i,1) = uexact(x(i),c);
  u2(i,n+1) = uexact(x(i),d);
end

k = 0;
while  max(max(abs(u1-u2))) > tol
k = k+1;
  u1 = u2;
  for i=2:n
    for j=2:n
      u2(i,j) = (1-omega)*u1(i,j) + omega*( (u2(i-1,j)+u2(i+1,j) ...
                 +u2(i,j-1)+u2(i,j+1))*0.25 -h1*f(i,j)/4 );
    end
  end
end

%-- after converge -------------------

disp('The number of iteration is:'); k
for i=1:n+1,
  for j=1:n+1,
    usol(i,j) = uexact(x(i),y(j));
  end
end

e = max(max(abs(u2-usol)))
figure(1); mesh(x,y,u2); title('The computed solution')
figure(2); mesh(x,y,u2-usol); title('The error plot')




