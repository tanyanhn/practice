function yporeg=yporeg(t,y)
yporeg(1) = 77.27*(y(2)-y(1)*y(2)+y(1)-(8.375*10^-6)*y(1)*y(1));
yporeg(2) = (-y(2) -y(1)*y(2)+y(3))/77.27 ;
yporeg(3) = .04*(y(1) - y(3)) ;
yporeg= [yporeg(1) yporeg(2) yporeg(3)]';