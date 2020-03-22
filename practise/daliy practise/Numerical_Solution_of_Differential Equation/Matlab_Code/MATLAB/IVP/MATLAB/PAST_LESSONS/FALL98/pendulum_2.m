
function yp = pendulum_1(x,y)

global w d
k = length(y);
yp = zeros(k,1);

yp(1) =  y(2)        ;       % Should be function of y(1), y(2), ...
yp(2) =  -w*w*sin(y(1)) - d* y(2)       ;

