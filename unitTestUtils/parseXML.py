#!/usr/bin/python
# -*- coding: utf-8 -*-

from __future__ import print_function
from xml.etree.ElementTree import ParseError
import xml.etree.ElementTree as ET
import glob
import sys

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def parse():
    for infile in glob.glob('*.xml'):
        try:
            tree = ET.parse(infile)
            root = tree.getroot()
            if root.findall('.//FatalError'):
                eprint("Error detected")
        except ParseError:
            eprint("The file xml isn't correct. There were some mistakes in the tests ")

parse()
