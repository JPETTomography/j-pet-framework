# -*- coding: utf-8 -*-
# Change the content of file with content from another file

import sys

g_sourceFile = ''
g_destinationFile = '../Config/configDB.cfg'


def getValueFromInput(p_argv):

  global g_sourceFile
  global g_destinationFile

  l_lenOfArgv = len(p_argv)

  if l_lenOfArgv < 2:
    sys.exit('Nothing to do:-(')
  elif l_lenOfArgv == 2:
    g_sourceFile = p_argv[1]
  elif l_lenOfArgv == 3:
    g_sourceFile = p_argv[1]
    g_destinationFile = p_argv[2]

def changeContentOfFileFromAnotherFile(p_sourceFile, p_destinationFile):
  
  p_sourceFile = '../Config/' + p_sourceFile
  
  try:
    sourceContent = open(p_sourceFile, 'r').read()
  except Exception, e:
    raise
    
  try:
    with open(p_destinationFile) as f:
      destinationContent = f.read()
  except Exception, e:
    raise
    
  # change the content of destination file
  destinationContent = sourceContent

  try:
    with open(p_destinationFile, 'w') as f:
      f.write(destinationContent)
  except Exception, e:
    raise
    
# Run script
getValueFromInput(sys.argv)
try:
  changeContentOfFileFromAnotherFile(g_sourceFile, g_destinationFile)
except Exception, e:
  print 'Exception: %s' % e
