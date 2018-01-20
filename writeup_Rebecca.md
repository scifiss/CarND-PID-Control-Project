**PID control Project**

The goals / steps of this project are the following:

* apply PID control so that the car can stay in the track
* tune the hyperparameter manually or using twiddle algorithm so that the turning of the car is smooth and fast

## [Rubric](https://review.udacity.com/#!/rubrics/824/view) Points

---
To help the car stay within the borders, a control on steering angle is used against "cross track error (CTE)" provided by the simulator, which is the distance from the middle of the lane in meters.
## 1. manually tune P.I.D.
### P: proportional controller
_**P**_ control is proportional to the current CTE. A high P gives a strong feedback of the error. When tuned manually, it is found that P > 0.5 will make the car very shaky between the borders. P = 0.25~0.5 gives a good response.

### I: integral controller
_**I**_ increases the control proportional to the accumulated error. It corrects systematical error, like drift. Since there is no drift in the simulator, the I value is very small to account for any accumulated errors.

### D: derivative controller
_**D**_ provides the control in proportion to the derivative of CTE. It aims to suppress the changing rate of error, and reduces the overshoot. A higher D value help the car drive more stable.

To easily tune the 3 parameters, they are fed into the main function so that I don't have to compile the file many times.
```
int main(int argc, char *argv[])
{
double kp=0.0,ki=0.0,kd=0.0;
if (argc>=4)
  {
        //std::cout<< atof(argv[1])<<std::endl;
        kp = atof(argv[1]);
        ki = atof(argv[2]);
        kd = atof(argv[3]);
  }
}
```
A range of combinations can lead to acceptable results.
The values I chose: P = 0.5 (0.2~0.5), I = 0.0001 (0.0001~0.001), D = 10 (5~15)
## 2. smooth the driving
To further smooth the behavior of the control, a previous control is used to be part of the current control. In this way, the changing of steering angle is not so sharp.
```
double steer= - Kp*p_error - Ki*i_error - Kd*d_error;
steer = factor * steer + (1-factor)*currSteer;
currSteer = steer;
```
The factor is tuned to be 0.8. 
## 3. adapt speed via throttle
Besides controlling on steering angle from CTE, throttle can also be controlled according to the speed. Intuitively, when CTE is high, the speed should be slowed with a negative throttle. When the speed is low, and CTE is small, throttle should be positive and increased to reach a higher speed.
A fixed throttle of 0.3 makes the car runs at 30 (I guess the unit is km/hr). I wish the ideal speed at 70. A higher target speed (like 80) makes the car runs too fast and can touch the boundary sometimes. A lower target speed (like 40) makes the car runs slower than 30. The reason that the ideal speed is never reached is probably due to the linear control. 
```
          double throttle = 0.3;
          double targetSpeed = 70;
          if (speed>=targetSpeed)
          {
              throttle = -0.05*(speed - targetSpeed);
          }
          else
          {
              throttle = - 0.0125*(speed-targetSpeed);
          }
```
## 4. twiddle
I would like to add twiddle into PID class, but haven't made it run successfully. By using twiddle, the speed and steering angle adaption will be much faster. I will submit another one if I can make it.

