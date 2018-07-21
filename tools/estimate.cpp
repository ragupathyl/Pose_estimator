
#ifndef POSE_ESTIMATOR_CPP
#define POSE_ESTIMATOR_CPP

//Header files for boost and standard C++ libraries
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <iostream>
#include <math.h>

//Custom functions required by estimate()
#include "initializing_covariances.cpp"
#include "jacobian_functions.cpp"
#include "matrix_inversion.cpp"

//Classes used by estimate()
#include "../headers/pose_2D.h"
#include "../headers/system_param.h"
#include "../headers/state_memory.h"

pose_2D estimate(float current_time,float steering_angle,int encoder_ticks,float angular_velocity)
{
        using namespace boost::numeric::ublas;

//Creating objects of required classes
        system_param inst;
        state_memory instance;
        matrix<float> x_predicted (3, 1);

//Calculate temporary variables
        float wheel_dist = inst.wheel_distance(encoder_ticks-instance.prev_encoder_tick);
        float current_heading = instance.prev_pose.heading+sin(steering_angle)*wheel_dist/inst.r;

//Check for redundancy in function call
        if(current_time==instance.prev_time) return instance.prev_pose;

//TIME UPDATE STEP:
//Predicting initial pose (Eq 4.1,4.2,4.3)
        if(steering_angle!=0)
        {
                x_predicted(0,0)=instance.prev_pose.x + inst.r/tan(steering_angle)*(sin(current_heading)-sin(instance.prev_pose.heading));
                x_predicted(1,0)=instance.prev_pose.y + inst.r/tan(steering_angle)*(-cos(current_heading)+cos(instance.prev_pose.heading));
                x_predicted(2,0)=instance.prev_pose.heading+sin(steering_angle)*wheel_dist/inst.r;
        }
        else
        {
                x_predicted(0,0)=instance.prev_pose.x + wheel_dist*cos(instance.prev_pose.heading);
                x_predicted(1,0)=instance.prev_pose.y + wheel_dist*sin(instance.prev_pose.heading);
                x_predicted(2,0)=instance.prev_pose.heading;
        }

//Initializing covariances during first function call
        if(instance.state==0)
        {
                instance.prev_state_covariance=initializing_covariances(STATE_COVARIANCE);
                instance.prev_system_covariance=initializing_covariances(SYSTEM_COVARIANCE);

                instance.prev_input_covariance=initializing_covariances(INPUT_COVARIANCE);
                instance.prev_measurement_covariance=initializing_covariances(MEASUREMENT_COVARIANCE);
        }


//Creating objects for Eq 4.4
        matrix<float> projected_state_covariance (3, 3);
        matrix<float> system_A (3, 3);
        matrix<float> input_B (3, 2);

//Updating jacobian functions A_k and B_k
        system_A = jacobian_functions(SYSTEM_A,steering_angle,current_heading,instance.prev_pose.heading,wheel_dist,inst.ticks_PR,inst.wheel_rad,inst.r,current_time,instance.prev_time);
        input_B = jacobian_functions(INPUT_B,steering_angle,current_heading,instance.prev_pose.heading,wheel_dist,inst.ticks_PR,inst.wheel_rad,inst.r,current_time,instance.prev_time);

//Projecting the state covariance matrix
        projected_state_covariance=prod(system_A,matrix<float>(prod(instance.prev_state_covariance,trans(system_A))))+prod(input_B,matrix<float>(prod(instance.prev_input_covariance,trans(input_B))))+instance.prev_system_covariance;

//MEASUREMENT UPDATE STEP:
//Updating jacobian function H_k
        matrix<float> measurement_H (1, 3);
        measurement_H = jacobian_functions(MEASUREMENT_H,steering_angle,current_heading,instance.prev_pose.heading,wheel_dist,inst.ticks_PR,inst.wheel_rad,inst.r,current_time,instance.prev_time);

//Calculating kalman gain vector (Eq 4.11)
        matrix<float> kalman_gain (3, 1);
        matrix<float> kalman_temp1 (3, 1);
        matrix<float> kalman_temp2 (1, 1);

        kalman_temp1 = prod(projected_state_covariance,trans(measurement_H));
        kalman_temp2 = matrix_inversion(matrix<float>(prod(measurement_H,matrix<float>(prod(instance.prev_state_covariance,trans(measurement_H))))+instance.prev_measurement_covariance));
        kalman_gain = prod(kalman_temp1,kalman_temp2);

//Updating the pose using measurement z (Eq 4.14)
        matrix<float> measurement_z(1,1);
        measurement_z(0,0)= angular_velocity;

        matrix<float> x_updated(3,1);
        x_updated = x_predicted + prod(kalman_gain,matrix<float>(measurement_z-instance.measurement_function(x_predicted,current_time)));

//Updating the state covariance matrix (Eq 4.15)
        matrix<float> covariance_temp(3,3);
        matrix<float> updated_state_covariance(3,3);

        covariance_temp = identity_matrix<float> (3,3) - prod(kalman_gain,measurement_H);
        updated_state_covariance = prod(covariance_temp,mat<float>(prod(instance.prev_state_covariance,trans(covariance_temp))))+prod(kalman_gain,mat<float>(prod(instance.prev_measurement_covariance,trans(kalman_gain))));

//Updating static variables for next function call

        instance.state++;
        instance.prev_pose.update(x_updated(0,0),x_updated(1,0),x_updated(2,0));
        instance.prev_state_covariance = updated_state_covariance;
        instance.prev_time = current_time;
        instance.prev_encoder_tick = encoder_ticks;

//Returning estimated pose
        return instance.prev_pose;
}

#endif
