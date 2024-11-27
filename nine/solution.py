def main_(flag: bool) -> None:
    total = 0

    with open("input.txt", "r") as f:
        lines = f.readlines()

    for line in lines:
        numbers = line.split(' ')
        numbers = list(map(lambda x : int(x), numbers))

        if flag:
            numbers = numbers[::-1]

        curr = numbers[:]

        all_lists = [curr]

        while any(curr):
            curr = [curr[i]  - curr[i-1] for i in range(1, len(curr))]
            all_lists = [curr] + all_lists
        
        for i in range(1, len(all_lists)):
            all_lists[i].append(all_lists[i-1][-1] + all_lists[i][-1])
        total += all_lists[-1][-1]

    print(total)


def main() -> None:
    main_(False)
    main_(True)


if __name__== "__main__":
    main()