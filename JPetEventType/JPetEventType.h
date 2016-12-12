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
 *  @file JPetEventType.h
 */

#ifndef JPETEVENTTYPE_H
#define JPETEVENTTYPE_H

#include<type_traits>

enum JPetEventType : unsigned {
  kUnknown = 1,
  k2Gamma = 2,
  k3Gamma = 4,
  kPrompt = 8,
  kScattered = 16
};


inline JPetEventType operator |(JPetEventType lhs, JPetEventType rhs)
{
  return static_cast<JPetEventType> (
           static_cast<std::underlying_type<JPetEventType>::type>(lhs) |
           static_cast<std::underlying_type<JPetEventType>::type>(rhs)
         );
}

inline JPetEventType operator &(JPetEventType lhs, JPetEventType rhs)
{
  return static_cast<JPetEventType> (
           static_cast<std::underlying_type<JPetEventType>::type>(lhs) &
           static_cast<std::underlying_type<JPetEventType>::type>(rhs)
         );
}

inline JPetEventType operator ^(JPetEventType lhs, JPetEventType rhs)
{
  return static_cast<JPetEventType> (
           static_cast<std::underlying_type<JPetEventType>::type>(lhs) ^
           static_cast<std::underlying_type<JPetEventType>::type>(rhs)
         );
}

inline JPetEventType operator ~(JPetEventType rhs)
{
  return static_cast<JPetEventType> (
           ~static_cast<std::underlying_type<JPetEventType>::type>(rhs)
         );
}

inline JPetEventType& operator |=(JPetEventType& lhs, JPetEventType rhs)
{
  lhs = static_cast<JPetEventType> (
          static_cast<std::underlying_type<JPetEventType>::type>(lhs) |
          static_cast<std::underlying_type<JPetEventType>::type>(rhs)
        );

  return lhs;
}

inline JPetEventType& operator &=(JPetEventType& lhs, JPetEventType rhs)
{
  lhs = static_cast<JPetEventType> (
          static_cast<std::underlying_type<JPetEventType>::type>(lhs) &
          static_cast<std::underlying_type<JPetEventType>::type>(rhs)
        );
  return lhs;
}

inline JPetEventType& operator ^=(JPetEventType& lhs, JPetEventType rhs)
{
  lhs = static_cast<JPetEventType> (
          static_cast<std::underlying_type<JPetEventType>::type>(lhs) ^
          static_cast<std::underlying_type<JPetEventType>::type>(rhs)
        );
  return lhs;
}
#endif /*  !JPETEVENTTYPE_H */
