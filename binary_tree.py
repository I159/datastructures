#! /usr/bin/env python
"""Binary tree.
Implemented by Pekelny 'I159' Ilya.
"""


class Node(object):
    """Base node class."""
    data, left, right = None

    def __init__(self, data):
        self.data = data

    def _direct(self, value):
        if value > self:
            return self.right
        return self.left

    def insert(self, value):
        if self.data == None:
            self.data = value
            return self
        child = self._direct(value)
        child.insert(value)

    def lookup(self, value, entry=None):
        entry = entry or self
        if value == entry:
            return entry
        else:
            child = self._direct(value)
            return self.lookup(value, child)

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
    """Base binary tree class
    """
    root = None

    def __init__(self, *args):
        self.root = Node(args.pop(0))
        for i in args:
            self.insert(Node(i))

    def insert(self, other):
        self.root.insert(other)
        return self

    def lookup(self, value):
        return self.root.lookup(value)

    def delete(self, value):
        self.root.delete(value)
        return self
