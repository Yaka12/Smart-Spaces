function attention_map = AttentionSimpleLocalContrast(I)
% This is a very simple local contrast based attention algorithm. It does
% not take into account any global information
% Author: Matei Mancas http://tcts.fpms.ac.be/attention
% Free for research purpose only
% If used, please reference my thesis from http://tcts.fpms.ac.be/~mancas
% input = I is an initial image (grey-level or colour) obtained using the imread()
% Matlab function
% output = attention_map is the output attention map using local contrast


% The image should be not bigger than 300*300 pixels as the maximum
% filtering kernel size is of 71 (~1/4 of the image)
M=max(size(I,1),size(I,2));
if M>300
    RR = (300/M);
    I=imresize(I,RR,'bicubic');
end

% From A1 (heavy filtering) to A6 (no filtering)
% When we open the eyes, the first image seen is A1, and than, A2, A3,
% etc..

f1=ones(uint8(71)); 
A1 = imfilter(I, f1/sum(sum(f1)),'symmetric');

f1=ones(uint8(57)); 
A2 = imfilter(I, f1/sum(sum(f1)),'symmetric');

f1=ones(uint8(43)); 
A3 = imfilter(I, f1/sum(sum(f1)),'symmetric');

f1=ones(uint8(29)); 
A4 = imfilter(I, f1/sum(sum(f1)),'symmetric');

f1=ones(uint8(15)); 
A5 = imfilter(I, f1/sum(sum(f1)),'symmetric');

f1=ones(uint8(1)); 
A6 = imfilter(I, f1/sum(sum(f1)),'symmetric');

% Building a simple background model by using the mean of all the
% resolutions but the better one
back = abs((im2double(A1)+im2double(A2)+im2double(A3)+im2double(A4)+im2double(A5))/5);

% The difference between the better resolution and the model of the image
% obtained is surprising ...
attention= abs(back-im2double(A6))+abs(im2double(A6)-back);

% If the image is a colour one, the attention map is the intensity of local
% contast
if size(I,3)==3
    attention = rgb2ycbcr(attention);
    attention_map = attention(:,:,1);
    attention_map = (double(attention_map)-double(min(min(attention_map))))./double(max(max(attention_map)));
end

% If grey-level, tha attention map is already there
if size(I,3)==1
    attention_map=attention;
    attention_map = (double(attention_map)-double(min(min(attention_map))))./double(max(max(attention_map)));
end