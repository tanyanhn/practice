clear;
% Initial Time
t(1) = 1;
%Initial Deposit
y(1) = 100.;
h = 1;
% Number of Months
n = 480;
% Use 6% Compounded Monthy
a = 1.01;
% Monthly Deposit is 100
b = 100;
% Execute the FOFD Algorithm
for k = 1:n
    y(k+1) = a*y(k) + b;
    t(k+1) = t(k) + h;
end
plot(t,y)

