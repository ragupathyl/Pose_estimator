#ifndef STATE_MEMORY_H
#define STATE_MEMORY_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/functional.hpp>

#define mat boost::numeric::ublas::matrix
class state_memory
{
public:
static pose_2D prev_pose;
static int state;
static float prev_time;
static int prev_encoder_tick;
static mat<float> prev_state_covariance;
static mat<float> prev_input_covariance;
static mat<float> prev_system_covariance;
static mat<float> prev_measurement_covariance;

private:
mat<float> z;

public:
state_memory() : z(prev_measurement_covariance.size1(),1){
}
mat<float> measurement_function(mat<float> x_predicted, float current_time)
{
        z(0,0)= (x_predicted(2,0)-prev_pose.heading)/(current_time-prev_time);
        return z;
}
};
mat<float> state_memory::prev_state_covariance(3,3);
mat<float> state_memory::prev_input_covariance(2,2);
mat<float> state_memory::prev_system_covariance(3,3);
mat<float> state_memory::prev_measurement_covariance(1,1);
int state_memory::state=0;
int state_memory::prev_encoder_tick=0;
float state_memory::prev_time=0;
pose_2D state_memory::prev_pose(0,0,0);

#endif
