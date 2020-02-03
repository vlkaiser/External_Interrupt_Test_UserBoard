# External_Interrupt_Test_UserBoard
Uses the User Board project settings on the Xplained Pro board.  

Intent:
Master will receive I2C commands from single board computer (user-interface)
Master will send appropriate commands to I2C Slave devices for processing.

Each button press is an External Interrupt:
0. Power Applied (eg hard switch)
	- Status Check  (Power, current...)
	- LED panel on
1. Power up 
	- LED panel On
	- send command: go to home position
2. Measure
	- Send measure command
	- LED panel On
3. Stop
	- Send stop command
	- Halt all processes
	- LED panel on
4. Power Off
	- Finish process
	- send home command
	- LED panel Off
