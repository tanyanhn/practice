close all;clear all;
% input values      
a = 0; b = 1; n = 80;coeff1=2.0;coeff2=-3.0;

 [A,F] = sa_cfd(a,b,coeff1,coeff2,n);

U=F\A;
U=U';

h=(b-a)/n;
 for  i = 1:n
x=a+i*h;
U_exact=exp(-x)*(x-1)^2;
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
title('CENTRAL DIFFERENCE SCHEME for SELF-ADOINT BVP','FontSize',14);
grid on;

