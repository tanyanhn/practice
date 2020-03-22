
clear all; close all;   

alf = 1/3; a=0; b=1; n=20; bl=100; br=1; bjump=br-bl;
h=(b-a)/n; x=a:h:b; x=x'; 

v = -1/(br*alf + bl*(1-alf) );

U = fem1d(x,bl,br,alf,v);

%%%%%% Compare errors:

%x2 = 0:0.01:1; k2 = length(x2);
%for i=1:k2,
%  u_exact(i) = uexact(x2(i),bl,br,alf); 
%  u_fem(i) = fem_soln(x,U,x2(i));  % Compute FEM solution at x2(i)
% end

u_exact=zeros(n+1,1);
for i=1:n+1
   u_exact(i) = uexact(x(i),bl,br,alf);
end

%error = norm(u_fem-u_exact,inf)  % Compute the infinity error
norm(U-u_exact,inf)
   
plot(x,U,'o',x,u_exact)
% plot(x2,u_fem,':', x2,u_exact)   % Solid: the exact, %dotted: FEM solution
% hold; plot(x,U,'o')              % Mark the solution at nodal points.
% xlabel('x'); ylabel('u(x) & u_{fem}(x)'); 
% title('Solid line: Exact solution, Dotted line: FEM solution')

% figure(2); plot(x2,u_fem-u_exact); title('Error plot')   
% xlabel('x'); ylabel('u-u_{fem}');  title('Error Plot')
