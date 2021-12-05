with open('input.txt', 'w') as file:
    for _ in range(1000):
        for _ in range(1000):
            file.write('1000 ')
        file.write('\n')