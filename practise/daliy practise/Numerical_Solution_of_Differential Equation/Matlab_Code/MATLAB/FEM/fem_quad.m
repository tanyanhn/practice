
function [y1,y2,y3] = fem_quad(x,x1,x2)

% This function compute the quadratic basis functions over  [x1,x2].

z=(x1+x2)/2;

y1 = (x-z)*(x-x2)/((x1-z)*(x1-x2) );
y2 = (x-x1)*(x-x2)/((z-x1)*(z-x2) );
y3 = (x-x1)*(x-z)/((x2-x1)*(x2-z) );

return
