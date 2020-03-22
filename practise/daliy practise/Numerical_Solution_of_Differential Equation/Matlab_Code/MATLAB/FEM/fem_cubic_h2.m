
function [y1,y2,y3,y4] = fem_cubic_h2(x)

% This function compute the cubic shape functions [-1,1] in H^2 space.

y1 = (x-1)^2*(x+2)/4; 
y2 = (x+1)^2*(-x+2)/4; 
y3 = (x-1)^2*(x+1)/4;
y4 = (x+1)^2*(x-1)/4;
return
