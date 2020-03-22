clear;
%Initial Time
t(1) = 0;
%Initial Temperature
y(1) = 200.;
h = 5;
% Number of Time Steps of Length h
n = 60;
% From y(2) = 190
a = 60/65;
b = 350/65;
% Execute the FOFD Algorithm
for k = 1:n
    y(k+1) = a*y(k) + b;
    t(k+1) = t(k) + h;
end
plot(t,y)

