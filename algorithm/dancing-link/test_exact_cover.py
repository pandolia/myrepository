import dancinglink

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
for solution in dancinglink.solve(matrixRows, matrixWidth):
    print solution
