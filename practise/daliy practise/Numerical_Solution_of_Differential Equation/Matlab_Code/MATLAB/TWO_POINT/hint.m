
% How to produce the matrix for Problem 4? The answer is provided below:

A = sparse(n-1;n-1);
F = zeros(n-1,1);

........

for i=1:n-3,
  A(i,i) = 1/h1; A(i,i+1) = -2/h1; A(i,i+2)= 1/h1;
end

for i=1:n-1,
  x(i) = a+i*h;
  F(i) = feval(f,x(i));
end

  A(n-2,n-2) = 1/h1; A(n-2,n-1) = -2/h1;
  F(n-2) = F(n-2) - ub/h1;

% Use the central scheme at $x=x(n-1)$.
  A(n-1,n-2) = 1/h1; A(n-1,n-1) = -2/h1; 
  F(n-1) = F(n-1) -ub/h1;

