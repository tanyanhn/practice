
function yp = chemistry(t,y)

k = length(y);
yp = zeros(k,1);

yp(1) = 50*(y(2)-y(1)*y(2)-0.1*y(1)^2);
yp(2) = (-y(2) - y(1)*y(2) + 2*y(3)) / 40 ;
yp(3) =  (y(1) - y(3) - y(1)*y(2)) ;
