function yp = yprft(t,y)

global d e et k M c kt Mt ct

l = length(y);
yp = zeros(l,1);

   yp(1) =-d*y(1) + e*y(1)*y(2) + et*y(1)*y(3);
   yp(2) = k*(M- y(2))*y(2) -c*y(1)*y(2);
   yp(3) = kt*(Mt - y(3))*y(3) -ct*y(1)*y(3);
