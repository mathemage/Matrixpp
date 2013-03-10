#!/usr/bin/env python
import random
(h,w) = (10,11)
(d,u) = (-1000,1000)
print h
print w
for i in xrange(h*w):
    x = random.randint(d, u)
    print x,
    if 0 == x % 5:
        print
