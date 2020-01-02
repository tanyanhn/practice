% function ReadIntoData
clc
clear
close all

total = 10;
% path_sol = {'Result/sol1/', 'Result/sol2/', 'Result/sol3/', 'Result/sol4/',  'Result/sol5/',  'Result/sol6/',  'Result/sol7/', 'Result/sol8/'};
path{1} = 'Result/data/pandadata/';    % len1 = 10;
path{2} = 'Result/data/mickeydata/'; % len2 = 6;
path{3} = 'Result/sol1/';
path{4} = 'Result/sol2/';
path{5} = 'Result/sol3/';
path{6} = 'Result/sol4/';
path{7} = 'Result/sol5/';
path{8} = 'Result/sol6/';
path{9} = 'Result/sol7/';
path{10} = 'Result/sol8/';

list = cell(1, total);  % table of filenames
tmp = cell(1, total);   % preOrder and direction of oriented loops
len = zeros(1, total);  % number of loops

for i = 1:total
    list0 = dir([path{i}, '*.txt']);  % table of filenames
    %    str0 = strcat(path, list0(1).name);
    str0 = [path{i}, list0(1).name]; % the first filename path
    tmp{i} = load(str0);
    % generating list of file path
    nameCell = cell(length(list0)-1,1);
    for j = 2:length(list0)
        nameCell{j-1} = list0(j).name;
    end
    list{i} = sort_nat(nameCell);
    len(i) = size(tmp{i}, 2);
end
%%
TITLE = {'P: interior of the panda P.', ...
    'M: interior of the mickey M.', ...
    'M\capP: setIntersection of M and P.', ...
    'P-M: setMinus of P and M.', ...
    'M-P: setMinus of M and P.', ...
    'M\cup^{\perp\perp}P: regularized union of M and P.', ...
    '(M-P)\cup(P-M): setSymmDiff of P and M.', ...
    'P^{\perp}\capLOOP^{+}: setIntersection of P^{\perp} and a loop', ...
    'M^{\perp}\capLOOP^{+}: setIntersection of M^{\perp} and a loop', ...
    'P^{\perp}: exterior of the panda P.', ...
    'P^{\perp} \cap M^{\perp}: complementary set of union of M and P.'};



%% Mickey mouse and Panda modeled as a Yin set M
figure;hold on;
for k = 1:2
    subplot(1,2,k);  axis off;
    print_pm(list{k}, path{k}, tmp{k}, k);
    set(gca,'position',[0.5 * (k-1),0.0,0.48,0.99]);
end
hold off;
set(gcf,'unit','normalized','position',[0.5,1,0.56,0.48]);

for k = 1:2
    figure; hold on;  axis off;
    print_pm(list{k}, path{k}, tmp{k}, 0);
    title(TITLE{k});
    hold off;
    set(gcf,'unit','normalized','position',[0.05 *(k-1),0,0.30,0.52]);
    set(gca,'position',[0.05,0.0,0.9,0.94]);
end

%% intersection of M and P
for k = [3 4 5 6 7 8 9]
    figure;   hold on;  axis off; 
    print_pm(list{k}, path{k}, tmp{k});
    if(k > 7)
        print_pm(list{k}, path{k}, tmp{k}, 1); 
    else
        print_pm(list{1}, path{1}, tmp{1}, 1);
        print_pm(list{2}, path{2}, tmp{2}, 2);
    end
    title(TITLE{k});
    hold off;
    set(gcf,'unit','normalized','position',[0.05 *(k-1),0,0.30,0.52]);
    set(gca,'position',[0.02,0.0,0.92,0.94] );
end
%%  Panda.complementary set
for k = 10
    figure;  hold on;  axis off
    patch([0.072 5.0 5.0 0.072 0.072], [-0.05 -0.05 4.6 4.6 -0.05],'y', 'linewidth', 0.1);
    plot([0.072 5.0 5.0 0.072 0.072], [-0.05 -0.05 4.6 4.6 -0.05],'y', 'linewidth', 0.1);
    print_pm(list{k}, path{k}, tmp{k});
    print_pm(list{k}, path{k}, tmp{k}, 1); 
    title(TITLE{k});   hold off;
    set(gcf,'unit','normalized','position',[0.05 *k,0,0.30,0.53]);
    set(gca,'position',[0.02,0.0,0.92,0.94] );

end


%%  modeled as a Yin set M
function print_pm(list1, path1, tmp1, flag1)
% flag1 =-1; patch with color yellow
% flag1 =0, patch with color black
% flag1 =1, plot yin set with blue line
% flag1 =2, plot yin set with red line
% flag1 =3, plot yin set with yellow line
if nargin < 4
    flag1 = -1;
end
c = ['b','r', 'y'];  c1 = ['y','k'];
hold on;
for i = 1:size(tmp1, 2)
    str= strcat(path1, list1{tmp1(1, i)});
    temp = load(str);
    if(tmp1(2, i) > 0) % fill the area of Yin set
        if(flag1 <= 0)
            patch(temp(1, :), temp(2, :), c1(flag1 + 2), 'linewidth', 0.01);
        else
            plot(temp(1, :), temp(2, :), c(flag1),  'linewidth', 1.5);
        end
    else
        if(flag1 <= 0)
            patch(temp(1, :), temp(2, :), 'w', 'linewidth', 0.1);
        else
            plot(temp(1, :), temp(2, :), [c(flag1), ':'],'linewidth', 2.0);
        end
    end
end

end