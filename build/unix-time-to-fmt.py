#!/usr/bin/env python3
"""
Usage:

  unix-time-to-fmt.py 1234567 [%Y-%m-%d[...]]

Convert unix timestamp to a string of the given format in UTC, according to
  https://docs.python.org/2/library/time.html
Default is '%Y-%b-%d' --> 2016-Jan-01
"""

import sys, time

if len(sys.argv) == 1:
    print("unknown")
    exit(0)

fmt = '%Y-%b-%d'
if len(sys.argv) > 2:
  fmt = sys.argv[2]

print(time.strftime(fmt, time.gmtime(float(sys.argv[1]))))
