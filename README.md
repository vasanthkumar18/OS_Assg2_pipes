Check out CS3003D_Assgn_02.pdf for questions
and Q1 and Q2 folders for respective answers.


The questions from CS3003D_Assgn_02.pdf  are 

Q1: 
Temperature Controller – Using named and unnamed pipes
Consider three processes P1, P2, and P3 in an IoT architecture. The process P1 reads the
temperature setting from the thermostats installed in a factory from five different
locations, viz., L1, L2, L3, L4, and L5. The recorded temperature should be in the range 15
deg Celsius to 45 deg Celsius. Process P1 collects and sends the data (user input
tesmperature data) to Process P2. Process P2 calculates the average and the standard
deviation of the recorded temperatures and send to Process P3. Process P3 analyses the
temperatures with the average (avg) and std. deviation (sd) and performs the following:
 If the location temperature is equal to avg, the location is categorized as Cat0
 If the location temperature is greater than avg+sd, the location is categorized as
Cat1
 If the location temperature is greater than avg but less than avg+sd, the location
is categorized as Cat2
 If the location temperature is less than avg but greater than avg – sd, the location
is categorized as Cat3
 If the location temperature is less than avg – sd, the location is categorized as Cat4
The Process P3 then sends the category of each location to Process P1. The Process P1
then actuates the thermostat temperature as per the rules as follows:
 Cat0: Temperature setting remains the same.
 Cat1: Temperature setting is reduced by 3 deg.
 Cat2: Temperature setting is reduced by 1.5 deg.
 Cat3: Temperature setting is increased by 2 deg.
 Cat4: Temperature setting is increased by 2.5 deg.
The Process P1 then prints the revised temperature at each of the locations.

Q2:
Password Strength Calculator – Using Shared memory
Consider three processes P1, P2, and P3 sharing a memory space. Process P1 receives a
character array, password, of length 10 (contains both special character as well as
alphanumeric characters) from the user. Process P1 stores the received character array
in the shared memory. Process P2 calculates the number of alphanumeric and special
characters present. Process P3 then determines the strength of the password by the
following:
 If number of alphanumeric characters ≥ the number of special characters, the
Password is ‘Weak’
 If number of alphanumeric characters < the number of special characters, the
Password is ‘Strong’
Process P3 then communicates to Process P1 the strength of the password as ‘Strong’ or
‘Weak’.

