close all; clear all;
format short e;

m = 79; tend = 2*pi; h = tend/(m+1);

t = ((1:m)*h)'; alf = 0.7; beta = 0.7;

% initial guess:
theta = alf*cos(t) + 0.5*sin(t);

plot([0;t;tend], [alf;theta;beta])
% ([0;t;tend]: add 0, tend to t; add alf, beta to theta

title('initial guess')
pause(2)
%query
hold on

% set up matrix A corresponding to central difference operator for
%      second derivative  (using sparse matrix storage):

e = ones(m,1);
a = spdiags([e -2*e e], [-1 0 1], m, m);

% begin iterations of Newton's method:
tol = 1.e-8;
err = 100.0

k = 0;
while err > tol

  % Jacobian:
  jac = a + spdiags(h^2*cos(theta), 0, m, m);

  % Right-hand side:
  f = a*theta + h^2 * sin(theta);
  f(1) = f(1) + alf;
  f(m) = f(m) + beta;

  delta = jac\f;
  theta1 = theta-delta;
  k = k + 1;
  err = max(abs(theta1-theta))
  theta = theta1;
  plot([0;t;tend], [alf;theta;beta])

  end

figure(2); plot([0;t;tend], [alf;theta;beta])
title('Final solution')
k               % Show number of iterations.

% Solution to the linear problem.

e = ones(m,1);
a = spdiags([e -2*e + h*h e], [-1 0 1], m, m);
b=zeros(m,1); b(1)=-alf; b(m) = -beta;
theta1 = a\b;
figure(2); hold
plot([0;t;tend], [alf;theta1;beta], ':')
figure(3); plot([0;t;tend], [0; theta1-theta;0])
max(abs(theta1-theta))
title('difference between linear and non-linear soln')
