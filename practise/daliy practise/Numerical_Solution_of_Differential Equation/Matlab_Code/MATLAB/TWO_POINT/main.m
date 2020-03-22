
%%%%%%%% Clear all unwanted variable and graphs.

clear;  close all

%%%%%%% Input 

a =0; b=1; n=40;
ua = 1; ub = -1;

%%%%%% Call solver: U is 

[x,U] = two_point(a,b,ua,ub,'f',n);

%%%%%%%%%%%%%%%%%%% Plot and error analysis: %%%%%%%%%%%%%%%%%%%

plot(x,U,'o'); set(gca,'FontSize',18);  hold

u=zeros(n-1,1);
for i=1:n-1,
  u(i) = cos(pi*x(i));
end
plot(x,u)

%%%%%%% Plot error

figure(2); plot(x,U-u)
set(gca,'FontSize',18);

norm(U-u,inf)		%%% Print out the maximum error.
