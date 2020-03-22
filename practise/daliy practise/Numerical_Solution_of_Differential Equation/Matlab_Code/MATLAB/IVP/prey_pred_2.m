function [ yp ] = prey_pred_2( t,y )

global a b c d 

k1 = length(y);  % Find the dimension of y.

yp = zeros(k1,1);

yp(1) = a*y(1)-b*y(1)*y(2);
yp(2) = - c*y(2) + d*y(1)*y(2);

end

