def tsp_dp(graph):
    """
    使用动态规划解决TSP问题
    graph: 邻接矩阵，graph[i][j]表示从城市i到城市j的距离
    返回最短路径长度和路径
    """
    n = len(graph)
    
    # dp[mask][i] 表示访问了mask中包含的城市，当前在城市i的最短距离
    # mask是二进制表示，第k位为1表示访问了城市k
    dp = [[float('inf')] * n for _ in range(1 << n)]
    parent = [[-1] * n for _ in range(1 << n)]
    
    # 从城市0开始
    dp[1][0] = 0  # mask=1表示只访问了城市0
    
    # 枚举所有可能的访问状态
    for mask in range(1, 1 << n):
        for u in range(n):
            if dp[mask][u] == float('inf'):
                continue
            if not (mask & (1 << u)):  # 如果当前状态不包含城市u
                continue
                
            # 尝试从城市u到达其他未访问的城市
            for v in range(n):
                if mask & (1 << v):  # 如果城市v已经访问过
                    continue
                
                new_mask = mask | (1 << v)  # 新状态：包含城市v
                new_dist = dp[mask][u] + graph[u][v]
                
                if new_dist < dp[new_mask][v]:
                    dp[new_mask][v] = new_dist
                    parent[new_mask][v] = u
    
    # 找到最优解：访问所有城市后回到起点
    all_visited = (1 << n) - 1
    min_cost = float('inf')
    last_city = -1
    
    for i in range(1, n):
        cost = dp[all_visited][i] + graph[i][0]  # 从城市i回到起点0
        if cost < min_cost:
            min_cost = cost
            last_city = i
    
    # 重构路径
    path = []
    mask = all_visited
    current = last_city
    
    while current != -1:
        path.append(current)
        next_city = parent[mask][current]
        mask ^= (1 << current)  # 从mask中移除当前城市
        current = next_city
    
    path.reverse()
    path.append(0)  # 回到起点
    
    return min_cost, path

def tsp_dp_by_subset_size(graph):
    """
    按照伪代码的思路，按子集大小顺序处理
    """
    n = len(graph)
    from itertools import combinations
    
    # C[mask][i] 表示访问集合mask中的城市，当前在城市i的最短距离
    C = {}
    
    # 初始化：C({1}, 1) = 0
    C[(1, 0)] = 0
    
    # 按子集大小从2到n处理
    for s in range(2, n + 1):
        # 遍历所有大小为s且包含城市0的子集
        for subset in combinations(range(1, n), s - 1):
            S = (0,) + subset  # 包含城市0的子集
            mask = sum(1 << i for i in S)
            
            for j in S:
                if j == 0:  # 不能在起点结束（除了最后）
                    continue
                
                C[(mask, j)] = float('inf')
                
                # C(S,j) = min{C(S-{j}, i) + d_ij : i ∈ S, i ≠ j}
                for i in S:
                    if i != j:
                        prev_mask = mask ^ (1 << j)  # S - {j}
                        if (prev_mask, i) in C:
                            C[(mask, j)] = min(C[(mask, j)], 
                                             C[(prev_mask, i)] + graph[i][j])
    
    # 找最优解：min_j C({1,...,n}, j) + d_j1
    all_visited = (1 << n) - 1
    min_cost = float('inf')
    
    for j in range(1, n):
        if (all_visited, j) in C:
            cost = C[(all_visited, j)] + graph[j][0]
            min_cost = min(min_cost, cost)
    
    return min_cost

def tsp_greedy(graph):
    """
    贪心算法解决TSP问题（近似解）
    """
    n = len(graph)
    visited = [False] * n
    path = [0]  # 从城市0开始
    visited[0] = True
    total_cost = 0
    
    current = 0
    for _ in range(n - 1):
        min_dist = float('inf')
        next_city = -1
        
        # 找到最近的未访问城市
        for i in range(n):
            if not visited[i] and graph[current][i] < min_dist:
                min_dist = graph[current][i]
                next_city = i
        
        visited[next_city] = True
        path.append(next_city)
        total_cost += min_dist
        current = next_city
    
    # 回到起点
    total_cost += graph[current][0]
    path.append(0)
    
    return total_cost, path

# 示例使用
if __name__ == "__main__":
    # 示例图：4个城市的距离矩阵
    graph = [
        [0, 10, 15, 20],
        [10, 0, 35, 25],
        [15, 35, 0, 30],
        [20, 25, 30, 0]
    ]
    
    print("使用动态规划算法：")
    cost_dp, path_dp = tsp_dp(graph)
    print(f"最短路径长度: {cost_dp}")
    print(f"路径: {' -> '.join(map(str, path_dp))}")
    
    print("\n使用贪心算法：")
    cost_greedy, path_greedy = tsp_greedy(graph)
    print(f"路径长度: {cost_greedy}")
    print(f"路径: {' -> '.join(map(str, path_greedy))}")
    
    print("\n使用按子集大小顺序处理的动态规划算法：")
    cost_dp_subset, = tsp_dp_by_subset_size(graph)
    print(f"最短路径长度: {cost_dp_subset}")


def tsp_dp_by_subset_size(graph):
    n = len(graph) # 城市总数
    C = {} # memo

    # 起点C初始化
    C[(1, 0)] = 0

    