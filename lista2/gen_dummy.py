#!/bin/env python3

from datetime import datetime
from os import system

today = datetime.today()
m = today.strftime("%m")
d = int(today.strftime("%d"))
hm = '1200'

for i in range(10):
    filename = 'dummy' + str(i).zfill(2)
    system('echo lorem ipsum > ' + filename)
    system('touch -t ' + m + str(d - i) + hm + ' ' + filename)
