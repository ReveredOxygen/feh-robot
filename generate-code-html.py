#!/usr/bin/env python3

'''
Utility to generate the HTML for the Final Code page of the website
'''

import os
import glob
import html

from pygments import highlight
from pygments.lexers import get_lexer_by_name
from pygments.formatters import HtmlFormatter

headers = glob.glob("src/*.h")
headers.sort()

files = []

for h in headers:
    files += [h]
    cpp = h[:-1] + "cpp"
    if os.path.exists(cpp):
        files += [cpp]

files = ["src/main.cpp"] + files

lexer = get_lexer_by_name("c++", stripall=True)

with open("website.html", "w") as out:
    for filename in files:
        out.write("\n<br/>")
        with open (filename, "r") as input:
            formatter = HtmlFormatter(linenos="inline", filename=filename[4:], nobackground=True, noclasses=True, wrapcode=True, style="default")
            code = input.read()
            result = highlight(code, lexer, formatter)
            out.write(result)