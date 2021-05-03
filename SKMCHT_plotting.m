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
close all

figure(33)
hold on
plot3(xcoord(1),ycoord(1),zcoord(1),'ko','markersize',30,'linewidth',30);
plot3(xcoord(end),ycoord(end),zcoord(end),'kx','markersize',30,'linewidth',30);
xlabel('$x$ ($\mu$m)','interpreter','latex','fontsize',19);
ylabel('$y$ ($\mu$m)','interpreter','latex','fontsize',19);
zlabel('$z$ ($\mu$m)','interpreter','latex','fontsize',19);

curve = animatedline('linewidth',2);
view(43,24);
set(gca, 'XLim', [-60 80], 'YLim', [-80 60], 'ZLim', [-20 65]);
% set(gca,'XColor', 'none','YColor','none','ZColor','none');
set(gca,'Color','k');
addpoints(curve,xcoord(1),ycoord(1),zcoord(1));
head = scatter3(xcoord(1),ycoord(1),zcoord(1),'filled','MarkerFaceColor','b','MarkerEdgeColor','b');
v = VideoWriter('poreWalk3D_black');
v.Quality = 95;
open(v);
M(1) = getframe(gcf);
writeVideo(v,M(1));
for i = 1:( length(xcoord)-1 )
    pause((simT(i+1)-simT(i))/10);
    delete(head);
    addpoints(curve,xcoord(i+1),ycoord(i+1),zcoord(i+1));
    head = scatter3(xcoord(i+1),ycoord(i+1),zcoord(i+1),'filled','MarkerFaceColor','b','MarkerEdgeColor','b');
%     h = plot3(xcoord(i),ycoord(i),zcoord(i),'b.','markersize',30,'linewidth',30);
%     pause((simT(i+1)-simT(i))/100);
%     delete(h);
%     h = plot3(xcoord(i:(i+1)),ycoord(i:(i+1)),zcoord(i:(i+1)),'b.-','markersize',30,'linewidth',2);
%     hold all
    drawnow
    simT(i+1)
    M(i+1) = getframe(gcf);
    writeVideo(v,M(i+1));
end
close(v);
movie(M);
% set(gca, 'XLim', [0 1], 'YLim', [0 1], 'ZLim', [0 1]); grid on
    hold off
