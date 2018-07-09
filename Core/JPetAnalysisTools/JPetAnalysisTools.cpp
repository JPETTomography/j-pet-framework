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
 *  @file JPetAnalysisTools.cpp
 */

#include "./JPetAnalysisTools.h"

/**
 * Sorting the input vector of JPetHits by ascending time
 */
std::vector<JPetHit> JPetAnalysisTools::getHitsOrderedByTime(const std::vector<JPetHit>& oldHits)
{
  auto hits(oldHits);
  std::sort(hits.begin(), hits.end(),
  [] (const JPetHit & h1, const JPetHit & h2) {
    return h1.getTime() < h2.getTime();
  });
  return hits;
}
