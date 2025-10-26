#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <stdio.h>

#define N 4
#define MAXLINE 100

double sin_taylor(double x, int terms){
    double v = x, num = x*x*x, den = 6.0; int s = -1;
    for(int j=1;j<=terms;j++){
        v += (double)s * (num/den);
        num *= x*x;
        den *= (2.0*j+2.0)*(2.0*j+3.0);
        s *= -1;
    }
    return v;
}

void sinx_tayler(int num_elements, int terms, double* x, double* result){
    int fd[2*N];
    pid_t pid;

    for(int i=0;i<num_elements;i++){
        pipe(fd+2*i);
        pid = fork();
        if(pid==0){
            close(fd[2*i+0]);
            double y = sin_taylor(x[i], terms);
            write(fd[2*i+1], &y, sizeof(double));
            close(fd[2*i+1]);
            _exit(0);
        }else{
            close(fd[2*i+1]);
        }
    }
    for(int i=0;i<num_elements;i++){
        read(fd[2*i+0], &result[i], sizeof(double));
        close(fd[2*i+0]);
    }
    for(int i=0;i<num_elements;i++) wait(NULL);
}

int main(){
    double x[N];
    x[0]=0.0;
    x[1]=M_PI/6.0;
    x[2]=M_PI/3.0;
    x[3]=0.134;

    double r[N];
    int terms=3;

    sinx_tayler(N, terms, x, r);

    for(int i=0;i<N;i++){
        printf("sin(%.3f) by Taylor series = %f\n", x[i], r[i]);
        printf("sin(%.3f) = %f\n", x[i], sin(x[i]));
    }
    return 0;
}

