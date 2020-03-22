
    clear; 
    kk =40; T= 10; dt =T/kk; u0 = 200; 
    c = 1/26; usur  = 70;

    t(1) = 0; u1(1) = u0; u2(1)=u0; u3(1)=u0; u4(1)=u0;
    ueaxt(1) = u0;

    for i=1:kk

      u1(i+1) = u1(i) + dt*ftay_b(t(i),u1(i));             % 1-st order
      u2(i+1) = u2(i) + dt*ftay_b(t(i),u2(i))  - ...
                dt^2*c*ftay_b(t(i),u2(i))/2;               % 2-nd order
      u3(i+1) =  u3(i) + dt*ftay_b(t(i),u3(i)) - ... 
                dt^2*c*ftay_b(t(i),u3(i))/2 +    ...
                dt^3*c^2*ftay_b(t(i),u3(i))/6;             % 3-rd order
      u4(i+1) =  u4(i) + dt*ftay_b(t(i),u4(i)) - ... 
                dt^2*c*ftay_b(t(i),u4(i))/2 +    ...
                dt^3*c^2*ftay_b(t(i),u4(i))/6   ...
                -dt^4*c^3*ftay_b(t(i),u4(i))/24;           % 4-th order
      t(i+1) = t(i) + dt;

      ueaxt(i+1) = usur + (u0-usur)*exp(-c*t(i+1));        % Exact

    end

    semilogy(t,abs(ueaxt-u1),t,abs(ueaxt-u2),t,abs(ueaxt-u3), ...
             t, abs(ueaxt-u4))

    title('Error plot in log scale')
    figure(2); 
    plot(t,abs(ueaxt-u1),t,abs(ueaxt-u2),t,abs(ueaxt-u3), ...
             t, abs(ueaxt-u4))         % Too small to see anything!

    xlabel('time')
    err = [ueaxt(kk)-u1(kk),ueaxt(kk)-u2(kk),ueaxt(kk)-u3(kk),...
           ueaxt(kk)-u4(kk)]

    dt

 

