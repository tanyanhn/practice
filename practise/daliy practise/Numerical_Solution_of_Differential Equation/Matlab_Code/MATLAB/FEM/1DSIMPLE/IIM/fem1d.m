
function U = fem1d(x,bl,br,alf,v)        

bjump=br-bl;

M = length(x);
for i=1:M-1,
  h(i) = x(i+1)-x(i);
end

for i=1:M-1
   if  x(i) <=alf & alf< x(i+1)
      j = i;
   end
end
 
A = sparse(M,M); F=zeros(M,1);           % Initialize
A(1,1) = 1; F(1)=0;
A(M,M) = 1; F(M)=0;
A(2,2) = 1/h(1); F(2) = int_hat1_f(x(1),x(2));

for i=2:M-2,
  A(i,i) = A(i,i) + 1/h(i);
  A(i,i+1)   = A(i,i+1) - 1/h(i);
  A(i+1,i)   = A(i+1,i) - 1/h(i);
  A(i+1,i+1) = A(i+1,i+1) + 1/h(i);
  F(i)       = F(i) + int_hat2_f(x(i),x(i+1));
  F(i+1)     = F(i+1) + int_hat1_f(x(i),x(i+1));
end

  A(M-1,M-1) = A(M-1,M-1) + 1/h(M-1);
  F(M-1)     = F(M-1) + int_hat2_f(x(M-1),x(M));

%  F(j) = F(j) + v*(x(j+1)-alf)/h(j);
%  F(j+1) = F(j+1) + v*(alf-x(j))/h(j);

   F(j) = F(j) + v*hat2(alf,x(j),x(j+1));
   F(j+1) = F(j+1) + v*hat1(alf,x(j),x(j+1));

  U = A\F;

  return

