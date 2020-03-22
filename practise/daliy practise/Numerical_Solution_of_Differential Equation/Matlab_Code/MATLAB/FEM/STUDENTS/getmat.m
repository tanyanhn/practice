   function [xk,xc,xq,xf] = getmat(x);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                    %
% function returns the meterial parameters of the two poiunts        %
% boundary value problems                                            %
%    -(k(x)u_x)_x + c(x) u_x + b(x) u(x) = f(x)                      %
%                                                                    %
%--------------------------------------------------------------------%

     xk = 0;
     xc = 0;
     xq = 1;
     xf = 0;

%   xk = 1+x*x;
%   xc = 1;
%   xq = exp(-x);
%   xf = -exp(x)*cos(x)*(1+2*x*x+2*x)-sin(x)*(2*x*exp(x)-exp(x)-1);

  return

%---------------- END OF GETMAT -------------------------------------%
