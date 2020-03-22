
clear; close all

 a = 0;  b=1; 
  m = 10; n=50;
 m = 20; n= 50;

 h = (b-a)/m;
  k = h^2/2;
% k = h^2/1.2;
% k = h^2/1.3;

 t = 0;
 for i=1:m+1,
   x(i) = a + (i-1)*h;
   y1(i) = uexact(t,x(i));
   y2(i) = 0;
 end

 tau = k/h^2;

 t = 0;
 for j=1:n,
   y1(1)=0; y1(m+1)=0;
   for i=2:m
     y2(i) = y1(i) + tau*(y1(i-1)-2*y1(i)+y1(i+1)) + k*f(t,x(i));
   end
   t = t + k;
   y1 = y2;
 end

 for i=1:m+1
   u_e(i) = uexact(t,x(i));
 end

 max(abs(u_e-y2))

 plot(x,y2,':',x,u_e)
   



