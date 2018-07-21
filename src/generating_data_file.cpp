#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>


class pose_2D
{
public:
float x;
float y;
float heading;
};

//use default data file names or get input from command line
int main(int argc, char* argv[])
{
        using namespace std;
        string data_location="./data/";
        ofstream output_file;
        if (argc == 1)
        {
                output_file.open("./data/input.dat", ios::out);
        }
        else
        {
                string output;
                output = argv[1];
                output = data_location + output;
                output_file.open(output.c_str(), ios::out);
        }


        float current_time, steering_angle, angular_velocity;
        int encoder_ticks;
        int total_ticks=0;
        float r=1;
        float wheel_dist;
        float pi = 3.1416;
        float wheel_rad = 0.2;
        int ticks_PR = 512;
        float current_heading;
        float x,y,heading;
        float x0,y0,heading0;
        srand (time(NULL));
        pose_2D prev_pose;
        prev_pose.x = 0;
        prev_pose.y = 0;
        prev_pose.heading = 0;
        int flag;

        for(int i=1; i<=1000; i++)
        {
//Randomize vehicle inputs encoder_ticks and steering_angle
                encoder_ticks = 25+rand()%76 + 1;
                steering_angle = -pi/2 + pi/180*((rand()%181+1)-1); //

                current_time=(float)i/10;
                wheel_dist = 2*pi*wheel_rad*encoder_ticks/ticks_PR;
                current_heading=prev_pose.heading+sin(steering_angle)*wheel_dist/r;

//Generating vehicle motion
                if(steering_angle!=0)
                {
                        x=prev_pose.x + r/tan(steering_angle)*(sin(current_heading)-sin(prev_pose.heading));
                        y=prev_pose.y + r/tan(steering_angle)*(-cos(current_heading)+cos(prev_pose.heading));
                        heading=prev_pose.heading+sin(steering_angle)*wheel_dist/r;
                }
                else
                {
                        x=prev_pose.x + wheel_dist*cos(prev_pose.heading);
                        y=prev_pose.y + wheel_dist*sin(prev_pose.heading);
                        heading=prev_pose.heading;
                }

                angular_velocity = (heading-prev_pose.heading)/0.1;

//Distort all inputs and state values to simulate a real system
                steering_angle =float( steering_angle*(1+((float)(rand()%11+1)-6)/100)); //+-5%
                if (steering_angle<-pi/2) steering_angle=-pi/2;
                if (steering_angle>pi/2) steering_angle=pi/2;

                encoder_ticks = ceil(encoder_ticks*(1+((float)(rand()%11+1)-6)/100)); //+-5%

                angular_velocity = angular_velocity*(1+((float)(rand()%11+1)-6)/100); //+-5%

                x0 = x*(1+((float)(rand()%7+1)-4)/100); //+-3%

                y0 = y*(1+((float)(rand()%7+1)-4)/100); //+-3%

                heading0 = heading*(1+((float)(rand()%7+1)-4)/100); //+-3%

                output_file.precision(4);
                total_ticks+=encoder_ticks;

//use flag to skip a few states randomly
                flag = rand()%10+1;
                if(flag>0) {
                        output_file<< current_time <<"\t"<< steering_angle <<"\t"<< total_ticks <<"\t";
                        output_file<< angular_velocity <<"\t"<< x0 <<"\t"<< y0 <<"\t" << heading0 << "\n";
                }



                prev_pose.x = x;
                prev_pose.y = y;
                prev_pose.heading = heading;

        }
        cout<<"\n Successfully written to file \n";
        if (output_file.is_open()) { output_file.close(); }

        return 0;
}
