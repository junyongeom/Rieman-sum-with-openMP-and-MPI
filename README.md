# Rieman-sum-with-openMP-and-MPI

It's a simple example dealing with the Rieman sum with openMP and MPI libraries.

Be cautious that my_pi variable has dependence because every threads shares/read/write it.

I used ```#pragama omp critical``` to deal with the problem.
