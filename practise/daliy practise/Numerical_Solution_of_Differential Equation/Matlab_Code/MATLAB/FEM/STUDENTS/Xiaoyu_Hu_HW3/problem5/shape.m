
  function [psi,dpsi]=shape(xi,n);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                    %
%   Function ``shape'' evaluates the values of the basis functions   %
%   and their derivatives at a point xi.                             %
%                                                                    %
%   n: The basis function. n=2, linear, n=3, quadratic, n=4, cubic.  %
%   xi: The point where the base function is evaluated.              %
%   Output:                                                          %
%   psi:  The value of the base function at xi.                      %
%   dpsi: The derivative of the base function at xi.                 %
%   Reference: Finite element. An introduction y E.Becker, G.Carey,  %
%   and J.Oden, Vol.1., pp. 95-96.                                   %
%--------------------------------------------------------------------%

   switch n
   case 2,
     % Linear base function
     psi(1) = (1-xi)/2;
     psi(2) = (1+xi)/2;
     dpsi(1) = -0.5;
     dpsi(2) = 0.5;  
     return

   case 3,
     % quadratic base function
     psi(1) = xi*(xi-1)/2;
     psi(2) = 1-xi*xi;
     psi(3) = xi*(xi+1)/2;
     dpsi(1) =  xi-0.5;
     dpsi(2) = -2*xi;
     dpsi(3) = xi + 0.5;
     return

   case 4,
     % cubic  base function
     psi(1) = 9*(1/9-xi*xi)*(xi-1)/16;
     psi(2) = 27*(1-xi*xi)*(1/3-xi)/16;
     psi(3) = 27*(1-xi*xi)*(1/3+xi)/16;
     psi(4) = -9*(1/9-xi*xi)*(1+xi)/16;

     dpsi(1) = -9*(3*xi*xi-2*xi-1/9)/16;
     dpsi(2) = 27*(3*xi*xi-2*xi/3-1)/16;
     dpsi(3) = 27*(-3*xi*xi-2*xi/3+1)/16;
     dpsi(4) = -9*(-3*xi*xi-2*xi+1/9)/16;
     return

   end

%--------------------------- END OF SHAPE -----------------------------

