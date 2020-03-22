
%%%%%%%% Clear all unwanted variable and graphs.

clear;  close all

%%%%%%% Input 

a =0; b=1/2; 
ua = 1; uxb = -pi;

%%%%%% Call solver: U is 

n=10;
k=1;

for k=1:5
    [x,U] = two_pointa(a,b,ua,uxb,'f',n);  %ghost-point method.
%    [x,U] = two_pointb(a,b,ua,uxb,'f',n);  %Backward Difference 
  u=zeros(n,1);
  for i=1:n,
    u(i) = cos(pi*x(i));
  end

  h(k) = 1/n;
  e(k) = norm(U-u,inf);		%%% Print out the maximum error.
  k = k+1; n=2*n;
end

loglog(h,e,h,e,'o'); axis('equal'); axis('square'), 
%title('The error plot in log-log scale, the slope = 2'); % Ghost point
title('The error plot in log-log scale, the slope = 1'); % BW
figure(2); plot(x,U-u); title('Error')

