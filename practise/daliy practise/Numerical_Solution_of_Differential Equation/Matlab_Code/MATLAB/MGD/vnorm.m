
function E = vnorm(n,v)

  l = length(v);
  E = 0;
  for i=1:l
    E = max(E, abs(v(i)) );
  end 
