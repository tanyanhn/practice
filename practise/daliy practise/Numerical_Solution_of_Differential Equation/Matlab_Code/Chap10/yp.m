function yp = yp(t,y)
k = length(y); yp = zeros(k,1); % detect the dimension of the problem, using column vector.
  yp(1) = y(2);           % Definition of f(t,y) in terms of y(1), y(2), ..., y(k).
  yp(2) = -y(1) + y(1)*y(2);
