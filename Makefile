#
# 'make depend' uses makedepend to automatically generate dependencies
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = g++

# define any compile-time flags
#CFLAGS =

# define any directories containing header files other than /usr/include
INCLUDES = 
#-I./src -I./headers -I./data -I./tools

# define library paths in addition to /usr/lib
LFLAGS= 


# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = 


# define the executable file
V0 = test_estimate
V1 = generating_data_file

#sourcepath
SRC = ./src/
DATA = ./data/




#Building executables
all:    $(V0).out $(V1).out
	@echo  Compiled all files

$(V0).out : $(SRC)$(V0).cpp
	$(CC) $(INCLUDES) $(LFLAGS) -o $(V0).out $(SRC)$(V0).cpp $(LIBS)

$(V1).out : $(SRC)$(V1).cpp
	$(CC) $(INCLUDES) $(LFLAGS) -o $(V1).out $(SRC)$(V1).cpp $(LIBS)


#clean command to remove .out files and default .dat files
clean: 
	$(RM) *.out $(DATA)input.dat $(DATA)output.dat




