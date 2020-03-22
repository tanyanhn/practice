
 
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

%----  Read Data From Matlab PDETOOL Box: Export Mesh:

    [ijunk,nelem] = size(t);
    [ijunk,nnode] = size(p);

    for i=1:nelem
      nodes(1,i)=t(1,i);
      nodes(2,i)=t(2,i);
      nodes(3,i)=t(3,i);
    end

    gk=zeros(nnode,nnode);
    gf = zeros(nnode,1);

    for nel = 1:nelem,   % Begin to assemle by element.

      for j=1:3,	   % The coordinates of the nodes in the 
        jj = nodes(j,nel);    % element.
	xx(j) = p(1,jj);
        yy(j) = p(2,jj);
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
	ii = nodes(ir,nel);
        for ic=1:3,
          ak = (b(ir)*b(ic) + c(ir)*c(ic))/(4*delta);
          jj = nodes(ic,nel);
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

    [ijunk,npres] = size(e);
    for i=1:npres,
       xb = p(1,e(1,i));  yb=p(2,e(1,i));
       g1(i) = uexact(xb,yb);
    end

    for i=1:npres,
      nod = e(1,i);
      for k=1:nnode,
	 gf(k) = gf(k) - gk(k,nod)*g1(i);
         gk(nod,k) = 0;
	 gk(k,nod) = 0;
      end
	 gk(nod,nod) = 1;
	 gf(nod) = g1(i);
    end

    u=gk\gf;		% Solve the linear system.

% Get error vector if possible

        err = u;
	for i=1:nnode
           xt = p(1,i); yt=p(2,i);
           err(i) = u(i) - uexact(xt,yt);
        end
       

    pdemesh(p,e,t,u)
    figure(2); pdemesh(p,e,t,err)

% End.

	
