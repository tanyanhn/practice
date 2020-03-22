% This matlab script plot a global basis function 

x=-2:1:2; x=x'; y=x'; m=length(x);   % A square [-2 2]x[-2 2]
nnode = m*m; nelem = (m-1)*2*(m-1);
phi = zeros(nnode,1); phi((nnode+1)/2) = 1;  % the basis function centered at (0,0)
 
% Plot a glocal basis function
x1=-2:0.1:2; x1=x1'; y1=x1; m2=length(x1); v=zeros(3,1); xt=v; yt=v;

for i=1:m2
    for j=1:m2
        it = fix(x2(i)+2)+1; jt = fix( y2(j)+2)+1;
        if x2(i)+ 3 + y2(j) + 3 < it+jt + 1 
            xt(1)=x(it); yt(1)=y(jt); v(1)= phi(m*(jt-1)+it);
            xt(2)=x(it+1); yt(2) = y(jt); v(2)= phi(m*(jt-1)+it+1);
            xt(3)=x(it); y3t=y(jt+1); v(3) = phi(m*jt+it);
        else
            xt(1) =x(it+1); yt(1)=y(jt); v(1)= phi(m*(jt-1)+it+1);
            xt(2) =x(it+1); yt(2) = y(jt+1); v(2) = phi(m*jt+it+1);
            xt(3)=x(it); yt(3)=y(jt+1); v(3) = phi(m*jt+it);
        end
        % transform to local coordinates
        xi = (yt(3)-yt(1))*(x2(i) -xt(1))- (xt(3)-xt(1))*(y2(j)-yt(1));
        eta = -(yt(2)-yt(1))*(x2(i) -xt(1))+ (xt(3)-xt(1))*(y2(j)-yt(1));
        z(i,j)=v(1)*(1-xi-eta) + v(2)*xi + v(3)*eta;
    end
end

mesh(x2,y2,z)