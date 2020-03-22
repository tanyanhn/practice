
function U = fem1d(x)        

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                    %
%                   Simple Matlab code for 1D FEM for                %
%                                                                    %
%            -(pu')' + qu = f(x),   a <= x <= b, u(a)=u(b)=0         %
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

% added by XYH to get stiffness mattix and load vector for -(pu')'+qu=f
A(1,1) = 1/h(1)+(x(1)+x(2))/2/h(1)+h(1)/3  + 2/3; 
A(M,M) = 1/h(M-1)+(x(M-1)+x(M))/2/h(M-1)+h(M-1)/3; 
A(M-1,M) = - 1/h(M-1)-(x(M-1)+x(M))/2/h(M-1)+ h(M-1)/6; 
A(M,M-1) = - 1/h(M-1)-(x(M-1)+x(M))/2/h(M-1)+ h(M-1)/6;
A(1,2) = - 1/h(1)-(x(1)+x(2))/2/h(1)+ h(1)/6;
A(2,1) = - 1/h(1)-(x(1)+x(2))/2/h(1)+ h(1)/6;
A(2,2) = 1/h(1)+(x(2)+x(1))/2/h(1)+h(1)/3; 
F(1) = int_hat2_f(x(1),x(2))+1;
F(M) = int_hat1_f(x(M-1),x(M)) +(3.1415926+1);
F(2) = int_hat1_f(x(1),x(2));

for i=2:M-2
    A(i,i)     = A(i,i) + 1/h(i)+(x(i)+x(i+1))/2/h(i)+h(i)/3;
    A(i,i+1)   = A(i,i+1) - 1/h(i)-(x(i)+x(i+1))/2/h(i)+ h(i)/6;
    A(i+1,i)   = A(i+1,i) - 1/h(i)-(x(i)+x(i+1))/2/h(i)+ h(i)/6;
    A(i+1,i+1) = A(i+1,i+1) + 1/h(i)+(x(i)+x(i+1))/2/h(i)+h(i)/3;
    F(i)       = F(i) + int_hat2_f(x(i),x(i+1));
    F(i+1)     = F(i+1)+ int_hat1_f(x(i),x(i+1));
end
  A(M-1,M-1) = A(M-1,M-1) + 1/h(M-1)+(x(M-1)+x(M))/2/h(M-1)+h(M-1)/3;
  F(M-1)     = F(M-1) + int_hat2_f(x(M-1),x(M));

  U = A\F;
  
  return

