
function yp = format_f(x,y)

k = length(y);
yp = zeros(k,1);

yp(1) = y(2)         ;       % Should be function of y(1), y(2), ...
yp(2) = -y(1)        ;
