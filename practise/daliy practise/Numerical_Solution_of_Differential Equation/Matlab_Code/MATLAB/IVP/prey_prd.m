
function yp = prey_prd(t,y)

global a b c d

k = length(y);
yp = zeros(k,1);

yp(1) = a*y(1) - b*y(1)*y(2) - 10*t*t;  % Should be function of y(1), y(2), ...
yp(2) = -c*y(2) + d*y(1)*y(2);
