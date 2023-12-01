import re

spelled_numbers = ['zero', 'one', 'two','three', 'four', 'five', 'six', 'seven', 'eight', 'nine']
wtod = {w:i for i,w in enumerate(spelled_numbers)} # word to digit dict

def unpack(iterator):
    return [elt for elt in iterator]

def elts_to_list(elts):
    result = []
    for elt in elts:
        pos = elt.span()[0]
        digit = wtod[elt.group(1)]
        result.append((pos, str(digit))) # (position, digit)
    return result

pattern = re.compile(f"(?=({'|'.join([n for n in spelled_numbers])}))")


if __name__ == "__main__":
    with open("input.txt", "r") as f:
        sum = 0
        for line in f.readlines():
            digits = []
            for char in line:
                if char.isdigit():
                    digits.append(char)

            number = digits[0] + digits[-1]
            sum += int(number)

    print(f"The answer for Day 1 Part 1 is: {sum}")

    with open("input.txt", "r") as f:
        sum = 0
        for line in f.readlines():
            digits = []
            for i,char in enumerate(line):
                if char.isdigit():
                    digits.append((i, char)) # (position, digit)

            elts = elts_to_list(unpack(pattern.finditer(line)))
            digits += elts
            digits.sort(key=lambda x : x[0])

            number = digits[0][1] + digits[-1][1]

            sum += int(number)

    print(f"The answer for Day 1 Part 2 is: {sum}")