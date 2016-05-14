# -*- coding: utf-8 -*-
"""
Created on Wed Dec 03 18:37:28 2014

@author: huang_cj2
"""

"""
Sudoku problem's subject conditions:
Type A:
     0) grid(0, 0) has a number
     1) grid(0, 1) has a number
        ...
    NA) grid(x, y) has a number, NA = x * 9 + y
        ...
    80) grid(8, 8) has a number
    
Type B:
    81) row 0 has number 0
    82) row 0 has number 1
        ...
    89) row 0 has number 8
    90) row 1 has number 0
        ...        
    NB) row x has number num, NB = x*9+num+81
        ...
   161) row 8 has number 8

Type C:
   162) col 0 has number 0
   163) col 0 has number 1
        ...
    NC) col y has number num, NC = y*9+num+162
        ...
   242) col 8 has number 8

Type D:
   243) box 0 has number 0
   244) box 0 has number 1
        ...
    ND) box b has number num, ND = b*9+num+243, b = int(y/3)*3 + int(x/3)
        ...
   323) box 8 has number 8

If all 324 subject conditions listed above are satisfied, 
and each condition is satisfied only once, Then we
find a valid solution of sudoku.

So we can convert sudoku problem to exact cover problem.

Consider "grid(x, y) has number num" is a state,
there are 9*9*9 = 729 kinds of states. Each state can 
satisfied 4 subject conditions above.

So, all we need to do is finding some states, to satisfy
all the 324 subject conditions above, and each condition
is satified only once.

Now consider the exact cover matrix, we build a matrix
with 324 columns: Mat[m][324]. It has 0s and 1s. Each 
row represents 1 state. And Mat[row][N] == 1 means that 
the state this row represents satisfy the condition N.

So, we need to find a set of rows containing exactly 
one 1 in each column.
"""

EMPTYCELL = ord('.') - ord('1')

# return conditions' Ids satisfied by 
# state "grid(x, y) has number num"
def columnsIds(x, y, num):
    NA = x * 9 + y
    NB = x * 9 + num + 81
    NC = y * 9 + num + 162
    ND = ((y/3)*3 + x/3) * 9 + num + 243
    return [NA, NB, NC, ND]

# return exact cover matrix's 
# matrixRows, matrixWidt
def makeMatrix(board):
    matrixRows = []
    for x in range(9):
        for y in range(9):
            if board[x][y] != EMPTYCELL:
                matrixRows.append(columnsIds(x, y, board[x][y]))
            else:
                for num in range(9):
                    matrixRows.append(columnsIds(x, y, num))
    
    sudokuMatrixWidth = 324
    
    return matrixRows, sudokuMatrixWidth

def translate(solution, matrixRows):
    board = [[0 for x in range(9)] for y in range(9)]
    for row in solution:
        NA, NB, NC, ND = matrixRows[row]
        x = NA / 9
        y = NA % 9
        num = NB - NA - 81 + y
        board[x][y] = num    
    return board

def show(board):
    for i, row in enumerate(board):
        if i % 3 == 0:
            print '++===+===+===++===+===+===++===+===+===++'
        else:
            print '++---+---+---++---+---+---++---+---+---++'
        s = '||'
        for j, x in enumerate(row):
            if x != EMPTYCELL:
                s += ' '+ str(x+1) + ' |'
            else:
                s += '   |'
            if j % 3 == 2:
                s += '|'
        print s
    print '++===+===+===++===+===+===++===+===+===++\n'

def solve_sudoku(board):    
    from dancinglink import solve

    board = [[ord(ch) - ord('1') for ch in row.strip()] \
                                for row in board.split('\n')]

    print 'the sudoku puzzle:'
    show(board)
    matrixRows, matrixWidth = makeMatrix(board)
    for solution in solve(matrixRows, matrixWidth):
        print 'solution:'
        show(translate(solution, matrixRows))
    
if __name__ == '__main__':
    # board = """8........
    #            ..36.....
    #            .7..9.2..
    #            .5...7...
    #            ....457..
    #            ...1...3.
    #            ..1....68
    #            ..85...1.
    #            .9....4.."""
    board = """53..7....
               6..195...
               .98....6.
               8...6...3
               4..8.3..1
               7...2...6
               .6....28.
               ...419..5
               ....8..79"""
    solve_sudoku(board)
