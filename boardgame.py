from collections import deque

# Generate possible moves based on given x and y
def generate_moves(x, y):
    return [(x, y), (y, -x), (-y, x), (-x, -y)]

# Check if the next position is valid
def is_position_valid(grid, row, col):
    return (
        0 <= row < len(grid) and 
        0 <= col < len(grid[0]) and 
        grid[row][col] == 0
    )

# Perform BFS to find the shortest path
def shortest_path_bfs(grid, start, end, x, y):
    rows, cols = len(grid), len(grid[0])
    queue = deque([(start[0], start[1], 0)])  # (row, col, steps)
    visited = set()
    visited.add((start[0], start[1]))
    possible_moves = generate_moves(x, y)

    while queue:
        current_row, current_col, steps = queue.popleft()

        # Check if the destination is reached
        if (current_row, current_col) == (end[0], end[1]):
            return steps

        # Explore all possible moves
        for dx, dy in possible_moves:
            new_row, new_col = current_row + dx, current_col + dy
            if (
                is_position_valid(grid, new_row, new_col) and 
                (new_row, new_col) not in visited
            ):
                visited.add((new_row, new_col))
                queue.append((new_row, new_col, steps + 1))
    
    return -1  # If destination is unreachable

# Input dimensions of the grid
rows, cols = map(int, input().split())

# Input the grid itself
grid = [list(map(int, input().split())) for _ in range(rows)]

# Input source and destination coordinates
start_point = tuple(map(int, input().split()))
end_point = tuple(map(int, input().split()))

# Input movement parameters x and y
x_move, y_move = map(int, input().split())

# Output the shortest path using BFS
print(shortest_path_bfs(grid, start_point, end_point, x_move, y_move), end="")
