
    function [data] = datain(a,b,nnode,nelem)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                    %
%   function datain provides partion information for one-dimensional %
%   finite element method. By chossing suitable data, we can generate%
%   the nodes with equal spacing in various sections of the grid     %
%   Reference: Finite element. An introduction by E.Becker, G.Carey, %
%   and J.Oden, Vol.1., pp. 101-102.                                 %
%--------------------------------------------------------------------%
%   
    h=(b-a)/(nnode-1);
    x = zeros(nnode,1);
    for i=1:nnode,
      x(i) = a +(i-1)*h;
    end

    for i=1:nnode,
     data(i,1) = i;
     data(i,2) = 0;
     data(i,3) = x(i);
     data(i,4) = x(i);
    end

   return

%--------------------------- END OF DATAIN -----------------------------

