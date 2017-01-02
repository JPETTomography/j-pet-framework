#!/usr/bin/python
# -*- coding: utf-8 -*-

from xml.etree.ElementTree import ParseError
import xml.etree.ElementTree as ET
import glob
import sys

def parse():
    for infile in glob.glob('*.xml'):
        try:
            tree = ET.parse(infile)
            root = tree.getroot()
            if ((root.findall('.//FatalError'))!=[]):
                print "Error detectedA"
                sys.exit(1)
        except ParseError:
            print "The file xml isn't correct. There were some mistakes in the tests "
            sys.exit(1)
def main():
    parse()

if __name__ == '_main_':
    main()