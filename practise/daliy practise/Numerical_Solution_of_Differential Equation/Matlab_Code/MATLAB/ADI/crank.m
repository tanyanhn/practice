
clear; close all

 a = 0;  b=1; m = 10; 
 h = (b-a)/m;  k = h; h1=h*h;

 tfinal = 0.5; n=fix(tfinal/k);

 t = 0;
 for i=1:m+1,
   x(i) = a + (i-1)*h;
   u0(i) = uexact(t,x(i));
 end

%-------- Set-up the coefficient matrix for Dirichlet BC -----------

A = sparse(m+1,m+1);
for i=2:m,
  A(i,i) = 1/k+1/h1; A(i,i-1) = -0.5/h1; A(i,i+1)= -0.5/h1;
end
  A(1,1) = 1;
  A(m+1,m+1) = 1;

  b = zeros(m+1,1);

%--------------- Time Iteration --------------------------------

 for j=1:n,

   for i=2:m
     b(i) = u0(i)/k + 0.5*(u0(i-1)-2*u0(i)+u0(i+1))/h1 + f(t+0.5*k,x(i));
   end
     b(1) =  g1(t+k);                      % Dirichlet BC at x =a.
     b(m+1) = g2(t+k);                     % Dirichlet BC at x =b.

   u1 = A\b;
   t = t + k;
   u0 = u1;
 end

 u_e = zeros(m+1,1);
 for i=1:m+1
   u_e(i) = uexact(t,x(i));
 end

 e_inf = max(abs(u_e-u1));
 disp('m, final_time, error'); [m,t,e_inf]
 plot(x,u1,':',x,u_e)
   



