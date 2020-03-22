
function [x,y] = euler2(a,b,yfun,y0,n)

h=(b-a)/n;

mdim=length(y0);     		% how many equations are there?
x = zeros(n+1,1);

y=zeros(n+1,mdim);              % initialize y

y(1,:)=y0;	                % put the initial value in the first row.
x(1) = a;

for i=1:n
    ytmp = y(i,:) + h * feval(yfun,x(i),y(i,:))';    % Euler's method
    y(i+1,:) = y(i,:) + h * ( feval(yfun,x(i),y(i,:))' + ...
                               feval(yfun,x(i)+h,ytmp)' )/2;
    x(i+1) = x(i) + h;
end
