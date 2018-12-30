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
 *  @file JPetTimeWindow.h
 */

#ifndef _JPETTIMEWINDOW_H_
#define _JPETTIMEWINDOW_H_

#include <TClonesArray.h>
#include <TNamed.h>
#include <iostream>
#include <vector>
#include <map>

/**
 * @brief Container class representing a time window of the DAQ system
 *
 * A single TimeWindow contains many objects (referred to as "events")
 * representing events which happened during one time window of the DAQ system.
 */
class JPetTimeWindow: public TObject
{
public:

  JPetTimeWindow() : fEvents() {}
  JPetTimeWindow(const char * event_type) : fEvents(event_type, 2000) {}

  template<typename T>
  void add(const T & evt){
    dynamic_cast<T&>(*(fEvents.ConstructedAt(fEventCount++))) = evt;
  }

  inline size_t getNumberOfEvents() const {
    return fEventCount;
  }

  inline const TObject & operator[](int i) const {
    return *fEvents[i];
  }

  template<typename T>
  inline const T& getEvent(int i) const {
    return *(dynamic_cast<T*>(fEvents[i]));
  }

  virtual ~JPetTimeWindow() {
    fEvents.Clear("C");
    fEventCount = 0;
  }

  virtual void Clear() {
    fEvents.Clear("C");
    fEventCount = 0;
  }

  ClassDef(JPetTimeWindow, 4);

private:
  TClonesArray fEvents;
  unsigned int fEventCount = 0;
};

#endif /* !_JPETTIMEWINDOW_H_ */
