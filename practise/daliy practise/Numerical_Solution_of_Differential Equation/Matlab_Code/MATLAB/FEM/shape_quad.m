
m=100; h=2/m;
x=-1:h:1;
y1=zeros(m+1,1); y2=y1; y3=y1;

for j=1:m+1
  [y1(j),y2(j),y3(j)] = fem_quad(x(j),-1, 1) ;
end

plot(x,y1,x,y2,x,y3)

hold
x3 = -1.2:0.2:1.2; y3=0*x3; plot(x3,y3,':')
axis([-1.05 1.05 -.2 1.05])


