
% Compare truncation errors of the forward, backward, and central
% scheme for approximating u'(x). Plot the error and estimate the
% convergence order.

%    u(x) = sin(x) at x=1.   Exact u'(1) = cos(1)

clear; close all
  h = 0.1;i=1;
  % for i=1:5,
  while h>1e-16
    a(i,1) = h;
    a(i,2) = (sin(1+h)-sin(1))/h - cos(1);
    a(i,3) = (sin(1) - sin(1-h))/h - cos(1);
    a(i,4) = (sin(1+h)-sin(1-h))/(2*h)- cos(1);
    h = h/2; i=i+1;
  end

  format short e
  a		% Display the result

  a = abs(a);	   % Take absolute value of the matrix.
  h1 = a(:,1);	   % Extract the first column which is h.
  e1 = a(:,2); e2 = a(:,3); e3 = a(:,4);

  loglog(h1,e1,h1,e2,h1,e3) 
  axis('square')
  axis([1e-12 1e1 1e-12 1e1])
  title('A grid refinement analysis & comparison')
  xlabel('Step size h')
  ylabel('Error')
  
  gtext('Slope of FW and BW = 1')
  gtext('Slope of CD = 2')

%%%%%%%%%%%%%%%%% End Of Matlab Program %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Computed Results:

%      h          forward      backward     central

%   1.0000e-01  -4.2939e-02   4.1138e-02  -9.0005e-04
%   5.0000e-02  -2.1257e-02   2.0807e-02  -2.2510e-04
%   2.5000e-02  -1.0574e-02   1.0462e-02  -5.6280e-05
%   1.2500e-02  -5.2732e-03   5.2451e-03  -1.4070e-05
%   6.2500e-03  -2.6331e-03   2.6261e-03  -3.5176e-06


