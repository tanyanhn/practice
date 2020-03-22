
function [tmesh,ysol] = euler2(a,b,yfun,y0,n)

%
% solve a system of initial value problems by the second order
% modified Euler method
%
%               y' = yfun(t,y)
%
%              on the interval [a,b] with initial contitions
%              y(a) = y0
% 
%              and stepsize h = (b-a)/n
%
% Input: a, b: endpoints of interval
%        yfun: the name of the function that defines the nonlinearity
%              the format of yfun should be (look at the examples, yfun1.m
%              and yfun2.m) 
%
%              function yp = yfun(t,y)
%
%        y0: initial value (row vector!!! if there are mdim equations,
%                           y0 should be an 1 x mdim vector
%         n: number of timesteps
%
% Output: ysol: the solution 
%               if there are mdim equations, ysol is an n+1 x mdim matrix
%         tmesh: the values of t, this is useful for plotting and
%                checking errors. It will be more useful when we begin
%                to vary the meshsize
%
% HINT: if Matlab complains that "matrix dimensions must agree", check to
%       see if you're adding row vectors to column vectors by using the
%       size command.
%
% It's part of your job to modify the demos to get this to work, add the
% new demo problem, and demonstrate second order accuracy
%

h=(b-a)/n;

%
% how many equations are there?
%

mdim=length(y0);
%
% initialize ysol to a matrix of zeros, ditto for tmesh
%

ysol=zeros(n+1,mdim);
tmesh=zeros(n+1,1); 

%
% put the initial value in the first row. 
%
ysol(1,:)=y0;
t=a; tmesh(1)=t;
%
% main solver loop
%
for i=1:n
    t=t+h; tmesh(i+1)=t;
    f1=feval(yfun,t,ysol(i,:));
    f2=feval(yfun,t+h,ysol(i,:)+h*f1');
    ysol(i+1,:)=ysol(i,:)+h*.5*(f1'+f2');
end
