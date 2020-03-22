clear;
y(1) = 200.;
T = 20;
KK = 100
h = T/KK;
t(1)= 0.;
for k = 1:KK
    y(k+1) = y(k) + h*feul(t(k),y(k));
    t(k+1) = t(k) + h;
end
plot(t,y)

