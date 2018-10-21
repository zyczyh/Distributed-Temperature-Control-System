# Distributed-Temperature-Control-System

Source of project demand：

In response to the concept of energy saving and environmental protection, a hotel promoted the self-service room temperature adjustment air conditioning system and proposed to us a requirement for developing a distributed temperature control system.

Project detail and functions:

1. The entire software is oriented to central air conditioning, slaves and operators, and the distributed temperature control system consists of central air conditioning and 4 room air conditioners.


2. Central air conditioner has three working states: shutdown, standby, work, after boot initialization, the working mode of the air conditioner (cooling and heating) needs to be set. The temperature in the default cooling mode is 22 °C, and in the heating mode, it is only 28 °C, and the wind speed is medium speed. There is a time when the control unit temperature control request is started, otherwise it is in the standby state. When the temperature control request conflicts with the central air conditioning working mode, the central air conditioning working mode is mainly used.

3. The slave control machine has two states: on and off. It needs to be connected with the central air conditioner after the controller is turned on. After the user enters the room number + ID number, the slave machine obtains the working mode from the central air conditioner and works. The default operating temperature is displayed on the control panel, and the target temperature and operating temperature can be set on the control panel (continuous keys are not responded within 1 second).

4. When the target temperature meets the central air conditioning working mode and the current room temperature does not reach the target temperature, the room temperature changes by 2 ° C in the case of medium speed wind, and the temperature changes by 2.5 ° C per minute in the case of high speed wind. The temperature changes by 1.5 ° C per minute.

5. After the target temperature of the room is reached, the slave controller stops sending the adjustment temperature request to the host computer. At this time, the room temperature changes by 1 °C every minute. When the room temperature exceeds the target temperature by 1 °C, the slave controller restarts.

6. The central air conditioner calculates the energy consumed by each room in real time (a standard power consumption unit per minute for low speed wind, 0.8 per minute for medium speed wind, 1.3 per minute for high speed wind) and the amount to be paid (5 yuan per unit) And send the corresponding information to each slave to display online, so that customers can view the usage and amount in real time.

7. The central air-conditioning monitoring has a statistical function, and daily reports, weekly reports, and monthly reports can be given as needed. The contents of the report are as follows: the room number, the number of times the machine is turned on, the start and stop time of the temperature control request, the start and end temperature of the temperature control request, and the air volume.

8. The central air conditioner can only process three slave control requests at the same time, and handle temperature control requests of more than three slaves in a time slice polling manner.

9. The central air conditioner can set the refresh rate and working mode.

