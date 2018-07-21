#ifndef JACOBIAN_FUNCTIONS_CPP
#define JACOBIAN_FUNCTIONS_CPP


#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>



namespace ublas = boost::numeric::ublas;
enum jacobian_func_type
{
        SYSTEM_A,
        INPUT_B,
        MEASUREMENT_H
};

ublas::matrix<float> jacobian_functions(jacobian_func_type type,float steering_angle,float current_heading,float prev_heading,float wheel_dist,int ticks_PR,float wheel_rad,float r,float current_time,float prev_time)
{
        ublas::matrix<float> mat33(3,3);
        ublas::matrix<float> mat32(3,2);
        ublas::matrix<float> mat13(1,3);
        float pi = 3.1416;
        float sin_SA= sin(steering_angle);
        float cos_SA= cos(steering_angle);
        float tan_SA= tan(steering_angle);
        float cos_CH= cos(current_heading);
        float sin_CH= sin(current_heading);
        float sin_PH= sin(prev_heading);
        float cos_PH= cos(prev_heading);
        float dist_per_tick = 2*pi*wheel_rad/ticks_PR;

        switch(type)
        {
        case SYSTEM_A:
                for (unsigned i = 0; i < 3; ++i) //why unsigned?
                        for (unsigned j = 0; j < 3; ++j)
                                mat33(i,j)=0;

                mat33(0,0)=1;
                mat33(1,1)=1;
                mat33(2,2)=1;
                if(steering_angle!=0)
                {
                        mat33(0,2)=r/tan_SA*(cos_CH-cos_PH);
                        mat33(1,2)=r/tan_SA*(sin_CH-sin_PH);
                }
                else
                {
                        mat33(0,2)=-1*wheel_dist*sin_PH;
                        mat33(1,2)=wheel_dist*cos_PH;
                }
                return mat33;
                break;

        case INPUT_B:
                if(steering_angle!=0)
                {
                        mat32(0,0)=sin_SA/tan_SA*dist_per_tick*cos_CH;
                        mat32(1,0)=sin_SA/tan_SA*dist_per_tick*sin_CH;
                        mat32(2,0)=sin_SA/r*dist_per_tick;
                        mat32(0,1)=cos_SA/tan_SA*wheel_dist*cos_CH;
                        mat32(1,1)=cos_SA/tan_SA*wheel_dist*sin_CH;
                        mat32(2,1)=cos_SA/r*wheel_dist;
                }
                else
                {
                        mat32(0,0)=dist_per_tick*cos_PH;
                        mat32(1,0)=dist_per_tick*sin_PH;
                        mat32(2,0)=0;
                        mat32(0,1)=0;
                        mat32(1,1)=0;
                        mat32(2,1)=wheel_dist/r*cos_SA;
                }
                return mat32;
                break;

        case MEASUREMENT_H:
                mat13(0,0)=0;
                mat13(0,1)=0;
                mat13(0,2)=1/(current_time-prev_time);

                return mat13;
                break;

        }
}

#endif
