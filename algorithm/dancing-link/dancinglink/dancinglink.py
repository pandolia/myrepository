from crossDoubleLink import CrossDoubleLinkNode

MAX_INT = 2147483647

class MatrixHeadNode(CrossDoubleLinkNode):
    pass

class ColumnHeadNode(CrossDoubleLinkNode):
    def __init__(self, matrixHead, col):
        super(self.__class__, self).__init__(right = matrixHead)
        self.size = 0
        self.col  = col

    def cover(self):
        for node in self.travel('down'):
            for r_node in node.travel('right'):
                r_node.leaveCol()
        self.leaveRow()


    def uncover(self):
        self.rejoinRow()
        for node in self.travel('up'):
            for l_node in node.travel('left'):
                l_node.rejoinCol()

class BodyNode(CrossDoubleLinkNode):    
    def __init__(self, colHead, rowFirstNode, row):
        super(self.__class__, self).__init__(down = colHead, right = rowFirstNode)
        self.row = row
        self.colHead = colHead
        self.colHead.size += 1

    def leaveCol(self):
        super(self.__class__, self).leaveCol()
        self.colHead.size -= 1

    def rejoinCol(self):
        super(self.__class__, self).rejoinCol()
        self.colHead.size += 1

def buildMatrix(matrixRows, matrixWidth):
    matrixHead = MatrixHeadNode()

    colHeads = [ColumnHeadNode(matrixHead, col) for col in range(matrixWidth)]

    for row in range(len(matrixRows)):
        rowFirstNode = BodyNode(colHeads[matrixRows[row][0]], None, row)
        for col in matrixRows[row][1:]:
            BodyNode(colHeads[col], rowFirstNode, row)

    return matrixHead

def getShortestCol(matrixHead):
    min_size = MAX_INT
    for colHead in matrixHead.travel('right'):
        if colHead.size < min_size:
            min_col = colHead
            min_size = colHead.size
    return min_col

def _solve(matrixHead):
    if matrixHead.right == matrixHead:
        yield []
        return

    colHead = getShortestCol(matrixHead)

    if colHead.down == colHead:
        return

    colHead.cover()

    for node in colHead.travel('down'): # except colHead
        for r_node in node.travel('right'): # except node
            r_node.colHead.cover()

        for solution in _solve(matrixHead):
            yield solution + [node.row]

        for l_node in node.travel('left'): # except node
            l_node.colHead.uncover()

    colHead.uncover()

def solve(matrixRows, matrixWidth):
    for solution in _solve(buildMatrix(matrixRows, matrixWidth)):
        yield sorted(solution)
    
if __name__ == '__main__':
    # matrixRows and matrixWidth represent matrix below:
    #   [[0, 0, 1, 0, 1, 1, 0],
    #    [1, 0, 0, 1, 0, 0, 1],
    #    [0, 1, 1, 0, 0, 1, 0],
    #    [1, 0, 0, 1, 0, 0, 0],
    #    [0, 1, 0, 0, 0, 0, 1],
    #    [0, 0, 0, 1, 1, 0, 1]]
    # each j in matrixRows[i] means matrix[i][j] = 1
    matrixRows = [ 
        [2, 4, 5],
        [0, 3, 6],
        [1, 2, 5],
        [0, 3],
        [1, 6],
        [3, 4, 6]
    ]
    matrixWidth = 7
    for solution in solve(matrixRows, matrixWidth):
        print solution
