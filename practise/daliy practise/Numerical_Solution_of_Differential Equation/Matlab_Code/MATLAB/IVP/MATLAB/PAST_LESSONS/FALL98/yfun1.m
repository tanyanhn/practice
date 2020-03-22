function yp = yfun1(t,y)

l = length(y);
yp = zeros(l,1);

yp(1) = -y(1)        ;       % Should be function of y(1), y(2), ...

