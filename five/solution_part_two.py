"""
The code below is not the most optimal and I did use some trial and error to find the solution (and some guessing).

How I landed on the correct answer:
- After some trial and error and some optimisation, I've managed to find a possible solution which was 20191110. 
- I then searched the space from `0` to `20,000,000` using increments of 10 and found no solution, so I (guessed that the solution is larger than this) used 20 million as the starting point.
- I then used the possible answer from above (`20191110`) as the maximum possible answer and using an increment of `1` starting from 20 million up to `20191110`, I found the correct answer which is `20191102`.
- Note: The script needs a few seconds to run.
"""

from solution_part_one import get_mapping, lines, seeds, category_indices, ranges

final_dests = [int(l.split(' ')[0]) for l in lines[category_indices[-1] + 1:]]
seeds_ranges = [(seeds[i], seeds[i] + seeds[i+1] - 1) for i in range(0, len(seeds), 2)]

# start = 0 # Initially started from 0
# initial_range = max(final_dests) # Used this initially before I found a smaller possible solution

start = 20_000_000
initial_range = 20191110  # Initial range to start the search
increment = 100000


if __name__ == "__main__":
    while True:

        found = False
        print(f"Range: {initial_range}, Increment: {increment}")

        for final_result in range(start, initial_range, increment):
            var = final_result
            for range_ in ranges[::-1]:
                for i in range_:
                    dest, src, length = map(lambda x : int(x), lines[i].strip().split(' '))
                    m = get_mapping(var, src, dest, length)
                    if m:
                        var = m
                        break

            for seed_range in seeds_ranges:
                if var >= seed_range[0] and var <= seed_range[1]:
                    found = True
                    print(f"The answer for Day 5 Part 2 is: {final_result}")
                    break

            if found: 
                initial_range = final_result
                break

        if increment == 1:
            break

        increment = max(increment // 10, 1)