   function formkf(kind,nint,nodes,x,xi,w)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                    %
%   function formkf forms the discrete system of finite element      %
%   by calling the elem to get the local stiffness matrix ek, ef     %
%   and assemb to add them to the global stiffness matrix ek and     %
%   the right hand side of gf.                                       %
%   Input:                                                           %
%      kind(i): The order of basis elements got from propset.m       %
%      ninit(i): The order of Gaussian quadrature got from propset.m %
%      x:        The coordinates of the donal points                 %
%      xi, w:    The Gaussian points and weights from setint.m       %
%--------------------------------------------------------------------%

    global nelem gk gf

    for nel = 1:nelem,
       n = kind(nel) + 1;
       i1 = nodes(1,nel);
       i2 = nodes(n,nel);
       i3 = nint(nel);

%  Takes i3-th order of Gaussian quadrature: 1, order 1; 2, order 2, ...

       xic = xi(:,i3);      wc = w(:,i3);

       [ek,ef] = elem(x(i1),x(i2),n,i3,xic,wc);
       assemb(ek,ef,nel,n,nodes);
    end
gk
    return

%--------------------------- END OF FORMKF -----------------------------


