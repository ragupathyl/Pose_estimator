#ifndef SYSTEM_PARAM_H
#define SYSTEM_PARAM_H


class system_param
{
private:
float distance;

public:
const float pi;
const int ticks_PR;
const float wheel_rad;
const float r;
public:
system_param() : pi(3.1416),ticks_PR(512),wheel_rad(0.2),r(1){
}
float wheel_distance(int n_ticks)
{

        distance = n_ticks*2*pi*wheel_rad/ticks_PR;
        return distance;
}
};

#endif
