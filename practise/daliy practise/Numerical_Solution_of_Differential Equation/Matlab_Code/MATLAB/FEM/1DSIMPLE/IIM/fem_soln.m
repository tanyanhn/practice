
function y = fem_soln(x,U,xp)


M = length(x);
for i=1:M-1,
  if xp >=x(i) & xp <= x(i+1)
     y = hat2(xp,x(i),x(i+1))*U(i) + hat1(xp,x(i),x(i+1))*U(i+1);
     return
  end
end
