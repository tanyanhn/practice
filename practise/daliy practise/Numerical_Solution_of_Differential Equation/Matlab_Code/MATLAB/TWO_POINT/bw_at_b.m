
function [x,U] = bw_at_b(a,b,ua,uxb,f,n)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%    This matlab function bw_at_b solves the following two-point       %
%    boundary value problem: u''(x) = f(x) using backward difference   %
%    scheme.                                                           %  
%    Input:                                                            %
%     a, b: Two end points.                                            %
%     ua, uxb: Dirichlet and Neumann boundary conditions at a and b    %
%     f: external function f(x).                                       %
%     n: number of grid points.                                        %
%    Output:                                                           %
%     x: x(1),x(2),...x(n-1), x(n) are grid points                     %
%     U: U(1),U(2),...U(n) are approximate solution at grid points.    %
%    The method is first order accurate unless uxb=0. When uxb=0, it   %
%    is second order accurate.                                         %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

h = (b-a)/n; h1=h*h;

A = sparse(n,n);
F = zeros(n,1);
        
for i=1:n-1,
  A(i,i) = -2/h1; A(i+1,i) = 1/h1; A(i,i+1)= 1/h1;
end
  A(n,n) = -1/h;
  A(n,n-1) = -1/h1;

for i=1:n
  x(i) = a+i*h;
  F(i) = feval(f,x(i));
end
  F(1) = F(1) - ua/h1;
  F(n) = uxb;
	
U = A\F;

return
