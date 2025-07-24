def shortest_reliable_path(graph, s, t, k):
    """
    从 s 走到 t，最多 k 条边，最短路径是多少？
    """
    n = len(graph) # 节点数量
    # 每个节点有k+1个状态（0-k条路径到达这个节点）
    dist = [ [float('inf')] * (k+1) for _ in graph ] 
    dist[s][0] = 0  # 起点初始化

    # 动态规划部分
    for num_edge in range(1, k + 1):
        for u in range(n): # 遍历每个节点 u
            for v, weight in graph[u]:
                if dist[u][num_edge - 1] + weight < dist[v][num_edge]:
                    dist[v][num_edge] = dist[u][num_edge - 1] + weight

    return min(dist[t])

# 测试图
graph = [
    [(1, 5), (2, 10)],  # 节点 0 的邻接表
    [(2, 3)],           # 节点 1 的邻接表
    [(3, 1)],           # 节点 2 的邻接表
    []                  # 节点 3 的邻接表
]

print(f"从节点 0 到节点 3 的最短路径长度: {shortest_reliable_path(graph, 0, 3, 3)}")
print(f"从节点 0 到节点 2，最多使用 2 条边: {shortest_reliable_path(graph, 0, 2, 2)}")
print(f"从节点 0 到节点 1，最多使用 1 条边: {shortest_reliable_path(graph, 0, 1, 1)}")
