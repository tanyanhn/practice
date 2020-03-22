
function [x,U] = two_pointc(a,b,ua,aa,bb,cc,f,n)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%    This matlab function two_point solvers the following two-point    %
%    boundary value problem: u''(x) = f(x) using center difference     %
%    scheme for mixed BC: aa u(b) + bb u'(b) = cc.                     %  
%    Input:                                                            %
%     a, b: Two end points.                                            %
%     ua, uxb: Dirichlet and Neumann boundary conditions at a and b    %
%     f: external function f(x).                                       %
%     n: number of grid points.                                        %
%    Output:                                                           %
%     x: x(1),x(2),...x(n-1),x(n) are grid points                      %
%     U: U(1),U(2),...U(n) are approximate solution at grid points.    %
%    The method is second order accurate.                              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

h = (b-a)/n; h1=h*h; 

A = sparse(n,n);
F = zeros(n,1);
        
for i=1:n,
  x(i) = a+i*h;
  F(i) = feval(f,x(i));
end

for i=1:n-1
  xl = x(i) - h/2;  xr = x(i) + h/2;
  A(i,i) = -(mb(xl) + mb(xr))/h1 - ga(x(i)); 
  A(i+1,i) = mb(xr)/h1; A(i,i+1)= mb(xr)/h1;
end

  i=n; xl = x(i) - h/2;  xr = x(i) + h/2;
  tmp = mb(xl)/( mb(xl) + mb(xr));
  A(i,i) =  - (mb(xl)/h1 + tmp*( ga(x(i)) + 2 *aa *mb(xr)/(bb*h) )) ;
  A(i,n-1) = mb(xl)/h1;

  F(1) = F(1) - ua/h1;
  F(i) = tmp*( F(i) - 2 *cc * mb(xr)/(bb*h) );
	
U = A\F;

return
