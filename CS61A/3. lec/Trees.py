# Tree Abstraction
def tree(label, branches = []):
    for branch in branches:
        assert is_tree(branch), 'branches must be trees'
    return [label] + list(branches)  # make sure stuff we appended is a list


def label(tree):
    # first element of the list is the label
    return tree[0]


def branches(tree):
    return tree[1:]


def is_tree(tree):
    if type(tree) != list or len(tree) < 1:
        return False
    for branch in branches(tree):
        if not is_tree(branch):
            return False
    return True


def is_leaf(tree):
    # if doesn't have branches
    return not branches(tree)


# tree-processing: fib tree
def fib_tree(n):
    if n <= 1:
        return tree(n)  # no branches
    else:
        left, right = fib_tree(n - 2), fib_tree(n - 1)
        return tree(label(left) + label(right), [left, right])  # branches are lists


def count_leaves(tree):
    """count the leaves of the tree"""
    if is_leaf(tree):
        return 1
    else:
        return sum([count_leaves(b) for b in branches(tree)])


def leaves(tree):
    """Return a list containing the leaf labels of the tree"""
    if is_leaf(tree):
        return [label(tree)]
    else:
        return sum([leaves(b) for b in branches(tree)], [])


# creating a tree
def increment_leaves(tree):
    """return a tree like t but with LEAF labels incremented"""
    if is_leaf(tree):
        return tree(label(tree) + 1)
    else:
        return tree(label(tree), [increment_leaves(b) for b in branches(tree)])


def increment(tree):
    """return a tree like t but with ALL labels incremented"""
    if is_leaf(tree):
        return tree(label(tree) + 1)
    else:
        return tree(label(tree) + 1, [increment(b) for b in branches(tree)])


# print tree
def print_tree(tree, indent = 0):
    # head label
    print(' ' * indent + str(label(tree)))
    for b in branches(tree):
        print_tree(b, indent + 1)


# count paths that have a total label sum
def count_paths(t, total):
    """Return the number of paths from the root to any node in tree t
    for which the labels along the path sum to total.

    >>> t = tree(3, [tree(-1), tree(1, [tree(2, [tree(1)]), tree(3)]), tree(1, [tree(-1)])])
    >>> count_paths(t, 3)
    2
    >>> count_paths(t, 4)
    2
    >>> count_paths(t, 5)
    0
    >>> count_paths(t, 6)
    1
    >>> count_paths(t, 7)
    2
    """
    if label(t) == total:
        found = 1
    else:
        found = 0
    return found + sum([count_paths(b, total - label(t)) for b in branches(t)])
