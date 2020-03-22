
    function [xk,xc,xq,xf] = getmat(x);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                    %
%   function returns the material parameters of the two points       %
%   boundary value problems                                          %
%                                                                    %
%         -(k(x) u_x)_x + c(x) u_x + q(x) u(x) = f(x)                %
%                                                                    %
%--------------------------------------------------------------------%

%    xk = 1;
%    xc = 0;
%    xq = 0;

%   xf = 6;
%    xf = sin(x);

     xk = 1+x;
     xc = cos(x);
     xq = x*x;
     xf = (1+x)*sin(x)-cos(x)+cos(x)*cos(x)+x*x*sin(x);

    return 

%--------------------------- END OF GETMAT ----------------------------- 

