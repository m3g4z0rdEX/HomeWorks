#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double integralTrapezoidCnt(double a, double b,
    size_t count, double(*getFunctionValue)(double))
{
    double len = (b - a)/(double)(count);
    double res = (getFunctionValue(a) + getFunctionValue(b)) * 0.5;

    for(size_t i = 1; i < count; ++i)
        res = res + (getFunctionValue(a + i * len));

    return len * res;
}

double integralTrapezoidEps(double a, double b,
    double eps, double(*getFunctionValue)(double))
{
    double res = integralTrapezoidCnt(a, b, 1, getFunctionValue);

    for (size_t cnt = 2;; ++cnt)
    {
        double tmp = integralTrapezoidCnt(a, b, cnt, getFunctionValue);
 
         if (fabs(tmp - res) < eps)
            return res;
        else
            res = tmp;
    }

    return res;
}

double sinFunc(double x)
{
    return sin(x);
}

double cosFunc(double x)
{
    return cos(x);
}

double sinCosFunc(double x)
{
    return sin(x) * cos(x);
}

int main()
{
    double res_1 = integralTrapezoidEps(0., 1., 0.000001, sinFunc);
    double res_2 = integralTrapezoidEps(0., 1., 0.000001, cosFunc);
    double res_3 = integralTrapezoidEps(0., 1., 0.000001, sinCosFunc);
    printf("Integral sin(x) on [0; 1] reange = %lf\n", res_1);
    printf("Integral cos(x) on [0; 1] reange = %lf\n", res_2);
    printf("Integral sin(x) * cos(x) on [0; 1] reange = %lf\n", res_3);

    return 0;
}