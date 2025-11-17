#!/usr/bin/env python3

import os, sys, random


def gen_number():
    while True:
        rtn = []
        rtn.append( random.randint(1,9))
        rtn.append( random.randint(1,9))
        rtn.append( random.randint(1,9))
        if len(rtn) == len(set(rtn)):
            return rtn

def match(userinput: str, com: list) -> (int, int):
    """
    pre: userinput is 3 digit string
    """
    rtn = [0, 0]
    compare = [ int(d) for d in userinput ]
    for idx, digit in enumerate(compare):
        if digit == com[idx]:
            rtn[0] += 1

    allmatch = 0
    for digit in compare:
        if digit in com:
            allmatch += 1

    rtn[1] = allmatch - rtn[0]
    return tuple(rtn)


def main():
    com = gen_number()
    for i in range(1, 11):
        print(f"Round {i}:  Enter your guess: ", end="")
        userinput = input().strip()

        # TODO: validate

        bull, cow = match(userinput, com)
        if bull == 3:
            print(f"Great!   You got this in {i} rounds. : {com}")
            return

        print(f"{bull} bulls, {cow} cows")

    print(f"Sorry:  The number was {com}.")

if __name__ == '__main__':
    main()
