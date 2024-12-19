"""The Game of Hog."""

from dice import six_sided, make_test_dice
from ucb import main, trace, interact

GOAL = 100  # The goal of Hog is to score 100 points.


######################
# Phase 1: Simulator #
######################


def roll_dice(num_rolls, dice = six_sided):
    """Simulate rolling the DICE exactly NUM_ROLLS > 0 times. Return the sum of
    the outcomes unless any of the outcomes is 1. In that case, return 1.

    num_rolls:  The number of dice rolls that will be made.
    dice:       A function that simulates a single dice roll outcome. Defaults to the six sided dice.
    """
    # These assert statements ensure that num_rolls is a positive integer.
    assert type(num_rolls) == int, 'num_rolls must be an integer.'
    assert num_rolls > 0, 'Must roll at least once.'
    # BEGIN PROBLEM 1
    result = 0
    turns = num_rolls
    for i in range(num_rolls):
        outcome = dice()
        if outcome == 1:
            return 1
        result += outcome
    return result
    # END PROBLEM 1


def boar_brawl(player_score, opponent_score):
    """Return the points scored by rolling 0 dice according to Boar Brawl.

    player_score:     The total score of the current player.
    opponent_score:   The total score of the other player.

    """
    # BEGIN PROBLEM 2
    value_1 = player_score % 10  # right-most digit
    value_2 = (opponent_score // 10) % 10  # tens digit
    abs_values = abs(value_1 - value_2)
    score = 3 * abs_values
    return max(1, score)  # if score=0,player actually gets 1 point
    # END PROBLEM 2


def take_turn(num_rolls, player_score, opponent_score, dice = six_sided):
    """Return the points scored on a turn rolling NUM_ROLLS dice when the
    player has PLAYER_SCORE points and the opponent has OPPONENT_SCORE points.

    num_rolls:       The number of dice rolls that will be made.
    player_score:    The total score of the current player.
    opponent_score:  The total score of the other player.
    dice:            A function that simulates a single dice roll outcome.
    """
    # Leave these assert statements here; they help check for errors.
    assert type(num_rolls) == int, 'num_rolls must be an integer.'
    assert num_rolls >= 0, 'Cannot roll a negative number of dice in take_turn.'
    assert num_rolls <= 10, 'Cannot roll more than 10 dice.'
    # BEGIN PROBLEM 3
    if num_rolls == 0:
        # player choose to roll the 0 dice
        return boar_brawl(player_score, opponent_score)
    else:
        return roll_dice(num_rolls, dice)
    # END PROBLEM 3


def simple_update(num_rolls, player_score, opponent_score, dice = six_sided):
    """Return the total score of a player who starts their turn with
    PLAYER_SCORE and then rolls NUM_ROLLS DICE, ignoring Sus Fuss.
    """
    score = player_score + take_turn(num_rolls, player_score, opponent_score, dice)
    return score


def is_prime(n):
    """Return whether N is prime."""
    if n == 1:
        return False
    k = 2
    while k < n:
        if n % k == 0:
            return False
        k += 1
    return True


def num_factors(n):
    """Return the number of factors of N, including 1 and N itself."""
    # BEGIN PROBLEM 4
    i = 1
    count = 0
    for i in range(1, n + 1):
        if n % i == 0:
            count += 1
    return count
    # END PROBLEM 4


def sus_points(score):
    """Return the new score of a player taking into account the Sus Fuss rule."""

    # BEGIN PROBLEM 4
    if num_factors(score) in (3, 4):
        new_score = score + 1
        while not is_prime(new_score):
            new_score += 1
        return new_score
    return score
    # END PROBLEM 4


def sus_update(num_rolls, player_score, opponent_score, dice = six_sided):
    """Return the total score of a player who starts their turn with
    PLAYER_SCORE and then rolls NUM_ROLLS DICE, *including* Sus Fuss.
    """
    # BEGIN PROBLEM 4
    # take turns first
    new_score = player_score + take_turn(num_rolls, player_score, opponent_score, dice = six_sided)
    # then apply sus rule
    return sus_points(new_score)
    # END PROBLEM 4


def always_roll_5(score, opponent_score):
    """A strategy of always rolling 5 dice, regardless of the player's score or
    the opponent's score.
    """
    return 5


def play(strategy0, strategy1, update,
         score0 = 0, score1 = 0, dice = six_sided, goal = GOAL):
    """Simulate a game and return the final scores of both players, with
    Player 0's score first and Player 1's score second.

    E.g., play(always_roll_5, always_roll_5, sus_update) simulates a game in
    which both players always choose to roll 5 dice on every turn and the Sus
    Fuss rule is in effect.

    A strategy function, such as always_roll_5, takes the current player's
    score and their opponent's score and returns the number of dice the current
    player chooses to roll.

    An update function, such as sus_update or simple_update, takes the number
    of dice to roll, the current player's score, the opponent's score, and the
    dice function used to simulate rolling dice. It returns the updated score
    of the current player after they take their turn.

    strategy0: The strategy for player0.
    strategy1: The strategy for player1.
    update:    The update function (used for both players).
    score0:    Starting score for Player 0
    score1:    Starting score for Player 1
    dice:      A function of zero arguments that simulates a dice roll.
    goal:      The game ends and someone wins when this score is reached.
    """
    who = 0  # Who is about to take a turn, 0 (first) or 1 (second)
    # BEGIN PROBLEM 5
    while score0 < goal and score1 < goal:
        if who == 0:  # player1's turn
            # calculate num_dice
            num_rolls = strategy0(score0, score1)
            score0=update(num_rolls, score0, score1, dice)
        else:
            num_rolls = strategy1(score1, score0)
            score1=update(num_rolls, score1, score0, dice)
        who = 1 - who
    # END PROBLEM 5
    return score0, score1


#######################
# Phase 2: Strategies #
#######################


def always_roll(n):
    """Return a player strategy that always rolls N dice.

    A player strategy is a function that takes two total scores as arguments
    (the current player's score, and the opponent's score), and returns a
    number of dice that the current player will roll this turn.

    >>> strategy = always_roll(3)
    >>> strategy(0, 0)
    3
    >>> strategy(99, 99)
    3
    """
    assert n >= 0 and n <= 10

    # BEGIN PROBLEM 6
    def strategy(player_score, opponent_score):
        return n  # ignore input parameters and ALWAYS return same value

    return strategy
    # END PROBLEM 6


def catch_up(score, opponent_score):
    """A player strategy that always rolls 5 dice unless the opponent
    has a higher score, in which case 6 dice are rolled.

    >>> catch_up(9, 4)
    5
    >>> strategy(17, 18)
    6
    """
    if score < opponent_score:
        return 6  # Roll one more to catch up
    else:
        return 5


def is_always_roll(strategy, goal = GOAL):
    """Return whether STRATEGY always chooses the same number of dice to roll
    given a game that goes to GOAL points.

    >>> is_always_roll(always_roll_5)
    True
    >>> is_always_roll(always_roll(3))
    True
    >>> is_always_roll(catch_up)
    False
    """
    # BEGIN PROBLEM 7

    # we don't have to compare every step. instead, choose some of them would be fine enough
    first_roll = None  # store the first value to compare
    for player_score in range(0, goal, 10):
        for opponent_score in range(0, goal, 10):
            current_roll = strategy(player_score, opponent_score)
            if first_roll is None:
                first_roll = current_roll
            elif current_roll != first_roll:
                return False
    return True
    # END PROBLEM 7


def make_averaged(original_function, times_called = 1000):
    """Return a function that returns the average value of ORIGINAL_FUNCTION
    called TIMES_CALLED times.

    To implement this function, you will have to use *args syntax.

    >>> dice = make_test_dice(4, 2, 5, 1)
    >>> averaged_dice = make_averaged(roll_dice, 40)
    >>> averaged_dice(1, dice)  # The avg of 10 4's, 10 2's, 10 5's, and 10 1's
    3.0
    """

    # BEGIN PROBLEM 8
    def averaged_function(*args, **kwargs):
        total = 0
        for i in range(times_called):
            total += original_function(*args, **kwargs)
        return total / times_called

    return averaged_function
    # END PROBLEM 8


def max_scoring_num_rolls(dice = six_sided, times_called = 1000):
    """Return the number of dice (1 to 10) that gives the maximum average score for a turn.
    Assume that the dice always return positive outcomes.

    >>> dice = make_test_dice(1, 6)
    >>> max_scoring_num_rolls(dice)
    1
    """
    # BEGIN PROBLEM 9
    max_average = 0
    best_num_rolls = 1  # initialize as 1

    # function for average(not input the variables num_rolls,dice yet)
    average_score_roll = make_averaged(roll_dice, times_called)

    # input num_rolls 1~10
    for num_rolls in range(1, 11):
        average = average_score_roll(num_rolls, dice)
        if average > max_average:
            max_average = average
            best_num_rolls = num_rolls
    return best_num_rolls
    # END PROBLEM 9


def winner(strategy0, strategy1):
    """Return 0 if strategy0 wins against strategy1, and 1 otherwise."""
    score0, score1 = play(strategy0, strategy1, sus_update)
    if score0 > score1:
        return 0
    else:
        return 1


def average_win_rate(strategy, baseline = always_roll(6)):
    """Return the average win rate of STRATEGY against BASELINE. Averages the
    winrate when starting the game as player 0 and as player 1.
    """
    win_rate_as_player_0 = 1 - make_averaged(winner)(strategy, baseline)
    win_rate_as_player_1 = make_averaged(winner)(baseline, strategy)

    return (win_rate_as_player_0 + win_rate_as_player_1) / 2


def run_experiments():
    """Run a series of strategy experiments and report results."""
    six_sided_max = max_scoring_num_rolls(six_sided)
    print('Max scoring num rolls for six-sided dice:', six_sided_max)

    print('always_roll(6) win rate:', average_win_rate(always_roll(6)))  # near 0.5
    print('catch_up win rate:', average_win_rate(catch_up))
    print('always_roll(3) win rate:', average_win_rate(always_roll(3)))
    print('always_roll(8) win rate:', average_win_rate(always_roll(8)))

    print('boar_strategy win rate:', average_win_rate(boar_strategy))
    print('sus_strategy win rate:', average_win_rate(sus_strategy))
    print('final_strategy win rate:', average_win_rate(final_strategy))
    "*** You may add additional experiments as you wish ***"


def boar_strategy(score, opponent_score, threshold = 11, num_rolls = 6):
    """This strategy returns 0 dice if Boar Brawl gives at least THRESHOLD
    points, and returns NUM_ROLLS otherwise. Ignore score and Sus Fuss.
    """
    # BEGIN PROBLEM 10
    boar_points = boar_brawl(score, opponent_score)

    if boar_points >= threshold:
        return 0
    return num_rolls
    # END PROBLEM 10


def sus_strategy(score, opponent_score, threshold = 11, num_rolls = 6):
    """This strategy returns 0 dice when your score would increase by at least threshold."""
    # BEGIN PROBLEM 11
    potential_score = sus_update(0, score, opponent_score)

    if potential_score - score >= threshold:
        return 0

    return num_rolls
    # END PROBLEM 11


def final_strategy(score, opponent_score):
    """
    This strategy combines different tactics to maximize the win rate:
    1. Check if rolling 0, 1, or 2 dice can SECURE a win.
    2. Use sus_strategy when it provides a significant advantage.
    3. Adjust the number of rolls based on the current score and lead/lag.
    """
    # BEGIN PROBLEM 12
    goal_score = 100

    # 1. If rolling 0 can win the game
    if sus_update(0, score, opponent_score) >= goal_score:
        return 0

    # 2. If rolling 1 or 2 dice can win the game
    if sus_update(1, score, opponent_score) >= goal_score:
        return 1
    if sus_update(2, score, opponent_score) >= goal_score:
        return 2

    # 3. Use sus_strategy for significant advantage
    threshold = 8  # A reasonable threshold for triggering sus_strategy
    num_rolls = 4 if score > opponent_score else 6  # Fewer rolls when leading
    if sus_strategy(score, opponent_score, threshold, num_rolls) == 0:
        return 0

    # 4. Adjust dice count dynamically
    if score >= 90:  # Close to winning, reduce risk
        return 2
    if score < opponent_score:  # Falling behind, take more risks
        return 6

    # Default rolls
    return 4
    # END PROBLEM 12


##########################
# Command Line Interface #
##########################

# NOTE: The function in this section does not need to be changed. It uses
# features of Python not yet covered in the course.

@main
def run(*args):
    """Read in the command-line argument and calls corresponding functions."""
    import argparse
    parser = argparse.ArgumentParser(description = "Play Hog")
    parser.add_argument('--run_experiments', '-r', action = 'store_true',
                        help = 'Runs strategy experiments')

    args = parser.parse_args()

    if args.run_experiments:
        run_experiments()
