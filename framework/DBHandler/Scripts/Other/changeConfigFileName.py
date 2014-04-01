# -*- coding: utf-8 -*-
# script find text with regular expression and change it to another in file

import os
import re
import fileinput
import sys


g_newNameOfConfigFile = ""
#g_directoryToChange = "/home/andrzej/Dokumenty/Programiki/Skrypty/pliki"
g_directoryToChange = "../"
g_expression = r'(.*)../Config/(.*).cfg(.*)'
g_expressionForFunctionTestSuite = r'(.*)m_db_configFileName == "(.*).cfg(.*)' # an extra expression for test suite FunctionsTestSuite.cpp
g_listOfValidExtensions = ['.cpp', '.h']


def getValueFromInput(p_argv):

  global g_newNameOfConfigFile
  global g_directoryToChange

  l_lenOfArgv = len(p_argv)

  if l_lenOfArgv < 2:
    sys.exit('Nothing to do:-(')
  elif l_lenOfArgv == 2:
    g_newNameOfConfigFile = p_argv[1]
  elif l_lenOfArgv == 3:
    g_newNameOfConfigFile = p_argv[1]
    g_directoryToChange = p_argv[2]

getValueFromInput(sys.argv)
print "New name of config file = '%s'" % g_newNameOfConfigFile, " Directory to change = '%s'" % g_directoryToChange

def showList(p_list):
  for i, val in enumerate(p_list):
    print "%d)" %(i+1), val

def isValidExtension(p_extension, p_listOfValidExtensions):

  l_listSize = len(p_listOfValidExtensions)
  for it in range(0, l_listSize):
    l_value = p_listOfValidExtensions[it]
    if p_extension == l_value:
      return True
  return False

def getFilepathsWithValidExtensions(p_directory, p_listOfValidExtensions):
  
  l_listOfFilePaths = []
  
  for root, directories, files in os.walk(p_directory):
    #print root
    for filename in files:
      #print filename
      l_filePath = os.path.join(root, filename)
      #print filepath
      l_fileName, l_fileExtension = os.path.splitext(l_filePath)
      #print l_fileName
      #print l_fileExtension
      if isValidExtension(l_fileExtension, p_listOfValidExtensions):
	l_listOfFilePaths.append(l_filePath)
	
  return l_listOfFilePaths
  
def changeTextInFiles(l_directoryToChange, l_listOfValidExtensions, p_expression, p_expressionForFunctionTestSuite, p_newNameOfConfigFile):
  
  l_fullFilePaths = getFilepathsWithValidExtensions(l_directoryToChange, l_listOfValidExtensions)
  l_numberOfChanges = 0
  l_changedTextList = []
  l_changedFilesList = []
  
  for currentFile in l_fullFilePaths:
    for currentLineInFile in fileinput.FileInput(currentFile, inplace=1):    
      matchedObject = re.match(p_expression, currentLineInFile, re.M|re.I)
      if matchedObject:
	l_numberOfChanges += 1
	l_thirdGroupOfmatchedObject = matchedObject.group(2)
	l_changedTextList.append(l_thirdGroupOfmatchedObject)
	l_changedFilesList.append(currentFile)
	currentLineInFile = currentLineInFile.replace(l_thirdGroupOfmatchedObject, p_newNameOfConfigFile)

      matchedObject = re.match(p_expressionForFunctionTestSuite, currentLineInFile, re.M|re.I)
      if matchedObject:
	l_numberOfChanges += 1
	l_thirdGroupOfmatchedObject = matchedObject.group(2)
	l_changedTextList.append(l_thirdGroupOfmatchedObject)
	l_changedFilesList.append(currentFile)
	currentLineInFile = currentLineInFile.replace(l_thirdGroupOfmatchedObject, p_newNameOfConfigFile)
	
      sys.stdout.write(currentLineInFile)
      
  print "Number of changes =", l_numberOfChanges
  print "Changed files :"
  showList(l_changedFilesList)
  print "Changed texts :"
  showList(l_changedTextList)

  return l_numberOfChanges
  
changeTextInFiles(g_directoryToChange, g_listOfValidExtensions, g_expression, g_expressionForFunctionTestSuite, g_newNameOfConfigFile)

