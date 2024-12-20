# func1
def delay(arg):
    """
    2 parameters input, but ignore the 2nd and only output the 1st
    >>>print(delay(print)()(4))
    delayed
    4
    """
    print('delayed')

    def g():
        return arg

    return g


# func2 (tricky!)
from operator import add, mul


def square(x):
    return mul(x, x)


# classic example! can be used to practise drawing environment diagram
def pirate(arggg):
    """
    >>>add(pirate(3)(square)(4), 1)
    17
    >>>pirate(pirate(pirate))(5)(7)
    error
    """
    print('matey')

    def plunder(arggg):
        return arggg

    return plunder


# horse-mask example
def horse(mask):
    horse = mask

    def mask(horse):
        return horse

    return horse(mask)


mask = lambda horse: horse(2)

horse(mask)


# trace decorator
def trace1(f):  # basically it is just trace(f(n))=f(n), not changing the function but with more annotation
    def traced(n):
        print('Calling', f, 'on argument', n)
        return f

    return traced


@trace1
def square(n):
    return x * x
