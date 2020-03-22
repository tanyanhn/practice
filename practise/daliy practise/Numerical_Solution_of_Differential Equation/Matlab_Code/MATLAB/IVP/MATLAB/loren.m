
function yp = loren(x,y)

l = length(y);
yp = zeros(l,1);

global r

b = 8/3;
tau = 10;

yp(1) = - tau*y(1) + tau*y(2);
yp(2) = -y(1)*y(3) + r*y(1) - y(2);
yp(3) = y(1)*y(2) - b*y(3);

