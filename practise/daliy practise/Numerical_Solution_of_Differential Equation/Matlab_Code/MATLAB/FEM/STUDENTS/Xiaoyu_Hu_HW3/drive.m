
clear all; close all;   % Clear every thing so it won't mess up with other
                        % existing variables.

%%%%%% Generate a triangulation

%  x(1)=0; x(2)=0.1; x(3)=0.3; x(4)=0.333; x(5)=0.5; x(6)=0.75;x(7)=1;
   pi=3.1415926;
%    x(1)=0; x(2)=pi/2; x(3)=pi;
   x=0:0.01:pi;

%%%%%% Call fem1d function to get the FEM solution at nodal points.

U = fem1d(x);

%%%%%% Compare errors:

x2 = 0:0.01:pi; k2 = length(x2);
for i=1:k2,
  u_exact(i) = soln(x2(i));
  u_fem(i) = fem_soln(x,U,x2(i));  % Compute FEM solution at x2(i)
end

error = norm(u_fem-u_exact,inf)  % Compute the infinity error
   
figure(3);plot(x2,u_fem,'-.', x2,u_exact)   % Solid: the exact, %dotted: FEM solution
% hold; plot(x,U,'o')              % Mark the solution at nodal points.
xlabel('x'); ylabel('u_f(x) & u_{h}(x)'); 
title('Solid line: solution with V_f, Dotted line: solution with V_h')

figure(4); plot(x2,u_fem-u_exact); title('Difference plot')   
xlabel('x'); ylabel('u_{f}-u_{h}');  title('Difference Plot')
