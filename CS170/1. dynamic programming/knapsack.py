def knapsack_with_repetition(data, W):
    """
    很直觉的做法：通过缩小盘子大小来开启遍历，
    本质上是find the longest path in a dag
    时间复杂度O(nW)
    """
    weight = list(data.keys())
    values = list(data.values())
    size = len(data)

    K = [0] * (W + 1)
    
    # K(W) = K(W - W_i) + V_i
    for w in range(1, W + 1):
        for j in range(size):
            if weight[j] <= w:
                K[w] = max(K[w], K[w - weight[j]] + values[j])
    return K[W]

# test
data = {
    6 : 30,
    3 : 14,
    4 : 16,
    2 : 9
}
print(knapsack_with_repetition(data, 10))  # 应该输出48
print(knapsack_with_repetition(data, 6))   # 应该输出30 (选择一个重量6的物品)
print(knapsack_with_repetition(data, 4))   # 应该输出18 (选择两个重量2）

def knapsack_without_repetition(data, W):
    """
    不允许重复用同样的物品，那么就逐个考虑是否放，
    时间复杂度O(nW)
    """
    weight = list(data.keys())
    values = list(data.values())
    n = len(data)
    
    # K[i][w] 表示前i个物品在容量w下的最大价值
    K = [[0 for _ in range(W + 1)] for _ in range(n + 1)]
    
    # dynamic programming
    for i in range(1, n + 1):
        for w in range(1, W + 1):
            # 不选择第i个物品
            K[i][w] = K[i-1][w]
            
            # 如果第i个物品重量不超过当前容量，考虑选择它
            if weight[i-1] <= w:
                K[i][w] = max(K[i][w], K[i-1][w - weight[i-1]] + values[i-1])
    
    return K[n][W]

# 测试无重复背包问题
print("\n无重复背包问题测试:")
print(knapsack_without_repetition(data, 10))  # 应该输出46 (选择重量6+4的物品)
print(knapsack_without_repetition(data, 6))   # 应该输出30 (选择一个重量6的物品)
print(knapsack_without_repetition(data, 5))   # 应该输出23 (选择重量3+2的物品)

