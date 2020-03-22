
x0=0; xfinal=0.2;y0=[1,0]; n=1;
%[x,y] = rk4_sol(x0,xfinal,'test',y0,n)
[x,y] = euler2(x0,xfinal,'test',y0,n)
