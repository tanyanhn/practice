
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Matlab Code for HW#1 Problem 3.
%  Files involved: main_h1_3.m, this file.
%      mixed.m: the main Matlab function for the problem.
%      rhs.m:   the f(x)
%      beta.m, gama.m, the coefficients
%     
%  Test results in the infinity norm.
%       n = 10, 	e = 0.0077		
%         = 20,		e = 0.0019	4.0526
%         = 40,		e = 4.8300e-04	3.9337
%         = 80,		e = 1.2077e-04	3.9993
%         = 160,	e = 3.0195e-05	3.9997
%
%%%%%%%% Clear all unwanted variable and graphs.

clear;  close all

%%%%%%% Input 

a =0; b=1; n=160;
aa = 2; bb = -3; cc=11;

%%%%%% Call solver: U is 

[x,U] = mixed(a,b,aa,bb,cc,n);

%%%%%%%%%%%%%%%%%%% Plot and error analysis: %%%%%%%%%%%%%%%%%%%

plot(x,U,'o'); hold

u=zeros(n-1,1);
for i=1:n+1,
  u(i) = exp(-x(i))*(1-x(i))^2;
end
plot(x,u)

%%%%%%% Plot error

figure(2); plot(x,U-u)

norm(U-u,inf)		%%% Print out the maximum error.
