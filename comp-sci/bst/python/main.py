from bst import BST


def main():
    bst = BST()

    print("Binary Search Tree Demo")
    print("-" * 40)

    values = [50, 30, 70, 20, 40, 60, 80]
    print(f"Inserting values: {values}")
    for value in values:
        bst.insert(value)

    print(f"\nInorder traverse: {bst.inorder_traverse()}")
    print(f"Preorder traverse: {bst.preorder_traverse()}")
    print(f"Postorder traverse: {bst.postorder_traverse()}")

    print(f"\nTree height: {bst.height()}")
    print(f"Tree size: {bst.size()}")
    print(f"Minimum value: {bst.minimum()}")
    print(f"Maximum value: {bst.maximum()}")

    search_value = 40
    print(f"\nSearching for {search_value}: {bst.exists(search_value)}")
    search_value = 100
    print(f"Searching for {search_value}: {bst.exists(search_value)}")

    # TODO:
    #  - Write a test code for deletion


if __name__ == "__main__":
    main()
