
function yp = yprf(t,y)

global b c d e

k = length(y);
yp = zeros(k,1);

yp(1) = -b*y(1) + c*y(1)*y(2);  % Should be function of y(1), y(2), ...
yp(2) = d*y(2) - e*y(1)*y(2);
