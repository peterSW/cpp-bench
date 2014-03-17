#include <gsl/gsl_fit.h>

#include <gmock/gmock.h>

TEST(LinearRegressionWithGSL, one_two_three)
{
    double x[] = {1, 2, 3};
    double y[] = {1, 2, 3};
    size_t stride(1);
    size_t len(3);
    
    // Outputs
    double c0;
    double c1; 
    double cov00;
    double cov01;
    double cov11; 
    double sumsq;
    
    gsl_fit_linear(x, stride, y, stride, len, &c0, &c1, &cov00, &cov01, &cov11, &sumsq);
    
    EXPECT_THAT(sumsq, ::testing::DoubleEq(0.0));
}

