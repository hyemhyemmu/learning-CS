def search(query, ranking = lambda r: -r.stars):
    results = [r for r in Restaurant.all_r if query in r.name]
    return sorted(results, key = ranking)


def reviewed_both(r, s):
    return len([x for x in r.reviewers if x in s.reviewers])


def fast_overlap(s, t):
    """Return the overlapped elements in S and T
    **This method is much faster than:
    len([x for x in r.reviewers if x in s.reviewers])
    >>>fast_overlap([3,4,6,7,9,10],[1,3,5,7,8])
    2
    """
    i, j, count = 0, 0, 0
    min_len = min(len(s), len(t))
    while i < min_len and j < min_len:
        if s[i] == t[j]:
            count += 1
            i += 1
            j += 1
        elif s[i] < t[j]:
            i += 1
        else:
            j += 1
    return count


class Restaurant:
    all_r = []

    def __init__(self, name, stars):
        self.name, self.stars = name, stars
        self.reviewers
        Restaurant.all_r.append(self)

    def __repr__(self):
        return f'<{self.name}>'

    def similar(self, k, similarity = reviewed_both):  # this is how we define similarity
        """Return the K most similar restaurants to SELF, using SIMILARITY for comparison"""
        other_r = list(Restaurant.all_r)
        other_r.remove(self)  # self shouldn't be in comparison
        return sorted(other_r, key = lambda r: -similarity(self, r))[:k]


# we want to implement a search engine finding 3 similar restaurants
results = search('Thai')
for r in results:
    print(r, 'is similar to', r.similar(3))
