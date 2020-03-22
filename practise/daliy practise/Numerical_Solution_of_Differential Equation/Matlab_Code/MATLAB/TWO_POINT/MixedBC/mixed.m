
function [x, u] = mixed(a,b,aa,bb,cc,n)

A = sparse(n+1,n+1);  bf= zeros(n+1,1);
h = (b-a)/n;  h1 = h*h; h2=0.5*h;
for i=0:n
  x(i+1) = a + i*h;
end

for i=2:n,
   A(i,i-1) = beta(x(i)-h2)/h1;
   A(i,i+1) = beta(x(i)+h2)/h1;
   A(i,i) = -( A(i,i-1) + A(i,i+1) ) - gama(x(i));
   bf(i) = rhs(x(i));
end
  
  bf(1) = rhs(x(1));
  bf(n+1) = rhs(x(n+1));

%%%% Boundary condition ------------------------------------

  i = 1;
  A(1,1) = -( beta(x(i)-h2) + beta(x(i)+h2) )/h1 - gama(x(i));
  A(1,1) = A(1,1) + 2*aa*beta(x(i)-h2)/(h*bb);
  A(1,2) = ( beta(x(i)-h2) + beta(x(i)+h2) )/h1;
  bf(1) = bf(1) +  2 *cc*beta(x(i)-h2)/(h*bb);

%%%% At another end x = b ------------------------------------

  i = n+1;
  A(i,i) = -( beta(x(i)-h2) + beta(x(i)+h2) )/h1 - gama(x(i));
  A(i,i-1) = ( beta(x(i)-h2) + beta(x(i)-h2) )/h1;

  u = A\bf;
  



