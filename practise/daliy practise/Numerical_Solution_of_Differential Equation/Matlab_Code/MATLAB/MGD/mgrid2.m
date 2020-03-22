%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%     complete V-cycle in the multigrid algorithm to solve
%     uxx = g(x), with u(0)=u(l)=0.
%
%     modified from D.R. Kincaid & E.W. Cheney fortran code.
%
%     parameter:  m  gives the number of grids to be employed.
%     parameter  k  gives the number of iterations to be performed


clear all; close all;
 
	m = input('Enter the number of levels m=');
	np1 = 2^m; n = np1 - 1; np2=np1+1;

	v=zeros(m,np2); f=zeros(m,np2); w=zeros(np2,1); 
        error = zeros(2*m+1,1);

        error(1) = 1.0;

      	for k=2:2*m+1     %  initialize arrays and
	                  %  put best available guess into v**m
         n = 2^m - 1;     %  k is the number of iterations to be performed
         h = 1.0/(n+1);

         for i=1:m
            for j=1:np2
               f(i,j) = 0.0;
               v(i,j) = 0.0;    % Dirichlet boundary conditions are
	    end                 % defined in v(i,1) and v(i,np2).
	 end
 
         for j=1:n
            f(m,j+1) = g(j*h);  % Define the source term in the fine level
	 end

         for i=m:-1:2           %  Multigrid downward
            for  p=1:k          %  Gauss-seidel iteration (k steps) 
               for j=2:n+1
                  v(i,j) = 0.5*(v(i,j-1) + v(i,j+1) - (h*h)*f(i,j)); 
	       end
	    end

            for j=2:n+1            % Compute the residual vector
               w(j) = f(i,j) - (v(i,j-1) - 2.0*v(i,j) + v(i,j+1))/(h*h);
	    end

            for j=1:(n-1)/2        %  Apply restriction operator
               f(i-1,j+1) = w(2*j+1);
	    end

            h = 2.0*h; n = (n-1)/2;      % Goto next level.
	
	    end

%        solve coarsest (smallest) system exactly

         v(1,2) = -g(0.5)/8.0;    % h=1/2; 

         % ' Bottom of V-cycle'
 
%        end downward phase of V-cycle
%        start upward phase of V-cycle

         for i=2:m
            h = 0.5*h;
            n = 2*n + 1;

%           apply extension operation, i.e.
%           interpolation up from coarse grid to fine grid

            for j=0:(n+1)/2
               w(2*j+1) = v(i-1,j+1);
	    end

	    for j=1:(n+1)/2      
               w(2*j) = 0.5*(v(i-1,j) + v(i-1,j+1));
	    end

%           add correction to extension operator

            for j=1:n+2
               v(i,j) = v(i,j) + w(j);
	    end

%           gauss-seidel iteration (k steps)

            for p=1:k
               for j=2:n+1
                  v(i,j) = 0.5*(v(i,j-1) + v(i,j+1) - (h*h)*f(i,j)); 
	       end
	    end

	   end

%        output phase  %   ' k =',k,' m =',m

         for j=1:np2
            w(j) = true((j-1)*h) - v(m,j);
	    x(j) = (j-1)*h;
	    ue(j) = true((j-1)*h);
	 end

	  error(k) = max(abs(w));
         'maximun error =', error(k),' ratio =', error(k)/error(k-1)

      end 
	U = v(m,:);    % The last rwo is the solution at the finest level.
	figure(1); plot(x,ue,x,U,'o'); xlabel('x')
        title('The exact solution and computed solution');
	figure(2); plot(x,w); xlabel('x')	
	title('The error plot')

