/******************************************************************************
we generate "iter" random numbers, each of which will be the upper limit of
the integration of a function (see below)
    f(x) = x^2*cos(x)*exp(x)
    f(x) = sin(x)*exp(x)/(x + 1.)
list of program functions:
    func   is the function to be integrated
    integ  is the integration routine (Simpson 3/8 rule)
Using iter=1000000000, this takes about 10 seconds on a single core.
It is turning out this is not being straightforward to optimize. Not
sure whether I should put the openmp directives inside integ or in the
main loop. The code gets stuck.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

// double func(double x){
// //    return x*x*cos(x)*exp(x);
//     return sin(x)*exp(x)/(x + 1.);
// }
//
// double integ(double upper){
//     int i, n;
//     double lower, step, sum, result;
//
//     n = 10000; // may change this
//     lower = 0.;
//     step  = (upper - lower)/n;
//
//     sum = sin(lower)*exp(lower)/(lower + 1.); + sin(upper)*exp(upper)/(upper + 1.);
//     for (i = 1; i < n; i++){
//         if (i % 3 == 0){
//             sum += 2.*sin(lower + i*step)*exp(lower + i*step)/(lower + i*step + 1.);
//         }
//         else {
//             sum += 3.*sin(lower + i*step)*exp(lower + i*step)/(lower + i*step + 1.);
//         }
//     }
//     return
// }

int main(int argc, char *argv[]){


    int i, iter;
    double x, limit;


    // read command-line argument
    if ( argc != 2 ) {
        printf( "Usage: %s n \n", argv[0] );
        exit(0);
    }
    sscanf(argv[1], "%d", &iter);

    srand(time(NULL));

    // computational loop

    double startTime = omp_get_wtime();
    #pragma omp parallel for private(i,limit,x)
    for (i = 0; i < iter; i++){
        limit =1000 % 200;
        int i, n;
        double lower, step, sum, result;

        n = 10000; // may change this
        lower = 0.;
        step  = (limit - lower)/n;

        sum = sin(lower)*exp(lower)/(lower + 1.) + sin(limit)*exp(limit)/(limit + 1.);
        for (i = 1; i < n; i++){
            if (i % 3 == 0){
                sum += 2.*sin(lower + i*step)*exp(lower + i*step)/(lower + i*step + 1.);
            }
            else {
                sum += 3.*sin(lower + i*step)*exp(lower + i*step)/(lower + i*step + 1.);
            }
        }
        x=(3.*step/8.)*sum;
    }

    printf("%f\n",omp_get_wtime()-startTime );



    return(0);
}
