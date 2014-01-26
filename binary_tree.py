#! /usr/bin/env python
"""Binary tree.
"""


class ChildlessError(Exception):
    def __init__(self, node_name):
        super(ChildlessError, self).__init__(
                'The {} Node instance have no children.'.format(node_name))


class Node(object):
    """Base node class."""
    data = left = right = None

    def __init__(self, data=None):
        self.data = data

    def __lt__(self, other):
        return self.data < other

    def __gt__(self, other):
        return self.data > other

    def __eq__(self, other):
        return self.data == other

    def __repr__(self):
        return "<{}.{}({}) object at {}>".format(
                    self.__class__.__module__,
                    self.__class__.__name__,
                    self.data,
                    hex(id(self)))

    def insert(self, value):
        """Add new node with given value to a tree."""

        if self.data == None:
            self.data = value
        else:
            if self < value:
                if not self.right:
                    self.right = Node()
                child = self.right
            else:
                if not self.left:
                    self.left = Node()
                child = self.left

            if child:
                return child.insert(value)
            else:
                child = Node(value)

    def lookup(self, value, entry=None):
        """Search for particular value from existing nodes below the node."""

        entry = entry or self
        if value == entry:
            return entry
        else:
            child = self.right if self < value else self.left
            return child and child.lookup(value, child) or None

    def delete(self, value):
        """Node deletion and further regroup."""

        if self == value:
            if self.right:
                child = self.right
                relative = None
                while child.left:
                    relative = child
                    child = child.left
                self.data = child.data
                child.right and self.right.insert(child.right.data)
                if relative:
                    relative.left = None
                else:
                    self.right = None
            elif self.left:
                self.data = self.left.data
                self.right = self.left.right
                self.left = self.left.left
            else:
                raise ChildlessError
        else:
            child = self.right if self < value else self.left
            if child:
                child.delete(value)
            else:
                raise LookupError


class BTree(object):
    """Base binary tree class.
    ::root: Node instance, entry point to all the tree operations.
    ::current: list of nodes, describes tree level. Nedded for iteration.
    """
    root = None
    current = None

    def __init__(self, *args):
        for i in args:
            self.insert(i)

    def __str__(self):
        string = ""
        for i in self:
            string += str(i)
        return string

    def __iter__(self):
        return self

    def next(self):
        """Returns next downwardly tree level every next iteration."""

        if not self.current:
            self.current = [self.root,]
            return self.current
        nc = []
        for i in self.current:
            if i:
                i.left and nc.append(i.left)
                i.right and nc.append(i.right)
        self.current = nc
        if self.current:
            return self.current
        raise StopIteration

    def insert(self, other):
        if self.root == None:
            self.root = Node(other)
        else:
            self.root.insert(other)
        return self

    def lookup(self, value):
        try:
            return self.root.lookup(value)
        except AttributeError:
            raise LookupError("{} has no {} item".format(
                self.__class__, value))

    def delete(self, value):
        try:
            self.root.delete(value)
        except ChildlessError:
            self.root = None
        return self
