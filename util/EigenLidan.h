//
// Created by 李源 on 2020-12-14.
//

#ifndef MYEIGEN_EIGENLIDAN_H
#define MYEIGEN_EIGENLIDAN_H

#include <fstream>
#include <vector>
#include <cmath>
#include <Lmath.h>
#include <complex>
#include <iostream>
#include <iomanip> // io manipulator
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <type_traits>
#include <assert.h>


using namespace std ;
# define M_PI_L           3.14159265358979323846  /* pi */


template<class T>
inline T Square(const T &a) { return a*a ; }

// note: double and float, pick float
template<class T>
inline const T& Max(const T& a, const T& b)
{ return b > a ? (b) : (a); }

inline float Max(const double &a, const float &b)
{return b > a ? (b) : float(a);}

inline float Max(const float &a, const double &b)
{return b > a ? float(b) : (a);}

// note: double and float, pick float
template<class T>
inline const T& Min(const T& a, const T& b)
{ return b > a ? (a) : (b); }

inline float Min(const double& a, const float& b)
{ return b > a ? float(a) : (b) ; }

inline float Min(const float& a , const double& b)
{ return b > a ? (a) : float(b) ; }

// note: double and float, pick float
// note: to make a has the same flag with b

template<class T>
inline T Sign(const T& a, const T& b)
{ return b >= 0 ? (a >= 0? (a) : (-a)) :(a >= 0? (-a) : (a)) ;}

inline float Sign(const double& a, const float& b)
{ return float(b >= 0 ? (a >= 0? (a) : (-a)) :(a >= 0? (-a) : (a))) ;}

inline float Sign(const float& a, const double& b)
{ return b >= 0 ? (a >= 0? (a) : (-a)) :(a >= 0? (-a) : (a)) ; }


template<class T>
inline void Swap(T& a, T& b)
{ T t = a ; a = b ; b = t ; }


// note: error Handler

#ifndef _USER_ERROR_CLASS_
#define throw(message) \
{ printf(" ERROR: %s/n   in file %s at line %d.\n", message, __FILE__, __LINE__); throw(1); }
#else

struct Lerror{
    char *message;
    char *file;
    int line;
    Lerror(char *m, char *f, int l) : message(m), file(f), line(l) {}
};

#define throw(message) throw(Lerror(message, __FILE__, __LINE__)) ;
void Lcatch(Lerror err)
{
    printf("ERROR: %s\n    in file %s at line %d\n", err.message, err.file, err.line) ;
    exit(1) ;
}

#endif

#ifdef _USESTDVECTOR_
#define NRvector vector
#else
template<class T>
class Lvector{
protected:
    int size_vector ;
    T* data ;

public:
    Lvector() ;
    explicit Lvector(int size) ;
    Lvector(int size, const T& a) ;
    Lvector(int size, const T* a) ;
    Lvector(const Lvector& rhs) ;
    Lvector & operator=(const Lvector& rhs) ;

    typedef T value_type ;
    inline T& operator[](const int i) ; // why is it inline?
    inline const T& operator[](const int i) const ;
    T multiply(const Lvector<T>& other) ;
    T* getData() const { return this->data ;}
    T length_squared() ;

    inline int size() const ;
    void resize(int newsize) ;
    void assign(int newsize, const T& a) ;
    void normlize() ;

    std::string toString() const;
    ~Lvector() ;
};

template<class T>
void Lvector<T>::normlize()
{
    T res = sqrt(double(length_squared())) ;
    for(int i = 0 ; i < size_vector;i++) data[i] /= res ;
}

template<class T>
T Lvector<T>::multiply(const Lvector<T>& other)
{
    T result = 0 ;
    assert(this->size_vector == other.size_vector) ;
    for(int i = 0 ; i < this->size_vector;i++)
    {
        result += this->data[i] * other[i] ;
    }
    return result ;
}

template<class T>
std::string Lvector<T>::toString() const
{
    std::string result = " " ;
    for(int i = 0; i < size_vector;i++)
    {
        result += std::to_string(data[i]) ;
        result += " " ;
    }
    return result ;
}

template <class T>
inline int Lvector<T>::size() const { return size_vector; }

template <class T>
Lvector<T>::Lvector() : size_vector(0), data(NULL) {}

// note : if Lvector size less than zero. You will get a nullptr data.
template <class T>
Lvector<T>::Lvector(int size) : size_vector(size), data( size > 0? new T[size]: nullptr) {}


template <class T>
Lvector<T>::Lvector(int size,const T& a) : size_vector(size), data( size > 0? new T[size]: nullptr)
{
    for(int i = 0  ; i < size ; i++)  data[i] = a  ;
}

// note : if put in the stack a pointer, the pointer must be a array pointer.
template <class T>
Lvector<T>::Lvector(int size, const T* a) : size_vector(size), data( size > 0? new T[size]: nullptr)
{
    for(int i = 0 ; i < size ; i++) data[i] = *a++ ;
}

// note : the : init list is also ordered.
template <class T>
Lvector<T>::Lvector(const Lvector& rhs) : size_vector(rhs.size_vector), data( size_vector > 0? new T[size_vector]: nullptr)
{
    for(int i = 0 ; i< size_vector ;i++)  data[i] = rhs.data[i] ;
}

//note: resize vector and copy data
template <class T>
Lvector<T>& Lvector<T>::operator=(const Lvector<T> &rhs) {
    if(this != &rhs)
    {
        if(size_vector!=rhs.size_vector)
        {
            if(data!=nullptr)
            {
                delete[] (data) ;
            }

            size_vector = rhs.size_vector ;
            data = size_vector>0 ? new T[size_vector] : NULL ;
        }

        for(int i = 0;  i < size_vector ;i++)
        {
            data[i] = rhs[i] ;
        }
    }

    return *this ;
}


// if you use []， you must has two version. one for [], another for const [].
template <class T>
inline T& Lvector<T>::operator[](const int i)
{
#ifdef _CHECKBOUNDS_
    if(i<0 || i >= size_vector) throw("Lvector subscript out of bounds.")
#endif
    return data[i] ;
}
template <class T>
T Lvector<T>::length_squared(){
    T result = 0 ;
    for(int i = 0 ; i < size_vector ; i++)  result += data[i]*data[i] ;
    return result ;
}



template <class T>
inline const T & Lvector<T>::operator[](const int i) const	//subscripting
{
#ifdef _CHECKBOUNDS_
    if (i<0 || i>=nn) {
	throw("Lvector subscript out of bounds");
}
#endif
    return data[i];
}

// note: resize would remove all data
template <class T>
void Lvector<T>::resize(int newsize)
{
    if (newsize != size_vector) {
        if (data != NULL) delete[] (data);
        size_vector  = newsize;
        data = size_vector > 0 ? new T[size_vector] : NULL;
    }
}

template <class T>
void Lvector<T>::assign(int newsize, const T& a)
{
    if(newsize != size_vector)
    {
        if(data != nullptr) delete[] data ;
        size_vector = newsize ;
        data = size_vector > 0? new T[size_vector] : nullptr ;
    }
    for( int i = 0; i< size_vector ;i++)  data[i] = a ;
}


template <class T>
Lvector<T>::~Lvector()
{
    if (data != nullptr) delete[] (data);
}

#endif

template<typename T>
struct is_for_Lvec{
    enum {
        value = std::is_fundamental<T>::value
    };
};




template <class T>
class Lvec3:public Lvector<T>{
public:
    static_assert(is_for_Lvec<T>::value, "type parameter of this class must derive from basic");
    Lvec3() :Lvector<T>(3){}
    Lvec3(T e0, T e1, T e2) ;
    double x() const { return this->data[0]; }
    double y() const { return this->data[1]; }
    double z() const { return this->data[2]; }
    Lvec3 operator-() const ;
    Lvec3& operator*=(const T t) ;
    Lvec3& operator+=(const Lvec3<T>& t) ;
    Lvec3& operator/=(const T t) ;
    T length() const ;
    T length_square() const ;
    Lvec3<T> normalized() const;
    static Lvec3 random()
    {
        return Lvec3<T>(T( rand()/RAND_MAX), T( rand()/RAND_MAX), T( rand()/RAND_MAX));
    }

    static Lvec3 random(T begin, T end)
    {
        return Lvec3<T>(T(T(rand()/RAND_MAX)*(end-begin)+begin),T(T(rand()/RAND_MAX)*(end-begin)+begin), T(T(rand()/RAND_MAX)*(end-begin)+begin));
    }


};

template <class T>
Lvec3<T> Lvec3<T>::normalized() const
{
    T t1 = this->data[0]/length() ;
    T t2 = this->data[1]/length() ;
    T t3 = this->data[2]/length() ;
    Lvec3<T> res(t1,t2,t3) ;
    return res ;
}

template<class T>
Lvec3<T>::Lvec3(T e0, T e1, T e2)
:Lvector<T>(3)
{
    this->data[0] = e0 ;
    this->data[1] = e1 ;
    this->data[2] = e2 ;
}


template<class T>
Lvec3<T> Lvec3<T>::operator-() const
{
    return Lvec3<T>(-this->data[0],-this->data[1],-this->data[2]) ;
}

template<class T>
Lvec3<T>& Lvec3<T>::operator*=(const T t)
{
    this->data[0] *= t ;
    this->data[1] *= t ;
    this->data[2] *= t ;

    return *this ;
}

template<class T>
Lvec3<T>& Lvec3<T>::operator+=(const Lvec3& t)
{
    this->data[0] += t[0] ;
    this->data[1] += t[1] ;
    this->data[2] += t[2] ;

    return *this ;
}

template<class T>
Lvec3<T>& Lvec3<T>::operator/=(const T t)
{
    this->data[0] /= t ;
    this->data[1] /= t ;
    this->data[2] /= t ;

    return *this ;
}

template<class T>
T Lvec3<T>::length() const
{
    return sqrt(length_square());
}

template<class T>
T Lvec3<T>::length_square() const
{
    return this->data[0]*this->data[0] + this->data[1]*this->data[1] + this->data[2]*this->data[2];
}

using Point3 = Lvec3<double> ;
using Color = Lvec3<double> ;
using Vec3 = Lvec3<double> ;

inline std::ostream& operator<<(std::ostream &out, const Lvec3<double> &v) {
    return out << v.toString();
}


inline Lvec3<double> operator+(const Lvec3<double> &u, const Lvec3<double> &v) {
    return Lvec3<double>(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline Lvec3<double> operator-(const Lvec3<double> &u, const Lvec3<double> &v) {
    return Lvec3<double>(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline Lvec3<double> operator*(const Lvec3<double> &u, const Lvec3<double> &v) {
    return Lvec3<double>(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline Lvec3<double> operator*(double t, const Lvec3<double> &v) {
    return Lvec3<double>(t*v[0], t*v[1], t*v[2]);
}

inline Lvec3<double> operator*(const Lvec3<double> &v, double t) {
    return t * v;
}

inline Lvec3<double> operator/(Lvec3<double> v, double t) {
    return (1/t) * v;
}

inline double dot(const Lvec3<double> &u, const Lvec3<double> &v) {
    return u[0] * v[0]
           + u[1] * v[1]
           + u[2] * v[2];
}

inline Lvec3<double> cross(const Lvec3<double> &u, const Lvec3<double> &v) {
    return Lvec3<double>(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

inline Lvec3<double> unit_vector(Lvec3<double> v) {
    return v / v.length();
}

inline Lvec3<double> random_unit_vector() {
    auto a = double(rand()/RAND_MAX)*2*M_PI_L+0;
    auto z = double(rand()/RAND_MAX)*2+-1;
    auto r = sqrt(1 - z*z);
    return Lvec3<double>(r*cos(a), r*sin(a), z);
}

inline Lvec3<double> random_in_unit_disk() {
    while (true) {
        auto p = Lvec3<double>(double(rand())/RAND_MAX*2-1, double(rand())/RAND_MAX*2-1, 0.0);
        if (p.length_squared() >= 1) {
//            std::cout<<p<<std::endl;
            continue;
        }
        return p;
    }
}


inline Lvec3<double> random_in_unit_sphere() {
    while (true) {
        auto p = Lvec3<double>::random(-1.0,1.0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline Lvec3<double> random_in_hemisphere(const Lvec3<double>& normal) {
    Lvec3<double> in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

inline Lvec3<double> reflect(const Lvec3<double>& v, const Lvec3<double>& n) {
    return v - 2*dot(v,n)*n;
}

inline Lvec3<double> refract(const Lvec3<double>& uv, const Lvec3<double>& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    Lvec3<double> r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    Lvec3<double> r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

template <class T>
class Lvec4:public Lvector<T> {
public:
    static_assert(is_for_Lvec<T>::value, "type parameter of this class must derive from basic");
    Lvec4() :Lvector<T>(4){}
    Lvec4(T e0, T e1, T e2, T e3) ;
    Lvec4(const Lvec3<T>& data) ;

    double r() const { return this->data[0]; }
    double g() const { return this->data[1]; }
    double b() const { return this->data[2]; }
    double a() const { return this->data[3]; }

    Lvec4 operator-() const ;
    Lvec4& operator*=(const T t) ;
    Lvec4& operator+=(const Lvec4& t) ;
    Lvec4& operator/=(const T t) ;
    T length() const ;
    T length_square() const ;
    Lvec3<T> toLvec3() ;

    inline static Lvec4 random()
    {
        return Lvec4<T>(T( rand()/RAND_MAX), T( rand()/RAND_MAX), T( rand()/RAND_MAX), T( rand()/RAND_MAX));
    }

} ;

template <class T>
Lvec4<T>::Lvec4(T e0, T e1, T e2, T e3)
:Lvector<T>(4)
{
    this->data[0] = e0 ;
    this->data[1] = e1 ;
    this->data[2] = e2 ;
    this->data[3] = e3 ;
}

template <class T>
Lvec4<T>::Lvec4(const Lvec3<T>& data)
:Lvector<T>(4)
{
    this->data[0] = data[0] ;
    this->data[1] = data[1] ;
    this->data[2] = data[2] ;
    this->data[3] = 1.0 ;
}

template <class T>
Lvec4<T> Lvec4<T>::operator-() const
{
    return Lvec4<T>(-this->data[0],-this->data[1],-this->data[2],-this->data[3]) ;
}

template <class T>
Lvec4<T>& Lvec4<T>::operator*=(const T t)
{
    this->data[0] *= t ;
    this->data[1] *= t ;
    this->data[2] *= t ;
    this->data[3] *= t ;

    return *this ;
}
template <class T>
Lvec4<T>& Lvec4<T>::operator+=(const Lvec4& t)
{
    this->data[0] += t[0] ;
    this->data[1] += t[1] ;
    this->data[2] += t[2] ;
    this->data[3] += t[3] ;

    return *this ;
}
template <class T>
Lvec4<T>& Lvec4<T>::operator/=(const T t)
{
    this->data[0] /= t ;
    this->data[1] /= t ;
    this->data[2] /= t ;
    this->data[3] /= t ;

    return *this ;
}
template <class T>
T Lvec4<T>::length() const
{
    return sqrt(length_square());
}

template <class T>
T Lvec4<T>::length_square() const
{
    T result = 0 ;
    for(int i = 0 ; i < size_vector ; i++)  result += this->data[i]*this->data[i] ;
    return result ;
}

template <class T>
Lvec3<T> Lvec4<T>::toLvec3()
{
    Lvec3<T> result(this->data[0],this->data[1],this->data[2]) ;
    return result ;
}

using Vec4 = Lvec4<double> ;




template <class T>
class Lmatrix {
private:
    int size_matrix_m ;
    int size_matrix_n ;
    T **data ;

public:
    static_assert(is_for_Lvec<T>::value, "type parameter of this class must derive from basic");
    Lmatrix() ;
    Lmatrix(int m, int n) ;
    Lmatrix(int m, int n, const T& a) ;
    Lmatrix(int m, int n, const T* a) ;
    Lmatrix(const Lmatrix& rhs) ;
    Lmatrix & operator=(const Lmatrix &rhs);
    typedef T value_type;
    inline T* operator[](const int i) ;
    inline const T* operator[](const int i) const;
    inline int mrows() const ;
    inline int ncols() const ;
    void resize(int newn, int newm) ;
    void assign(int newn, int newm, const T& a) ;

    T* getData() const { return data[0] ; }

    Lvector<T> row(int index) ;
    Lvector<T> col(int index) ;
    void setRow(int index, const Lvector<T>& res) ;
    void setCol(int index, const Lvector<T>& res) ;
    void fill(float value) ;
    bool isAffine() const ;
//    void fromAxes(const Lvector<T>& xAxis, const Lvector<T>& yAxis) ;
    inline void transpose() { *this = Lmatrix<T>::transpose(*this); }

    inline bool isZero() const {
        for(int i = 0; i < size_matrix_m; i++)
            for(int j = 0 ; j < size_matrix_n ; j++)
                if(data[i][j] != 0.0)
                    return false ;
        return true ;
    } ;
    inline void setZero() const{
        for(int i = 0 ; i < size_matrix_m; i++)
            for(int j = 0 ; j < size_matrix_n; j++)
                data[i][j] = 0.0 ;
    }

    inline bool isIdentity() const {
        for(int i = 0; i < size_matrix_m; i++)
            for(int j = 0 ; j < size_matrix_n ; j++)
                if((i!=j && data[i][j] != 0.0) || (i==j&& data[i][j]!=1.0))
                    return false ;
        return true ;
    } ;

    inline void setIdentity() const {
        for(int i = 0; i < size_matrix_m; i++)
            for(int j = 0 ; j < size_matrix_n ; j++)
                if(i == j) data[i][j] = 1.0 ;
                else data[i][j] = 0.0 ;
    } ;




    static void multiply(const Lmatrix<T>& left, const Lmatrix<T>& right,  Lmatrix<T>& result) ;
    static void multiply(const Lvector<T>& left, const Lmatrix<T>& right, Lvector<T>& result) ;
    static void multiply(const Lmatrix<T>& left, const Lvector<T>& right, Lvector<T>& result) ;
    static void multiply(const Lmatrix<T>& left, const T& right, Lmatrix<T>& result) ;
    static void multiply(const T& left, const Lmatrix<T>& right,  Lmatrix<T>& result) ;
    static Lmatrix<T> multiply(const Lmatrix<T>& left, const Lmatrix<T>& right ) ;
    static Lvector<T> multiply(const Lvector<T>& left, const Lmatrix<T>& right ) ;
    static Lvector<T> multiply(const Lmatrix<T>& left, const Lvector<T>& right ) ;
    static Lmatrix<T> multiply(const Lmatrix<T>& left, const T& right ) ;
    static Lmatrix<T> multiply(const T& left, const Lmatrix<T>& right ) ;


    static void substract(const Lmatrix<T>& left, const Lmatrix<T>& right, Lmatrix<T>& result) ;
    static Lmatrix<T> substract(const Lmatrix<T>& left, const Lmatrix<T>& right) ;

    static void add(const Lmatrix<T>& left, const Lmatrix<T>& right, Lmatrix<T>& result) ;
    static Lmatrix<T> add(const Lmatrix<T>& left, const Lmatrix<T>& right) ;


    static void transpose(const Lmatrix<T>& matrix, Lmatrix<T>& result) ;
    static Lmatrix<T> transpose(const Lmatrix<T>& other) ;


    friend bool operator==(const Lmatrix<T> &m1, const Lmatrix<T> &m2);
    friend bool operator!=(const Lmatrix<T> &m1, const Lmatrix<T> &m2);
    inline friend Lmatrix<T> operator+(const Lmatrix<T> &m1, const Lmatrix<T> &m2) { return Lmatrix<T>::add(m1, m2);}
    inline friend Lmatrix<T> operator-(const Lmatrix<T> &m1, const Lmatrix<T> &m2) { return Lmatrix<T>::subtract(m1, m2); }
    inline friend Lmatrix<T> operator*(float factor, const Lmatrix<T> &mat2) { return Lmatrix<T>::multiply(factor, mat2); }
    inline friend Lmatrix<T> operator*(const Lmatrix<T> &mat2, float factor) { return Lmatrix<T>::multiply(mat2, factor); }
    inline friend Lmatrix<T> operator*(const Lmatrix<T> &m1, const Lmatrix<T> &m2) { return Lmatrix<T>::multiply(m1, m2); }
    friend Lvector<T> operator*(const Lmatrix<T> &mat2, const Lvector<T> &vec2);
    friend Lvector<T> operator*(const Lvector<T> &vec2, const Lmatrix<T> &mat2);

//    friend std::ostream& operator<<( std::ostream&, const Lmatrix<T>& ) ;
    ~Lmatrix() ;

};


//template<class TA>
//std::ostream& operator<<(std::ostream &os, const Lmatrix<TA>& obj)
//{
//    os<<"Matrix "<<obj.size_matrix_m<<"x"<<obj.size_matrix_n<<std::endl ;
//    for(int i = 0 ; i < obj.size_matrix_m; i++)
//    {
//        for(int j = 0;  j < obj.size_matrix_n; j++)
//        {
//            os<<obj[i][j]<<" ";
//        }
//        os<<std::endl ;
//    }
//    return os ;
//}

template <class T>
Lmatrix<T>::Lmatrix() : size_matrix_m(0), size_matrix_n(0), data(NULL) {}

template<class T>
Lmatrix<T>::Lmatrix(int m, int n ): size_matrix_m(m), size_matrix_n(n) , data(m>0? new T*[m] : nullptr)
{
    int i,nel=m*n;
    if (data) data[0] = nel>0 ? new T[nel] : NULL;
    for (i=1;i<m;i++) data[i] = data[i-1] + n;
}

template<class T>
Lmatrix<T>::Lmatrix(int m, int n, const T &a) : size_matrix_m(m), size_matrix_n(n), data(size_matrix_m>0 ? new T*[size_matrix_m] : NULL)
{
    int i,j,nel=size_matrix_m*size_matrix_n ;
    if (data) data[0] = nel>0 ? new T[nel] : NULL;
    for (i=1; i< size_matrix_m ; i++) data[i] = data[i-1] + size_matrix_n;
    for (i=0; i< size_matrix_m ; i++) for (j=0; j<size_matrix_n; j++) data[i][j] = a;
}

template<class T>
Lmatrix<T>::Lmatrix(int m, int n, const T* a) : size_matrix_m(m), size_matrix_n(n), data(size_matrix_m>0 ? new T*[size_matrix_m] : NULL)
{
    int i,j,nel = size_matrix_m*size_matrix_n ;
    if(data) data[0] = nel>0? new T[nel] : NULL ;
    for(int i = 0; i < size_matrix_m; i++) data[i] = data[i-1] + size_matrix_n ;
    for(int i = 0; i < size_matrix_m ; i++) for(int j = 0 ; j< size_matrix_n ; j++) data[i][j] = *a++ ;
}



template<class T>
Lmatrix<T>::Lmatrix(const Lmatrix &rhs) : size_matrix_m(rhs.size_matrix_m), size_matrix_n(rhs.size_matrix_n), data(size_matrix_m>0 ? new T*[size_matrix_m] : NULL)
{

    int i,j,nel= size_matrix_m*size_matrix_n ;
    if (data) data[0] = nel>0 ? new T[nel] : NULL;
    for (i=1; i< size_matrix_m; i++) data[i] = data[i-1] + size_matrix_n;
    for (i=0; i< size_matrix_m; i++) for (j=0; j<size_matrix_n; j++) data[i][j] = rhs[i][j];
}


// other matrix named rhs may has the different size with this matrix
template <class T>
Lmatrix<T> & Lmatrix<T>::operator=(const Lmatrix &rhs)
{
    if(this != rhs)
    {
        int i,j,nel ;
        if(size_matrix_m != rhs.size_matrix_m || size_matrix_n != rhs.size_matrix_n)
        {
            if(data!=nullptr)
            {
                // why we need to delete data first?
                delete[] data[0];
                delete[] data ;
            }

            size_matrix_m = rhs.size_matrix_m ;
            size_matrix_n = rhs.size_matrix_n ;
            data = size_matrix_m > 0 ? new T*[size_matrix_m] : nullptr ;
            nel = size_matrix_m*size_matrix_n ;
            if(data) data[0] = nel >0 ? new T[nel] : nullptr ;
            for(int i = 1;  i < size_matrix_m; i++) data[i] = data[i-1] + size_matrix_n;
        }
        for(int i = 0; i <size_matrix_m; i++) for(int j = 0 ; j< size_matrix_n; j++) data[i][j] = rhs[i][j] ;

    }
    return *this ;
}

template <class T>
inline T* Lmatrix<T>::operator[](const int i)
{
#ifdef _CHECKBOUNDS_
    if (i<0 || i>=size_matrix_m) {
	throw("NRmatrix subscript out of bounds");
}
#endif
    return data[i];

}

template <class T>
inline const T* Lmatrix<T>::operator[](const int i) const
{
#ifdef _CHECKBOUNDS_
    if (i<0 || i>=size_matrix_m) {
	throw("NRmatrix subscript out of bounds");
}
#endif
    return data[i];
}

template <class T>
inline int Lmatrix<T>::mrows() const
{
    return size_matrix_m ;
}


template <class T>
inline int Lmatrix<T>::ncols() const
{
    return size_matrix_n ;
}

template <class T>
void Lmatrix<T>::resize(int newm, int newn)
{
    int i,nel;
    if (newm != size_matrix_m || newn != size_matrix_n) {
        if (data != NULL) {
            delete[] (data[0]);
            delete[] (data);
        }
        size_matrix_m = newm ;
        size_matrix_n = newn ;
        data = size_matrix_m>0 ? new T*[size_matrix_m] : NULL;
        nel = size_matrix_m*size_matrix_n;
        if (data) data[0] = nel>0 ? new T[nel] : NULL;
        for (i=1; i< size_matrix_m; i++) data[i] = data[i-1] + size_matrix_n;
    }
}


template <class T>
void Lmatrix<T>::assign(int newm, int newn, const T& a)
{
    int i,j,nel ;
    if ( newm!=size_matrix_m || newn != size_matrix_n)
    {
        if (data != NULL) {
            delete[] (data[0]);
            delete[] (data);
        }

        size_matrix_m = newm ;
        size_matrix_n - newn ;
        data = size_matrix_m>0 ? new T*[size_matrix_m] : NULL;
        nel = size_matrix_m*size_matrix_n;
        if (data) data[0] = nel>0 ? new T[nel] : NULL;
        for (i=1; i< size_matrix_m; i++) data[i] = data[i-1] + size_matrix_n;
        for (i=0; i< size_matrix_m; i++) for (j=0; j<size_matrix_n; j++) data[i][j] = a;
    }
}

template <class T>
Lmatrix<T>::~Lmatrix()
{
    if (data != NULL) {
        delete[] (data[0]);
        delete[] (data);
    }
}

template <class T>
Lvector<T> Lmatrix<T>::row(int index)
{
    Lvector<T> result(this->ncols()) ;
    for(int i = 0 ; i < this->ncols();i++)
    {
        result[i] = data[index][i] ;
    }
    return result ;
}

template <class T>
Lvector<T> Lmatrix<T>::col(int index)
{
    Lvector<T> result(this->mrows()) ;
    for(int i = 0 ; i < this->mrows(); i++)
    {
        result[i] = data[i][index] ;
    }

    return result ;
}

template <class T>
void Lmatrix<T>::setRow(int index, const Lvector<T>& res)
{
    assert(this->ncols() == res.size_vector) ;
    for(int i = 0 ; i < this->ncols();i++)
    {
        data[index][i] = res[i] ;
    }
}

template <class T>
void Lmatrix<T>::setCol(int index, const Lvector<T>& res)
{
    assert(this->mrows() == res.size()) ;
    for(int i = 0 ; i < this->mrows() ;i++)
    {
        data[i][index] = res[i] ;
    }
}

template <class T>
void Lmatrix<T>::fill(float value)
{
    int r = mrows() ;
    int c = ncols() ;
    for(int i = 0 ; i < mrows() ; i++)
    {
        for(int j = 0 ; j < ncols() ;j++ )
        {
            data[i][j] = value ;
        }
    }
}

template <class T>
bool Lmatrix<T>::isAffine() const
{
    for( int i = 0 ; i < this->size_matrix_m ;i++)
    {
        T result = 0 ;
        for(int j = 0 ; j < this->size_matrix_n ; j++)
        {
            result += data[i][j] ;
        }
        if((result-1.0)>DBL_EPSILON) return false ;
    }
    return true ;
}

/*
template <class T>
void Lmatrix<T>::fromAxes(const Lvector<T>& xAxis, const Lvector<T>& yAxis)
{
        //pass
}
*/


template <class T>
void Lmatrix<T>::multiply(const Lmatrix<T>& left, const Lmatrix<T>& right,  Lmatrix<T>& result)
{
    assert(left.ncols()==right.mrows() && result.mrows()==left.mrows() && result.ncols()==right.ncols()) ;
    for(int i = 0 ; i < result.mrows(); i++)
    {
        for(int j = 0 ; j < result.ncols() ; j++)
        {
            result[i][j] = left.row(i).multiply( right.col(j)) ;
        }
    }
}

template <class T>
void Lmatrix<T>::multiply(const Lvector<T>& left, const Lmatrix<T>& right, Lvector<T>& result)
{
    assert(left.size_vector == right.size_matrix_m && result.size_vector == right.size_matrix_n) ;
    for(int i = 0 ; i < right.ncols() ; i++)
    {
        result[i] = left.multiply(right.col(i)) ;
    }
}

template <class T>
void Lmatrix<T>::multiply(const Lmatrix<T>& left, const Lvector<T>& right, Lvector<T>& result) \
{
    assert(right.size_vector == left.size_matrix_n && result.size_vector == left.size_matrix_m) ;
    for(int i = 0 ; i < left.mrows() ;i++)
    {
        result[i] = left.row(i).multiply(right) ;
    }
}

template <class T>
void Lmatrix<T>::multiply(const Lmatrix<T>& left, const T& right, Lmatrix<T>& result)
{
    for(int i = 0 ; i < left.size_matrix_m;i++)
    {
        for(int j = 0 ; j < left.size_matrix_n ; j++)
        {
            result[i][j] *= right ;
        }
    }
}

template <class T>
void Lmatrix<T>::multiply(const T& left, const Lmatrix<T>& right,  Lmatrix<T>& result)
{
    for(int i = 0 ; i < right.size_matrix_m;i++)
    {
        for(int j = 0 ; j < right.size_matrix_n ; j++)
        {
            result[i][j] *= left ;
        }
    }
}

template <class T>
Lmatrix<T> Lmatrix<T>::multiply(const Lmatrix<T>& left, const Lmatrix<T>& right )
{
    assert(left.size_matrix_n == right.size_matrix_m) ;
    Lmatrix<T> result(left.size_matrix_m, right.size_matrix_n) ;
    multiply(left,right,result) ;
    return result ;
}

template <class T>
Lvector<T> Lmatrix<T>::multiply(const Lvector<T>& left, const Lmatrix<T>& right )
{
    assert(left.size_vector == right.size_matrix_m) ;
    Lvector<T> result(right.size_matrix_n) ;
    multiply(left,right,result) ;
    return result ;
}

template <class T>
Lvector<T> Lmatrix<T>::multiply(const Lmatrix<T>& left, const Lvector<T>& right )
{
    assert(left.size_matrix_n == right.size_vector) ;
    Lvector<T> result(left.size_matrix_m) ;
    multiply(left,right,result) ;
    return result ;
}

template <class T>
Lmatrix<T> Lmatrix<T>::multiply(const Lmatrix<T>& left, const T& right )
{
    Lmatrix<T>  result(left.size_matrix_m,left.size_matrix_n) ;
    multiply(left,right,result) ;
    return result ;
}

template <class T>
Lmatrix<T> Lmatrix<T>::multiply(const T& left, const Lmatrix<T>& right )
{
    Lmatrix<T> result(right.size_matrix_m,right.size_matrix_n) ;
    multiply(left, right,result) ;
    return result ;
}

template <class T>
 void Lmatrix<T>::substract(const Lmatrix<T>& left, const Lmatrix<T>& right, Lmatrix<T>& result)
{
    assert(left.mrows()==right.mrows() && left.ncols() == right.ncols()&&left.mrows()==result.mrows()&& left.ncols()==result.ncols()) ;
    for(int i = 0 ; i < left.size_matrix_m ;i++)
    {
        for (int j = 0; j < left.size_matrix_n ; ++j) {
            result[i][j] = left[i][j] - right[i][j] ;
        }
    }
}

template <class T>
 Lmatrix<T> Lmatrix<T>::substract(const Lmatrix<T>& left, const Lmatrix<T>& right)
{
    Lmatrix<T> res(left.mrows(),left.ncols()) ;
    substract(left,right,result) ;
    return result ;
}

template <class T>
void Lmatrix<T>::add(const Lmatrix<T>& left, const Lmatrix<T>& right, Lmatrix<T>& result)
{
    assert(left.mrows()==right.mrows() && left.ncols() == right.ncols()&&left.mrows()==result.mrows()&& left.ncols()==result.ncols()) ;
    for(int i = 0 ; i < left.size_matrix_m ;i++)
    {
        for (int j = 0; j < left.size_matrix_n ; ++j) {
            result[i][j] = left[i][j] + right[i][j] ;
        }
    }
}

template <class T>
 Lmatrix<T> Lmatrix<T>::add(const Lmatrix<T>& left, const Lmatrix<T>& right)
{
    Lmatrix<T> res(left.mrows(),left.ncols()) ;
    add(left,right,result) ;
    return result ;
}

template <class T>
 void Lmatrix<T>::transpose(const Lmatrix<T>& matrix, Lmatrix<T>& result)
{
    assert(matrix.size_matrix_m == result.size_matrix_n && matrix.size_matrix_n == result.size_matrix_m) ;

    for(int i = 0 ; i < matrix.size_matrix_n ; i++)
    {
        for(int j = 0 ; j < matrix.size_matrix_m ; j++)
        {
            result[i][j] = matrix.data[j][i] ;
        }
    }
}

template <class T>
 Lmatrix<T> Lmatrix<T>::transpose(const Lmatrix<T>& matrix)
{
    Lmatrix<T> res(matrix.size_matrix_n,matrix.size_matrix_m) ;
    transpose(matrix,res);
    return res ;
}

template <class T>
 bool operator==(const Lmatrix<T> &m1, const Lmatrix<T> &m2)
 {
    if(!(m1.size_matrix_m == m2.size_matrix_m && m1.size_matrix_n == m2.size_matrix_n) ) return false;
    for(int i = 0 ; i < m1.size_matrix_m ;i++)
    {
        for(int j = 0 ; j < m1.size_matrix_n ; j++)
        {
            if( m1[i][j] != m2[i][j]) return false ;
        }
    }
    return true ;
 }

template <class T>
 bool operator!=(const Lmatrix<T> &m1, const Lmatrix<T> &m2)
 {
    if(m1==m2) return true ;
    return false ;
 }

template <class T>
 Lvector<T> operator*(const Lmatrix<T> &mat2, const Lvector<T> &vec2)
{
    return Lmatrix<T>::multiply(mat2,vec2) ;
}

template <class T>
 Lvector<T> operator*(const Lvector<T> &vec2, const Lmatrix<T> &mat2)
{
    return Lmatrix<T>::multiply(vec2,mat2) ;
}


template <class T>
class LMat3d {
private:
    int nn;
    int mm;
    int kk;
    T ***v;
public:
    LMat3d();
    LMat3d(int n, int m, int k);
    inline T** operator[](const int i);	//subscripting: pointer to row i
    inline const T* const * operator[](const int i) const;
    inline int dim1() const;
    inline int dim2() const;
    inline int dim3() const;
    ~LMat3d();

};

template <class T>
LMat3d<T>::LMat3d(): nn(0), mm(0), kk(0), v(NULL) {}

template <class T>
LMat3d<T>::LMat3d(int n, int m, int k) : nn(n), mm(m), kk(k), v(new T**[n])
{
    int i,j;
    v[0] = new T*[n*m];
    v[0][0] = new T[n*m*k];
    for(j=1; j<m; j++) v[0][j] = v[0][j-1] + k;
    for(i=1; i<n; i++) {
        v[i] = v[i-1] + m;
        v[i][0] = v[i-1][0] + m*k;
        for(j=1; j<m; j++) v[i][j] = v[i][j-1] + k;
    }
}


template <class T>
inline T** LMat3d<T>::operator[](const int i) //subscripting: pointer to row i
{
    return v[i];
}

template <class T>
inline const T* const * LMat3d<T>::operator[](const int i) const
{
    return v[i];
}

template <class T>
inline int LMat3d<T>::dim1() const
{
    return nn;
}

template <class T>
inline int LMat3d<T>::dim2() const
{
    return mm;
}

template <class T>
inline int LMat3d<T>::dim3() const
{
    return kk;
}

template <class T>
LMat3d<T>::~LMat3d()
{
    if (v != NULL) {
        delete[] (v[0][0]);
        delete[] (v[0]);
        delete[] (v);
    }
}




// define datatype
typedef int Int; // 32 bit integer
typedef unsigned int Uint;


// MSVC provide int 64  other provide long long
#ifdef _MSC_VER
typedef __int64 Llong; // 64 bit integer
typedef unsigned __int64 Ullong;
#else
// other compiler provide all
typedef long long int Llong; // 64 bit integer
typedef unsigned long long int Ullong;
#endif

typedef char Char; // 8 bit integer
typedef unsigned char Uchar;

typedef double Doub; // default floating type
typedef long double Ldoub;

typedef complex<double> Complex; // default complex type

typedef bool Bool;


// note: three method for getting NaN
//note: uncomment one of the following 3 methods of defining a global NaN
// you can test by verifying that (NaN != NaN) is true
static const Doub NaN = numeric_limits<Doub>::quiet_NaN();

//Uint proto_nan[2]={0xffffffff, 0x7fffffff};
//double NaN = *( double* )proto_nan;

//Doub NaN = sqrt(-1.);


// const for I
typedef const Lvector<Int> VecInt_I ;
typedef Lvector<Int> VecInt, VecInt_O, VecInt_IO;

typedef const Lvector<Uint> VecUint_I;
typedef Lvector<Uint> VecUint, VecUint_O, VecUint_IO;

typedef const Lvector<Llong> VecLlong_I;
typedef Lvector<Llong> VecLlong, VecLlong_O, VecLlong_IO;

typedef const Lvector<Ullong> VecUllong_I;
typedef Lvector<Ullong> VecUllong, VecUllong_O, VecUllong_IO;

typedef const Lvector<Char> VecChar_I;
typedef Lvector<Char> VecChar, VecChar_O, VecChar_IO;

typedef const Lvector<Char*> VecCharp_I;
typedef Lvector<Char*> VecCharp, VecCharp_O, VecCharp_IO;

typedef const Lvector<Uchar> VecUchar_I;
typedef Lvector<Uchar> VecUchar, VecUchar_O, VecUchar_IO;

typedef const Lvector<Doub> VecDoub_I;
typedef Lvector<Doub> VecDoub, VecDoub_O, VecDoub_IO;

typedef const Lvector<Doub*> VecDoubp_I;
typedef Lvector<Doub*> VecDoubp, VecDoubp_O, VecDoubp_IO;

typedef const Lvector<Complex> VecComplex_I;
typedef Lvector<Complex> VecComplex, VecComplex_O, VecComplex_IO;

typedef const Lvector<Bool> VecBool_I;
typedef Lvector<Bool> VecBool, VecBool_O, VecBool_IO;

// matrix types

//
typedef const Lmatrix<Int> MatInt_I;
typedef Lmatrix<Int> MatInt, MatInt_O, MatInt_IO;

typedef const Lmatrix<Uint> MatUint_I;
typedef Lmatrix<Uint> MatUint, MatUint_O, MatUint_IO;

typedef const Lmatrix<Llong> MatLlong_I;
typedef Lmatrix<Llong> MatLlong, MatLlong_O, MatLlong_IO;

typedef const Lmatrix<Ullong> MatUllong_I;
typedef Lmatrix<Ullong> MatUllong, MatUllong_O, MatUllong_IO;

typedef const Lmatrix<Char> MatChar_I;
typedef Lmatrix<Char> MatChar, MatChar_O, MatChar_IO;

typedef const Lmatrix<Uchar> MatUchar_I;
typedef Lmatrix<Uchar> MatUchar, MatUchar_O, MatUchar_IO;

typedef const Lmatrix<Doub> MatDoub_I;
typedef Lmatrix<Doub> MatDoub, MatDoub_O, MatDoub_IO;


typedef const Lmatrix<Bool> MatBool_I;
typedef Lmatrix<Bool> MatBool, MatBool_O, MatBool_IO;

// 3D matrix types

typedef const LMat3d<Doub> Mat3DDoub_I;
typedef LMat3d<Doub> Mat3DDoub, Mat3DDoub_O, Mat3DDoub_IO;

#ifdef _TURNONFPES_
#ifdef _MSC_VER
struct turn_on_floating_exceptions {
	turn_on_floating_exceptions() {
		int cw = _controlfp( 0, 0 );
		cw &=~(EM_INVALID | EM_OVERFLOW | EM_ZERODIVIDE );
		_controlfp( cw, MCW_EM );
	}
};
turn_on_floating_exceptions yes_turn_on_floating_exceptions;
#endif /* _MSC_VER */
#endif /* _TURNONFPES */



#endif //MYEIGEN_EIGENLIDAN_H
