function [x,m] = plotTruncatedPowerFunc2Bsplines(n,k,a,b)
   % f = zero(n+2,n+2);
   x = a:0.01:b;
   y = zeros(n+2,n+2,(b-a)*100 +1);
    for j = 1:1:(1+n+1)
        for i = j:1:(1+n+1)
            if j ==1
                y(i,j,:) = truncate(x,n,i+k-2);
                for l = 1:1:((b-a)*100 + 1)
                    m(l) = y(i,j,l);
                end
                %m = y(i,j,:);
                %figure;
                %plot(x,m);
                %axis([0 n+3 0 1]);
                %plot(x, y(i,j,:));
            else
                y(i,j,:) = (y(i,j-1,:) - y(i-1,j-1,:))./(j-1) ;
                for l = 1:1:((b-a)*100 + 1)
                    m(l) = y(i,j,l);
                end
                %figure;
                %plot(x,m);
                %axis([0 n+3 0 1]);
            end
        end
    end
    m = (n+1)*m
    %figure;
    %plot(x,(n+1)*m);
    %axis([0 n+3 0 1]);
end

function y = truncate(x,k,x0)
    %x = (x0-k-2):0.01:(x0 +1);
    y = ((x0 - x).^k).*(x < x0) + (0).*(x >= x0);
    %fun = @c;
end