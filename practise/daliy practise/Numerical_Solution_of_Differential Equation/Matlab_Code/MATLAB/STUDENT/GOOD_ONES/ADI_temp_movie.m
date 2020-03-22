%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                        %
%  ADI Method for 2D heat equation in prob.3 hw#4                        %
%                                                                        %
%          u_t = u_{xx} + u_{yy} + f(x,y,t)                              %
%                                                                        %
%  Test problem:                                                         %
%    Exact solution: u(t,x,y) = cos(t) cos(pi*y) (x^2+1)                 %
%    Source term:  f(t,x,y) = cos(pi*y)*(-sin(t)*(x*x+1)                 %
%                             +cos(t)*((pi*pi)*(x*x+1)-2))               %
%    Function:     g(y,t) = cos(t)*cos(pi*y)*(p*(b+1)+2*b*q)      %
%  Files needed for the test:                                            %
%                                                                        %
%     adi.m:      This file, the main calling code.                      %
%     f.m:        The file defines the f(t,x,y)                          %
%     g.m:        The file defines the g(y,t)                            %
%     uexact.m:    The exact solution.                                   %
%                                                                        %
%     Results:         n              e            ratio                 %
%                     10           0.0074                                %
%     t_final=0.5     20           0.0021           3.5238               %
%                     40           6.2963e-04       3.3353               %       
%                     80           1.7449e-04       3.6084               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

   clear; close all;

   a = 0; b=1;  c=0; d=1; n = 40;  tfinal = 1.0;
   p=1; q=1; w=1;

   m = n;
   h = (b-a)/n;        dt=0.5*h;   
   h1 = h*h;
   x=a:h:b; y=c:h:d;

%-- Initial condition:

   t = 0;
   for i=1:m+1,
      for j=1:m+1,
%         u1(i,j) = uexact(t,x(i),y(j));
          u1(i,j) = 0.0;
      end
   end

%---------- Big loop for time t --------------------------------------




k_t = fix(tfinal/dt);


for k=1:k_t

t1 = t + dt; t2 = t + dt/2;

%--- sweep in x-direction --------------------------------------

for i=1:m+1,                              % Boundary condition.
  %u2(i,1)   = uexact(t2,x(i),y(1));
  u2(i,1)   = 0;
  %u2(i,n+1) = uexact(t2,x(i),y(n+1));
  u2(i,n+1) =0;
  %u2(1,i)   = uexact(t2,x(1),y(i));
  u2(1,i)=0;
%  u2(m+1,i) = uexact(t2,x(m+1),y(i));
end

for j = 2:n,                             % Look for fixed y(j) 

   A = sparse(m,m); b=zeros(m,1);
   for i=2:m+1,
      b(i-1) = (u1(i,j-1) -2*u1(i,j) + u1(i,j+1))/h1 + ...
		       + 2*u1(i,j)/dt;
  
      if i == 2
        b(i-1) = b(i-1) + 0;
        A(i-1,i) = -1/h1;
      else
	  
      if i == m+1
          b(i-1) = b(i-1) - 2*w/h;
          A(i-1,i-2) =  -2/h1;

	  else
	   A(i-1,i) = -1/h1;
	   A(i-1,i-2) = -1/h1;
      end
      end

      A(i-1,i-1) = 2/dt + 2/h1;

   end


     ut1 = A\b;                          % Solve the diagonal matrix.
     for i=1:m,
	 u2(i+1,j) = ut1(i);
     end

 end                                    % Finish x-sweep.
%     'xsweep', A, b,u2
%-------------- loop in y -direction --------------------------------

for i=1:m+1,                                % Boundary condition
  %u1(i,1) = uexact(t1,x(i),y(1));
  u1(i,1) =0;
  %u1(i,n+1) = uexact(t1,x(i),y(n+1));
  u1(i,n+1)=0;
  %u1(1,i) = uexact(t1,x(1),y(i));
  u1(1,i) = 0;
 % u1(m+1,i) = uexact(t1,x(m+1),y(i));
end


    
   A2 = sparse(n-1,n-1); b2=zeros(n-1,1);
   
   for i=2:m+1,
       
 
   for j = 2:n,
       
       if i==m+1
       b2(j-1) = (2*u2(i-1,j) - 2 *u2(i,j))/h1 + ...
                 + 2*u2(i,j)/dt - 2*w/h;
           
       else
       b2(j-1) = (u2(i-1,j) -2*u2(i,j) + u2(i+1,j))/h1 + ...
                 + 2*u2(i,j)/dt;
       end
       if j == 2
   
          b2(j-1) = b2(j-1) + 0;

          A2(j-1,j) = -1/h1;

       else
      
      if j==n

          b2(j-1) = b2(j-1) + 0;

          A2(j-1,j-2) =  -1/h1;

        else
           A2(j-1,j) = -1/h1;
           A2(j-1,j-2) = -1/h1;
        end
      end

      A2(j-1,j-1) = 2/dt + 2/h1;              % Solve the system
   end
      ut2= A2\b2;
      for j=1:n-1,
        u1(i,j+1) = ut2(j);
      end
     
   end

contour(x,y,u1,40); 
M(k) = getframe;     
  
 t = t + dt;


%--- finish ADI method at this time level, go to the next time level.
      
end       %-- Finished with the loop in time

%----------- Data analysis ----------------------------------

  for i=1:m+1,
    for j=1:n+1,
       ue(i,j) = uexact(tfinal,x(i),y(j));
    end
  end

  e = max(max(abs(u1-ue)))        % The infinity error.

  %figure(1); mesh(x,y,ue); title('The mesh plot of exact solution'), xlabel('y'), ylabel('x')
  %figure(2);contour(x,y,ue, 40); title('The contour plot of exact solution'), xlabel('y'), ylabel('x')
  %figure(3);mesh(x,y,u1); title('The mesh plot of heat propagation at steady state'), xlabel('y'), ylabel('x')
  
  %k,t
  %figure(1);contour(x,y,u1, 40); title('The contour plot of heat propagation at t=1.0'), xlabel('y'), ylabel('x')
  %figure(5); mesh(x,y,u1-ue); title('The mesh plot of error'), xlabel('y'), ylabel('x')
  %figure(6);contour(x,y,u1-ue,40); title('The contour plot of error'),xlabel('y'), ylabel('x')

movie(M,20)
