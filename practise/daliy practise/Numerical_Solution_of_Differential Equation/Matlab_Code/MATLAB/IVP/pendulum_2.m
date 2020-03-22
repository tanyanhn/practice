function [ yp ] = pendulum_2( t,y )

global K c

k1 = length(y);  % Find the dimension of y.

yp = zeros(k1,1);

yp(1) = y(2);
yp(2) = - K*sin(y(1)) -c*y(2);

end

