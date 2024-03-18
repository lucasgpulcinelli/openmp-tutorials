# Openmp tutorials

This project implements the official openmp tutorial excercises (and some other extra stuff beyond it) by Tim Mattson at Intel, avaliable [here](https://www.youtube.com/playlist?list=PLLX-Q6B8xqZ8n8bwjGdzBJ25X2utwnoEG). 

I plan on keep adding other openmp, mpi and cuda programs as I study about the subject of parallel computing.

## How to compile and run the code 
Run `make PROJECT=<project>`, where <project> is the project file name in the src/ directory. After that, run it with `make PROJECT=<project> run`, or `./build/<project>`.

As of now, the projects are:
* integral, that calculates the integral of 4/(1 + x^2), which should be equal to pi;
* mandelbrot, that calculates the area of the mandelbrot set, which should be around 1.510659;
* sort_randomarr, that generates a random array of 100 million integers in a multithreaded way with a linear congruential generator, then sorts it using a parallel version of quicksort.
