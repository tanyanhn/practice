clc;
clear;

file = "output/output";

syms x;
g = 1 / (1 + x^2);


for i=2:1:3
    figure;
    s = "N=";
    s = s + (i-1);
    title("s");
    fplot(g);
    hold on;
    filename = file + (i-1);
    data = dlmread(filename);
    [c,n] = size(data);
    d = zeros(n);
    start = data(1,1);
    a = start - 5;
    b = start + n + 5;
    [x,m] = plotTruncatedPowerFunc2Bsplines(i,start,a,b);
    m = data(2,1) .* m;
    for j =1:1:(n-1)
        [x,temp] = plotTruncatedPowerFunc2Bsplines(i,start + j, a,b);
        m = data(2,j+1) * temp + m;
    end
    plot(x,m)
    axis([start-3 start+n+3 -0.5 1.5]);
end