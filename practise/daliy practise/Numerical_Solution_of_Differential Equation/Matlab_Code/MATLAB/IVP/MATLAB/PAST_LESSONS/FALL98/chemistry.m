
function yp = chemistry(x,y)

l = length(y);
yp = zeros(l,1);

yp(1) = 77.27*(y(2)-y(1)*y(2)+y(1)-8.375e-6*y(1)^2);
yp(2) = (-y(2) - y(1)*y(2) + y(3)) / 77.27 ;
yp(3) = 0.161 * (y(1) - y(3)) ;
