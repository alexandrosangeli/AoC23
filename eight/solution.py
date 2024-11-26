from math import lcm


def main():
    with open("input.txt", "r") as f:
        lines = f.readlines()

    directions = lines[0].strip()
    no_steps =  len(directions)
    camel_map = {}

    for line in lines[1:]:
        val = line[:3]
        left = line[7:10]
        right = line[12:15]
        camel_map[val] = {'L' : left, 'R' : right}
        directions

    counter = 0
    current = 'AAA'
    i = 0
    while current != "ZZZ":
        step = directions[i]
        counter += 1
        current = camel_map[current][step]
        i = (i + 1) % no_steps 

    print(f"The answer for Day 8 Part 1 is: {counter}")


    starting_nodes = []
    for elt in camel_map.keys():
        if elt.endswith("A"):
            starting_nodes.append(elt)

    counters = []
    for current in starting_nodes:
        counter = 0
        i = 0
        while not current.endswith('Z'):
            step = directions[i]
            counter += 1
            current = camel_map[current][step]
            i = (i + 1) % no_steps 
        counters.append(counter)



    print(f"The answer for Day 8 Part 2 is: {lcm(*counters)}")

if __name__ == "__main__":
    main()