
function yp = format_f(t,y)

global a b

k = length(y);
yp = zeros(k,1);

yp(1) = a - (b+1)*y(1) + y(1)^2*y(2);    
yp(2) = b*y(1) - y(1)^2 * y(2) ;
