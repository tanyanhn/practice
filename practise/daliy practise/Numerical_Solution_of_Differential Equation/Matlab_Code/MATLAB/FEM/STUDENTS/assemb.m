    function assemb(ek,ef,nel,n,nodes)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                     %
%   function assemb assemble the stiffness matrix gk and the right    %
%   hand side gf by looping through the nel-th elements.              %     
%                                                                     %
%-- nel: The nel-th element.                                          %
%-- n:   number of nodal points in the element, e.g. linear n=2;      %
%        quadrtic, n=3; cubic: n=4.                                   %
%-- nodes:  nodal point numbers of nodes in the nel-th element,       %
%        nodes(1,nel), nodes(2,nel), ..., nodes(n,nel).               %
%        see propset.m 
%--------------------------------------------------------------------%

    global gk gf

    for i=1:n,
      ig = nodes(i,nel);
                      % Assemble global vector gf
      gf(ig) = gf(ig) + ef(i);

       for j=1:n,
         jg = nodes(j,nel);
                     % Assemble global stiffness matrix gk
         gk(ig,jg) = gk(ig,jg) + ek(i,j);
       end
     end 

	return

%--------------------------- END OF ASSEMB -----------------------------


