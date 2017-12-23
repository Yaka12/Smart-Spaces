function attention_map =SimpleGlobalRarity(I, quantification)
% Author: Matei Mancas http://tcts.fpms.ac.be/attention
% Free for research purpose only
% If used, please reference my thesis from http://tcts.fpms.ac.be/~mancas
% This is not the main function, type >help AttentionSimpleGlobalRarity 


% quantification of I
I = uint8(((double(I)-double(min(min(I))))./max(max(double(I))))*quantification);

% global probability for each grey level
P = (imhist(I)./numel(I))+eps;

% the histogram is computed on 256 levels, if quantification < 256, one may
% get rid of the unusefull bins
P(quantification+1:end)=[];

% attention map initialisation
attention_map = double(zeros(size(I)));

% attention map reconstruction
for i=0:(length(P)-1)
    % self-information computation
    attention(i+1) = -log(P(i+1)+0.000001);
    attention_map = attention_map + double(I==i).*double(attention(i+1));
end
