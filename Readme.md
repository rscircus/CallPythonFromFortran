# How to call Python from within Fortran (and return values)

## Genesis Note

I had this problem recently, as I wanted to interface from a really old and large
piece of Fortran-Code to Python. Basically, I didn't find anything existing, so
I came up with this solution.

I hope it helps.


## Don't forget:

* To link the Python libraries
* Include Python.h when compiling the C++ part

when compiling.
