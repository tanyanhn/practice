
clear; close all

xspan = [0, 6*pi];                  % Starting and ending points.
y0 = [1, 0]';                       % Initial condition as column vector
[x,y] = ode45('rhs',xspan, y0);     % Solve IVP using ode45

y1 = y(:,1); y2=y(:,2);             % Extract solution components
plot(x,y1,x,y2)                     % Plot the solution versus tiem
figure(2); plot(y1,y2)              % Plot the first solution versus
                                    % the second one, phase plot.
figure(1); print -deps fig1.eps
figure(2); print -deps fig2.eps     % Save plots.

