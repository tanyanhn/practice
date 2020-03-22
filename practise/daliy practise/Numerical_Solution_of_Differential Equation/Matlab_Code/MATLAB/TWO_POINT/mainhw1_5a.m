
%%%%%%%% Clear all unwanted variable and graphs.

clear;  close all

%%%%%%% Input 

a =0; b=pi; n=160;
ua = cos(pi*a); ub = cos(pi*b);

%%%%%% Call solver: U is 

[x,U] = two_pointhw1_5a(a,b,ua,ub,'fhw1_5a',n);

%%%%%%%%%%%%%%%%%%% Plot and error analysis: %%%%%%%%%%%%%%%%%%%

plot(x,U,'o'); hold

u=zeros(n-1,1);
for i=1:n-1,
  u(i) = cos(pi*x(i));
end
plot(x,u)

%%%%%%% Plot error

figure(2); plot(x,U-u)

norm(U-u,inf)		%%% Print out the maximum error.
