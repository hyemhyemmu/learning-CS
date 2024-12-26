# Lists
def min_abs_indices(s):
    """
    >>>min_abs_indices([-4,-3,-2,3,2,4])
    [2,4]
    """
    min_abs = min(map(abs, s))
    return [i for i in range(len(s)) if abs(s[i]) == min_abs]


def largest_adj_sum(s):
    """
    >>>largest_adj_sum([-4,-3,-2,3,2,4])
    6
    """
    return max(a + b for a, b in zip(s[:-1], s[1:]))


def digit_dict(s):
    """
    >>>digit_dict([5,8,13,21,34,55,89])
    stuff
    """
    result = {}
    for num in s:
        last_digit = num % 10
        if last_digit not in result:
            result[last_digit] = [num]
        else:
            result[last_digit].append(num)
    return result


# or just use one line
def digit_dict_2(s):
    last_digit = [x % 10 for x in s]
    return {d: [x for x in s if x % 10 == d] for d in last_digit}


def all_have_an_equal(s):
    """
    >>>all_have_an_equal([-4,-4,-2,3,2,4])
    False
    >>>all_have_an_equal([4,3,2,3,2,4])
    True
    """
    for i in range(len(s)):
        other = s[:i] + s[i + 1:]
        if s[i] not in other:
            return False
    return True


# simpler version
def all_have_an_equal_2(s):
    return all(s[i] in (s[:i] + s[i + 1:]) for i in range(len(s)))


def all_have_an_equal_3(s):
    return min([sum([1 for y in s if y == x]) for x in s]) > 1


def all_have_an_equal_4(s):
    return min(s.count(x) for x in s) > 1


# Linked Lists Pra
def ordered(s, pre_num = -float('inf')):
    """
    >>>ordered(Link(1,Link(3,Link(4))))
    True
    >>>ordered(Link(1,Link(7,Link(4))))
    False
    """
    if s is Link.empty:
        return True
    if not s.first > pre_num:
        return False
    return ordered(s.rest, s.first)


def merge(s, t):  # iterate version
    """
    >>>a=Link(1,Link(5))
    >>>b=Link(1,Link(4))
    >>>merge(a,b)
    Link(1,Link(1,Link(4,Link(5)))
    """
    result = Link(None)
    p = result
    while s is not Link.empty and t is not Link.empty:
        if s.first <= t.first:
            p.rest = Link(s.first)
            s = s.rest

        elif s.first > t.first:
            p.rest = Link(t.first)
            t = t.rest
        p = p.rest

    if s is Link.empty:
        p.rest = t
    elif t is Link.empty:
        p.rest = s

    return result.rest


def merge_2(s, t):  # recursive version
    """
    >>>a=Link(1,Link(5))
    >>>b=Link(1,Link(4))
    >>>merge_2(a,b)
    Link(1,Link(1,Link(4,Link(5)))
    """
    if s is Link.empty:
        return t
    elif t is Link.empty:
        return s
    elif s.first < t.first:
        return Link(s.first, merge_2(s.rest, t))
    else:
        return Link(t.first, merge_2(s, t.rest))


def merge_in_place(s, t):  # recursive version
    """
    >>>a=Link(1,Link(5))
    >>>b=Link(1,Link(4))
    >>>merge_in_place(a,b)
    Link(1,Link(1,Link(4,Link(5)))
    """
    if s is Link.empty:
        return t
    elif t is Link.empty:
        return s
    elif s.first < t.first:
        # return Link(s.first, merge_2(s.rest, t))
        s.rest = merge_in_place(s.rest, t)
        return s
    else:
        # return Link(t.first, merge_2(s, t.rest))
        t.rest = merge_in_place(s, t.rest)
        return t


# Link Class
class Link:
    empty = ()

    def __init__(self, first, rest = empty):
        assert rest is Link.empty or isinstance(rest, Link)
        self.first = first
        self.rest = rest

    def __repr__(self):
        if self.rest is Link.empty:
            return f'Link({self.first})'
        return f'Link({self.first}, {self.rest})'
