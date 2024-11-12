#Write a program to solve a 0-1 Knapsack problem using dynamic programming or branch and bound strategy

def knapsack(items, capacity):
    n = len(items)
    dp = [[0] * (capacity + 1) for i in range(n + 1)]
    
    for i in range(1, n + 1):
        weight, profit = items[i - 1]
        for w in range(capacity + 1):
            if weight <= w:
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weight] + profit)
            else:
                dp[i][w] = dp[i - 1][w]
    
    return dp[n][capacity]

n = int(input("Enter number of items: "))
items = []

for i in range(n):
    weight = int(input("Enter weight of item" + str(i + 1)+ ": "))
    profit = int(input(f"Enter profit of item" + str(i + 1)+ ": "))
    items.append((weight, profit))

capacity = int(input("Enter capacity: "))

print("Maximum Profit:", knapsack(items, capacity))
