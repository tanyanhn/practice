x=-1:0.1:2; l=length(x);
for i=1:l,                      % Use a loop to find the function value
   if x(i) < 0
     y(i) = -x(i);
   else
     if x(i) <= 1
        y(i) = x(i)*x(i);
     else
        y(i) = log(x(i));
     end
   end
end
close all
plot(x,y)
print -deps plot3.eps

