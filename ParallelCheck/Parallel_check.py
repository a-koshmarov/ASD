with open('input.txt') as inp:
    n, m = map(int, inp.readline().split())
    edges = []
    ans = False
    for _ in range(m):
        pair = list(map(int, inp.readline().split()))
        if sorted(pair) not in edges:
            edges.append(sorted(pair))
        else:
            ans = True
            break

with open('output.txt', 'w') as out:
    if ans:
        out.write("YES")
    else:
        out.write("NO")