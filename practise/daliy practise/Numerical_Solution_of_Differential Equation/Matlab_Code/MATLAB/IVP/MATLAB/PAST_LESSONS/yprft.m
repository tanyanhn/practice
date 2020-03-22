function yprft =yprft(t,y)
	yprft(1) =-.5*y(1) + .01*y(1)*y(2) + .02*y(1)*y(3);
	yprft(2) = .01*(100 - y(2))*y(2) -.01*y(1)*y(2);
   yprft(3) = .04*(80 - y(3))*y(3) -.03*y(1)*y(3);
   yprft = [yprft(1) yprft(2) yprft(3)]';
