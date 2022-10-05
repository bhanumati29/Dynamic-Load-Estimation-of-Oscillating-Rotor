clc
clear
close all

data = readtable("HighRPM_quarterOscillation_20s_raw.csv");
Y_lable = ["Fx","Fy","Fz","Mx","My","Mz"];


d=designfilt('lowpassfir','FilterOrder', 100,'CutoffFrequency',20,'SampleRate',1000);


F_Fx =filtfilt(d,data.Fx);
figure(1)
plot(data.Time,data.Fx)
hold on
plot(data.Time,F_Fx,'LineWidth',1)
legend('Input Data','Filtered Data')
xlabel("Time(s)")
ylabel("Fx(N)")
daspect([0.8 5 1])

F_Fy = filtfilt(d,data.Fy);
figure(2)
plot(data.Time,data.Fy)
hold on
plot(data.Time,F_Fy,'LineWidth',1)
legend('Input Data','Filtered Data')
xlabel("Time(s)")
ylabel("Fy(N)")
daspect([1 5 1])

F_Fz = filtfilt(d,data.Fz);
figure(3)
plot(data.Time,data.Fz)
hold on
plot(data.Time,F_Fz,'LineWidth',1)
legend('Input Data','Filtered Data')
xlabel("Time(s)")
ylabel("Fz(N)")
daspect([0.8 5 1])

F_Mx = filtfilt(d,data.Mx);
figure(4)
plot(data.Time,data.Mx)
hold on
plot(data.Time,F_Mx,'LineWidth',1)
legend('Input Data','Filtered Data')
xlabel("Time(s)")
ylabel("Mx(N-m)")
daspect([3 2 1])

F_My = filtfilt(d,data.My);
figure(5)
plot(data.Time,data.My)
hold on
plot(data.Time,F_My,'LineWidth',1)
legend('Input Data','Filtered Data')
xlabel("Time(s)")
ylabel("My(N-m)")
daspect([0.5 1 1])

F_Mz = filtfilt(d,data.Mz);
figure(6)
plot(data.Time,data.Mz)
hold on
plot(data.Time,F_Mz,'LineWidth',1)
legend('Input Data','Filtered Data')
xlabel("Time(s)")
ylabel("Mz(N-m)")
daspect([3 3 1])