#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import os

# This code copies the markdown documents in the /docs folder to the
# /localdocs folder, while converting image links to local links.
# Basically, it makes a version of the readme that can be viewed offline.

# generate the image map
# first, open the imgmap.txt
f = open("imgmap.txt",'r')
s = f.read().split('\n')
f.close()

# Now lets generate a list
imgmap = []
for i in s:
    if i != '':
        imgmap += [i.split(' ')]

# Now let's loop through all of the .md files in /docs and copy to /localdocs
for root, dirs, files in os.walk(os.path.join("..", "docs")):
    for file in files:
        if file.endswith(".md"):
            fn = os.path.join(root, file)
            f = open(fn,'r')
            s = f.read()
            f.close()
            for i in imgmap:
                s=s.replace(i[0],"img/"+i[1])
            f = open(fn.replace("docs","localdocs"),'w')
            f.write(s)
            f.close()
