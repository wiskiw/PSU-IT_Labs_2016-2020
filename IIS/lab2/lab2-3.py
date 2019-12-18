

import math
import numpy as np

pi = 3.14

def factorial(n):
    if n == 0:
        return 1
    else:
        return n * factorial(n-1)

min = -1.0;
max = 1.0;

def run(step):
    for x in np.arange(min, max, step):
        funYx(x)
        funSx(x)


def funYx(x):
    result = ( pi * math.sin(x)) / 4
    print("funYx: x=", x, " y(x)=", result)


def funSx(x):
    result = 0
    for n in range(1,6):
        tempValue = (pow(x, 2 * n + 1)) / factorial((2 * n + 1))
        result = result  + pow(-1, n) * tempValue
    result = pi/4 * result
    print("funSx: x=", x, " s(x)=", result)

step = float(input("Enter x step: "))
run(step)
