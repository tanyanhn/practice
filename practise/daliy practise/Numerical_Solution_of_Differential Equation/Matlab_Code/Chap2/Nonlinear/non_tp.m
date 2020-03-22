%%% Solve non-linear ODE u''-u^2 = f(x), u(0)=u(1)=0; f=-sin(x)-sin(x)^2

close all; clear all;

m = 40; h=pi/m; N=m-1;

x=0:h:pi;  x=x'; ue=sin(x); % mesh and true soln

uc =  x.*(pi -x);  % initial guess:
b = -sin(x) - sin(x).^2; % right hand side

plot(x,uc)
%title('initial guess')
pause(2)
hold on

u1=uc(2:m); F=b(2:m);  % Take off two BC
e = ones(N,1); R=e;     % initial set-up
tol = 1.e-8; err = 10.0;

% begin iterations of Newton's method:
k = 0; kmax=1000;
while err > tol & k <kmax
   
  for i=1:N
     jac(i,i)=-2*(1+h^2*u1(i))/h^2;  % Jacobian diagonals.
     R(i) = (uc(i)-2*uc(i+1)-(h*uc(i+1))^2+uc(i+2))/h^2 - F(i);
  end
  
  for i=1:N-1
   jac(i,i+1) = 1/h^2; jac(i+1,i)=1/h^2; % Jacobian off diagonals.
  end
  
  delta = -jac\R;
  u2 = u1 + delta;
  k = k + 1;
  err = max(abs(u2-u1))
  u1 = u2; 
  uc=[0
      u2
      0];
  plot(x,uc)

end

set(gca,'FontSize',18);
set(0,'DefaulttextFontSize',18)
  max(abs(uc-ue))
figure(2); plot(x,uc,x,ue)
title('Final and computed solution')
figure(3); plot(x,uc-ue)
title('The error')
k               % Show number of iterations.


