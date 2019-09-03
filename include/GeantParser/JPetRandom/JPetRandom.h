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
 *  @file JPetRandom.h
 */

#ifndef JPETRANDOM_H
#define JPETRANDOM_H

#include<TRandom3.h>

/**
 * @brief wrapping class for random generator 
 * Allows to create only a single instance of random generator 
 * through the program (see c++ singleton)
 */
class JPetRandom : public TRandom3  
{
      public:
      static TRandom3* GetRandomGenerator(); ///< only single instance can exists
      static void setGeneratorSeed(unsigned long seed);
      static unsigned long getGeneratorSeed();

      protected:
      static TRandom3* fRandomGenerator;
      JPetRandom();
      ~JPetRandom();
};
#endif


