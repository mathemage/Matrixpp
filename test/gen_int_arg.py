#!/usr/bin/env python
import random
import sys
[h,w,d,u] = map(int, sys.argv[1:])
print h
print w
for i in xrange(h*w):
    x = random.randint(d, u)
    print x,
    if (u-d) % w == x % w:
        print
