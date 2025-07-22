def find_longest_increasing_subsequence(nums):
    """
    用动态规划来寻找最长子序列
    时间复杂度为O(n^2)
    """
    n = len(nums)
    L = [1] * n
    prev = [-1] * n

    # 嵌套for，时间复杂度为O(n^2)
    for j in range(1, n):
        for i in range(j):
            if nums[i] < nums[j] and L[i] + 1 > L[j]: 
                L[j] = L[i] + 1
                prev[j] = i


    # 遍历完之后，找最好的
    max_length = -1
    end_index = -1
    for i in range(n):
         if L[i] > max_length:
              max_length = L[i]
              end_index = i
    
    # 输出序列
    subsequence = []
    curr_index = end_index
    while curr_index != -1:
         subsequence.append(nums[curr_index])
         curr_index = prev[curr_index]
    return subsequence[::-1]

# test
print(find_longest_increasing_subsequence([5, 2, 8, 6, 3, 6, 9, 7]))

    