#!/usr/bin/env python3
# -*- coding: utf-8 -*-

data = [2, 5, 1, 6, 4, 3]

a = 0
for i in range(1, len(data)):
    v = data[i]
    j = i - 1
    while j >= 0 and v < data[j]:
        data[j+1] = data[j]
        j = j - 1
    data[j+1] = v
    print(data)


if __name__ == '__main__':
    pass
