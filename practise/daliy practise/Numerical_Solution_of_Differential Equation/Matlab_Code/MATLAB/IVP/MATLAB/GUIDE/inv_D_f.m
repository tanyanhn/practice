
function z = inv_D_f(x,vec_f_J)     % Now vector x and vec_f_J are both
  z = zeros(length(x),1);           % We can use composite functions
  [y D] = feval(vec_f_J,x);
  z = D\y;                          % Solve D z = y.
return

