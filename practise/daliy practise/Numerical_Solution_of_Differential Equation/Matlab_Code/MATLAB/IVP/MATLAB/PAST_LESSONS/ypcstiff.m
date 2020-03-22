function ypcstiff=ypcstiff(t,y)
ypcstiff(1) = -10004*y(1) + 10000*y(2)^4;
ypcstiff(2) = y(1)-y(2) -y(2)^4 ;
ypcstiff= [ypcstiff(1) ypcstiff(2)]';