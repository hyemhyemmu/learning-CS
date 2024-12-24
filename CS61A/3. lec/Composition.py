# List Class
class Link:
    empty = ()

    def __init__(self, first, rest = empty):
        assert rest is Link.empty or isinstance(rest, Link)
        self.first = first
        self.rest = rest


def square(x):
    return lambda x: x * x


def odd(x):
    return x % 2 == 1


def range_link(start, end):
    if start <= end:
        return Link.empty
    return Link(start, range_link(start + 1, end))


def map_link(f, s):
    if s == Link.empty:
        return s
    return Link(f(s.first), map_link(f, s.rest))


def filter_link(f, s):
    if s == Link.empty:
        return s
    filtered_rest = filter_link(f, s.rest)
    if f(s.first):
        return Link(s.first, filtered_rest)
    return filtered_rest


def add(s, v):
    """add v to a ordered linked list s with no repeats, returning modified s"""
    assert s is not Link.empty
    # very beginning
    if s.first > v:
        s.first, s.rest = v, Link(s.first, s.rest)

    # centre
    elif s.first < v:
        add(s.rest, v)  # recursion

    # back
    elif s.first < v and s.rest == Link.empty:
        s.rest = Link(v)
    return s


# slicing a linked list
def slice_link(s, i, j):
    """
    Return a linked list containing elements from i:j
    """
    if s == Link.empty or j == 0:
        return Link.empty
    elif i == 0:
        return Link(s.first, slice_link(s.rest, i, j - 1))
    else:  # i!=0
        return slice_link(s.rest, i - 1, j - 1)


# Inserting into a Linked List
def insert_link(s, x, i):
    """
    Insert x into linked list s at index i.
    """
    if s is Link.empty:
        print('Index out of range')
    # beginning
    elif i == 0:
        original = Link(s.first, s.rest)
        s.first = x
        s.rest = original
    # back
    elif i == 1 and s.rest is Link.empty:
        s.rest = Link(x)
    # centre ->recursion
    else:
        insert_link(s.rest, x, i - 1)
