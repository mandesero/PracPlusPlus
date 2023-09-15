add_library(Rational STATIC Rational.cpp Rational.h)

add_library(Complex STATIC Complex.cpp Complex.h)

add_library(Vector STATIC Vector.cpp Vector.h)

add_library(Matrix STATIC Matrix.cpp Matrix.h)

target_link_libraries(SparceMatrixKit Rational Complex Vector Matrix)