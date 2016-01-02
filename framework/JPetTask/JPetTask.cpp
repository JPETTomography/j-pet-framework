/**
  *  @copyright Copyright (c) 2014, Wojciech Krzemien
  *  @file JPetTask.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */ 

#include "../JPetParamManager/JPetParamManager.h"
#include "./JPetTask.h"

JPetTask::JPetTask(const char * name, const char * description):
fEvent(0),
fParamManager(0),
TNamed(name, description)
{
}


void JPetTask::init(const JPetTaskInterface::Options& opts)
{
}

void JPetTask::exec() 
{
  // do something with event
}

void JPetTask::terminate() 
{
}

void JPetTask::setEvent(TNamed* ev){
  fEvent = ev;
}

void JPetTask::setParamManager(JPetParamManager* paramManager) {
  fParamManager = paramManager;
}

const JPetParamBank& JPetTask::getParamBank() {
  assert(fParamManager);
  return fParamManager->getParamBank();
}

void JPetTask::setStatistics(JPetStatistics * statistics) {
  assert(statistics);
  fStatistics = statistics;
}

JPetStatistics & JPetTask::getStatistics() {
  assert(fStatistics);
  return *fStatistics;
}

