//
// Created by lidan on 2021/2/28.
//

#ifndef VR_MATRIX_H
#define VR_MATRIX_H

#include "EigenLidan.h"
#include "assert.h"

// jordan gauss elimation and LU decompose
template <class T>
class SolverMatrix
{
private:
    Lmatrix<T> data ;

    Int n;
    MatDoub lu;
    VecInt indx;
    Doub d;

public:

    SolverMatrix(Lmatrix<T>& a):n(a.mrows()), lu(a), aref(a), indx(n)
    {
        this->data = a ;
    }

    MatDoub_IO GetInverse()
    {
        assert(data.ncols()==data.mrows()) ;
        MatDoub_IO input(data) ;
        MatDoub_IO indentify(data.mrows(),data.ncols()) ;
        indentify.setIdentity() ;
        this->gaussj(input,indentify) ;
        return input ;
    }

    MatDoub_IO GetResult(Lmatrix<T>& b)
    {
        assert(data.ncols()==data.mrows()) ;
        MatDoub_IO input(data) ;
        MatDoub_IO t = b ;
        this->gaussj(input,t) ;
        return b ;
    }

    // We must change the matrix to L*U form for determinant
    Doub GetDet()
    {
        const Doub TINY=1.0e-40;
        Int i,imax,j,k;
        Doub big,temp;
        VecDoub vv(n);
        d=1.0;
        for (i=0;i<n;i++) {
            big=0.0;
            for (j=0;j<n;j++)
                if ((temp=abs(lu[i][j])) > big) big=temp;
            if (big == 0.0) throw("Singular matrix in LUdcmp");
            vv[i]=1.0/big;
        }
        for (k=0;k<n;k++) {
            big=0.0;
            imax=k;
            for (i=k;i<n;i++) {
                temp=vv[i]*abs(lu[i][k]);
                if (temp > big) {
                    big=temp;
                    imax=i;
                }
            }
            if (k != imax) {
                for (j=0;j<n;j++) {
                    temp=lu[imax][j];
                    lu[imax][j]=lu[k][j];
                    lu[k][j]=temp;
                }
                d = -d;
                vv[imax]=vv[k];
            }
            indx[k]=imax;
            if (lu[k][k] == 0.0) lu[k][k]=TINY;
            for (i=k+1;i<n;i++) {
                temp=lu[i][k] /= lu[k][k];
                for (j=k+1;j<n;j++)
                    lu[i][j] -= temp*lu[k][j];
            }
        }
        Doub dd = d;
        for (Int i=0;i<n;i++) dd *= lu[i][i];
        return dd;
    }

    // 如果某一个变量消去，那么不需要再维护这一列的value了，因为都是0-0 或者1-0 浪费计算资源
    // note: the matrix must be n*n
    // https://www.mathsisfun.com/algebra/matrix-inverse-row-operations-gauss-jordan.html
    // he just find some Redundant calculation. So he decides to delete them.
    /*
     * MatDoub_IO a [m*m]
     * MatDoub_IO b [m*n]
     *
     * a*x = b
     *
     * begin:
     * a is the input matrix
     * b is the m num n*1 matrix
     *
     * end:
     * a is the inverse matrix
     * b is the solve result
     */

    void gaussj(MatDoub_IO &a, MatDoub_IO &b)
    {
        Int i, irow, icol, j, k, l, ll, m_a = a.mrows(), n_b = b.ncols() ;
        Doub big, dum, pivinv ;
        VecInt indxc(m_a), indxr(m_a) ,ipiv(m_a) ;

        for(j =0 ; j < m_a; j++) { ipiv[j] = 0 ; }

        // just count all
        for(i = 0 ; i< m_a; i++) {
            big = 0.0;

            // select the biggest value of all the matrix( just including no pivot rows)
            for (j = 0; j < m_a; j++)
                if (ipiv[j] != 1) {

                    //note: just select biggest value of j row; we get the col order.
                    // so the col order must be the real row, and the biggest will be col,col
                    for (k = 0; k < m_a; k++) {
                        if (ipiv[k] == 0) {
                            if (abs(a[j][k]) >= big) {
                                big = abs(a[j][k]);
                                irow = j;
                                icol = k;
                            }
                        }
                    }
                }

            // flag this row will be pivot
            ++(ipiv[icol]);

            // change the row of a and b
            if (irow != icol) {
                for (l = 0; l < m_a; l++) Swap(a[irow][l], a[icol][l]);
                for (l = 0; l < n_b; l++) Swap(b[irow][l], b[icol][l]);
            }

            indxr[i] = irow;
            indxc[i] = icol;
            if (a[icol][icol] == 0.0) throw("gaussj: Singular Matrix");

            // icol row just using 1
            pivinv = 1.0 / a[icol][icol];
            a[icol][icol] = 1.0;
            for (l = 0; l < m_a; l++) a[icol][l] *= pivinv;
            for (l = 0; l < n_b; l++) b[icol][l] *= pivinv;

            std::cout<<"begin"<<a<<b<<std::endl ;

            for (ll = 0; ll < m_a; ll++)
                if (ll != icol) {
                    dum = a[ll][icol];
                    std::cout<<dum<<std::endl ;
                    a[ll][icol] = 0.0;
                    for (l = 0; l < m_a ; l++) a[ll][l] -= a[icol][l] * dum;
                    for (l = 0; l < n_b ; l++) b[ll][l] -= b[icol][l] * dum;
                }

            std::cout<<"end"<<a<<b<<std::endl ;
        }
        for (l = m_a - 1; l >= 0; l--) {
            if (indxr[l] != indxc[l])
                for (k = 0; k < m_a; k++)
                    Swap(a[k][indxr[l]], a[k][indxc[l]]);
        }
        std::cout<<a<<b<<std::endl ;

    }

    template<class T>
    inline static std::ostream& operator<<(std::ostream &os, const Lmatrix<T>& obj)
    {
        os<<"Matrix "<<obj.mrows()<<"x"<<obj.ncols()<<std::endl ;
        for(int i = 0 ; i < obj.mrows(); i++)
        {
            for(int j = 0;  j < obj.ncols(); j++)
            {
                os<<obj[i][j]<<" ";
            }
            os<<std::endl ;
        }
        return os ;
    }

}



#endif //VR_MATRIX_H
