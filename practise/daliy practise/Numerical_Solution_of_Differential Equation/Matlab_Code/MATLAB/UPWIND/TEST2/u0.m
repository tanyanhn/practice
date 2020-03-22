function y = u0(x)

if x >= 0.1 & x <=0.2,
  y = 1.0;
else
  y = 0.0;
end

% y = sin(x);                % y \in C^0, L-W: 0-1-st order
% y = sin(x)*sin(x);         % y \in C^1, L-W: 1-st order.
% y= sin(x)*sin(x)*sin(x);   % L-W: 2nd order
