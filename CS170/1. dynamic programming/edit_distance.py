# 求两个单词之间的最小修改距离

def edit_distance(word1, word2):
    m = len(word1)
    n = len(word2)
    dp = [[0 for _ in range(n + 1)] for _ in range(m + 1)]

    def diff(i, j):
        if word1[i - 1] == word2[j - 1]:
            return 0
        else:
            return 1

    # base case
    for i in range(m + 1):
        dp[i][0] = i
    for j in range(n + 1):
        dp[0][j] = j
    
    # main case
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            dp[i][j] = min(
                dp[i - 1][j] + 1, 
                dp[i][j - 1] + 1, 
                dp[i - 1][j - 1] + diff(i, j)
            )

    return dp[m][n] 


# test
print(edit_distance('exponential', 'polynomial'))

    