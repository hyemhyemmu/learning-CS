"""Typing test implementation"""
from utils import (
    lower,
    split,
    remove_punctuation,
    lines_from_file,
    count,
    deep_convert_to_tuple,
)
from ucb import main, interact, trace
from datetime import datetime
import random


###########
# Phase 1 #
###########


def pick(paragraphs, select, k):
    """Return the Kth paragraph from PARAGRAPHS for which the SELECT returns True.
    If there are fewer than K such paragraphs, return an empty string.

    Arguments:
        paragraphs: a list of strings representing paragraphs
        select: a function that returns True for paragraphs that meet its criteria
        k: an integer

    >>> ps = ['hi', 'how are you', 'fine']
    >>> s = lambda p: len(p) <= 4
    >>> pick(ps, s, 0)
    'hi'
    >>> pick(ps, s, 1)
    'fine'
    >>> pick(ps, s, 2)
    ''
    """
    # BEGIN PROBLEM 1
    qualify_para = [p for p in paragraphs if select(p)]
    if k < len(qualify_para):
        return qualify_para[k]
    else:
        return ''
    # END PROBLEM 1


def about(subject):
    """Return a function that takes in a paragraph and returns whether
    that paragraph contains one of the words in SUBJECT.

    Arguments:
        subject: a list of words related to a subject

    >>> about_dogs = about(['dog', 'dogs', 'pup', 'puppy'])
    >>> pick(['Cute Dog!', 'That is a cat.', 'Nice pup!'], about_dogs, 0)
    'Cute Dog!'
    >>> pick(['Cute Dog!', 'That is a cat.', 'Nice pup.'], about_dogs, 1)
    'Nice pup.'
    """
    assert all([lower(x) == x for x in subject]), "subjects should be lowercase."

    # BEGIN PROBLEM 2
    # important:"about_dogs"is a function that will later input "paragraphs" (2 argument input)
    def match(para):
        # lower case
        processed_para = lower(para)
        # remove punc
        processed_para = remove_punctuation(processed_para)
        # compare
        processed_para = split(processed_para)
        # any word would be fine
        for words in processed_para:
            for subject_word in subject:
                if words == subject_word:
                    return True
        return False

    return match
    # END PROBLEM 2


def accuracy(typed, source):
    """Return the accuracy (percentage of words typed correctly) of TYPED
    compared to the corresponding words in SOURCE.

    Arguments:
        typed: a string that may contain typos
        source: a model string without errors

    >>> accuracy('Cute Dog!', 'Cute Dog.')
    50.0
    >>> accuracy('A Cute Dog!', 'Cute Dog.')
    0.0
    >>> accuracy('cute Dog.', 'Cute Dog.')
    50.0
    >>> accuracy('Cute Dog. I say!', 'Cute Dog.')
    50.0
    >>> accuracy('Cute', 'Cute Dog.')
    100.0
    >>> accuracy('', 'Cute Dog.')
    0.0
    >>> accuracy('', '')
    100.0
    """
    typed_words = split(typed)
    source_words = split(source)

    # BEGIN PROBLEM 3
    def match(typed_words, source_words):
        correct_words = []
        # either of them empty, means that the recursion is over
        if not source_words or not typed_words:
            return []
        # if first same -> add it to the list
        elif source_words[0] == typed_words[0]:
            return [typed_words[0]] + match(typed_words[1:], source_words[1:])
        else:
            # not match -> continue to recurse
            return match(typed_words[1:], source_words[1:])

    # special cases
    if not source_words and not typed_words:
        return 100.0
    if not source_words or not typed_words:
        return 0.0
    else:
        list_match = match(typed_words, source_words)
        percentage = len(list_match) / len(typed_words) * 100
        # correctness percentage
        return percentage
    # END PROBLEM 3


def wpm(typed, elapsed):
    """Return the words-per-minute (WPM) of the TYPED string.

    Arguments:
        typed: an entered string
        elapsed: an amount of time in seconds

    >>> wpm('hello friend hello buddy hello', 15)
    24.0
    >>> wpm('0123456789',60)
    2.0
    """
    assert elapsed > 0, "Elapsed time must be positive"
    # BEGIN PROBLEM 4
    minutes = elapsed / 60
    words = len(typed) / 5
    return words / minutes
    # END PROBLEM 4


################
# Phase 4 (EC) #
################


def memo(f):
    """A general memoization decorator."""
    cache = {}

    def memoized(*args):
        immutable_args = deep_convert_to_tuple(args)  # convert *args into a tuple representation
        if immutable_args not in cache:
            result = f(*immutable_args)
            cache[immutable_args] = result
            return result
        return cache[immutable_args]

    return memoized


def memo_diff(diff_function):
    """A memoization function."""
    cache = {}

    def memoized(typed, source, limit):
        # BEGIN PROBLEM EC
        "*** YOUR CODE HERE ***"
        # END PROBLEM EC

    return memoized


###########
# Phase 2 #
###########


def autocorrect(typed_word, word_list, diff_function, limit):
    """Returns the element of WORD_LIST that has the smallest difference
    from TYPED_WORD based on DIFF_FUNCTION. If multiple words are tied for the smallest difference,
    return the one that appears closest to the front of WORD_LIST. If the
    difference is greater than LIMIT, return TYPED_WORD instead.

    Arguments:
        typed_word: a string representing a word that may contain typos
        word_list: a list of strings representing source words
        diff_function: a function quantifying the difference between two words
        limit: a number

    >>> ten_diff = lambda w1, w2, limit: 10 # Always returns 10
    >>> autocorrect("hwllo", ["butter", "hello", "potato"], ten_diff, 20)
    'butter'
    >>> first_diff = lambda w1, w2, limit: (1 if w1[0] != w2[0] else 0) # Checks for matching first char
    >>> autocorrect("tosting", ["testing", "asking", "fasting"], first_diff, 10)
    'testing'
    """
    if typed_word in word_list:
        return typed_word
    # the smallest difference
    min_difference = diff_function(typed_word, word_list, limit)
    # corresponding word from word list
    min_word = min(word_list, key = lambda word: (typed_word, word_list, limit))
    # BEGIN PROBLEM 5
    return min_word if min_difference < limit else typed_word
    # END PROBLEM 5


def furry_fixes(typed, source, limit):
    """A diff function for autocorrect that determines how many letters
    in TYPED need to be substituted to create SOURCE, then adds the difference in
    their lengths and returns the result.

    Arguments:
        typed: a starting word
        source: a string representing a desired goal word
        limit: a number representing an upper bound on the number of chars that must change

    >>> big_limit = 10
    >>> furry_fixes("nice", "rice", big_limit)    # Substitute: n -> r
    1
    >>> furry_fixes("range", "rungs", big_limit)  # Substitute: a -> u, e -> s
    2
    >>> furry_fixes("pill", "pillage", big_limit) # Don't substitute anything, length difference of 3.
    3
    >>> furry_fixes("roses", "arose", big_limit)  # Substitute: r -> a, o -> r, s -> o, e -> s, s -> e
    5
    >>> furry_fixes("rose", "hello", big_limit)   # Substitute: r->h, o->e, s->l, e->l, length difference of 1.
    5
    """

    # BEGIN PROBLEM 6
    if limit < 0:
        # we don't have to get the actual number, we only need to know if it is bigger than limit
        return limit + 1
    # typed becomes empty
    if not typed:
        return len(source)
    elif not source:
        return len(typed)

    if typed[0] == source[0]:
        return furry_fixes(typed[1:], source[1:], limit)
    else:
        return 1 + furry_fixes(typed[1:], source[1:], limit - 1)
    # END PROBLEM 6


def minimum_mewtations(typed, source, limit):
    """A diff function for autocorrect that computes the edit distance from TYPED to SOURCE.
    This function takes in a string TYPED, a string SOURCE, and a number LIMIT.

    Arguments:
        typed: a starting word
        source: a string representing a desired goal word
        limit: a number representing an upper bound on the number of edits

    >>> big_limit = 10
    >>> minimum_mewtations("cats", "scat", big_limit)       # cats -> scats -> scat
    2
    >>> minimum_mewtations("purng", "purring", big_limit)   # purng -> purrng -> purring
    2
    >>> minimum_mewtations("ckiteus", "kittens", big_limit) # ckiteus -> kiteus -> kitteus -> kittens
    3
    """
    if limit < 0:  # Base cases should go here, you may add more base cases as needed.
        return limit + 1
        # Recursive cases should go below here
    if not typed:
        return len(source)
    elif not source:
        return len(typed)

    if typed[0] == source[0]:
        return minimum_mewtations(typed[1:], source[1:], limit)
    else:
        # add is similar to remove the digit from source!
        add = minimum_mewtations(typed, source[1:], limit - 1)
        # delete the digit
        remove = minimum_mewtations(typed[1:], source, limit - 1)
        # remove the digit from both string
        substitute = minimum_mewtations(typed[1:], source[1:], limit - 1)

        return 1 + min(add, remove, substitute)  # act as a counter


# nearby letters
keyboard_neighbors = {
    'q': ['w', 'a'],
    'w': ['q', 'e', 's'],
    'e': ['w', 'r', 'd'],
    'r': ['e', 't', 'f'],
    't': ['r', 'y', 'g'],
    'y': ['t', 'u', 'h'],
    'u': ['y', 'i', 'j'],
    'i': ['u', 'o', 'k'],
    'o': ['i', 'p', 'l'],
    'p': ['o', ';'],
    'a': ['q', 'w', 's', 'z'],
    's': ['a', 'w', 'e', 'd', 'z'],
    'd': ['s', 'e', 'r', 'f', 'x'],
    'f': ['d', 'r', 't', 'g', 'c'],
    'g': ['f', 't', 'y', 'h', 'v'],
    'h': ['g', 'y', 'u', 'j', 'b'],
    'j': ['h', 'u', 'i', 'k', 'n'],
    'k': ['j', 'i', 'o', 'l', 'm'],
    'l': ['k', 'o', 'p', ';'],
    'z': ['a', 's', 'x'],
    'x': ['z', 's', 'd', 'c'],
    'c': ['x', 'd', 'f', 'v'],
    'v': ['c', 'f', 'g', 'b'],
    'b': ['v', 'g', 'h', 'n'],
    'n': ['b', 'h', 'j', 'm'],
    'm': ['n', 'j', 'k']
}


def is_neighbor(letter1, letter2):
    return letter2 in keyboard_neighbors.get(letter1, [])


def final_diff(typed, source, limit):
    """A diff function that takes in a string TYPED, a string SOURCE, and a number LIMIT.
    If you implement this function, it will be used.
    Take into account which additions and deletions are more likely than others.
        Treat two adjacent letters that have swapped positions as one change, not two.
    Try to incorporate common misspellings.
    Letters near to each other on the keyboard are more commonly substituted."""
    if limit < 0:  # Base cases should go here, you may add more base cases as needed.
        return limit + 1
        # Recursive cases should go below here
    if not typed:
        return len(source)
    elif not source:
        return len(typed)

    if typed[0] == source[0]:
        return furry_fixes(typed[1:], source[1:], limit)
    else:
        # add is similar to remove the digit from source!
        add = minimum_mewtations(typed, source[1:], limit - 1)
        # delete the digit
        remove = minimum_mewtations(typed[1:], source, limit - 1)
        # remove the digit from both string
        substitute = minimum_mewtations(typed[1:], source[1:], limit - 1)

        if is_neighbor(typed[0], source[0]):
            substitute = min(substitute, minimum_mewtations(typed[1:], source[1:], limit - 1))
        return 1 + min(add, remove, substitute)  # act as a counter


FINAL_DIFF_LIMIT = 6  # REPLACE THIS WITH YOUR LIMIT


###########
# Phase 3 #
###########


def report_progress(typed, source, user_id, upload):
    """Upload a report of your id and progress so far to the multiplayer server.
    Returns the progress so far.

    Arguments:
        typed: a list of the words typed so far
        source: a list of the words in the typing source
        user_id: a number representing the id of the current user
        upload: a function used to upload progress to the multiplayer server

    >>> print_progress = lambda d: print('ID:', d['id'], 'Progress:', d['progress'])
    >>> # The above function displays progress in the format ID: __, Progress: __
    >>> print_progress({'id': 1, 'progress': 0.6})
    ID: 1 Progress: 0.6
    >>> typed = ['how', 'are', 'you']
    >>> source = ['how', 'are', 'you', 'doing', 'today']
    >>> report_progress(typed, source, 2, print_progress)
    ID: 2 Progress: 0.6
    0.6
    >>> report_progress(['how', 'aree'], source, 3, print_progress)
    ID: 3 Progress: 0.2
    0.2
    """
    # BEGIN PROBLEM 8
    count = 0
    for i in range(min(len(typed), len(source))):
        if typed[i] == source[i]:
            count += 1
        else:
            break

    progress = count / len(source)
    upload({'id': user_id, 'progress': progress})
    return progress
    # END PROBLEM 8


def time_per_word(words, timestamps_per_player):
    """Return a dictionary {'words': words, 'times': times} where times
    is a list of lists that stores the durations it took each player to type
    each word in words.

    Arguments:
        words: a list of words, in the order they are typed.
        timestamps_per_player: A list of lists of timestamps including the time
                          the player started typing, followed by the time the
                          player finished typing each word.

    >>> p = [[75, 81, 84, 90, 92], [19, 29, 35, 36, 38]]
    >>> result = time_per_word(['collar', 'plush', 'blush', 'repute'], p)
    >>> result['words']
    ['collar', 'plush', 'blush', 'repute']
    >>> result['times']
    [[6, 3, 6, 2], [10, 6, 1, 2]]
    """
    tpp = timestamps_per_player  # A shorter name (for convenience)
    # BEGIN PROBLEM 9
    """
    a version for two players:
    tpp_1, tpp_2 = tpp[0], tpp[1]

    def time(tpp):
        if len(tpp) == 1:
            return []
        return [(tpp[1] - tpp[0])] + time(tpp[1:])

    times = [time(tpp_1), time(tpp_2)]
    return {'words': words, 'times': times}
    """
    # Initialize the list to store the time durations for all players
    times = []

    # Iterate over each player's timestamps
    for player_timestamps in timestamps_per_player:
        # Initialize the list to store the time durations for this player
        player_times = []

        # Compute the time differences between consecutive timestamps
        for i in range(1, len(player_timestamps)):
            player_times.append(player_timestamps[i] - player_timestamps[i - 1])

        times.append(player_times)

    return {'words': words, 'times': times}
    # END PROBLEM 9


def fastest_words(words_and_times):
    """Return a list of lists indicating which words each player typed fastests.

    Arguments:
        words_and_times: a dictionary {'words': words, 'times': times} where
        words is a list of the words typed and times is a list of lists of times
        spent by each player typing each word.

    >>> p0 = [5, 1, 3]
    >>> p1 = [4, 1, 6]
    >>> fastest_words({'words': ['Just', 'have', 'fun'], 'times': [p0, p1]})
    [['have', 'fun'], ['Just']]
    >>> p0  # input lists should not be mutated
    [5, 1, 3]
    >>> p1
    [4, 1, 6]
    """
    check_words_and_times(words_and_times)  # verify that the input is properly formed
    words, times = words_and_times['words'], words_and_times['times']
    player_indices = range(len(times))  # contains an *index* for each player
    word_indices = range(len(words))  # contains an *index* for each word
    # BEGIN PROBLEM 10
    # lists
    lists = [[] for _ in player_indices]

    # iterate over each words
    for word_index in word_indices:
        # assume initially that the fastest is the first player
        fastest_player = 0
        min_time = get_time(times, 0, word_index)

        # iterate over each player to compare
        for player_num in player_indices:
            player_time = get_time(times, player_num, word_index)
            if player_time < min_time:
                fastest_player = player_num
                min_time = player_time

        # add to the list after finish iterating each word
        lists[fastest_player].append(words[word_index])
    return lists
    # END PROBLEM 10


def check_words_and_times(words_and_times):
    """Check that words_and_times is a {'words': words, 'times': times} dictionary
    in which each element of times is a list of numbers the same length as words.
    """
    assert 'words' in words_and_times and 'times' in words_and_times and len(words_and_times) == 2
    words, times = words_and_times['words'], words_and_times['times']
    assert all([type(w) == str for w in words]), "words should be a list of strings"
    assert all([type(t) == list for t in times]), "times should be a list of lists"
    assert all([isinstance(i, (int, float)) for t in times for i in t]), "times lists should contain numbers"
    assert all([len(t) == len(words) for t in times]), "There should be one word per time."


def get_time(times, player_num, word_index):
    """Return the time it took player_num to type the word at word_index,
    given a list of lists of times returned by time_per_word."""
    num_players = len(times)
    num_words = len(times[0])
    assert word_index < len(times[0]), f"word_index {word_index} outside of 0 to {num_words - 1}"
    assert player_num < len(times), f"player_num {player_num} outside of 0 to {num_players - 1}"
    return times[player_num][word_index]


enable_multiplayer = False  # Change to True when you're ready to race.


##########################
# Command Line Interface #
##########################


def run_typing_test(topics):
    """Measure typing speed and accuracy on the command line."""
    paragraphs = lines_from_file("data/sample_paragraphs.txt")
    random.shuffle(paragraphs)
    select = lambda p: True
    if topics:
        select = about(topics)
    i = 0
    while True:
        source = pick(paragraphs, select, i)
        if not source:
            print("No more paragraphs about", topics, "are available.")
            return
        print("Type the following paragraph and then press enter/return.")
        print("If you only type part of it, you will be scored only on that part.\n")
        print(source)
        print()

        start = datetime.now()
        typed = input()
        if not typed:
            print("Goodbye.")
            return
        print()

        elapsed = (datetime.now() - start).total_seconds()
        print("Nice work!")
        print("Words per minute:", wpm(typed, elapsed))
        print("Accuracy:        ", accuracy(typed, source))

        print("\nPress enter/return for the next paragraph or type q to quit.")
        if input().strip() == "q":
            return
        i += 1


@main
def run(*args):
    """Read in the command-line argument and calls corresponding functions."""
    import argparse

    parser = argparse.ArgumentParser(description = "Typing Test")
    parser.add_argument("topic", help = "Topic word", nargs = "*")
    parser.add_argument("-t", help = "Run typing test", action = "store_true")

    args = parser.parse_args()
    if args.t:
        run_typing_test(args.topic)
