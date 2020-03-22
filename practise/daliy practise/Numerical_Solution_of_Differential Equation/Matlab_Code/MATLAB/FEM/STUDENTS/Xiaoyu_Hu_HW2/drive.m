
clear all; close all;   % Clear every thing so it won't mess up with other
                        % existing variables.

%%%%%% Generate a triangulation
Pi=3.141592653589;
 x(1)=0; x(4)=3*Pi/4; x(2)=Pi/4; x(3)=Pi/2; x(5)=Pi; 

%%%%%% Call fem1d function to get the FEM solution at nodal points.

U = fem1d(x);

%%%%%% Compare errors:

x2 = 0:0.001:Pi; k2 = length(x2);
for i=1:k2,
  u_fem(i) = fem_soln(x,U,x2(i));  % Compute FEM solution at x2(i)
end

plot(x2,u_fem,'-.')   % Solid: the exact, %dotted: FEM solution
hold; plot(x,U,'o')   % Mark the solution at nodal points.
xlabel('x'); ylabel('u_{fem}(x)'); 
title('Dotted line: FEM solution')
