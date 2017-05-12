%To import data from txt file, change extension of txt to .csv and open
%with Excel. Clean up any garbage data. Then import and save the workspace
%as a .mat

figure(1);
plot(time,xAcc,time,yAcc);
title('graph of time vs acceleration');
xlabel('time');
ylabel('acceleration');
legend('xAcc','yAcc');


%Create a magnitude Acceleration
xMag = sqrt( xAcc.^2 + yAcc.^2 );
figure(2);
plot(time,xMag);
title('time vs Magnitude of acceleration');
xlabel('time');
ylabel('xMag');

