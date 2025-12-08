from maxheap import MaxHeap

def main():
    heap = MaxHeap()
    heap.insert(10)
    heap.insert(20)
    heap.insert(15)
    heap.insert(30)
    heap.insert(5)

    print(f"Heap size: {heap.size()}")
    print(f"Max element: {heap.peek()}")

    print("Extracting elements:")
    while heap.size() > 0:
        print(heap.extract_max())

if __name__ == "__main__":
    main()
