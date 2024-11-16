def minimum_moves(instructions):
    directions = ["up", "down", "left", "right"]
    num_steps = len(instructions)
    
    # Initialize a 3D DP array with infinity
    dp = [[[float('inf')] * 4 for _ in range(4)] for _ in range(num_steps + 1)]
    
    # Base case: No moves required at step 0
    for i in range(4):
        for j in range(4):
            dp[0][i][j] = 0

    # Fill the DP table
    for k in range(1, num_steps + 1):
        current_direction = directions.index(instructions[k - 1])  # Get the index of the current instruction
        for left_foot in range(4):
            for right_foot in range(4):
                if dp[k - 1][left_foot][right_foot] != float('inf'):
                    # Case 1: No move required
                    if current_direction == left_foot or current_direction == right_foot:
                        dp[k][left_foot][right_foot] = min(dp[k][left_foot][right_foot], dp[k - 1][left_foot][right_foot])
                    else:
                        # Case 2: Move left foot or right foot
                        dp[k][left_foot][right_foot] = min(
                            dp[k][left_foot][right_foot],
                            dp[k - 1][current_direction][right_foot] + 1,  # Move left foot
                            dp[k - 1][left_foot][current_direction] + 1   # Move right foot
                        )

    # Find the minimum moves in the last step
    min_moves = float('inf')
    for left_foot in range(4):
        for right_foot in range(4):
            min_moves = min(min_moves, dp[num_steps][left_foot][right_foot])
    
    return min_moves

if __name__ == "__main__":
    m = int(input("Enter the number of steps: ").strip())
    instructions = [input("Enter direction (up/down/left/right): ").strip() for _ in range(m)]
    result = minimum_moves(instructions)
    print(f"Minimum moves required: {result}")
