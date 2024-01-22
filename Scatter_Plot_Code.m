% Clear all variables and configurations
clear all;

% Set simulation options for the model
opt = simset('SrcWorkspace','current','solver','ode45', 'ZeroCross', 'off');

% Simulate the model "Trilat3DPlot.slx" for a duration of 10 seconds
sim('Trilat3DPlot.slx',[0 10], opt);

% Define the coordinates of the sensors
sensor1_x = -4.2; sensor1_y = 9.8; sensor1_z = 2.7;
sensor2_x = -4.2; sensor2_y = 0.5; sensor2_z = 2.5;
sensor3_x = -8.7; sensor3_y = 0.5; sensor3_z = 2.9;
sensor4_x = -8.7; sensor4_y = 9.8; sensor4_z = 2.1;

% Create a new figure for the 3D plot
figure();

% Set the size of the markers on the scatter plot
S = 100;

% Scatter plot of the detected human's coordinates
scatter3(X1, Y1, Z1, "*", 'DisplayName','Detected Human');
hold on;

% Scatter plot of the actual human's coordinates
scatter3(-5.1, 10.9, -3.0, "*", 'DisplayName','Actual Human');
hold on;

% Scatter plot of the sensor coordinates
% Each sensor is represented as a filled blue marker on the plot
scatter3(sensor1_x, sensor1_y, sensor1_z, S, "blue",'filled', 'DisplayName','Sensor1');
hold on;
scatter3(sensor2_x, sensor2_y, sensor2_z, S, "blue", 'filled', 'DisplayName','Sensor2');
hold on;
scatter3(sensor3_x, sensor3_y, sensor3_z, S, "blue", 'filled', 'DisplayName','Sensor3');
hold on;
scatter3(sensor4_x, sensor4_y, sensor4_z, S, "blue", 'filled', 'DisplayName','Sensor4');

% Display the legend to differentiate between different markers
legend;

% Set the axis labels and title for the plot
xlabel('X');
ylabel('Y');
zlabel('Z');
title('3D Scatter Plot');
