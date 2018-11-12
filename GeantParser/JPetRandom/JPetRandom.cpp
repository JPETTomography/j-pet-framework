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
 *  @file JPetRandom.cpp
 */

#include <JPetRandom/JPetRandom.h>

TRandom3* JPetRandom::fRandomGenerator =0; 

TRandom3* JPetRandom::GetRandomGenerator()
{
      if (fRandomGenerator == 0)
      {
            fRandomGenerator = new TRandom3(0);
      }
      return fRandomGenerator;
}

/**
 * @brief Set the seed of a single pseudorandom number generator used for smearing of generated values in JPetGeantParserTools methods
 *
 * This method can be optionally used to have the pseudorandom number generator
 * start with a particular seed. If this method is not used, the generator will
 * be initialized with seed=4357, see:
 * https://root.cern.ch/doc/master/classTRandom3.html
 *
 */

void JPetRandom::setGeneratorSeed(unsigned long seed)
{
      fRandomGenerator->SetSeed(seed);
}

unsigned long JPetRandom::getGeneratorSeed()
{
      return fRandomGenerator->GetSeed();
}


JPetRandom::JPetRandom()
{}


JPetRandom::~JPetRandom()
{}
