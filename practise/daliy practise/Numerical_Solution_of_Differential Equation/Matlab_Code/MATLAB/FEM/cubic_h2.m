
m=100; h=2/m;
x=-1:h:1; 
y1=zeros(m+1,1); y2=y1; y3=y1; y4=y1;

for j=1:m+1
   [y1(j),y2(j),y3(j),y4(j)] = fem_cubic_h2(x(j)) ;
end
    
 plot(x,y1,x,y2,x,y3,x,y4)
 


