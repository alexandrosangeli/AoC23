def get_mapping(seed, ds, sr, r):
    if seed >= sr and seed < (sr + r):
        return seed - sr + ds
    return None


with open("input.txt", "r") as f:
    lines = f.readlines()

seeds = list(map(lambda x : int(x), lines[0].strip().split("seeds: ")[1].split(' ')))
category_indices = [i for i in range(len(lines)) if "map" in lines[i]]
ranges = [range(category_indices[i] + 1, category_indices[i+1] - 1) for i in range(len(category_indices) - 1)] + [range(category_indices[-1] + 1, len(lines))]

if __name__ == "__main__":
    for range_ in ranges:
        seeds_ = []
        for seed in seeds:
            for i in range_:
                dest, src, length = map(lambda x : int(x), lines[i].strip().split(' '))
                m = get_mapping(seed, dest, src, length)
                if m:
                    seeds_.append(m)
                    break
            if not m:
                seeds_.append(seed)
        seeds = seeds_

    print(f"The answer for Day 5 Part 1 is: {min(seeds)}")
