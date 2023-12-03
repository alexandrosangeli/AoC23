import re
import math

pattern = re.compile(r"(\d)+")

grid = []
symbols = '#$%&*+-/=@'

with open("input.txt", "r") as f:
    # unique_chars = ''.join(sorted(list(set(f.read())))) # '\n#$%&*+-./0123456789=@'
    for line in f.readlines():
        grid.append(list(line.strip()))

if __name__ == "__main__":
    sum = 0
    for i, line in enumerate(grid):
        for elt in pattern.finditer(''.join(line)):
            start, stop = elt.span()
            has_symbol = False
            number = int(''.join(line[start:stop]))
            for j in range(start, stop):
                up = max(0, i-1)
                down = min(len(grid)-1, i+1)
                left = max(0, j-1)
                right = min(len(grid[0])-1, j+1)
                if \
                    grid[up][j] in symbols or \
                    grid[down][j] in symbols or \
                    grid[i][left] in symbols or \
                    grid[i][right] in symbols or \
                    grid[up][left] in symbols or \
                    grid[up][right] in symbols or \
                    grid[down][left] in symbols or \
                    grid[down][right] in symbols:
                    has_symbol = True
                    break
            if has_symbol:
                sum += number

    print(f"The answer for Day 3 Part 1 is: {sum}")

    gears = {} # tuple position : {numbers}
    for i, line in enumerate(grid):
        for elt in pattern.finditer(''.join(line)):
            start, stop = elt.span()
            number = int(''.join(line[start:stop]))
            for j in range(start, stop):
                up = max(0, i-1)
                down = min(len(grid)-1, i+1)
                left = max(0, j-1)
                right = min(len(grid[0])-1, j+1)
                if grid[up][j] == '*' :
                    gears[(up, j)] = gears.get((up, j), set()).union({number})
                if grid[down][j] == '*' :
                    gears[(down, j)] = gears.get((down, j), set()).union({number})
                if grid[i][left] == '*' :
                    gears[(i, left)] = gears.get((i, left), set()).union({number})
                if grid[i][right] == '*' :
                    gears[(i, right)] = gears.get((i, right), set()).union({number})
                if grid[up][left] == '*' :
                    gears[(up, left)] = gears.get((up, left), set()).union({number})
                if grid[up][right] == '*' :
                    gears[(up, right)] = gears.get((up, right), set()).union({number})
                if grid[down][left] == '*' :
                    gears[(down, left)] = gears.get((down, left), set()).union({number})
                if grid[down][right] == '*' :
                    gears[(down, right)] = gears.get((down, right), set()).union({number})

    ratio_sum = 0

    for nums in gears.values():
        if len(nums) == 2:
            ratio_sum += math.prod(list(nums))

    print(f"The answer for Day 3 Part 2 is: {ratio_sum}")


