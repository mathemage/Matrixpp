#!/usr/bin/env python
import random
import sys
[h,w,d,u] = map(int, sys.argv[1:])
print h
print w
for i in xrange(h*w):
    print round(random.uniform(d, u), 2)
