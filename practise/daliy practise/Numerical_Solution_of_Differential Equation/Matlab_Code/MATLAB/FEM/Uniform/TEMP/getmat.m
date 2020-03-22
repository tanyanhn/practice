
    function [xk,xc,xb,xf] = getmat(x);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                    %
%   function returns the material parameters of the two points       %
%   boundary value problems                                          %
%                                                                    %
%         -(k(x) u_x)_x + c(x) u_x + b(x) u(x) = f(x)                %
%                                                                    %
%--------------------------------------------------------------------%

%    xk = 1;
%    xc = 0;
%    xb = 0;

%   xf = 6;
%    xf = sin(x);

     xk = 1+x;
     xc = cos(x);
     xb = x*x;
     xf = (1+x)*sin(x)-cos(x)+cos(x)*cos(x)+x*x*sin(x);

aa=1; bb=2;
if x <1/3
  xk = aa;
elseif x == 1/3
  xk = 0.5*(aa+bb);
else
  xk = bb;
end
  
xc = 0;
xb=0.0;
xf=-12*x*x;

xk=0;
xc=0;
xb=-1;
xf=0;
    return 

%--------------------------- END OF GETMAT ----------------------------- 

