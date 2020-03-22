% This matlab script plot a global basis function 

clear all; close all;

x=-2:1:2; x=x'; y=x'; m=length(x);   % A square [-2 2]x[-2 2]
nnode = m*m; nelem = (m-1)*2*(m-1);
phi = zeros(nnode,1); phi((nnode+1)/2) = 1;  % the basis function centered at (0,0)
 
% Plot a glocal basis function
x2=-2:0.1:2; x2=x2'; y2=x2; m2=length(x2); v=zeros(3,1); xt=v; yt=v;
z=zeros(m2,m2); index_z = zeros(m2,m2);

% Compute the node value and index them as already done.
for i=1:m
    for j=1:m
        k = m*(j-1) + i;
        z(10*(i-1)+1,10*(j-1)+1) = phi(k);
        index_z(10*(i-1)+1,10*(j-1)+1) = 1;
    end
end

for i=2:m2-1
    for j=2:m2-1
        if  index_z(i,j) == 0
            if fix( y2(j)+2)== y2(j)+2
                jt = fix( y2(j)+2)+1;
            else
                jt = fix( y2(j)+2)+1;
            end
            if fix(x2(i)+2) == x2(i)+2
                it = x2(i)+2;
            else
                it = fix(x2(i)+2)+1; 
            end
            it = fix(x2(i)+2)+1;jt = fix( y2(j)+2)+1;
        if x2(i)+ 3 + y2(j) + 3 < it+jt + 1 
            xt(1)=x(it); yt(1)=y(jt); v(1)= phi(m*(jt-1)+it);
            xt(2)=x(it+1); yt(2) = y(jt); v(2)= phi(m*(jt-1)+it+1);
            xt(3)=x(it); yt(3)=y(jt+1); v(3) = phi(m*jt+it);
        else
            xt(1) =x(it+1); yt(1)=y(jt); v(1)= phi(m*(jt-1)+it+1);
            xt(2) =x(it+1); yt(2) = y(jt+1); v(2) = phi(m*jt+it+1);
            xt(3)=x(it); yt(3)=y(jt+1); v(3) = phi(m*jt+it);
        end
        % transform to local coordinates
        xi = (yt(3)-yt(1))*(x2(i) -xt(1))- (xt(3)-xt(1))*(y2(j)-yt(1));
        eta = -(yt(2)-yt(1))*(x2(i) -xt(1))+ (xt(2)-xt(1))*(y2(j)-yt(1));
        z(i,j)=v(1)*(1-xi-eta) + v(2)*xi + v(3)*eta;
        
        index_z(i,j)=1;
        end
        
    end
end

mesh(x2,y2,z)
axis('square')
axis([-2 2 -2 2])
hold
 for k=-3:1:3
   y3 = k-x; 
   plot(x,y3,':')
end