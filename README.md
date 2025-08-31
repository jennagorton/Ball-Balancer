<h1 align="center">Ball Balancing Robot</h1>
<p align="center">Jenna Gorton, August 2025</p>


<p align="center">
  <img src="https://github.com/user-attachments/assets/fe2f6cdb-b272-48fe-b524-41fdfa31bff9"
       alt="workingTest" width="420">
</p>
<p align="center">Figure 1: Stabilizing at center</p>

 
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


