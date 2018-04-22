with open('input.txt') as inp:
    n = int(inp.readline())
    matrix = [list(map(int, inp.readline().split())) for j in range(n)]

def check(n, mtr):
    for i in range(n):
        for j in range(i, n):
            if i==j:
                if mtr[i][j] == 1:
                    return False
                continue

            if matrix[i][j] != matrix[j][i]:
                return False
    return True

with open('output.txt', 'w') as out:
    ans = check(n, matrix)
    if ans:
        out.write("YES")
    else:
        out.write("NO")