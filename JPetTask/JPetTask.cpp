/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file JPetTask.cpp
 */

#include "../JPetParamManager/JPetParamManager.h"
#include "./JPetTask.h"


JPetTask::JPetTask(const char* name, const char* description):
  fName(name, description),
  fEvent(0),
  fParamManager(0),
  fStatistics(0),
  fAuxilliaryData(0)
{
}


void JPetTask::init(const JPetTaskInterface::Options&)
{
}

void JPetTask::exec()
{
  // do something with event
}

void JPetTask::terminate()
{
}

void JPetTask::setEvent(TNamed* ev)
{
  fEvent = ev;
}

void JPetTask::setParamManager(JPetParamManager* paramManager)
{
  fParamManager = paramManager;
}

const JPetParamBank& JPetTask::getParamBank()
{
  DEBUG("JPetTask");
  assert(fParamManager);
  return fParamManager->getParamBank();
}

void JPetTask::setStatistics(JPetStatistics* statistics)
{
  assert(statistics);
  fStatistics = statistics;
}

JPetAuxilliaryData& JPetTask::getAuxilliaryData()
{
  assert(fAuxilliaryData);
  return *fAuxilliaryData;
}

void JPetTask::setAuxilliaryData(JPetAuxilliaryData* auxData)
{
  assert(auxData);
  fAuxilliaryData = auxData;
}

JPetStatistics& JPetTask::getStatistics()
{
  assert(fStatistics);
  return *fStatistics;
}

