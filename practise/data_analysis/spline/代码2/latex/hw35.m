%This is a file named hw35.m.
% a,b,c,d represent t_{i-1}, t_i, t_{i+1}, t_{i+2}
syms a b c d;
x = (c*d-b*a)/(c+d-a-b);
numerator = -(c+d-a-b)*x*x + 2*(c*d-b*a)*x-(a*c*d+d*b*c-a*b*c-a*b*d);
denominator = (c-a)*(c-b)*(d-b);
res = numerator/denominator - 1;
simplify(res)