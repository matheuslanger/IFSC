clear all;
freq = [1, 1.8, 2.45, 3.5, 4.2, 5.8];
d=10;
delta_D= 10;
h=-10;
c=3e8;

for i=1:6
    rf(i)=17.32*sqrt(d/(4*freq(i)));
    obst(i)=delta_D/rf(i);
    
    if(obst(i)<0.6)
        lamb(i)=c/(freq(i)*10^9);
        v(i)=h*sqrt((2*(10000))/(lamb(i)*5000*5000));
        if(v(i)<=-1)
            Gd(i)=0;
        end
        if(v(i)>-1 && v(i)<0)
            Gd(i)=20*log10(0.5-0.62*v(i));
        end
        if(-1<v(i) && v(i)<0)
            Gd(i)=20*log10(0.5^(-0.95*v(i)));
        end
        if(-1<v(i) && v(i)<0)
            Gd(i)=;
        end
        if(-1<v(i) && v(i)<0)
            Gd(i)=;
        end
    end
end
v;