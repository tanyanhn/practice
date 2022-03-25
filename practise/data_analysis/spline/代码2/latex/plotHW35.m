figure(1);
x=-1.5:0.01:2.5;
y=0.5.*((x+1).^2).*(x>=-1 & x<=0)+(0.5.*(x+1).*(1-x)+0.5.*(2-x).*x).*(x>0 & x <=1)+ 0.5.*((2-x).^2).*(x>1 & x<=2);
plot(x,y,'LineWidth',3);
title('Quadratic B-splines');
saveas(1,'QuadBspline.png');