function[A,F] = cfd(a,b,coeff1,coeff2,n)

%generating the A-matrix

A=zeros(n,n);

h=(b-a)/n;
h1=h*h;
hh=h/2.0;

%diagonal elements
for irow=1:n-1
x1=(irow+0.5)*h;
x2=(irow-0.5)*h;
beta1=1 + x1^2;
beta2=1 + x2^2;
gamma=irow*h;
    A(irow,irow)=-(beta1 + beta2 + h1*gamma)/h1;
end

x1=(n+0.5)*h;
x2=(n-0.5)*h;
beta1=1 + x1^2;
beta2=1 + x2^2;
gamma=n*h;

    A(n,n)=-(2.0*coeff1*beta1/(coeff2*h)+beta2/h1+beta1/h1+gamma)

%upper diagonal elements

for irow=1:n-1
x1=(irow+0.5)*h;
beta1=1 + x1^2;
A(irow,irow+1)=beta1/h1;
end

%lower diagonal elements

for irow=2:n-1
x2=(irow-0.5)*h;
beta2=1 + x2^2;
A(irow,irow-1)=beta2/h1;
end

x1=(n+0.5)*h;
x2=(n-0.5)*h;
beta1=1 + x1^2;
beta2=1 + x2^2;
A(n,n-1)=(beta1+beta2)/h1;

%generating the F-matrix

for irow=1:n
x=irow*h;
F(irow,1)=exp(-x)*(x^4 -9.0*x^3 + 18.0*x^2 - 13.0*x + 7);
end

beta1=1+(h/2.0)^2;Ua=1.0;
F(1,1)=F(1,1)-(beta1*Ua/h1);

