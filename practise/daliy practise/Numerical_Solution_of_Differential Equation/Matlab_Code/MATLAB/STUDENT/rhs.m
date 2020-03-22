
function yp = rhs(x)

   x2 = x*x;  
   yp = exp(-x)*( x2*x2 - 9*x2*x + 18*x2-13*x+7);
