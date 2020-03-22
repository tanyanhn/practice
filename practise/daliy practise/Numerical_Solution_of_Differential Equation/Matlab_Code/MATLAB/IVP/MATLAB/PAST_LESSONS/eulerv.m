% your name, your student number, lesson number 
clear; 
y(1) =200; tol = 0.01; h = 0.01; t(1)= 0.; 

k = 1; 
while (t(k)<20) & (k<2000)  
  t(k+1) = t(k) + h; 
  ye = y(k) + h*flr(t(k),y(k));
  y(k+1) = y(k) + 0.5*h*(flr(t(k),y(k)) + flr(t(k),ye));
       h = h*sqrt( tol/(abs(ye-y(k+1))+1e-14) );
  k = k+1;
end 
k
plot(t,y)
title('your name, your student number, lesson number') 
xlabel('time') 
ylabel('the solution') 

