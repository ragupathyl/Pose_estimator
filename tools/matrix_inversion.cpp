#ifndef MATRIX_INVERSION_CPP
#define MATRIX_INVERSION_CPP

#include <./boost/numeric/ublas/vector.hpp>
#include <./boost/numeric/ublas/vector_proxy.hpp>
#include <./boost/numeric/ublas/matrix.hpp>
#include <./boost/numeric/ublas/triangular.hpp>
#include <./boost/numeric/ublas/lu.hpp>
#include <./boost/numeric/ublas/io.hpp>


namespace ublas = boost::numeric::ublas;


ublas::matrix<float> matrix_inversion (ublas::matrix<float> mat)
{
        ublas::permutation_matrix<float> per_mat(mat.size1());

        ublas::matrix<float> inv(mat.size1(),mat.size2());

        int fact = lu_factorize(mat,per_mat);

        inv = ublas::identity_matrix<float>(mat.size1());
        lu_substitute(mat, per_mat, inv);

        return inv;
}

#endif
