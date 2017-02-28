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
 *  @file JPetReaderInterface.h 
 */

#ifndef JPETREADERINTERFACE_H 
#define JPETREADERINTERFACE_H 

#include <TNamed.h> // for Event typedef

class JPetReaderInterface {
 public:
  typedef TObject MyEvent; 
  virtual ~JPetReaderInterface() {;}
  virtual MyEvent& getCurrentEvent()=0;   
  virtual bool nextEvent()=0;
  virtual bool firstEvent()=0;
  virtual bool lastEvent()=0;
  virtual bool nthEvent(long long int n)=0;
  virtual long long getCurrentEventNumber() const =0;
  virtual long long getNbOfAllEvents() const =0; 
  virtual TObject* getObjectFromFile(const char* name)=0;
  
  virtual bool openFileAndLoadData(const char* filename, const char* treename)=0;
  virtual void closeFile()=0; 
};
#endif /*  !JPETREADERINTERFACE_H */

