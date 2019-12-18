e = pow(10,-6 )
pi = 3.14

def run(x):
    r = 1
    i = 1
    sum = 0

    while (abs(r) > e):
        sign = pow(-1, i + 1)
        r = sign * ((pow(x, 2 * i-1)-1) / (2 * i + 1))
        sum = sum + r
        i = i + 1
        print("sum: ", sum, "r: ", r)

x = float(input("Enter x: "))
run(x)
