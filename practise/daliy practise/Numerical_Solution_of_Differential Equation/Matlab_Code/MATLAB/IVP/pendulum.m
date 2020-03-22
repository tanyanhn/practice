
function yp = pendulum(x,y)

global m c k 
k1 = length(y);
yp = zeros(k1,1);

yp(1) =  y(2)        ;       % Should be function of y(1), y(2), ...
yp(2) =  -k *sin(y(1))/m - c* y(2)/m       ;

