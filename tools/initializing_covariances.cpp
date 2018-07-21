#ifndef INITIALIZING_COVARIANCES_CPP
#define INITIALIZING_COVARIANCES_CPP


#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace ublas = boost::numeric::ublas;

enum covariance_type
{
        STATE_COVARIANCE,
        INPUT_COVARIANCE,
        SYSTEM_COVARIANCE,
        MEASUREMENT_COVARIANCE
};

ublas::matrix<float> initializing_covariances (covariance_type type)
{
        ublas::matrix<float> mat33(3,3);
        ublas::matrix<float> mat22(2,2);
        ublas::matrix<float> mat11(1,1);

        switch(type)
        {
        case STATE_COVARIANCE:
                for (unsigned i = 0; i < 3; ++i) //why unsigned?
                        for (unsigned j = 0; j < 3; ++j)
                                mat33(i,j)=0;
                return mat33;
                break;

        case INPUT_COVARIANCE:
                mat22(1,0)=0;
                mat22(0,1)=0;
                mat22(0,0) = 25;
                mat22(1,1) = 3.04e-4;
                return mat22;
                break;

        case SYSTEM_COVARIANCE:
                for (unsigned i = 0; i < 3; ++i) //why unsigned?
                        for (unsigned j = 0; j < 3; ++j)
                                mat33(i,j)=0;

                mat33(0,0)=0.01;
                mat33(1,1)=0.01;
                mat33(2,2)=3.04e-4;
                return mat33;
                break;

        case MEASUREMENT_COVARIANCE:
                ublas::matrix<float> mat(1,1);
                mat11(0,0)=0.01;
                return mat11;
                break;

        }


}

#endif
