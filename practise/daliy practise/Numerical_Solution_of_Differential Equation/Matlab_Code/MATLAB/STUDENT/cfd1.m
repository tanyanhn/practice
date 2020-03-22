function[A,B] = cfd1(a,b,n,epsilon,Ua,Ub)

%generating the A-matrix

A=zeros(n-1,n-1);
     h=(b-a)/n;
h1=h*h;

%diagonals
for irow=1:n-1
%    A(irow,irow)=-2.0*epsilon/h1;
A(irow,irow)=-(2.0*epsilon/h1 + 1.0/h);
end

%upper diagonals

for irow=1:n-2
%A(irow,irow+1)=(epsilon/h1) - (1/(2.0*h));
A(irow,irow+1)=epsilon/h1;
end


%lower diagonals
for irow=2:n-1
%A(irow,irow-1)=(epsilon/h1) + (1/(2.0*h));
A(irow,irow-1)=epsilon/h1 + 1/(h);
end


%generating the B-matrix

B=-ones(n-1,1);
%B(1,1)=B(1,1)-((epsilon/h1) + (1/(2.0*h)))*Ua;
%B(n-1,1)=B(n-1,1)-((epsilon/h1) - (1/(2.0*h)))*Ub;

B(1,1)=B(1,1)-(epsilon/h1 + 1/h)*Ua;
B(n-1,1)=B(n-1,1)-(epsilon/h1)*Ub;

