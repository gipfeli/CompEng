% Code for the class Computational Methods for Engineering Applications
% Created by P--
% Copyright (c) CSElab, ETH Zurich, 2015

data = load('ex6_data.txt');
r1 = load('ex6_result_case1.txt');
r2 = load('ex6_result_case2.txt');
r3 = load('ex6_result_case3.txt');



figure(1);
scatter(data(:,1),data(:,2),100,'ko','filled');
hold on;
plot(r1(:,1),r1(:,2),'-b','LineWidth',3); 
plot(r2(:,1),r2(:,2),'-r','LineWidth',3); 
plot(r3(:,1),r3(:,2),'-m','LineWidth',3); 
axis square; 
set(gca,'FontSize',14)
xlabel('T'); ylabel('change of size w.r.t. ref. time')
legend('data','Linear','Exp','S-Shape','Location','NorthWest');
hold off;

