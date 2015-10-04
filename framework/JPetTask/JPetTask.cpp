/**
  *  @copyright Copyright (c) 2014, Wojciech Krzemien
  *  @file JPetTask.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */ 

#include "../JPetParamManager/JPetParamManager.h"
#include "./JPetTask.h"

JPetTask::JPetTask():
fEvent(0),
fParamManager(0)
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

