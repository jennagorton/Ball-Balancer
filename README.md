<h1 align="center">Ball Balancing Robot</h1>
<p align="center">Jenna Gorton, August 2025</p>


<p align="center">
  <img src="https://github.com/user-attachments/assets/b5f14a29-0212-48ce-ab44-57efbd1dfccd"
       alt="workingTest" width="420">
</p>
<p align="center">Stabilizing at center</p>

 
-----

About 
= 
I designed and built a 3RRS parallel manipulator to stabilize a ball on a platform. To complete this project, I developed the robot in CAD, derived the inverse kinematic model, and used a PID algorithm to control the robot.

Files
=
- **`Main.ino`** - Runs the code on the arduino
- **`InverseKinematics.cpp`** - Uses the target tilt angles of the platform to calculate the servo angles
- **`ScreenControl.cpp`** - Finds the calibrated position of the ball
- **`ServoControl.cpp`** - Handles smooth movement of the servos
- **`PID.cpp`** - Creates the PID equations based on the target point and the current location of the ball


Design
=
This robot was designed using CAD and then 3D printed with PLA
- This robot has a servo to control each leg of the 3RRS parallel manipulator. The lower limb of the leg has a rotational joint attached to the servo and upper limb, and the upper limb connects to the platform with a spherical joint.
- On the platform, there is a 4-wire resistive touch screen to track the position of the ball
  

Programming
=
The code was written in C++, then compiled and executed through an Arduino sketch
- The inverse kinematic model was hand-derived, and the equations were implemented in C++. The inputs are the height of the platform and the tilt of the platform in the X and Y directions.
- Two PID controllers are running simultaneously, one handles the tilt in the Y direction and the other handles the tilt in the X direction. Different gain constants were used when the ball was near the target and far away. The gain constants were carefully tuned by hand until the movement was smooth and precise.

Patterns
=
Four different pattern modes continuously move the target balance point around the platform. The modes can be changed by pressing a button, and the screen displays the current mode.


| <div align="center">![GIF 1](https://github.com/user-attachments/assets/e0388074-9499-45ad-b376-4a15687dd7b5)<br>**Ellipse Pattern**</div> | <div align="center">![GIF 2](https://github.com/user-attachments/assets/7451cad8-90ad-40f7-8ca3-b2c4b2532f88)<br>**Line Pattern**</div> |
|---|---|
| <div align="center">![GIF 3](https://github.com/user-attachments/assets/b3a61f1d-1b0f-4124-ab4a-5146a49c95c9)<br>**Figure 8 Pattern**</div> | <div align="center">![GIF 4](https://github.com/user-attachments/assets/e1071c8b-4cf8-47b1-85a4-86f633d5cabf)<br>**Triangle Pattern**</div> |











