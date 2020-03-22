
function U = fem1d(x)        

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                    %
%                   Simple Matlab code for 1D FEM for                %
%                                                                    %
%                    -u'' = f(x),   a <= x <= b, u(a)=u(b)=0         %
%    Input: x, Nodal points                                          %
%    Output: U, FEM solution at nodal points                         %
%                                                                    %
%    Function needed: f(x).                                          %
%                                                                    % 
%    Matlab functions used:                                          %
%                                                                    %
%     hat1(x,x1,x2), hat function in [x1,x2] that is 1 at x2; and    %
%     0 at x1.                                                       %
%                                                                    %
%     hat2(x,x1,x2), hat function in [x1,x2] that is 0 at x1; and    %
%     1 at x1.                                                       %
%                                                                    %
%     int_hat1_f(x1,x2): Contribution to the load vector from hat1   %
%     int_hat2_f(x1,x2): Contribution to the load vector from hat2   %
%                                                                    %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                                    
M = length(x);
for i=1:M-1,
  h(i) = x(i+1)-x(i);
end
 
A = sparse(M,M); F=zeros(M,1);           % Initialize
A(1,1) = 1; F(1)=0;
A(M,M) = 1; F(M)=0;
A(2,2) = 1/h(1); F(2) = int_hat1_f(x(1),x(2));

for i=2:M-2,
  A(i,i) = A(i,i) + 1/h(i);
  A(i,i+1)   = A(i,i+1) - 1/h(i);
  A(i+1,i)   = A(i+1,i) - 1/h(i);
  A(i+1,i+1) = A(i+1,i+1) + 1/h(i);
  F(i)       = F(i) + int_hat2_f(x(i),x(i+1));
  F(i+1)     = F(i+1) + int_hat1_f(x(i),x(i+1));
end

  A(M-1,M-1) = A(M-1,M-1) + 1/h(M-1);
  F(M-1)     = F(M-1) + int_hat2_f(x(M-1),x(M));

  U = A\F;

  return

