close all;clear all;
% input values      
a = 0; b = 1; n = 50; Ua=1; Ub=3;

epsilon=0.1;

 [A,B] = cfd1(a,b,n,epsilon,Ua,Ub);

U=A\B;

h=(b-a)/n;
 for  i = 1:n-1
   x(i) =a+i*h;
 end

U1 =1+ x + (exp((x-1)/epsilon)-exp(-1/epsilon))/(1-exp(-1/epsilon));
U1=U1';

plot(x,U);
figure(2); plot(x,U-U1)
pause(50)

U1=(exp((x-1)/epsilon)-exp(-1/epsilon))/(1-exp(-1/epsilon));
U_exact=1 + x + U1;
i,h,x,U1,U_exact
draw(i,1)=i;
draw(i,2)=x;
draw(i,3)=U(i,1);
draw(i,4)=U_exact;
end


V1=figure;
plot(draw(:,2),draw(:,3));
hold on;
plot(draw(:,2),draw(:,4),'r o -');
xlabel('i','FontSize',14);
ylabel('U','FontSize',14);
title('CENTRAL DIFFERENCE SCHEME','FontSize',14);
grid on;

