"""
This is an optimised solution for Day 5 Part 2 which requires no guessing the initial start.
"""

from solution_part_one import get_mapping, lines, seeds, category_indices, ranges

final_dests = [int(l.split(' ')[0]) for l in lines[category_indices[-1] + 1:]]
seeds_ranges = [(seeds[i], seeds[i] + seeds[i+1] - 1) for i in range(0, len(seeds), 2)]

initial_range = max(final_dests) 
start = 0
increment = 100000


if __name__ == "__main__":
    while True:
        found = False

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
                    break

            if found: 
                initial_range = final_result
                break
            else:
                # track the greatest location values that mapped to no seeds
                start = final_result if final_result > start else start

        if increment == 1:
            break

        increment = max(increment // 10, 1)

    print(f"The answer for Day 5 Part 2 is: {final_result}")