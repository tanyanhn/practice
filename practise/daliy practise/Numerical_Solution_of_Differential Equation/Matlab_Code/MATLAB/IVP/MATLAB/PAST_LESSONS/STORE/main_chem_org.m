
% Define the symbolic function.

F=sym('77.27*(y-x*y+x-8.375e-06*x*x), (-y-x*y+z)/77.27, 0.161*(x-z)');
v=sym('[x,y,z]');

% Find the Jacobian matrix:        [ f_x,f_y,f_z
%                                    g_x,g_y,g_z
%                                    h_x,h_y,h_z ]

A=jacobian(F,v);

[x1,y1,z1]=solve(F)              % Solve for all equilibriums.
k = length(y1);

EIGA = zeros(3,k);
                                 % Find all the eigenvalues corresponding
                                 % to the equilibriums.
for i=1:k,
  v1 = sym([x1(i),y1(i),z1(i)]);
  A1 = numeric( subs(A,v,v1) );
  EIGA(:,i) =  eig(A1);
end

EIGA		       % First column contains the three eigenvalues of 
                       % the first equilibrium and so for other columns.

%%%%%%%%%%% Now we are solve the problem numerically and plot the solution

clear

flops(0);
tspan=[0,1000]; y0=[1 1 1]; 
%[x,y]=ode15s('chemistry',tspan,y0);
%[x,y]=ode23s('chemistry',tspan,y0);
options = odeset('reltol',1e-4, 'Stats', 'on');      % Set certain options.
[x,y]=ode23s('chemistry',tspan,y0,options);
flops
y1 = y(:,1); y2 = y(:,2); y3=y(:,3);

figure(1); plot(x,y1) 
figure(2); plot(x,y2)
figure(3); plot(x,y3)

figure(4); plot3(y1,y2,y3); axis('square');               % Phase plot.

disp('Strike any key to continue')
disp(' ')
pause

close all

figure(1); semilogy(x,y1); 
%axis([0,20,0.1,1e6]);
figure(2); semilogy(x,y2)
figure(3); semilogy(x,y3)





