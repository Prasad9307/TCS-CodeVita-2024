from collections import defaultdict

def identify_connected_blocks(grid, rows, cols):
    block_map = defaultdict(set)
    visited_cells = set()

    def depth_first_search(x, y, block_id):
        if (x, y) in visited_cells or x < 0 or x >= rows or y < 0 or y >= cols or grid[x][y] != block_id:
            return
        
        visited_cells.add((x, y))
        block_map[block_id].add((x, y))
        
        for nx, ny in [(x+1, y), (x-1, y), (x, y+1), (x, y-1)]:
            depth_first_search(nx, ny, block_id)

    for i in range(rows):
        for j in range(cols):
            if (i, j) not in visited_cells:
                depth_first_search(i, j, grid[i][j])

    return block_map

def calculate_dependencies(block_map, rows, cols, target_block):
    """
    Determine the number of blocks to remove to access the target block.
    """
    block_top_rows = {}
    for block_id, positions in block_map.items():
        block_top_rows[block_id] = min(x for x, y in positions)
    
    target_positions = block_map[target_block]
    target_top_row = block_top_rows[target_block]
    blocks_to_clear = set()
    
    for block_id, positions in block_map.items():
        if block_id == target_block:
            continue
        
        block_top_row = block_top_rows[block_id]
        if block_top_row <= target_top_row:
            target_columns = {y for x, y in target_positions}
            block_columns = {y for x, y in positions}
            
            if target_columns & block_columns:
                blocks_to_clear.add(block_id)
    
    return len(blocks_to_clear)

def solve_extraction_problem():
    rows, cols = map(int, input().split())
    
    grid = []
    for _ in range(rows):
        grid.append(list(map(int, input().split())))
    
    target_block = int(input())
    
    block_map = identify_connected_blocks(grid, rows, cols)
    result = calculate_dependencies(block_map, rows, cols, target_block)
    print(result)

if __name__ == "__main__":
    solve_extraction_problem()
