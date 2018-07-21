#ifndef POSE_2D_H
#define POSE_2D_H

class pose_2D
{
public:
float x; //check for the best data type
float y;
float heading;

pose_2D(){}

pose_2D(float x0, float y0, float heading0)
{
        x = x0;
        y = y0;
        heading = heading0;
}
void update(float x0, float y0, float heading0)
{
        x = x0;
        y = y0;
        heading = heading0;
}
};

#endif
