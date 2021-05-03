data = load("SKMCHT19.o");
iter19 = data(:,1)+1;
D19 = data(:,2);
data = load("SKMCHT25.o");
iter25 = data(:,1)+1;
D25 = data(:,2);
data = load("SKMCHT36.o");
iter36 = data(:,1)+1;
D36 = data(:,2);

D19kmc = D19(end);
D25kmc = D25(end);
D36kmc = D36(end);

D19exp = 0.5;
D25exp = 1;
D36exp = 2;

Dkmc = [D19kmc,D25kmc,D36kmc];
Dkmc = [0.67, 1.0, 2.3];
Dexp = [D19exp,D25exp,D36exp];
xfit = [0.25:0.25:2.75];
yfit = 0.88*xfit;
figure(31)
hold on
for i = 1:3
    plot(Dkmc(i),Dexp(i),'ro');
end
plot(xfit,yfit,'k-','linewidth',3)
hold off

figure(32)
hold on
plot(iter19,D19,'m.');
plot(iter25,D25,'g.');
plot(iter36,D36,'b.');
hold off

walkData = load("poreWalk3D.o");
step = walkData(1:end-1,1);
diffusivity = walkData(end,1);
xcoord = walkData(1:end-1,2)*0.01;
ycoord = walkData(1:end-1,3)*0.01;
zcoord = walkData(1:end-1,4)*0.01;
simT = walkData(1:end-1,5);

figure(33)
hold on
plot3(xcoord(1),ycoord(1),zcoord(1),'ro');
plot3(xcoord(end),ycoord(end),zcoord(end),'co');
for i = 1:( length(xcoord)-1 )
    plot3(xcoord(i:(i+1)),ycoord(i:(i+1)),zcoord(i:(i+1)),'linewidth',1.0);
end
    hold off
