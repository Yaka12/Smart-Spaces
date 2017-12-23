function attention_map = AttentionSimpleGlobalRarity(I)
% This is a very simple global rarity based attention algorithm. It does
% not take into account any local information
% Author: Matei Mancas http://tcts.fpms.ac.be/attention
% Free for research purpose only
% If used, please reference my thesis from http://tcts.fpms.ac.be/~mancas
% This is the main function
% output: attention_map (2D matrix)
% input: image I (used after Matlab imread() function = 2D or 3D matrix)
% Example : 
% >I=imread('autumn.tif');
% >attention_map = AttentionSimpleGlobalRarity(I)
% >figure,imshow(I), title('original') 
% >figure,imshow(attention_map), title('simple global rarity attention map')

%parameters
quantification = 16; % quantification: number of bins for rarity counting 
win_size = 3; % neighbourhood size


% if grey-level
if size(I,3)==1
    % mean and standard deviation (low and high frequencies) are both
    % considered
    attention_map = (SimpleGlobalRarity(imfilter(I,ones(win_size)/9,'symmetric'), quantification) + SimpleGlobalRarity(stdfilt(I, ones(win_size)), quantification))/2;
    attention_map = (double(attention_map)-double(min(min(attention_map))))./double(max(max(attention_map)));
end

% if colour image
if size(I,3)>1

    %opponent colour system
    II=rgb2ycbcr(I);
    I1=II(:,:,1);
    I2=abs(I1-I(:,:,3))+abs(I(:,:,3)-I1);
    I3=abs(I(:,:,1)-I(:,:,2))+abs(I(:,:,2)-I(:,:,1));
    
    % mean and standard deviation global rarities are computed on the three
    % colour components
    attention_map1 = (SimpleGlobalRarity(imfilter(I1,ones(win_size)/9,'symmetric'), quantification) + SimpleGlobalRarity(stdfilt(I1,ones(win_size)), quantification))/2;
    attention_map2 = (SimpleGlobalRarity(imfilter(I2,ones(win_size)/9,'symmetric'), quantification) + SimpleGlobalRarity(stdfilt(I2,ones(win_size)), quantification))/2;
    attention_map3 = (SimpleGlobalRarity(imfilter(I3,ones(win_size)/9,'symmetric'), quantification) + SimpleGlobalRarity(stdfilt(I3,ones(win_size)), quantification))/2;
    
    % the maximum of the three components is finally used
    attention_map = double(max(max(attention_map1,attention_map2),attention_map3));
    attention_map = (double(attention_map)-double(min(min(attention_map))))./double(max(max(attention_map)));
end