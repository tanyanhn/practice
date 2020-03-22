
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%    
%    This program solves Poisson equation
%       u_{xx} + u_{yy} = f(x,y),  a < x <b,  c < y < d.
%    with Dirichlet boundary condition along x=b, y=c, y=d, and a 
%    Neumann BC at x=a. 
%    
%    Computed result:
%    m = 10, n=20       0.0021
%    m=20; n=40;	5.1077e-04	4.1114
%    m = 40; n=80	1.2756e-04	4.0042

clear;  close all

a = 1; b=2; c = -1; d=1;

m=32; n=64;

hx = (b-a)/m; hx1 = hx*hx; x=zeros(m+1,1);
for i=1:m+1,
  x(i) = a + (i-1)*hx;
end

hy = (d-c)/n; hy1 = hy*hy; y=zeros(n+1,1);
for i=1:n+1,
  y(i) = c + (i-1)*hy;
end


M = (n-1)*m; A = sparse(M,M); bf = zeros(M,1);

for j = 1:n-1,
  for i=1:m,
    k = i + (j-1)*m;
    bf(k) = f(x(i),y(j+1));
    A(k,k) = -2/hx1 -2/hy1;
    if i == 1
        A(k,k+1) = 2/hx1;
        bf(k) = bf(k) + 2*ux(y(j+1))/hx;
    else
       if i==m
         A(k,k-1) = 1/hx1;
         bf(k) = bf(k) - ue(x(i+1),y(j+1))/hx1;
       else
	  A(k,k-1) = 1/hx1;
	  A(k,k+1) = 1/hx1;
       end
    end

%-- y direction --------------

    if j == 1
        A(k,k+m) = 1/hy1;
        bf(k) = bf(k) - ue(x(i),c)/hy1;
    else
       if j==n-1
         A(k,k-m) = 1/hy1;
         bf(k) = bf(k) - ue(x(i),d)/hy1;
       else
          A(k,k-m) = 1/hy1;
          A(k,k+m) = 1/hy1;
       end
     end

  end
end

  U = A \bf;

%--- Transform back to (i,j) form to plot the solution ---


j = 1;
for k=1:M
  i = k - (j-1)*m ;
  u(i,j) = U(k);
  u2(i,j) = ue(x(i),y(j+1));
  j = fix(k/m) + 1;
end

% Analyze abd Visualize the result.

e = max( max( abs(u-u2)))        % The maximum error
x1=x(1:m); y1=y(2:n);

set(gca,'FontSize',18);
mesh(y1,x1,u); title('The solution plot'); xlabel('y'); ylabel('x');
figure(2); set(gca,'FontSize',18);
mesh(y1,x1,u-u2); title('The error plot'); xlabel('y');
ylabel('x');
