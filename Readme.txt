///////////////////////////////////////
/* Pose estimator API- Quick guide  */
//////////////////////////////////////

Created by Lakshmi Naarayanan Ragupathy: As part of a coding skill review for Brain Corp.

gitlab link: https://gitlab.com/lakshmiragupathy/Pose_estimator


The file layout is organized as follows:

<current_directory>/boost    -  Contains the necessary boost/numeric/ublas directory with all its .hpp files
                   
<current_directory>/data     -  Where all the input and output data files are stored

<current_directory>/headers  -  Contains the Class definition files for classes pose_2D, system_param and state_memory
                   
<current_directory>/images   -  Image files and plots used in the PDF are saved here

<current_directory>/src      -  Contains the source files test_estimate.cpp and generating_data_file.cpp

<current_directory>/tools    -  Contains the API code estimate.cpp along with its supporting function files 
                                 (matrix_inversion.cpp, initializing_covariances.cpp and jacobian_functions.cpp)

-------------------------------------------------------------------------
|The Required estimate() API file is saved in <current_directory>/tools |
-------------------------------------------------------------------------


Testing:
--------
This project is fully self contained with boost files included.(Requires make and g++ to compile) 

1)To start with, run $make in the <current_directory> 

2)If compilation is successful, it creates two executable files in the <current_directory>
     generating_data_files.out and test_estimate.out

3)Execute generating_data_file.out as 

    >  $ ./generating_data_file.out to create a data file "./data/input.dat"
    >  $ ./generating_data_file.out <file_name> to create data file with custom name

4)Execute test_estimate.out as 
    
    >  $ ./test_estimate.out to process data from "./data/input.dat" and save the estimated pose in "./data/output.dat"
    >  $ ./test_estimate.out <file_name> <file_name> to process and deliver to custom files

5) Optional : To obtain the plots for comparison, use gnuplot

Run gnuplot from <current_folder>/data

True path vs estimated path:
    
    > set title "True path vs estimated path"
    > set ylabel "Y position(m)"
    > set xlabel "X position(m)"
    > plot "input.dat" using 5:6 title "True path",\
    > "output.dat" using 2:3 title "Estimated path"

True X and estimated X vs time

    > set title "True X and estimated X vs time"
    > set ylabel "X position(m)"
    > set xlabel "time(s)"
    > plot "input.dat" using 1:5 title "True X",\
    > "output.dat" using 1:2 title "Estimated X"

True Y and estimated Y vs time

    > set title "True Y and estimated Y vs time"
    > set ylabel "Y position(m)"
    > set xlabel "time(s)"
    > plot "input.dat" using 1:6 title "True Y",\
    > "output.dat" using 1:3 title "Estimated Y"

True heading and estimated heading vs time

    > set title "True heading and estimated heading vs time"
    > set ylabel "Heading(rad)"
    > set xlabel "time(s)"
    > plot "input.dat" using 1:7 title "True heading",\
    > "output.dat" using 1:4 title "Estimated heading"






