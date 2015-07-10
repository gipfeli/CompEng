% Code for the class Computational Methods for Engineering Applications
% Created by Lina Kulakova
% Copyright (c) CSElab, ETH Zurich, 2015

xvis = load('q2-result.txt');
zvis = xvis(:,3);
yvis = xvis(:,2);
xvis = xvis(:,1);

Nvisx = 100;
Nvisy = 100;

figure(1);
mesh(reshape(xvis,Nvisx,Nvisy),reshape(yvis,Nvisx,Nvisy),reshape(zvis,Nvisx,Nvisy));
axis equal
xlim([-0.1 0.1]); ylim([-0.1,0.1]); zlim([0.01 0.06]);
