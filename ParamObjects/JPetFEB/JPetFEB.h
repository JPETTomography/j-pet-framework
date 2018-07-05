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
 *  @file JPetFEB.h
 */

#ifndef JPET_FEB_H
#define JPET_FEB_H

#include "./JPetLoggerInclude.h"
#include "./JPetTRB/JPetTRB.h"
#include "TNamed.h"
#include <TRef.h>

/**
 * @brief Representation of a front-end board in J-PET barrel
 *
 * Parametric class representing database information on parameters of a front-end board (FEB).
 * The board represented by this class can be: KonradBoard(KB), Majewski Board or MP board.
 */
class JPetFEB: public TNamed
{
public:
  static JPetFEB& getDummyResult();

  JPetFEB();
  explicit JPetFEB(int id);
  explicit JPetFEB(bool isNull);
  JPetFEB(int p_id, bool p_isActive, std::string p_status,
    std::string p_description, int p_version, int p_userId,
    int p_n_time_outputs_per_input, int p_n_notime_outputs_per_input);
  virtual ~JPetFEB(void);
  bool operator==(const JPetFEB& feb);
  bool operator!=(const JPetFEB& feb);
  virtual int getID(void) const;
  virtual bool isActive(void) const;
  virtual std::string status(void) const;
  virtual std::string description(void) const;
  virtual int version(void) const;
  int getCreator() const;
  virtual int getNtimeOutsPerInput(void) const;
  virtual int getNnotimeOutsPerInput(void) const;
  const JPetTRB& getTRB() const;
  void setTRB(JPetTRB& p_TRB);
  bool isNullObject() const;

protected:
  struct JPetFEBChannel {
    int m_id;
    bool m_isActive;
    std::string m_status;
    int m_portNumber;
    std::string m_description;
  };

  struct JPetFEBInput: public JPetFEBChannel {
    JPetFEBInput(int p_FEBId);
    int m_FEBId;
  };

  struct JPetFEBOutput: public JPetFEBChannel {
    JPetFEBOutput(bool p_passedInformationIsTime,
      std::string p_passedInformation, int p_FEBId, int p_inputId, int p_FEBInputId);
    bool m_passedInformationIsTime;
    std::string m_passedInformation;
    int m_FEBId;
    int m_inputId;
    int m_FEBInputId;
  };

  void clearTRefTRBs();

#ifndef __CINT__
  int m_id = 0;
  bool m_isActive = false;
  std::string m_status = "";
  std::string m_description = "";
  const int m_version = 0;
  const int m_userId = 0;
  int m_n_time_outputs_per_input = 0;
  int m_n_notime_outputs_per_input = 0;
  bool fIsNullObject = false;
#else
  int m_id;
  bool m_isActive;
  std::string m_status;
  std::string m_description;
  const int m_version;
  const int m_userId;
  int m_n_time_outputs_per_input;
  int m_n_notime_outputs_per_input;
  bool fIsNullObject;
#endif
  TRef fTRefTRBs;
  friend class JPetParamManager;
  ClassDef(JPetFEB, 2);
};

#endif /* JPET_FEB_H */
