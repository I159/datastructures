#! /usr/bin/env python
"""Binary tree.
Implemented by Pekelny 'I159' Ilya.
"""


class Node(object):
    """Base node class."""
    data = left = right = None

    def __init__(self, data):
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

    def _direct(self, value):
        if value > self:
            return self.right
        return self.left

    def insert(self, value):
        if self.data == None:
            self.data = value
        else:
            child = self._direct(value)
            if child:
                child.insert(value)
            else:
                child = Node(value)
        return self


    def lookup(self, value, entry=None):
        entry = entry or self
        if value == entry:
            return entry
        else:
            child = entry._direct(value)
            return child.lookup(value, child)

    def delete(self, value):
        expel = self.lookup(value)
        if expel.left == None == expel.right:
            del expel
        elif expel.right:
            child = expel.right
            while child.left:
                child = child.left
            expel = child
        elif expel.left:
            expel = expel.left
        return self


class BTree(object):
    """Base binary tree class.
    ::attr root: entry point to all the tree operations.
    """
    root = None
    current = None

    def __init__(self, *args):
        for i in args:
            self.insert(i)

    def __str__(self):
        string = ""
        for i in self:
            string += i
        return string

    def __iter__(self):
        return self

    def next(self):
        raise NotImplementedError("Need to implement algorithm "
                "to display tree like structure")

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
        self.root.delete(value)
        return self
