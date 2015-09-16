/**
  *  @copyright Copyright (c) 2014, Wojciech Krzemien
  *  @file JPetTask.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */ 

#include "./JPetTask.h"

JPetTask::JPetTask():
fEvent(0)
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
