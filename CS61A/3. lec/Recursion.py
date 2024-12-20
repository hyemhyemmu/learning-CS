# example：returning a function by its own name
def print_sums(n):
    """
    print_sums: print the sum
    next_sum: do the summing work
    """
    print(n)

    def next_sum(k):
        return print_sums(n + k)

    return next_sum


# recursion example:sum digits
def split(n):
    return n // 10, n % 10


def digit_sum(n):
    all_but_last, last = split(n)
    if n < 10:
        return n
    else:
        return digit_sum(all_but_last) + last


# Luhn Algorithm (using iteration)
def luhn_sum_1(n):
    count = 1
    sum = 0
    while n:
        all_but_last, last = split(n)
        if count % 2 == 0:  # only even number need to be doubled
            double = last * 2
            if double > 9:
                sum += digit_sum(double)
            else:
                sum += double
        else:
            sum += last
        count += 1
        n = all_but_last
    return sum


# another version :using mutual recursion
def luhn_sum_2(n):
    if n < 10:
        return n
    else:
        all_but_last, last = split(n)
        return luhn_sum_double(all_but_last) + last


def luhn_sum_double(n):
    all_but_last, last = split(n)
    last_digit_doubled = digit_sum(2 * last)
    if n < 10:
        return last_digit_doubled
    else:
        return luhn_sum_1(all_but_last) + last_digit_doubled
