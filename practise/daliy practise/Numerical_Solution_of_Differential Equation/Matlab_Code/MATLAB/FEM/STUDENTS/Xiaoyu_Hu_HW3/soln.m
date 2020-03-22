
function u = soln(xx)

 FF=zeros(3,1);
 pi=3.1415926;

syms x ;
FF(1,1)=int(x,x,0,pi)+pi;
FF(2,1)=int(sin(x),x,0,pi);
FF(3,1)=int(sin(2*x),x,0,pi);

AA=zeros(3,3);

AA(1,1)=int(1+x^2,x,0,pi)+pi^2;
AA(1,2)=int(cos(x)+x*sin(x),x,0,pi);
AA(1,3)=int(2*cos(2*x)+x*sin(2*x),x,0,pi);
AA(2,1)=AA(1,2);
AA(2,2)=pi;
AA(2,3)=int(2*cos(x)*cos(2*x)+sin(x)*sin(2*x),x,0,pi);
AA(3,1)=AA(1,3);
AA(3,2)=AA(2,3);
AA(3,3)=int(3*cos(2*x)*cos(2*x)+1,x,0,pi);

UU=AA\FF;

u=UU(1,1)*xx+UU(2,1)*sin(xx)+UU(3,1)*sin(2*xx);
end
