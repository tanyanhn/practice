
%---------- Matlab code for the Predator-Prey Model with Fishing

f='a*x - c*x*y -f0*x';              % Define symbolic f(x,y), g(x,y)
g = '-b*y + d*x*y - f0*y';

[x0,y0]= solve(f,g,'x,y');     % Find all the equilibrium
			       % The solution is: (x0(1), y0(1)),
                               % (x0(1),y0(1)) ...

fpx = diff(f,'x'); fpy=diff(f,'y');     % Find all the partial derivatives
gpx = diff(g,'x'); gpy = diff(g,'y');   

A=[fpx fpy			        % Form the linearization matrix
gpx gpy];

D=eig(A);			        % Find all the eigenvalues.

D1=subs(D,{'x','y'},{x0(1),y0(1)});     % Find the eigenvalues
simplify(D1)			        % corresponding to the first
					% equilibrium state.

D2=subs(D,{'x','y'},{x0(2),y0(2)});	% Find the eigenvalues
simplify(D2)                            % corresponding to the second
                                        % equilibrium state.
