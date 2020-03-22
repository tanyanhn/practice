function [tmesh,ysol,stats] = rkf45_sol(a,b,yfun,y0,tol)

%
% solve a system of initial value problem with the RKF 45 method
%
% This is a front end to Shampines ode45.m code to make it look like
% the solvers we've been using.
%

%options=odeset('rtol',tol,'atol',tol);
options=odeset('reltol',tol,'AbsTol',tol);
range=zeros(1,2); range(1)=a; range(2)=b;

[tmesh, ysol, stats]=ode45(yfun, range, y0, options);
