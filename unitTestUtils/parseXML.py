#!/usr/bin/python
# -*- coding: utf-8 -*-

from __future__ import print_function
from xml.etree.ElementTree import ParseError
import xml.etree.ElementTree as ET
import glob
import sys

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def parseXmlReports():
  all_errors = []
  for infile in glob.glob('*.xml'):
    try:
      tree = ET.parse(infile)
      root = tree.getroot()
      errors = root.findall('.//FatalError')
      exceptions = root.findall('.//Exception')
      all_errors = all_errors + errors + exceptions
    except ParseError:
      eprint("The file format of:"+infile+" is not a correct xml. There were some mistakes in the tests ")
      sys.exit(1)
  if all_errors:
    for occur in all_errors:
      eprint("*******************")
      eprint("type: " +occur.tag)
      eprint("message: "+occur.text)
      eprint("additional message: " + str(occur.attrib))
      for subInfo in occur:
        eprint("info:" +subInfo.tag)
        eprint("additional info: " + str(subInfo.attrib))
    return False 
  return True

def main():
  res = parseXmlReports()
  if not res:
    sys.exit(1)
    
if __name__ == '__main__':
    main()
