    function drchltb(vbc)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                    %
%   function incorporates the Dirichlet BC at x=b to the discrete    %
%   linear system. Reference: Finite element. An introduction by     %
%   E.Becker, G.Carey, and J.Oden, Vol.1., pp. 107- 108              %
%--------------------------------------------------------------------%

    global nnode gk gf

    for i=1:nnode,
       gf(i) = gf(i) - gk(i,nnode)*vbc(1,2);
       gk(nnode,i) = 0;
       gk(i,nnode) = 0;
    end

    gk(nnode,nnode)=1;
    gf(nnode) = vbc(1,2);

    return

%--------------------------- END OF DRCHLTB ----------------------------- 

