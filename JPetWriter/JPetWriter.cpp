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
 *  @file JPetWriter.cpp
 */

#include "JPetWriter.h"
#include "../JPetUserInfoStructure/JPetUserInfoStructure.h"


JPetWriter::JPetWriter(const char* p_fileName) :
  fFileName(p_fileName),			// string z nazwą pliku
  fFile(0),	// plik
  fIsBranchCreated(false),
  fTree(0)
{
  fFile = new TFile(fFileName.c_str(), "RECREATE");
  if (!isOpen()) {
    ERROR("Could not open file to write.");
  } else {
    fTree = new TTree("tree", "tree");
    fTree->SetAutoSave(10000);
  }
}

JPetWriter::~JPetWriter()
{
  DEBUG("destructor of JPetWriter");
  if (isOpen()) {
    fTree->AutoSave("SaveSelf");
    if (fFile) {
      delete fFile;
      fFile = 0;
    }
    fTree = 0;
  }
  DEBUG("exiting destructor of JPetWriter");
}

void JPetWriter::closeFile()
{
  if (isOpen() ) {
    fTree->AutoSave("SaveSelf");
    delete fFile;
    fFile = 0;
  }
  fFileName.clear();
  fIsBranchCreated = false;
}

void JPetWriter::writeHeader(TObject* header)
{
  // @todo as the second argument should be passed some enum to indicate position of header
  fTree->GetUserInfo()->AddAt(header, JPetUserInfoStructure::kHeader);
}

