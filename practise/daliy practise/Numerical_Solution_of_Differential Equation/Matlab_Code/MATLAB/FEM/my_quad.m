
m=3; h=1/m;
x=0:h:1; z=0:h/2:1;
x1=0:1/1000:1;

n=length(x1); A=zeros(2*m+1,n);
for k=1:2:2*m+1
   for j=1:n     % compute at x1(j)
      i= fix( x1(j)/h) + 1; 
        if i==m+1
          i=m;
        end
          xl=x(i); xr=x(i+1);
          if abs(x((k+1)/2)-x1(j)) <=h
            [y1,y2,y3] = fem_quad(x1(j),xl,xr);
            if x1(j) >= x((k+1)/2)
              A(k,j) = y1;  
            else
               A(k,j) = y3;
            end
         end
   end
end

   for j=1:n     % compute the last one
        xl=x(m); xr=x(m+1);
        if abs(x(m+1)-x1(j)) <=h
            [y1,y2,y3] = fem_quad(x1(j),xl,xr);
            A(2*m+1,j) = y3;
        end
  end

for k=2:2:2*m
   for j=1:n     % compute at x1(j)
      i= fix( x1(j)/h) + 1; 
        if i==m+1
          i=m;
        end
          xl=x(i); xr=x(i+1);
          if abs(x(k/2)-x1(j)) <=h
            [y1,y2,y3] = fem_quad(x1(j),xl,xr);
             A(k,j) = y2;  
         end
   end
end

subplot(211)
 plot(x1,A(1,:), x1,A(3,:),x1,A(5,:),x1,A(7,:),x1,A(2,:), x1,A(4,:),x1,A(6,:))


