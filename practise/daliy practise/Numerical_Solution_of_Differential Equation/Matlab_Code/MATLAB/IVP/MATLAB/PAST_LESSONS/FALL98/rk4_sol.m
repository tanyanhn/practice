function [tmesh,ysol]=rk4_sol(a,b,yfun,y0,n)

%
% Solve a system of initial value problems by the fourth order Runge-Kutta
% method, where the initial value problem is of the form
%           
%              y' = yfun(t,y)
%
% on the interval [a,b] with the initial conditions y(a) = y0 and stepsize
% h = (b-a)/n.
%
% Input:  a, b: endpoints of the interval
%         yfun: the name of the MATLAB function that defines y'
%         y0: initial values
%         n: number of time steps
%
% Output: ysol: the solution - if there are mdim equations, ysol is an
%               n+1 x mdim matrix
%         tmesh: the values of the spatial mesh points.                
%

h = (b-a)/n;

[ijunk, mdim] = size(y0);
ysol = zeros(n+1, mdim);
tmesh = zeros(n+1, 1);
ysol(1,:) = y0;
t = a; tmesh(1) = t;

%
% This is the loop that implements RK4.  Note that there are four function
% evaluations for each time step.
%

for i = 1:n
   k1 = h*feval(yfun,tmesh(i),ysol(i,:))';
   k2 = h*feval(yfun,tmesh(i)+(1/2)*h,ysol(i,:)+k1/2)';
   k3 = h*feval(yfun,tmesh(i)+(1/2)*h,ysol(i,:)+k2/2)';
   k4 = h*feval(yfun,tmesh(i)+h,ysol(i,:)+k3)';
   ysol(i+1,:) = ysol(i,:) + (1/6)*(k1+2*k2+2*k3+k4);
   t = t + h; tmesh(i+1) = t;
end

