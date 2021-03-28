/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetEventType.h
 */

#ifndef JPETEVENTTYPE_H
#define JPETEVENTTYPE_H

enum class JPetEventType
{
  kUnknown = 1,
  k2Gamma = 2,
  k3Gamma = 4,
  kPrompt = 8,
  kScattered = 16,
  kCosmic = 32
};

inline JPetEventType operator|(JPetEventType a, JPetEventType b) { return static_cast<JPetEventType>(static_cast<int>(a) | static_cast<int>(b)); }
inline JPetEventType operator&(JPetEventType a, JPetEventType b) { return static_cast<JPetEventType>(static_cast<int>(a) & static_cast<int>(b)); }
inline JPetEventType operator~(JPetEventType a) { return static_cast<JPetEventType>(~static_cast<int>(a)); }

#endif /* !JPETEVENTTYPE_H */
