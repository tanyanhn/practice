
   function [x,kbc,vbc,kind,nint,nodes] = propset

   global nnode nelem 
   global gk gf
   global xi w

   a = -4;		% Two end points,   a <= x <= b.
   b = 4;

   nnode = 41;

   nnode = 49;
   inf_ele = 1;
   inf_ele = 3;
   x = zeros(nnode,1);

   nelem = (nnode - 1)/inf_ele;
   gk = zeros(nnode,nnode);
   gf = zeros(nnode,1);

%  load data.m	% n1,n2,x1,x2

   [data] = datain(a,b,nnode,nelem);
   [nrec,junk]=size(data);

   for nr=1:nrec,
     n1=data(nr,1); n2=data(nr,2); x1=data(nr,3);x2=data(nr,4);
     if n2 == 0
       x(n1) = x1;
     else
       dn = n2 - n1;
       dx = (x2-x1)/dn;
       xx = x1 - dx;
       %  Begin loop to define nodal point coordinates
       for i=n1:n2,
         xx = xx + dx;
         x(i) = xx;
       end
     end
    end

    % Define the type of basis function
    for i=1:nelem
       kind(i) = inf_ele;	   % Use linear elements
       nint(i) = 1;        % oder of the integration rule
       nint(i) = 3; 
       for j=1:kind(i)+1,
         nodes(j,i) = j + kind(i)*(i-1);   % nodal point numbers of nodes
       end		           % in the element
    end

%--------------------------------------------------------------
%  Sep up boundary conditions:

    kbc(1) = 3;  % BC at x = a, 1: Dirichlet, 2: Neumann BC; 3: Mixed.
    kbc(2) = 3;  % BC at x = b, The meaning is the same as above.

%kbc(1) = 2;

    ua = sin(a);
    ub = sin(b);		% Dirichlet BC.

    uxa = -(1+a)*cos(a);
    uxb = (1+ b)*cos(b);	% Neumann BC.

    alf = 3;
    beta = 4;
    gamma = alf*sin(a) + beta*cos(a);
    uxma = -alf*(1+a)/beta;
    uaa = gamma/alf;                % Mixed BC.

    gammab = alf*sin(b) + beta*cos(b);
    uxmb = alf*(1+b)/beta;
    ubb = gammab/alf;

%--------------- finish setting up boundary conditions ----------
  
    switch kbc(1) 
      case 1,
         vbc(1,1) = ua;
         vbc(2,1) = 0;
      case 2, 
         vbc(1,1) = uxa;
         vbc(2,1) = 0;
      case 3,
         vbc(1,1) = uxma;
         vbc(2,1) = uaa;
     end

    switch kbc(2) 
      case 1,
         vbc(1,2) = ub;
         vbc(2,2) = 0;
      case 2, 
         vbc(1,2) = uxb;
         vbc(2,2) = 0;
      case 3,
         vbc(1,2) = uxmb;
         vbc(2,2) = ubb;
     end


     return
