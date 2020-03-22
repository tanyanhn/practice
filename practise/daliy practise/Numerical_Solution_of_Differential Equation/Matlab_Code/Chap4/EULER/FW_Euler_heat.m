
clear; close all
a = 0; b =1; 
m = 10; n=20;

h = (b-a)/m;
k2 = h^2/2;
k = 2*h^2/1.0;

t = 0;
for i=1:m+1,
   x(i) = a + (i-1)*h; y1(i) = uexact(t,x(i)); y2(i) = 0; y4(i)=0;
end

tau = k/h^2;
tau2 = k2/h^2; 
plot(x,y1,'k'); hold

y3=y1; y4=y1;

t = 0; t2=0;
for j=1:n,
  y1(1)=0; y1(m+1)=0;
  for i=2:m
    y2(i) = y1(i) + tau*(y1(i-1)-2*y1(i)+y1(i+1)) + k*f(t,x(i));
    y4(i) = y3(i) + tau2*(y3(i-1)-2*y3(i)+y3(i+1)) + k2*f(t2,x(i));
  end
  plot(x,y2,'r'); pause(0.25)
  t = t + k;  t2=t2+k2;
  y1 = y2; y3=y4; 
end

 for i=1:m+1
   u_e(i) = uexact(t,x(i));
   u_e2(i) = uexact(t2,x(i));
 end

 max(abs(u_e-y2)), max(abs(u_e-y4))

 figure(1); plot(x,y2,'k*',x,u_e,x,y4,'bo',x,u_e2,'b')
 figure(2); plot(x,y2-u_e,'k', x,y4-u_e2,'b')
   



