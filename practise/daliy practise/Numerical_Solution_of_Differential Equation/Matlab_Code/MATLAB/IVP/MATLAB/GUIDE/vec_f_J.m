  function [f,J] = vec_f_J(x)
    k = length(x);                 % Find the length of the input x
    f = zeros(k,1);                % Output is a column vector
    J = zeros(k,k);
    f(1) = x(1)^2 - x(2)^3;
    f(2) = sin(x(1)) + x(2) -1;
    J(1,1) = 2*x(1); J(1,2) = -3*x(2)^2;
    J(2,1) = cos(x(1)); J(2,2) = 1;
  return

