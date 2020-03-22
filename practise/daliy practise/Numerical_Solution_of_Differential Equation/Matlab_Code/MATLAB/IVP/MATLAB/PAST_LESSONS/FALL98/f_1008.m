
function yp = f_1008(x,y)
 
k = length(y);
yp = zeros(k,1);
 
yp(1) = y(2);  
yp(2) = (-x*y(1) - 2*y(2))/(1+ x*x);         ;

