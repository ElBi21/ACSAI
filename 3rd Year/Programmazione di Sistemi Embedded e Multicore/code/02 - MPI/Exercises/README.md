# Exercises Summary

|File|Assignment|Status|
|---|---|---|
|`01-trapezoidal.c` & `01-trapezoidal-receive.c`| `N/A` | **Solved ✓** |
|`02-stima-pi.c`|Suppose we toss darts randomly at a square dartboard, whose bullseye is at the origin, and whose sides are 2 feet in length. Suppose also that there’s a circle inscribed in the square dartboard. The radius of the circle is 1 foot, and it’s area is $\pi$ square feet. If the points that are hit by the darts are uniformly distributed (and we always hit the square), then the number of darts that hit inside the circle should approximately satisfy the equation<br><br>$$\frac{\text{darts in the circle}}{\text{darts in the square}} = \frac{\pi}{4}$$<br><br>Remember that if origin $(0, \; 0)$, the circle must respect the condition $x^2 + y^2 = r^2$. The method of estimating $\pi$ with $n$ random trials is called “Monte Carlo” method, since it uses randomness (the dart tosses). Write an MPI program that uses a Monte Carlo method to estimate $\pi$.|**Solved ✓**|
