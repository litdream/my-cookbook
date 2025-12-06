import os

class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

class BST:
    def __init__(self):
        self.root:Node = None

    def insert(self, data):
        if self.root is None:
            self.root = Node(data)
        else:
            self._insert(self.root, data)
    def _insert(self, cur:Node, data):
        if data < cur.data:
            if cur.left is None:
                cur.left = Node(data)
            else:
                self._insert(cur.left, data)
        elif data > cur.data:
            if cur.right is None:
                cur.right = Node(data)
            else:
                self._insert(cur.right, data)
        else:
            raise KeyError("Duplicate data exists in BST.")

    def exists(self, data) -> bool:
        return self._exists(self.root, data)
    def _exists(self, cur, data) -> bool:
        if cur is None:
            return False
        if cur.data == data:
            return True
        elif data < cur.data:
            return self._exists(cur.left, data)
        else:
            return self._exists(cur.right, data)

    def delete(self, data):
        pass

    def minimum(self):
        cur = self.root
        while cur.left is not None:
            cur = cur.left
        return cur.data

    def maximum(self):
        cur = self.root
        while cur.right is not None:
            cur = cur.right
        return cur.data

    def inorder_traverse(self) -> list:
        result = []    # ref will be passed around to collect
        self._inorder(self.root, result)
        return result
    def _inorder(self, cur:Node, result):
        if cur is not None:
            self._inorder(cur.left, result)
            result.append(cur.data)
            self._inorder(cur.right, result)

    def preorder_traverse(self) -> list:
        result = []
        self._preorder(self.root, result)
        return result
    def _preorder(self, cur:Node, result):
        if cur is not None:
            result.append(cur.data)
            self._preorder(cur.left, result)
            self._preorder(cur.right, result)

    def postorder_traverse(self) -> list:
        result = []
        self._postorder(self.root, result)
        return result
    def _postorder(self, cur:Node, result):
        if cur is not None:
            self._postorder(cur.left, result)
            self._postorder(cur.right, result)
            result.append(cur.data)

    def height(self) -> int:
        return self._height(self.root)
    def _height(self, node) -> int:
        if node is None:
            return -1
        left_height = self._height(node.left)
        right_height = self._height(node.right)
        return 1 + max(left_height, right_height)

    def size(self):
        return len(self.inorder_traverse())
    
        
