/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetFEB.cpp
 */

#include "JPetFEB.h"

ClassImp(JPetFEB);

JPetFEB::JPetFEBInput::JPetFEBInput(int p_FEBId): JPetFEBChannel(), m_FEBId(p_FEBId) {}

JPetFEB::JPetFEBOutput::JPetFEBOutput(bool p_passedInformationIsTime,
  std::string p_passedInformation, int p_FEBId, int p_inputId, int p_FEBInputId):
  JPetFEBChannel(), m_passedInformationIsTime(p_passedInformationIsTime),
  m_passedInformation(p_passedInformation), m_FEBId(p_FEBId), m_inputId(p_inputId),
  m_FEBInputId(p_FEBInputId) {}

JPetFEB::JPetFEB() { SetName("JPetFEB"); }

JPetFEB::JPetFEB(int id): m_id(id) { SetName("JPetFEB"); }

JPetFEB::JPetFEB(int p_id, bool p_isActive, std::string p_status,
  std::string p_description, int p_version, int p_userId,
  int p_n_time_outputs_per_input, int p_n_notime_outputs_per_input):
  m_id(p_id), m_isActive(p_isActive), m_status(p_status), m_description(p_description),
  m_version(p_version), m_userId(p_userId), m_n_time_outputs_per_input(p_n_time_outputs_per_input),
  m_n_notime_outputs_per_input(p_n_notime_outputs_per_input)
{
  SetName("JPetFEB");
}

JPetFEB::JPetFEB(bool isNull): fIsNullObject(isNull)
{
  SetName("JPetFEB");
}

JPetFEB::~JPetFEB(){}

int JPetFEB::getID() const
{
  return m_id;
}

bool JPetFEB::isActive() const
{
  return m_isActive;
}

std::string JPetFEB::status() const
{
  return m_status;
}

std::string JPetFEB::description() const
{
  return m_description;
}

int JPetFEB::version() const
{
  return m_version;
}

/**
 * @brief Get number of output time channels per one FEB input channel
 */
int JPetFEB::getNtimeOutsPerInput(void) const
{
  return m_n_time_outputs_per_input;
}

/**
 * @brief Get number of output non-time (e.g. TOT or charge) channels per one FEB input channel
 */
int JPetFEB::getNnotimeOutsPerInput(void) const
{
  return m_n_notime_outputs_per_input;
}

int JPetFEB::getCreator() const
{
  return m_userId;
}

const JPetTRB& JPetFEB::getTRB() const
{
  if (fTRefTRBs.GetObject()) return (JPetTRB&) * fTRefTRBs.GetObject();
  else {
    ERROR("No JPetTRB slot set, Null object will be returned");
    return JPetTRB::getDummyResult();
  }
}

void JPetFEB::setTRB(JPetTRB& p_TRB)
{
  fTRefTRBs = &p_TRB;
}

bool JPetFEB::operator==(const JPetFEB& feb)
{
  return getID() == feb.getID();
}

bool JPetFEB::operator!=(const JPetFEB& feb)
{
  return getID() != feb.getID();
}

bool JPetFEB::isNullObject() const
{
  return fIsNullObject;
}

JPetFEB& JPetFEB::getDummyResult()
{
  static JPetFEB DummyResult(true);
  return DummyResult;
}

void JPetFEB::clearTRefTRBs()
{
  fTRefTRBs = NULL;
}
