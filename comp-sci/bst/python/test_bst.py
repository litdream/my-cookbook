import pytest
from bst import BST, Node


class TestBSTBasics:
    def test_empty_tree_creation(self):
        bst = BST()
        assert bst.root is None

    def test_insert_root(self):
        bst = BST()
        bst.insert(10)
        assert bst.root is not None
        assert bst.root.data == 10
        assert bst.root.left is None
        assert bst.root.right is None


class TestInsert:
    def test_insert_left_child(self):
        bst = BST()
        bst.insert(10)
        bst.insert(5)
        assert bst.root.left.data == 5

    def test_insert_right_child(self):
        bst = BST()
        bst.insert(10)
        bst.insert(15)
        assert bst.root.right.data == 15

    def test_insert_multiple_nodes(self):
        bst = BST()
        values = [10, 5, 15, 3, 7, 12, 20]
        for val in values:
            bst.insert(val)

        assert bst.root.data == 10
        assert bst.root.left.data == 5
        assert bst.root.right.data == 15
        assert bst.root.left.left.data == 3
        assert bst.root.left.right.data == 7
        assert bst.root.right.left.data == 12
        assert bst.root.right.right.data == 20

    def test_insert_duplicate_raises_error(self):
        bst = BST()
        bst.insert(10)
        with pytest.raises(KeyError, match="Duplicate data exists in BST"):
            bst.insert(10)


class TestExists:
    def test_exists_empty_tree(self):
        bst = BST()
        assert bst.exists(10) is False

    def test_exists_root_only(self):
        bst = BST()
        bst.insert(10)
        assert bst.exists(10) is True
        assert bst.exists(5) is False

    def test_exists_multiple_nodes(self):
        bst = BST()
        values = [10, 5, 15, 3, 7, 12, 20]
        for val in values:
            bst.insert(val)

        for val in values:
            assert bst.exists(val) is True

        assert bst.exists(1) is False
        assert bst.exists(6) is False
        assert bst.exists(25) is False


class TestMinMax:
    def test_minimum(self):
        bst = BST()
        values = [10, 5, 15, 3, 7, 12, 20]
        for val in values:
            bst.insert(val)
        assert bst.minimum() == 3

    def test_minimum_root_only(self):
        bst = BST()
        bst.insert(10)
        assert bst.minimum() == 10

    def test_maximum(self):
        bst = BST()
        values = [10, 5, 15, 3, 7, 12, 20]
        for val in values:
            bst.insert(val)
        assert bst.maximum() == 20

    def test_maximum_root_only(self):
        bst = BST()
        bst.insert(10)
        assert bst.maximum() == 10


class TestTraversals:
    def test_inorder_traverse(self):
        bst = BST()
        values = [10, 5, 15, 3, 7, 12, 20]
        for val in values:
            bst.insert(val)
        assert bst.inorder_traverse() == [3, 5, 7, 10, 12, 15, 20]

    def test_inorder_empty_tree(self):
        bst = BST()
        assert bst.inorder_traverse() == []

    def test_preorder_traverse(self):
        bst = BST()
        values = [10, 5, 15, 3, 7, 12, 20]
        for val in values:
            bst.insert(val)
        assert bst.preorder_traverse() == [10, 5, 3, 7, 15, 12, 20]

    def test_postorder_traverse(self):
        bst = BST()
        values = [10, 5, 15, 3, 7, 12, 20]
        for val in values:
            bst.insert(val)
        assert bst.postorder_traverse() == [3, 7, 5, 12, 20, 15, 10]


class TestHeight:
    def test_height_empty_tree(self):
        bst = BST()
        assert bst.height() == -1

    def test_height_single_node(self):
        bst = BST()
        bst.insert(10)
        assert bst.height() == 0

    def test_height_balanced_tree(self):
        bst = BST()
        values = [10, 5, 15, 3, 7, 12, 20]
        for val in values:
            bst.insert(val)
        assert bst.height() == 2

    def test_height_unbalanced_tree(self):
        bst = BST()
        values = [10, 9, 8, 7, 6]
        for val in values:
            bst.insert(val)
        assert bst.height() == 4


class TestSize:
    def test_size_empty_tree(self):
        bst = BST()
        assert bst.size() == 0

    def test_size_single_node(self):
        bst = BST()
        bst.insert(10)
        assert bst.size() == 1

    def test_size_multiple_nodes(self):
        bst = BST()
        values = [10, 5, 15, 3, 7, 12, 20]
        for val in values:
            bst.insert(val)
        assert bst.size() == 7


##        
## UNITTEST: Written by CLAUDE
##
        
## class TestDelete:
##     """Test cases for delete method - implement these after writing delete()"""

##     def test_delete_from_empty_tree(self):
##         bst = BST()
##         with pytest.raises(KeyError):
##             bst.delete(10)

##     def test_delete_nonexistent_value(self):
##         bst = BST()
##         bst.insert(10)
##         with pytest.raises(KeyError):
##             bst.delete(5)

##     def test_delete_leaf_node(self):
##         bst = BST()
##         values = [10, 5, 15, 3, 7, 12, 20]
##         for val in values:
##             bst.insert(val)

##         bst.delete(3)
##         assert bst.exists(3) is False
##         assert bst.inorder_traverse() == [5, 7, 10, 12, 15, 20]

##     def test_delete_node_with_one_child_left(self):
##         bst = BST()
##         values = [10, 5, 15, 3]
##         for val in values:
##             bst.insert(val)

##         bst.delete(5)
##         assert bst.exists(5) is False
##         assert bst.inorder_traverse() == [3, 10, 15]

##     def test_delete_node_with_one_child_right(self):
##         bst = BST()
##         values = [10, 5, 15, 20]
##         for val in values:
##             bst.insert(val)

##         bst.delete(15)
##         assert bst.exists(15) is False
##         assert bst.inorder_traverse() == [5, 10, 20]

##     def test_delete_node_with_two_children(self):
##         bst = BST()
##         values = [10, 5, 15, 3, 7, 12, 20]
##         for val in values:
##             bst.insert(val)

##         bst.delete(5)
##         assert bst.exists(5) is False
##         assert bst.inorder_traverse() == [3, 7, 10, 12, 15, 20]
##         assert bst.size() == 6

##     def test_delete_root_node_leaf(self):
##         bst = BST()
##         bst.insert(10)
##         bst.delete(10)
##         assert bst.root is None
##         assert bst.size() == 0

##     def test_delete_root_node_with_children(self):
##         bst = BST()
##         values = [10, 5, 15, 3, 7, 12, 20]
##         for val in values:
##             bst.insert(val)

##         bst.delete(10)
##         assert bst.exists(10) is False
##         assert bst.inorder_traverse() == [3, 5, 7, 12, 15, 20]
##         assert bst.size() == 6

##     def test_delete_multiple_nodes(self):
##         bst = BST()
##         values = [10, 5, 15, 3, 7, 12, 20]
##         for val in values:
##             bst.insert(val)

##         bst.delete(3)
##         bst.delete(7)
##         bst.delete(20)

##         assert bst.inorder_traverse() == [5, 10, 12, 15]
##         assert bst.size() == 4

##     def test_delete_preserves_bst_property(self):
##         bst = BST()
##         values = [50, 30, 70, 20, 40, 60, 80]
##         for val in values:
##             bst.insert(val)

##         bst.delete(30)
##         result = bst.inorder_traverse()
##         assert result == sorted(result)
