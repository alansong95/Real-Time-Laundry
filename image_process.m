count = 0;
first = 1;

tog = 0;

diameter = 0;
diameter2 = 0;

quit = 0;

sticker_array = zeros(4,3)+1;


img = imread('2 (4).jpg');

filter2 = fspecial('log',[50 50], 0.47);
img2 = imfilter(img,filter2,'replicate');

on = 0;
on2 = 0;

count_tog = 0;


 

[height, width, z1] = size(img);


i = 1;
j = 1;

count2 = 0;

% get sticker info
while j < width
    while i < height
        if i >= height || j >= width
           break; 
        end
        count_tog = 1;
        first = 1;
        while img(i,j,1) > 180 && img(i,j,3) > 180 && img (i, j, 2) < 30
            if first == 1
                sticker_array(count+1, 1) = j;
                sticker_array(count+1, 2) = i;
                if count_tog == 1
                   count = count + 1;
                   count_tog = 0;
                end
            end
            first = 0;
            img(i, j, :) = 0;
            
            j = j + 1;
            tog = 1;
            diameter = diameter + 1;
        end
        
        if tog == 1
            j = j + 10;
            sticker_array(count,3) = diameter;
            tog = 0;
        end     
        
        i = i + 1;
    end
    j = j + 1;
    i = 1;
end





if count == 2
    for j = sticker_array(1,1)+sticker_array(1,3)+30:sticker_array(2,1)-15
        for i = sticker_array(1,2)-round(sticker_array(1,3)/2)-15:sticker_array(1,2)+round(sticker_array(1,3)/2)+15
            if img2(i, j, 1) > 240 && img2(i, j, 2) < 200 && img2(i, j, 3) < 200
                on = 1;
            end        
        end
    end
end


if count == 4
    for j = sticker_array(1,1)+sticker_array(1,3)+30:sticker_array(2,1)-15
        for i = sticker_array(1,2)-round(sticker_array(1,3)/2)-15:sticker_array(1,2)+round(sticker_array(1,3)/2)+15
            if img2(i, j, 1) > 130 && img2(i, j, 2) < 110 && img2(i, j, 3) < 110
                on = 1;
            end        
        end
    end
    
    for j = sticker_array(3,1)+sticker_array(1,3)+30:sticker_array(4,1)-15
        for i = sticker_array(3,2)-round(sticker_array(1,3)/2)-15:sticker_array(3,2)+round(sticker_array(1,3)/2)+15
            if img2(i, j, 1) > 130 && img2(i, j, 2) < 110 && img2(i, j, 3) < 110
                on2 = 1;
            end        
        end
    end
    
end








 
 
 
for i=sticker_array(1,2):sticker_array(1,2)+10
    for j=sticker_array(1,1):sticker_array(1,1)+10
        img(i,j,:) = 0;
    end
end
% 
for i=sticker_array(2,2):sticker_array(2,2)+10
     for j=sticker_array(2,1):sticker_array(2,1)+10
         img(i,j,:) = 0;
     end
end

for i=sticker_array(3,2):sticker_array(3,2)+10
     for j=sticker_array(3,1):sticker_array(3,1)+10
         img(i,j,:) = 0;
     end
end

for i=sticker_array(4,2):sticker_array(4,2)+10
     for j=sticker_array(4,1):sticker_array(4,1)+10
         img(i,j,:) = 0;
     end
end
% 
% xx = 474;
% yy = 811;
% 
% for i=yy:yy+10
%     for j=xx:xx+10
%         img(i,j,:) = 0;
%     end
% end


figure(1); imshow(img)
figure(2); imshow(img2)

laundry_count = count / 2;

if laundry_count == 1
    status = sprintf('%d %d ', laundry_count, on);
end

if laundry_count == 2
   status = sprintf('%d %d %d ', laundry_count, on, on2); 
end


% send data 
ip = '128.199.185.239';
port = 4950;
my_port = 33833;

udpA = udp(ip, port, 'LocalPort', my_port);
fopen(udpA);
fwrite(udpA, status);
fclose(udpA);

    