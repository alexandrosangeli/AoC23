def prod(lst):
    result = 1
    for elt in lst:
        result *= elt
    return result

limits = {
    'red' : 12,
    'green' : 13,
    'blue' : 14
    }


if __name__ == "__main__":
    sum = 0
    with open("input.txt", "r") as f:
        for line in f.readlines():
            possible = True
            id, game_info = line.strip()[5:].split(':')
            game_sets = game_info.split(';')
            for set in game_sets:
                for cube_info in set.split(','):
                    num_cubes, colour = cube_info.strip().split(' ')
                    if int(num_cubes) > limits[colour]:
                        possible = False
                        break
            if possible:
                sum += int(id)

    print(f"The answer for Day 2 Part 1 is: {sum}")

    power_sum = 0
    with open("input.txt", "r") as f:
        for line in f.readlines():
            possible = True
            minimum_cubes = {
                'red' : 0,
                'green' : 0,
                'blue' : 0
                }
            id, game_info = line.strip()[5:].split(':')
            game_sets = game_info.split(';')
            for set in game_sets:
                for cube_info in set.split(','):
                    num_cubes, colour = cube_info.strip().split(' ')
                    if int(num_cubes) > minimum_cubes[colour]:
                        minimum_cubes[colour] = int(num_cubes)
            power_sum += prod(minimum_cubes.values())

    print(f"The answer for Day 2 Part 2 is: {power_sum}")