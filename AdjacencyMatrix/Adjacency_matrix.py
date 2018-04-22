with open('input.txt') as inp:
    n, m = map(int, inp.readline().split())
    matrix = [[0 for i in range(n)] for j in range(n)]
    for _ in range(m):
        n, m = map(int, inp.readline().split())
        matrix[n-1][m-1]+=1

with open('output.txt', 'w') as out:
    out.writelines(' '.join(str(j) for j in i) + '\n' for i in matrix)