
function y=del4(x,h)

x1=abs(x);

if( x1 > h) 
  y = 0;
else
%  y = (h-x)/h;
   y = 1;
end
