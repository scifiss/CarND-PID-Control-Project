#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID()
{
    p_error=0.0;
    i_error=0.0;
    d_error=0.0;
    currSteer = 0.0;
}

PID::~PID() {}

void PID::Init(double sKp, double sKi, double sKd)
{


    Kp = sKp;
    Ki = sKi;
    Kd = sKd;
}

void PID::UpdateError(double cte)
{
    i_error += cte;
    d_error = cte - p_error;
    p_error = cte ;

}

double PID::TotalError()
{
    return i_error;
}

double PID::Steering(double factor)
{

    double steer= - Kp*p_error - Ki*i_error - Kd*d_error;
    steer = factor * steer + (1-factor)*currSteer;
    if (steer>MAX_STEERING)
        steer = MAX_STEERING;
    if (steer<MIN_STEERING)
        steer = MIN_STEERING;
    currSteer = steer;
    return steer;
}

