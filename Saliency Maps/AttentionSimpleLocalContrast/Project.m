% This code has been written for a project in the Smart Spaces course.
% The aim of this project is to get information about the visual attention of
% people images.

% Nathan Hubens - Alexandre Beis


% Choose the first or second set :
set = 2;


% Specify the paths
image_path = strcat('../Data/Set',num2str(set),'/Images/');
heat_maps = strcat('../Data/Set',num2str(set),'/Maps Local/');
basename1 = strcat('blurred_Set',num2str(set),'_');
basename2 = strcat('map',num2str(set),'_');


% Plot the images and their heatmaps and save them
for m=1:4

FileName1=strcat(basename1,num2str(m),'.jpg')
FileName2=strcat(basename2,num2str(m),'.jpg')

I = im2double(imread(strcat(image_path, FileName1)));
R = AttentionSimpleLocalContrast(I);

figure
subplot(121), imagesc(I), title('Initial image')
subplot(122), imagesc(R), title('Saliency map')

imwrite(R, strcat(maps,FileName2))

end
