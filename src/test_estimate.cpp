#include <./boost/numeric/ublas/matrix.hpp>
#include <./boost/numeric/ublas/io.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "../tools/estimate.cpp"

int main(int argc, char* argv[]) {

        using namespace std;
        ifstream input_file;
        ofstream output_file;
        string data_location="../data/";
//use default data file names or get input from command line
        if (argc == 1)
        {
                input_file.open("./data/input.dat", ios::in);
                output_file.open("./data/output.dat", ios::out);
        }
        else
        {
                string input = argv[1];
                string output = argv[2];
                input = data_location+input;
                output = data_location+output;
                input_file.open(input.c_str(), ios::in);
                output_file.open(output.c_str(), ios::out);
        }


        float current_time, steering_angle, angular_velocity;
        int encoder_ticks;
        string line;

//Extracting data from input file
        while(getline(input_file,line))
        {
                istringstream iss(line);
                iss >> current_time;
                iss >> steering_angle;
                iss >> encoder_ticks;
                iss >> angular_velocity;

//Estimate pose with estimate() call
                pose_2D estimated_pose = estimate(current_time,steering_angle,encoder_ticks,angular_velocity);

//write current time and estimated pose to output file
                output_file<< current_time<<"\t"<<estimated_pose.x <<"\t"<<estimated_pose.y<<"\t"<<estimated_pose.heading<<"\n";


        }
        cout<<"\n Successfully written to file \n";

//close both file streams
        if (output_file.is_open()) { output_file.close(); }
        if (input_file.is_open()) { input_file.close(); }

        return 0;

}
