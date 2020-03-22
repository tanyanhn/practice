      clear;
		i=0;
      kk =64;
      T  =1.0;
		dt =T/kk;
		u0 = 200.;
		c  = 1.0;
		usur  = 70.;
		uk  = u0;
		ut  = u0;
		for k = 1:kk
			uk = uk +dt*c*(usur -uk);
         uex = usur + (u0 -usur)*exp(-c*k*dt);
         ute = ut +dt*c*(usur -ut);
			ut= ut +dt/2*(c*(usur -ut)+c*(usur -ute));
			erreul = abs(uk - uex);
			errimeul = abs(ut - uex);
		end
      kk
      erreul
      errimeul