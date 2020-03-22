
    function aplybc(kbc,vbc)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                    %
%   function aplybc applies the boundary condition to modifies the   %
%   linear system obtained from the finite element method.           %
%   For the meanings of the parameter, see propset.m.                %
%   Fot the treatment of the BC, see Finite element. An introduction %
%   by E.Becker, G.Carey, and J.Oden, Vol.1., pp. 80-84, 107-109.    %
%--------------------------------------------------------------------%

    global nnode
    global gk gf

    if kbc(1) == 1,
      drchlta(vbc);	                   % Dirichlet BC at x=a.
    else
      if kbc(1) == 2,	                   % Neumann DC at x=a.
         gf(1) = gf(1) + vbc(1,1);
      else				   % Mixed BC at x=a.
         gk(1,1) =  gk(1,1) + vbc(1,1);
         gf(1) = gf(1) + vbc(1,1)*vbc(2,1); 
      end
    end

    if kbc(2) == 1,		                    % Dirichlet BC at x=b.
       drchltb(vbc);
    else
       if kbc(2) == 2,                              % Neumann DC at x=b.
          gf(nnode) = gf(nnode) + vbc(1,2); 
       else				            % Mixed BC at x=b.
          gf(nnode) = gf(nnode) + vbc(1,2)*vbc(2,2);
          gk(nnode,nnode) =  gk(nnode,nnode) + vbc(1,2);
       end
    end

    return
    
%--------------------------- END OF APLYBC -----------------------------
