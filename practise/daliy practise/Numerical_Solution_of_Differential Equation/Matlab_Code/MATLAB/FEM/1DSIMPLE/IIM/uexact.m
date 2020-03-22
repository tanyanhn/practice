function y=uexact(x,bl,br,alf) 
 
a=-1/(br*alf + bl*(1-alf) ); 
if x < alf 
   y = a*x*(1-alf); 
else 
   y = a*alf*(1-x); 
end 

