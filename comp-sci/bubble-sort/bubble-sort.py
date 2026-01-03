import os
import random


def bubble_sort(data:list):
    """
    In-Place sort.
    """
    for i in range(len(data)):
        for j in range(0, len(data) -i-1):
            if data[j] > data[j+1]:
                data[j], data[j+1] = data[j+1], data[j]
                
    
if __name__ == '__main__':
    data = list( range(1, 100))
    random.shuffle(data)

    data = data[:10]    # For test, only 10  random numbers
    print(f"Before Sort: {data}")
    bubble_sort(data)
    print(f"After  Sort: {data}")
    
