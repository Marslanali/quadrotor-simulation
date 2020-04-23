function [positionData Size] = trajectoryAlignment( demonstration1, demonstration2, demonstration3 )

length1 = size(demonstration1,2);
length2 = size(demonstration2,2);
length3 = size(demonstration3,2);

lenVector = [length1 length2 length3];

Size = min (lenVector);

x1 = linspace(0,1,length1);
y1 = demonstration1([1 2 3],:);
xx1 = linspace(0,1,Size);

x2 = linspace(0,1,length2);
y2 = demonstration2([1 2 3],:);
xx2 = linspace(0,1,Size);

x3  = linspace(0,1,length3);
y3  = demonstration3([1 2 3],:);
xx3 = linspace(0,1,Size);

yy1 = spline (x1,y1,xx1);
yy2 = spline (x2,y2,xx2);
yy3 = spline (x3,y3,xx3);

clock = linspace (0,2*pi,Size)';

clockSignal = [clock ; clock ; clock ];

demonstrations = [yy1 yy2 yy3]';

positionData = [clockSignal demonstrations]';


end


