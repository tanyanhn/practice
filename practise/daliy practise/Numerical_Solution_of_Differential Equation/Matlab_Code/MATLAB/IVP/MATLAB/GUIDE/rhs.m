
function yp = rhs(x,y)

yp = zeros(length(y),1);             % Set output as a column vector.

yp(1) = y(2);
yp(2) = -y(1);

return
