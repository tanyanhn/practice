
    function [y] = uxeact(x)

%   y = 1 + 2*x-3*x*x;

    y = sin(x);

        c = -1/(exp(1)-exp(-1));
     y = c*(exp(x)-exp(-x)) + x;

aa=1; bb=2;
if x <1/3
  y = x^4/aa;
else
  y= x^4/bb + (1/aa - 1/bb)/81;
end



    return 
