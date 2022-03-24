# Implementation-of-PID-controller-using-Qt creator
This project is done tp simulate a second order system of the form: H(s)=b0/(s^2+a1s+a0) where the parameters of the system are unkown.

The implementation is done using threading methdology for the system and the controller.
The communication between the controller and the plant is only possible using event triggering.
Measurement noise is considered in the output of the system to give the better approximation of the real world.
The implementation is done within two phases:

The first phase is the system parameters identification using less sequare method.

The second phase is conroller design and implemntation of PID controller class.

Identification is done using less square error method. The controller design is done after the identification to reach a desired performance.
