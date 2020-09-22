# RTOS Analog Compass
Real Time Operating Systems project for school. This code runs on the MSP432 device with an Educational BoosterPack MKII (BOOSTXL-EDUMKII).


Joystick 9 Quadrants: Details
State 0: 880 Hz, Duty Cycle: 0%
x_pos: 341 <= x <= 682
y_pos: 341 <= y <= 682
Select: (x, y) 511, 511

State 1: 880 Hz, Duty Cycle: 50%
x_pos: x < 341
y_pos: y > 682

State 2: 988 Hz, Duty Cycle: 50%
x_pos: 341 <= x <= 682
y_pos: y > 682

State 3: 1109 Hz, Duty Cycle: 50%
x_pos: x > 682
y_pos: y > 682

State 4: 1175 Hz, Duty Cycle: 50%
x_pos: x < 341
y_pos: 341 <= y <= 682

State 5: 1319 Hz, Duty Cycle: 50%
x_pos: x > 682
y_pos: 341 <= y <= 682

State 6: 1480 Hz, Duty Cycle: 50%
x_pos: x < 341
y_pos: y < 341

State 7: 1661 Hz, Duty Cycle: 50%
x_pos: 341 <= x <= 682
y_pos: y < 341

State 8: 1760 Hz, Duty Cycle: 50%
x_pos: x > 682
y_pos: y < 341 
