#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys, socket
if len(sys.argv) != 2:
    print 'Usage: %s <inet_address>' % sys.argv[0]
else:
    print socket.gethostbyname(sys.argv[1])
