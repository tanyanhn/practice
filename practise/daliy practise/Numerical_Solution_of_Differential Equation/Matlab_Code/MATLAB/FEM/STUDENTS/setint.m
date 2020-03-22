 function [xi,w] = setint

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                    %
%  Function setint provides the integration points x(i), and the     %
%  weights of the Gaussian quadrature formula.                       %
%  Output:                                                           %
%     x(4,4):  x(:,i) is the Gaussian points of order i.             %
%     w(4,4):  w(:,i) is the weights of quadrature of order i.       %
%                                                                    %
% Reference: Finite element, An introduction, Vol. 1 by E.Becker,    %
% G.Carey, and J.Oden, pp. 94.                                       %
%--------------------------------------------------------------------%

  clear x
  clear w

     xi(1,1) = 0;
     w(1,1) = 2;		% Gaussian quadrature of order 1

     xi(1,2) = -1/sqrt(3);
     xi(2,2) = -xi(1,2);
     w(1,2) = 1;
     w(2,2) = w(1,2);		% Gaussian quadrature of order 2

     xi(1,3) = -sqrt(3/5);
     xi(2,3) = 0;
     xi(3,3) = -xi(1,3);
     w(1,3) = 5/9;
     w(2,3) = 8/9;
     w(3,3) = w(1,3);	        % Gaussian quadrature of order 3

     xi(1,4) = - 0.8611363116;
     xi(2,4) = - 0.3399810436;
     xi(3,4) = -xi(2,4);
     xi(4,4) = -xi(1,4);
     w(1,4) = 0.3478548451;
     w(2,4) = 0.6521451549;
     w(3,4) = w(2,4);
     w(4,4) = w(1,4);		% Gaussian quadrature of order 4

     return

%--------------------------- END OF SETINT -----------------------------

