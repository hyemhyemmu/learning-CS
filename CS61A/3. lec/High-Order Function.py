# L4 HOF
def make_adder(n):
    def adder(k):
        return n + k

    return adder


# simpler:
def make_adder_2(n):
    return lambda k: n + k


# L7 Functional Abstraction
def search(f):  # find the smallest number that satisfies f
    x = 0
    """while True:
        if f(x):  # get Boolean value returned from functions
            return x
        x += 1
    """
    # better version:
    while not f(x):
        x += 1
    return x


def is_three(x):
    return x == 3


def square(x):
    return x ** x


def inverse(f):
    """Return g(y) such that g(f(x))==x"""  # what it returned is a function
    return lambda y: search(lambda x: f(x) == y)
    # f(x):x is a variable and returns y;
    # lambda y: y is a variable and returns x who satisfies f(x)=y
