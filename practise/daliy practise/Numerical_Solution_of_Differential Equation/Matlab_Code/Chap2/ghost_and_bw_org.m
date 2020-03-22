
%%%%%%%% Clear all unwanted variable and graphs.

clear;  close all

%%%%%%% Input 

a =0; b=1/2; 
ua = 1; uxb = -pi;

%%%%%% Call solver: U is the results from the backwad method, Ug is
%%     the results from the ghost point method

n=10;
k=1;

for k=1:5
    [x,Ug] = ghost_at_b(a,b,ua,uxb,'f',n);  %ghost-point method.
     [x,U] = bw_at_b(a,b,ua,uxb,'f',n);  %Backward Difference
  u=zeros(n,1);
  for i=1:n,
    u(i) = cos(pi*x(i));
  end

  h(k) = 1/n;
  eg(k) = norm(Ug-u,inf);		%%% Print out the maximum error.
  e(k) = norm(U-u,inf);
  k = k+1; n=2*n;
end

loglog(h,eg,h,e); axis('square')
axis([1e-4 5e+0 1e-5 5e-1]);
title('Grid refiment analysis and comparison'); 
gtext('The 1st order method: slope = 1')
gtext('The ghost point method: slope = 2')
xlabel('The step size h')
ylabel('Error')
figure(2); plot(x,Ug-u); title('Error from the ghost point method')
axis('square'); xlabel('x'); ylabel('Error')
