
clear; close all
x0 = 0; x_final=20; y0=[1,-1]; n=200;
[x, y] = euler2(x0,x_final,'f_1008',y0,n);

%--- Plot the solution.

y1=y(:,1); y2=y(:,2);
figure(1); plot(x,y1); xlabel('x'); ylabel('y_1');
figure(2); plot(x,y2); xlabel('x'); ylabel('y_2');
figure(3); plot(y1,y2); xlabel('y_1'); ylabel('y_2');


