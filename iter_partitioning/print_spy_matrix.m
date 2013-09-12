%close all; clc; clear all;
%matrix = 'dfl001';
%str = ['../matrices_preliminary/' matrix '.mtx'];
strdir = '../matrices/';
finaldir = '../../thesis/img/';
d = dir([strdir '*.mtx']);

for k=1:length(d)
	matrix = d(k).name;
    str = [strdir matrix ];
	%matrix = 'italy_osm'; str = [str '.mtx'];
	A  = mmread(str);

	figure(k);
    spy(A);
    matrix2 = matrix(1:end-4);
    str2 = [finaldir matrix2 '.eps'];
    print(k,'-depsc','-r300',str2);
    close(k);
end
%end
