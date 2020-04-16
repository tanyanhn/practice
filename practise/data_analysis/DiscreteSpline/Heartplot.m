clc;
clear;

file = "output/Heart";



for i=0:1:2
    figure;
    s = "N=";
    s = s + i;
    title("s");
    filename = file + i;
    data = dlmread(filename);
    [m,n] = size(data);
%    error(i,1) = 0;
    for j=1:1:m/5
       a = data(5 * j - 4,1);
       b = data(5 * j - 4,2);
       x0 = data(5 * j - 3,1);
       param1 = data(5 * j - 2,:);
       param2 = data(5 * j , :);
       x = a:0.01:b;
       y1 = param1(1,1) * (x - x0).^3 + param1(1,2) * (x - x0).^2 + param1(1,3) * (x - x0).^1 + param1(1,4);
       y2 = param2(1,1) * (x - x0).^3 + param2(1,2) * (x - x0).^2 + param2(1,3) * (x - x0).^1 + param2(1,4);
       plot(y1,y2);
       hold on;
       plot(-y1,y2);
       hold on;
%       e = g - y;
%       fplot(e,[a,b]);
%        k =  max(subs(e,x,(a:0.001:b)));
%        if(error(i,1) < k)
%            error(i,1) = k;
%        end
%       hold on;
    end
    %gtext('interpolation curve');
    %gtext('error curve');
end