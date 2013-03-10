#!/usr/bin/env python
import random
(h,w) = (7,5)
(d,u) = (-50,50)
print h
print w
for i in xrange(h*w):
    print round(random.uniform(d, u), 2)
