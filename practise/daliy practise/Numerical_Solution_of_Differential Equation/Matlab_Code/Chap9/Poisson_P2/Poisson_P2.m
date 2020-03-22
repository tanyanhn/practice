function Poisson_P2
%% OK!
% -nu*\laplace u=f in \Omega
%  u=0 on \partial\Omega
% u=x(1-x)y(1-y)
% f=2*nu*(y(1-y)+x(1-x))

for level=0:4
    n=1*2^level;
    h=1/n;

    N=2*n;
    H=1/N;
    nele=2*n^2;
    nunk=(N+1)^2;

    for node=1:nunk %% coordinates of P2
        i=mod(node-1,N+1);  % line
        j=fix((node-1)/(N+1));   % collu
        coordinate(node,1)=i*H;
        coordinate(node,2)=j*H;
    end

    element(1,1) = 1;
    element(1,2) = 3;
    element(1,3) = 2*N + 3;
    element(1,4) = 2;
    element(1,5) = N + 3;
    element(1,6) = N + 2;

    element(2,1) = 2*N + 5;
    element(2,2) = 2*N + 3;
    element(2,3) = 3;
    element(2,4) = 2*N + 4;
    element(2,5) = N + 3;
    element(2,6) = N + 4;
    for i = 3 : 2 * n
        element(i,1:6) = element(i-2,1:6) + 2;
    end
    for i = 2 * n + 1 : nele
        element(i,1:6) = element(i-2*n,1:6) + 2 * ( N + 1);
    end
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    a=sparse(nunk,nunk);   
    f=sparse(nunk,1);
    [a, f] = assemble( element, nele, nunk, n );

    u=a\f;

    uu=exact(coordinate, nunk);
    norm(uu-(u(1:nunk))')

    %% draw figures %%
    x=0:H:1;
    y=0:H:1;
    figure(n);
    perr=reshape(abs(uu-u'),N+1,N+1);
    surf(y,x,perr);
    figure(n+1);
    up=reshape(u',N+1,N+1);
    surf(y,x,up);
end

save Poisson.mat
