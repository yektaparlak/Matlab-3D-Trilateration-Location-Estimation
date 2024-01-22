% Define the number of readings to take
num_readings = 2;

% Read distance data from each sensor and sum the readings
sum1 = 0;
sum2 = 0;
sum3 = 0;
sum4 = 0;

% Accumulate readings from each sensor
% In this loop, distance readings from each sensor are accumulated to obtain the total sum of readings.
% The variables sum1, sum2, sum3, and sum4 store the cumulative sum for each sensor.
for i = 1:num_readings
    sum1 = sum1 + u1;
    sum2 = sum2 + u2;
    sum3 = sum3 + u3;
    sum4 = sum4 + u4;
end

% Calculate the average distance for each sensor
% The average distance for each sensor is computed by dividing the respective sum by the number of readings.
% The variables distance1, distance2, distance3, and distance4 store the average distances from sensors 1, 2, 3, and 4, respectively.
distance1 = sum1 / num_readings;
distance2 = sum2 / num_readings;
distance3 = sum3 / num_readings;
distance4 = sum4 / num_readings;

% Trilateration Calculation
% Calculate the squared distances between each sensor and the unknown point
% The squared distances between each sensor and the unknown point are computed using the average distances obtained earlier.
% The variables d1_squared, d2_squared, d3_squared, and d4_squared store the squared distances from sensors 1, 2, 3, and 4, respectively.
d1_squared = distance1^2;
d2_squared = distance2^2;
d3_squared = distance3^2;
d4_squared = distance4^2;

% Calculate the coefficients for the linear equations
% The coefficients for the linear equations used in the trilateration process are calculated based on the sensor coordinates and squared distances.
% The variables a1, b1, c1, d1, a2, b2, c2, d2, a3, b3, c3, and d3 store the coefficients for the linear equations.
a1 = 2 * (sensor1_x - sensor2_x);
b1 = 2 * (sensor1_y - sensor2_y);
c1 = 2 * (sensor1_z - sensor2_z);
d1 = d2_squared - d1_squared - sensor2_x^2 + sensor1_x^2 - sensor2_y^2 + sensor1_y^2 - sensor2_z^2 + sensor1_z^2;

a2 = 2 * (sensor1_x - sensor3_x);
b2 = 2 * (sensor1_y - sensor3_y);
c2 = 2 * (sensor1_z - sensor3_z);
d2 = d3_squared - d1_squared - sensor3_x^2 + sensor1_x^2 - sensor3_y^2 + sensor1_y^2 - sensor3_z^2 + sensor1_z^2;

a3 = 2 * (sensor1_x - sensor4_x);
b3 = 2 * (sensor1_y - sensor4_y);
c3 = 2 * (sensor1_z - sensor4_z);
d3 = d4_squared - d1_squared - sensor4_x^2 + sensor1_x^2 - sensor4_y^2 + sensor1_y^2 - sensor4_z^2 + sensor1_z^2;

% Calculate the determinants for Cramer's rule
% The determinants required for Cramer's rule are calculated using the coefficients of the linear equations.
% The variables detA, detX, detY, and detZ store the determinants for subsequent calculations.
detA = a1 * (b2 * c3 - b3 * c2) - b1 * (a2 * c3 - a3 * c2) + c1 * (a2 * b3 - a3 * b2);
detX = d1 * (b2 * c3 - b3 * c2) - b1 * (d2 * c3 - d3 * c2) + c1 * (d2 * b3 - d3 * b2);
detY = a1 * (d2 * c3 - d3 * c2) - d1 * (a2 * c3 - a3 * c2) + c1 * (a2 * d3 - a3 * d2);
detZ = a1 * (b2 * d3 - b3 * d2) - b1 * (a2 * d3 - a3 * d2) + d1 * (a2 * b3 - a3 * b2);

% Calculate the coordinates of the unknown point
% Finally, the coordinates of the unknown point are computed using the determinants and coefficients obtained above.
% The variables X1, Y1, and Z1 store the calculated coordinates of the unknown point.
X1 = detX / detA;
Y1 = detY / detA;
Z1 = detZ / detA;
