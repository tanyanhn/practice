
    function drchlta(vbc)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                    %
%   function incorporates the Dirichlet BC at x=a to the discrete    %
%   linear system. Reference: Finite element. An introduction by     %
%   E.Becker, G.Carey, and J.Oden, Vol.1., pp. 107- 108              %
%--------------------------------------------------------------------%
    global nnode gk gf

    for i=1:nnode,
       gf(i) = gf(i) - gk(i,1)*vbc(1,1);
       gk(i,1) = 0;
       gk(1,i) = 0;
    end

    gf(1) = vbc(1,1);
    gk(1,1) = 1;

    return

%--------------------------- END OF DRCHLTA -----------------------------
