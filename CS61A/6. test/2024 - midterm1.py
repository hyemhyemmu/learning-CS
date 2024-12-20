# Final Digit
def final_digit(n):
    """
    Implement final_digit, which takes a non-negative integer n. As long as n has more than one digit, replace n
with the sum of the digits of n. This process repeats until n becomes a single-digit number, which is returned.
    """
    while n >= 10:
        s = 0  # act as sum
        while n > 0:  # iterate in all digit of n
            n, s = n // 10, s + n % 10  # throw the last digit away and then add it to s
        # when n=0,jump out of while.
        n = s
    return n


# close enough
def close(m, n):
    """
    Implement close, which takes two non-negative integers m and n. It returns whether m can be changed into n
by either inserting one digit, removing one digit, or changing one digit. If m and n are the same number, they
are not close.
    """
    # rearrange the order
    if m < n:
        m, n = n, m
    while m or n:  # neither of them is 0
        # compare the last digit. if same,move on to the next digit
        if m % 10 == n % 10:
            m, n = m // 10, n // 10
        # if not the same, further compare and don't allow those who have 2 indifferent
        else:  # 345 34          #345 344
            return m // 10 == n or m // 10 == n // 10
    return False


# which one?
x,y,z=1,2,3
def switch(x):
    z=4
    if x==y:
        def which(one):
            return x+one
    else:
        def which (one):
            return x-one
    x=which(x)
    which(x)

def which(one):
    return x+one

switch(x+1)
x=5
which(z)