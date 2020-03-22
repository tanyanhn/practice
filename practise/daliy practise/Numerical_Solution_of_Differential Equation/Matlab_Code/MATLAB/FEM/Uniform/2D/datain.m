
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                    %
%  Matlab program for two-dimensinal finite element method for       %
%                                                                    %
%    -u_xx - u_yy  = f(x,y)                                          %
%                                                                    %
%  on rectangular domain with Dirichlet and homogeneous Neumann      %
%  boundary conditions.                                              %
%                                                                    %
%  Input information (chnage the parameters in this file):           %
%     a, b, c, d:  Rectangular domain: a <= x <= b, c <= y <= d.     %
%     nx, ny:      The number of grid in x and y directions          % 
%                                                                    %
%  This program will generate a uniform triangulation. The node      %
%  are arranged as following:                                        %
%                                                                    %
%  ny(nx+1)+1  ny(nx+1)+2   ny(nx+1)+3   ...     (ny+1)*(nx+1)       %
%                                                                    %
%           ......................................                   %
%                                                                    % 
%     nx+2        nx+3          nx+4     ...         2*nx+2          %
%      1           2              3      ...          nx+1           %
%                                                                    % 
%  The triangles are arranged in the order described below:          %
%                                                                    % 
%      (ny-1)*2*nx+1    (ny-1)*2*nx+3    ...      ny*2*nx-1          %
%           (ny-1)*2*nx+2    (ny-1)*2*nx+4   ...        ny*nx*2      %
%                                                                    % 
%                   ..................................               %
%                                                                    %   
%            1                 3         ...        2*nx-1           %
%                 2                 4        ...          2*nx       %
%                                                                    %   
%  If the boundary condition is u_n = 0, nothing needs to be done,   %
%  however, for pure Neumann problem, the solution may not exist     %
%  or may not unique.                                                %
%                                                                    %
%  For the Dirichlet boundary condition. The following information   %
%  are required:                                                     %
%     npres: The number of node points where the solution is         %
%	     prescribed.                                             %
%     npt(i): i=1, 2, ...  npres, the index of the nodal points      %
%             where the solution is prescribed.                      %
%     g1(i) : i=1, 2, ...  npres, the value of the solution at       %
%             those nodal points.                                    %
%                                                                    %
%--------------------------------------------------------------------%

  clear

  a=0; b=2;  c=0; d=2;   	% Rectangular domain: a <= x <= b,
				%		      c <= y <= d.
  nx = 2; ny = 4;		% Number of grid points in x, y direction.

  hx = (b-a)/nx;  hy = (d-c)/ny;
  nnode = (nx+1)*(ny+1);
  nelem = nx*ny*2;

%-- Generate the x and y coordinates of the nodal points as the order 
%-- described above.

  ni = 0;
  for  j=0:ny,
    for i=0:nx,
      ni = ni+1;
      x(ni) = a + hx*i;
      y(ni) = c + hy*j;
    end
  end

%-- Assign the nodal points to each element according to the order 
%-- described above.

  for i=0:nx-1,
    for j=0:ny-1,
      nelei = 2*nx*j + 2*i + 1;
      node(nelei,1) = (nx+1)*(j+1) + i+1;
      node(nelei,2) = node(nelei,1) - nx-1;
      node(nelei,3) = node(nelei,1) + 1;
      node(nelei+1,1) = node(nelei,2) + 1;
      node(nelei+1,2) = node(nelei,3);
      node(nelei+1,3) = node(nelei,2);
    end
  end

%----------------------------------------------------------------------
%-- Define the Dichlet boundary conditions.

  npres = 2*nx+2;
  for i=0:nx,
    npt(i+1) = i+1;
    g1(i+1) = 70;
    npt(i+nx+2) = ny * (nx + 1)  + i + 1;
    g1(i+nx+2) = 212;
  end

     
