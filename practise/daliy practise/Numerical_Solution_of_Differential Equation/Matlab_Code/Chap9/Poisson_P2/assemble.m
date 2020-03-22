function [a, f] = assemble( element, nele, nunk, n )

nu=1.0;

a=sparse(nunk,nunk);
f=sparse(nunk,1);

h=1/n;
hh=h^2;

q6a = 0.124949503233232;
q6b = 0.437525248383384;
q6v = 0.205950504760887;
q6c = 0.797112651860071;
q6d = 0.165409927389841;
q6e = 0.037477420750088;
q6w = 0.063691414286223;
q6xy=zeros(6,2);
for ele=1:nele    
    a(element(ele,1),element(ele,1))=a(element(ele,1),element(ele,1)) + nu;
    a(element(ele,2),element(ele,2))=a(element(ele,2),element(ele,2)) + nu/2;
    a(element(ele,3),element(ele,3))=a(element(ele,3),element(ele,3)) + nu/2;
    a(element(ele,1),element(ele,2))=a(element(ele,1),element(ele,2)) + nu/6;
    a(element(ele,2),element(ele,1))=a(element(ele,2),element(ele,1)) + nu/6;
    a(element(ele,1),element(ele,3))=a(element(ele,1),element(ele,3)) + nu/6;
    a(element(ele,3),element(ele,1))=a(element(ele,3),element(ele,1)) + nu/6;
    
    a(element(ele,4),element(ele,4))=a(element(ele,4),element(ele,4)) + nu*8/3;
    a(element(ele,5),element(ele,5))=a(element(ele,5),element(ele,5)) + nu*8/3;
    a(element(ele,6),element(ele,6))=a(element(ele,6),element(ele,6)) + nu*8/3;
    a(element(ele,4),element(ele,5))=a(element(ele,4),element(ele,5)) - nu*4/3;
    a(element(ele,5),element(ele,4))=a(element(ele,5),element(ele,4)) - nu*4/3;
    a(element(ele,5),element(ele,6))=a(element(ele,5),element(ele,6)) - nu*4/3;
    a(element(ele,6),element(ele,5))=a(element(ele,6),element(ele,5)) - nu*4/3;
    
    a(element(ele,1),element(ele,4))=a(element(ele,1),element(ele,4)) - nu*2/3;
    a(element(ele,4),element(ele,1))=a(element(ele,4),element(ele,1)) - nu*2/3;
    a(element(ele,1),element(ele,6))=a(element(ele,1),element(ele,6)) - nu*2/3;
    a(element(ele,6),element(ele,1))=a(element(ele,6),element(ele,1)) - nu*2/3;
    a(element(ele,2),element(ele,4))=a(element(ele,2),element(ele,4)) - nu*2/3;
    a(element(ele,4),element(ele,2))=a(element(ele,4),element(ele,2)) - nu*2/3;
    a(element(ele,3),element(ele,6))=a(element(ele,3),element(ele,6)) - nu*2/3;
    a(element(ele,6),element(ele,3))=a(element(ele,6),element(ele,3)) - nu*2/3;
    
    if mod(ele,2)==1
        j=mod((ele-1),2*n)/2;  % line
        k=fix((ele-1)/(2*n));   % collu
        x3 = j*h;
        y3 = k*h;
        x1 = x3+h;
        y1 = y3;
        x2 = x3;
        y2 = y3+h;
        f1=0;
        f2=0;
        f3=0;
        f4=0;
        f5=0;
        f6=0;
        q6xy(1,1)=q6a*x1+q6b*x2+q6b*x3;
        q6xy(1,2)=q6a*y1+q6b*y2+q6b*y3;
        q6xy(2,1)=q6b*x1+q6a*x2+q6b*x3;
        q6xy(2,2)=q6b*y1+q6a*y2+q6b*y3;
        q6xy(3,1)=q6b*x1+q6b*x2+q6a*x3;
        q6xy(3,2)=q6b*y1+q6b*y2+q6a*y3;
        for i=1:3
            f1=f1+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( (1-(q6xy(i,1)-x3)/h-(q6xy(i,2)-y3)/h).*(1-2*(q6xy(i,1)-x3)/h-2*(q6xy(i,2)-y3)/h) )*q6v;
            f2=f2+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( (q6xy(i,1)-x3)/h*(2*(q6xy(i,1)-x3)/h-1) )*q6v;
            f3=f3+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( (q6xy(i,2)-y3)/h*(2*(q6xy(i,2)-y3)/h-1) )*q6v;
            f4=f4+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( 4*(q6xy(i,1)-x3)/h*(1-(q6xy(i,1)-x3)/h-(q6xy(i,2)-y3)/h) )*q6v;
            f5=f5+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( 4*(q6xy(i,1)-x3)/h*(q6xy(i,2)-y3)/h )*q6v;
            f6=f6+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( 4*(q6xy(i,2)-y3)/h*(1-(q6xy(i,1)-x3)/h-(q6xy(i,2)-y3)/h) )*q6v;
        end
        q6xy(1,1)=q6c*x1+q6d*x2+q6e*x3;
        q6xy(1,2)=q6c*y1+q6d*y2+q6e*y3;
        q6xy(2,1)=q6c*x1+q6e*x2+q6d*x3;
        q6xy(2,2)=q6c*y1+q6e*y2+q6d*y3;
        q6xy(3,1)=q6d*x1+q6c*x2+q6e*x3;
        q6xy(3,2)=q6d*y1+q6c*y2+q6e*y3;
        q6xy(4,1)=q6d*x1+q6e*x2+q6c*x3;
        q6xy(4,2)=q6d*y1+q6e*y2+q6c*y3;
        q6xy(5,1)=q6e*x1+q6c*x2+q6d*x3;
        q6xy(5,2)=q6e*y1+q6c*y2+q6d*y3;
        q6xy(6,1)=q6e*x1+q6d*x2+q6c*x3;
        q6xy(6,2)=q6e*y1+q6d*y2+q6c*y3;
        for i=1:6
            f1=f1+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( (1-(q6xy(i,1)-x3)/h-(q6xy(i,2)-y3)/h).*(1-2*(q6xy(i,1)-x3)/h-2*(q6xy(i,2)-y3)/h) )*q6w;
            f2=f2+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( (q6xy(i,1)-x3)/h*(2*(q6xy(i,1)-x3)/h-1) )*q6w;
            f3=f3+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( (q6xy(i,2)-y3)/h*(2*(q6xy(i,2)-y3)/h-1) )*q6w;
            f4=f4+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( 4*(q6xy(i,1)-x3)/h*(1-(q6xy(i,1)-x3)/h-(q6xy(i,2)-y3)/h) )*q6w;
            f5=f5+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( 4*(q6xy(i,1)-x3)/h*(q6xy(i,2)-y3)/h )*q6w;
            f6=f6+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( 4*(q6xy(i,2)-y3)/h*(1-(q6xy(i,1)-x3)/h-(q6xy(i,2)-y3)/h) )*q6w;
        end
        f(element(ele,1))=f(element(ele,1)) + f1*hh/2;
        f(element(ele,2))=f(element(ele,2)) + f2*hh/2;
        f(element(ele,3))=f(element(ele,3)) + f3*hh/2;
        f(element(ele,4))=f(element(ele,4)) + f4*hh/2;
        f(element(ele,5))=f(element(ele,5)) + f5*hh/2;
        f(element(ele,6))=f(element(ele,6)) + f6*hh/2;
    else
        j=mod(ele-1,2*n);  % line
        k=fix((ele-1)/(2*n));   % collu
        x3 = (j+1)*h/2;
        y3 = (k+1)*h;
        x1 = x3-h;
        y1 = y3;
        x2 = x3;
        y2 = y3-h;
        f1=0;
        f2=0;
        f3=0;
        f4=0;
        f5=0;
        f6=0;
        q6xy(1,1)=q6a*x1+q6b*x2+q6b*x3;
        q6xy(1,2)=q6a*y1+q6b*y2+q6b*y3;
        q6xy(2,1)=q6b*x1+q6a*x2+q6b*x3;
        q6xy(2,2)=q6b*y1+q6a*y2+q6b*y3;
        q6xy(3,1)=q6b*x1+q6b*x2+q6a*x3;
        q6xy(3,2)=q6b*y1+q6b*y2+q6a*y3;
        for i=1:3
            f1=f1+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( (1-(x3-q6xy(i,1))/h-(y3-q6xy(i,2))/h).*(1-2*(x3-q6xy(i,1))/h-2*(y3-q6xy(i,2))/h) )*q6v;
            f2=f2+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( (x3-q6xy(i,1))/h*(2*(x3-q6xy(i,1))/h-1) )*q6v;
            f3=f3+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( (y3-q6xy(i,2))/h*(2*(y3-q6xy(i,2))/h-1) )*q6v;
            f4=f4+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( 4*(x3-q6xy(i,1))/h*(1-(x3-q6xy(i,1))/h-(y3-q6xy(i,2))/h) )*q6v;
            f5=f5+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( 4*(x3-q6xy(i,1))/h*(y3-q6xy(i,2))/h )*q6v;
            f6=f6+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( 4*(y3-q6xy(i,2))/h*(1-(x3-q6xy(i,1))/h-(y3-q6xy(i,2))/h) )*q6v;
        end
        q6xy(1,1)=q6c*x1+q6d*x2+q6e*x3;
        q6xy(1,2)=q6c*y1+q6d*y2+q6e*y3;
        q6xy(2,1)=q6c*x1+q6e*x2+q6d*x3;
        q6xy(2,2)=q6c*y1+q6e*y2+q6d*y3;
        q6xy(3,1)=q6d*x1+q6c*x2+q6e*x3;
        q6xy(3,2)=q6d*y1+q6c*y2+q6e*y3;
        q6xy(4,1)=q6d*x1+q6e*x2+q6c*x3;
        q6xy(4,2)=q6d*y1+q6e*y2+q6c*y3;
        q6xy(5,1)=q6e*x1+q6c*x2+q6d*x3;
        q6xy(5,2)=q6e*y1+q6c*y2+q6d*y3;
        q6xy(6,1)=q6e*x1+q6d*x2+q6c*x3;
        q6xy(6,2)=q6e*y1+q6d*y2+q6c*y3;
        for i=1:6
            f1=f1+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( (1-(x3-q6xy(i,1))/h-(y3-q6xy(i,2))/h).*(1-2*(x3-q6xy(i,1))/h-2*(y3-q6xy(i,2))/h) )*q6w;
            f2=f2+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( (x3-q6xy(i,1))/h*(2*(x3-q6xy(i,1))/h-1) )*q6w;
            f3=f3+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( (y3-q6xy(i,2))/h*(2*(y3-q6xy(i,2))/h-1) )*q6w;
            f4=f4+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( 4*(x3-q6xy(i,1))/h*(1-(x3-q6xy(i,1))/h-(y3-q6xy(i,2))/h) )*q6w;
            f5=f5+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( 4*(x3-q6xy(i,1))/h*(y3-q6xy(i,2))/h )*q6w;
            f6=f6+2*nu*(q6xy(i,2)*(1-q6xy(i,2))+q6xy(i,1)*(1-q6xy(i,1)))*( 4*(y3-q6xy(i,2))/h*(1-(x3-q6xy(i,1))/h-(y3-q6xy(i,2))/h) )*q6w;
        end
        f(element(ele,1))=f(element(ele,1)) + f1*hh/2;
        f(element(ele,2))=f(element(ele,2)) + f2*hh/2;
        f(element(ele,3))=f(element(ele,3)) + f3*hh/2;
        f(element(ele,4))=f(element(ele,4)) + f4*hh/2;
        f(element(ele,5))=f(element(ele,5)) + f5*hh/2;
        f(element(ele,6))=f(element(ele,6)) + f6*hh/2;
    end
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%   Essential boundary condtion  %%%%%%%%%%%%%%%%%%%%%%%%%%   
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
N=2*n;
for node = 1 : N+1         %% low boundary
% Assume all boundary are Dirichlet Type
    for i= 1 : nunk           
        f(i)=f(i)-a(i,node)*0.0; %zeros dirichlet condition
        a(i,node)=0.0E+00;
        a(node,i)=0.0E+00;   
    end
    f(node)=0.0;
    a(node,node)=1.0E+00;
end

for node = nunk-N+1 : nunk-1         %% top boundary
    for i= 1 : nunk           
        f(i)=f(i)-a(i,node)*0.0E+00; %zeros dirichlet condition
        a(i,node)=0.0E+00;
        a(node,i)=0.0E+00;         
    end
    f(node)=0.0E+00;
    a(node,node)=1.0E+00;    
end

for node = N+2: (N+1) : nunk         %% left boundary
    for i= 1 : nunk           
        f(i)=f(i)-a(i,node)*0.0E+00; %zeros dirichlet condition
        a(i,node)=0.0E+00;
        a(node,i)=0.0E+00;         
    end
    f(node)=0.0E+00;
    a(node,node)=1.0E+00;      
end

for node = 2*(N+1) : (N+1) : nunk         %% right boundary
    for i= 1 : nunk           
        f(i)=f(i)-a(i,node)*0.0E+00; %zeros dirichlet condition
        a(i,node)=0.0E+00;
        a(node,i)=0.0E+00;         
    end
    f(node)=0.0E+00;
    a(node,node)=1.0E+00;    
end
