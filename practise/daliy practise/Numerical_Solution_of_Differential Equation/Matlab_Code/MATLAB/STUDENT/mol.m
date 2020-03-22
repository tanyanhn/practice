
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                      %
%    Example of Method of Line for the heat equation                   %
%                                                                      %
%          u_t = u_{xx} + f(x,t)                                       %
%                                                                      %
%    Using Matlab built in function ode23s or ode15s.                  %
%                                                                      %
%    Test problme:                                                     %
%                 Exact solution: u(t,x) = exp(-t) sin(pi*x)           %
%                 Source term:    f(t,x) = exp(-t) sin(pi*x)(pi^2-1)   %
%                                                                      %
%    Files needed for the test:                                        %
%                                                                      %
%     mol.m:      This file, the main calling code.                    %
%     yfun_mol.m: The file defines the ODE system                      %
%     ux_mol.m:   The exact solution.                                  %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


clear; close;

global n h x

a = 0; b=1; n=80; tfinal = 1;

h=(b-a)/n; tspan=[0,tfinal];

x= zeros(n-1,1);
for i=1:n-1;
  x(i) = a + i*h;
  y0(i) = ux_mol(0,x(i));
end

[t y] = ode23s('yfun_mol',tspan,y0);

[mr,nc] = size(y);  y_mol=y(mr,:);
for i=1:n-1,
  ye(i) = ux_mol(tfinal,x(i));
end

e = max(abs(ye-y_mol))
plot(x,ye); hold
plot(x,y_mol,'o')

