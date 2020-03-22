      clear;
		kk =40;
      T  =10.0;
		dt =T/kk;
		u0 = 200.;
		c  = 1/26;
		usur  = 70.;
		uk  = u0;
		ut  = u0;
		for k = 1:kk
			uk = uk + dt*c*(usur -uk);
         uex = usur + (u0 -usur)*exp(-c*k*dt);
         utp = ut;
         ut = ut + dt*c*(usur -utp);
         ut = ut - (dt^2)/2*c*(c*(usur -utp));
         ut = ut + (dt^3)/6*c^2*(c*(usur -utp));
         ut = ut - (dt^4)/24*c^3*(c*(usur -utp));
         erreul = abs(uk - uex);
			errtay = abs(ut - uex);
		end
      kk
      erreul
      errtay