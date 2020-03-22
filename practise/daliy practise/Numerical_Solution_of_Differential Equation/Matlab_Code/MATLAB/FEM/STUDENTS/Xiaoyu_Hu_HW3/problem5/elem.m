
   function [ek,ef] = elem(x1,x2,n,nl,xi,w)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                      %
%   function elem evaluates the stiffness matrix gk and the right      %
%   hand side gf.                                                      %
%  x1,x2 : Coordinates x1 and x2 of the ends of the element.           %
%  n     : Number of nodal points (and shape functions) in the element.%
%  nl    :  Order of the integration rule of Gaussian formula, 1,2,3,4 %
%  xi(l) :  The value of the global coordinate at an integration point.%
%  w(l)  :  The integration weights.                                   %
%  dx    :  dx/d\xi = *x2-x1)/2                                        %
%  psi(i),dps(i): The value of shape functions and their derivatives   %
%  xk,xc,xb,xf: values of the material properties at x_l obtained bt   %
%  calling getmat(x).                                                  %
%                                                                      %
%  Functions called: getmat(x); shape(xi(l),n)                         %
%  Reference: Finite element. An introduction by E.Becker, G.Carey,    %
%  and J.Oden, Vol.1., pp. 97-99.                                      %
%--------------------------------------------------------------------%  

   dx = (x2-x1)/2;
   
% Initialize element arrays

  ef = zeros(n,1);
  ek = zeros(n,n);

% Begin integration point loop

  for l=1:nl,
    x = x1 + (1.0 + xi(l))*dx;
    [xk,xc,xb,xf] = getmat(x);
    [psi,dpsi] = shape(xi(l),n);

    for i=1:n,
       ef(i) = ef(i) + psi(i)*xf*w(l)*dx;
       for j=1:n,
          ek(i,j)=ek(i,j)+(xk*dpsi(i)*dpsi(j)/(dx*dx) ...
               +xc*psi(i)*dpsi(j)/dx+xb*psi(i)*psi(j) )*w(l)*dx;
       end
    end
  end

  return

%--------------------------- END OF ELEM -----------------------------

