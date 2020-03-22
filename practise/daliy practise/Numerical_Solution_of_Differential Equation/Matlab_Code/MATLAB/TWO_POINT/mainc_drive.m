
%%%%%%%% Clear all unwanted variable and graphs.

clear;  close all

%%%%%%% Input 

a =0; b=1; 
ua = 1; aa=2; bb=-3; cc=0;

%%%%%% Call solver: U is 

n=40;

    [x,U] = two_pointc(a,b,ua,aa,bb,cc,'f3_1',n);  %ghost-point method.
  u=zeros(n,1);
  for i=1:n,
    u(i) = exp(-x(i))*(x(i)-1)^2;
  end

  % Add BC at x=a;  
      u=[ua
         u ];   U=[ua
                   U]; x=[a x];

  e = norm(U-u,inf)		%%% Print out the maximum error.
figure(1); plot(x,U,'o', x,u); title('Computed and exact solutions')
figure(2); plot(x,U-u); title('Error')

