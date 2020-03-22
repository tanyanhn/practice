
% Test Euler's method for y'= -11y;  y(0) = 1; y(t) = exp(-11 t)
clear all; close all;

T=2; n= 100; h=0.1/2^2;  yf(1)=1; yb(1)=1;  t(1)=0; ye(1) = 1;

h=0.1/2^4;

N=fix(T/h);

for i=1:N+1
  yf(i+1) = yf(i) +h *(-11*yf(i));
  yb(i+1) = yb(i)/(1+h*11);
  t(i+1) = t(i) + h;
  ye(i+1) = exp(-11*t(i+1));
end

norm(ye-yf,inf), norm(ye-yb,inf)

figure(1)
plot(t,yf,t,yb,t,ye)

figure(2) 
plot(t,ye-yf,t,ye-yb)

