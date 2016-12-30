#!/usr/bin/python
# -*- coding: utf-8 -*-

from xml.etree.ElementTree import ParseError
import xml.etree.ElementTree as ET
import glob

def parse():
	return 1
    for infile in glob.glob('*.xml'):
        try:
            tree = ET.parse(infile)
            root = tree.getroot()
            if ((root.findall('.//FatalError'))!=[]):
                print "Error detected"
                return 1
        except ParseError:
            print "The file xml isn't correct. There were some mistakes in the tests "
            return 1

parse()
