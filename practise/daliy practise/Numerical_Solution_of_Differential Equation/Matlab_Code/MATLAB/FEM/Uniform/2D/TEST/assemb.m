
 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                    %
%  Matlab program for two-dimensinal finite element method for       %
%                                                                    %
%    -u_xx - u_yy  = f(x,y)                                          %
%                                                                    %
%  on rectangular domain with Dirichlet and homogeneous Neumann      %
%  boundary conditions.                                              %
%                                                                    %
%  With all set up information provided by datain.m, this code       %
%  form a linear basis over triangles, assemble the stiffness        %
%  matrix and load vecotor, and finally solve the linear system      %
%  The solution is then defined on the nodal points.                 %
%                                                                    %
%  Reference: An introdunction to the finite element with            %
%             applications to non-linear problems                    %
%    R. E. White: John Wiley & Sons, Inc. 1985.	                     %
%--------------------------------------------------------------------%

    gk=zeros(nnode,nnode);
    gf = zeros(nnode,1);

    for nel = 1:nelem,   % Begin to assemle by element.

      for j=1:3,	   % The coordinates of the nodes in the 
        jj = node(nel,j);    % element.
	xx(j) = x(jj);
        yy(j) = y(jj);
      end

      for i=1:3, 
	j = i+1 - fix((i+1)/3)*3;
        if j == 0
           j = 3;
        end
        m = i+2 - fix((i+2)/3)*3;
        if m  == 0
           m = 3;
        end

	a(i) = xx(j)*yy(m) - xx(m)*yy(j);
        b(i) = yy(j) - yy(m);
        c(i) = xx(m) - xx(j);
      end

      delta = ( c(3)*b(2) - c(2)*b(3) )/2.0;   % Area.

      for ir = 1:3,
	ii = node(nel,ir);
        for ic=1:3,
          ak = (b(ir)*b(ic) + c(ir)*c(ic))/(4*delta);
          jj = node(nel,ic);
          gk(ii,jj) = gk(ii,jj) + ak;
        end
	  j = ir+1 - fix((ir+1)/3)*3;
	     if j == 0
                j = 3;
             end
	  m = ir+2 - fix((ir+2)/3)*3;
             if m == 0
                m = 3;
             end
	  gf(ii) = gf(ii)+( f(xx(ir),yy(ir))*2.0 + f(xx(j),yy(j)) ...
		              + f(xx(m),yy(m)) )*delta/12.0; 
      end

    end                  % End assemling by element.

%------------------------------------------------------
% Now deal with the Dirichlet boundary condition

    for i=1:npres,
      nod = npt(i);
      for k=1:nnode,
	 gf(k) = gf(k) - gk(k,nod)*g1(i);
         gk(nod,k) = 0;
	 gk(k,nod) = 0;
      end
	 gk(nod,nod) = 1;
	 gf(nod) = g1(i);
    end

    u=gk\gf;		% Solve the linear system.

% End.

	
