function ypvdpol=ypvdpol(t,y)
ypvdpol(1) = y(2);
ypvdpol(2) = 1*(1-y(1)^2)*y(2)-y(1);
ypvdpol= [ypvdpol(1) ypvdpol(2)]';