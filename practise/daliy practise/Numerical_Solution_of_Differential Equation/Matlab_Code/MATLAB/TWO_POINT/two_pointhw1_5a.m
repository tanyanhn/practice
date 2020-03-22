
function [x,U] = two_pointhw1_5a(a,b,ua,ub,f,n)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%    This matlab function two_point solvers the following two-point    %
%    boundary value problem: u''(x) + p(x) u'(x) +q(x) u(x) = f(x),    %
%    where p(x) = 1 + x^2, q(x) = x, f(x) = -pi^2 cos(pi x)            %
%    -(1+x^2) pi sin(pi x) + x cos(pi x)										  % 	
%    using the center difference 												  %
%    scheme.                                                           %  
%                                                                      %
%    Input:                                                            %
%     a, b: Two end points.                                            %
%     ua, ub: Dirichlet boundary conditions at a and b                 %
%     f: external function f(x).                                       %
%     n: number of grid points.                                        %
%                                                                      %
%    Output:                                                           %
%     x: x(1),x(2),...x(n-1) are grid points                           %
%     U: U(1),U(2),...U(n-1) are approximate solution at the grid      %
%     points   %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

h = (b-a)/n; h1=h*h;

A = sparse(n-1,n-1);
F = zeros(n-1,1);

for i=1:n-1,
  x(i) = a+i*h;
  F(i) = feval(f,x(i));
end
  F(1) = F(1) - ua/h1 + (1+x(1)^2)*ua/(2*h);
  F(n-1) = F(n-1) - ub/h1 - (1+x(n-1)^2)*ub/(2*h);
	

for i=1:n-2,
   A(i,i) = -2/h1+x(i); A(i,i+1) = 1/h1+(1+x(i)^2)/(2*h);
%   A(i+1,i) = 1/h1-(1+x(i)^2)/(2*h); 
	A(i+1,i) = 1/h1-(1+x(i+1)^2)/(2*h);
end
  A(n-1,n-1) = -2/h1+x(n-1);

U = A\F;

return

