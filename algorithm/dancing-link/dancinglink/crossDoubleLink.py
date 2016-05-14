class CrossDoubleLinkNode(object):
    def __init__(self, val = None, down = None, right = None):
        if right is None:
            self.right = self
            self.left  = self
        else:
            self.right = right
            self.left  = right.left
            CrossDoubleLinkNode.rejoinRow(self) # child class main overload
                                                # this function. so use class
                                                # name, instead "self.rejoinRow()"
        if down is None:
            self.down = self
            self.up   = self
        else:
            self.down = down
            self.up   = down.up
            CrossDoubleLinkNode.rejoinCol(self)

        self.val = val

    def leaveRow(self):
        self.left.right = self.right
        self.right.left = self.left

    def rejoinRow(self):
        self.left.right = self
        self.right.left = self

    def leaveCol(self):
        self.up.down = self.down
        self.down.up = self.up

    def rejoinCol(self):
        self.up.down = self
        self.down.up = self

    def travel(self, direction, visitSelf = False, loopForever = False):
        if visitSelf:
            yield self

        node = getattr(self, direction)
        while node != self or loopForever:
            yield node
            node = getattr(node, direction)
