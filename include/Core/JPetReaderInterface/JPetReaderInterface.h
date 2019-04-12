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
 *  @file JPetReaderInterface.h
 */

#ifndef JPETREADERINTERFACE_H
#define JPETREADERINTERFACE_H

#include <TObject.h>

class JPetReaderInterface {
 public:
  typedef TObject MyEvent;
  virtual ~JPetReaderInterface() {;}
  virtual MyEvent& getCurrentEntry()=0;
  virtual bool nextEntry()=0;
  virtual bool firstEntry()=0;
  virtual bool lastEntry()=0;
  virtual bool nthEntry(long long int n)=0;
  virtual long long getCurrentEntryNumber() const =0;
  virtual long long getNbOfAllEntries() const =0;
  virtual bool openFileAndLoadData(const char* filename, const char* treename)=0;
  virtual void closeFile()=0;
};
#endif /* !JPETREADERINTERFACE_H */
