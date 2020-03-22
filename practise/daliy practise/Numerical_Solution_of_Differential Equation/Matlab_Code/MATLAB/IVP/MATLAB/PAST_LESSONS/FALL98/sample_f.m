
function yp = format_f(x,y)

k = length(y);
yp = zeros(k,1);

global a b c d e f g h

yp(1) = -a*y(1) + b*y(1)*y(2);    % Should be function of y(1), y(2), ...
yp(2) = -c*y(2) -d*y(1)*y(2)+e*y(2)*y(3);
yp(3) = f*y(3) - g*y(3)^2 - h*y(2)*y(3);


%%%%%%% Text Book: Ch. 6.13, page: 112
