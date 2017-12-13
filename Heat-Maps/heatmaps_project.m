% This code has been written for a project in the Smart Spaces course.
% The aim of this project is to get information about the visual attention of
% people images.

% Nathan Hubens - Alexandre Beis


% Choose the first or second set :
set = 2;


% Specify the paths
image_path = strcat('Set',num2str(set),'/Images/');
heat_maps = strcat('Set',num2str(set),'/Heat Maps/');
basename1 = strcat('Set',num2str(set),'_');
basename2 = strcat('heatmap',num2str(set),'_');


% Plot the images and their heatmaps and save them
for m=1:4

FileName1=strcat(basename1,num2str(m),'.jpg')
FileName2=strcat(basename2,num2str(m),'.jpg')

I = im2double(imread(strcat(image_path, FileName1)));
R = RARE2012(I);

figure
subplot(121), imagesc(I), title('Initial image')
subplot(122), imagesc(R), title('Saliency map')

imwrite(R, strcat(heat_maps,FileName2))

end
