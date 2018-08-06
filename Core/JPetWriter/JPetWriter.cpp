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
 *  @file JPetWriter.cpp
 */

#include "JPetWriter.h"
#include "./JPetUserInfoStructure/JPetUserInfoStructure.h"

/**
 * This tree name is compatible with the tree name produced by the Unpacker.
 */
const std::string JPetWriter::kRootTreeName = "T";
const long long JPetWriter::kTreeBufferSize = 10000;

JPetWriter::JPetWriter(const char* p_fileName) :
  fFileName(p_fileName),
  fFile(0),
  fIsBranchCreated(false),
  fTree(0)
{
  fFile = new TFile(fFileName.c_str(), "RECREATE");
  if (!isOpen()) {
    ERROR("Could not open file to write.");
  } else {
    fTree = new TTree(JPetWriter::kRootTreeName.c_str() , JPetWriter::kRootTreeName.c_str());
    fTree->SetAutoSave(JPetWriter::kTreeBufferSize);
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
  if (isOpen()) {
    fTree->AutoSave("SaveSelf");
    delete fFile;
    fFile = 0;
  }
  fFileName.clear();
  fIsBranchCreated = false;
}

void JPetWriter::writeHeader(TObject* header)
{
  assert(fTree);
  /// @todo as the second argument should be passed some enum to indicate position of header
  fTree->GetUserInfo()->AddAt(header, JPetUserInfoStructure::kHeader);
}

/**
 * @brief Write all TObjects from a given TCollection into a certain directory
 * structure in the file.
 *
 * @param col pointer to a TCollection-based container
 * @param dirname name of a directory inside the output file to which the objects should be written
 * @param subdirname optional name of a subdirectory inside dirname to which the objects should be written
 *
 * This method whites all TObject-based objects contained in the TCollection-based
 * container (see ROOT documentation) into a directory, which name is given by
 * the directory name inside the output file. If 'dirname' does not exist
 * in the output file, it will be created. Otherwise, contents of the collection
 * will be appended to an existing directory.
 * If the optional subdirectory name is specified (subdirname parameter, defaults
 * to empty string), then the contents of the collection will be written to
 * 'dirname/subdirname'. If the "subdirname" directory does not exist inside
 * the 'dirname' directory, it will be created.
 */
void JPetWriter::writeCollection(
  const TCollection* col, const char* dirname, const char* subdirname)
{
  TDirectory* current =  fFile->GetDirectory(dirname);
  if (!current) {
    current = fFile->mkdir(dirname);
  }
  assert(current);

  // use a subdirectory if requested by user
  if (!std::string(subdirname).empty()) {
    if (current->GetDirectory(subdirname)) {
      current = current->GetDirectory(subdirname);
    } else {
      current = current->mkdir(subdirname);
    }
  }
  assert(current);
  current->cd();
  TIterator* it = col->MakeIterator();
  TObject* obj;
  while ((obj = it->Next())) {
    obj->Write();
  }
  fFile->cd();
}
