add_library(Rational STATIC Rational.cpp Rational.h)

add_library(Complex STATIC Complex.cpp Complex.h)

target_link_libraries(SparceMatrixKit Rational Complex)