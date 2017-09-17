/**
 *  @copyright Copyright 2017 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetOptionsTransformators.h
 */

#ifndef JPETOPTIONSTRANSFORMATORS_H
#define JPETOPTIONSTRANSFORMATORS_H

#include <boost/any.hpp>

namespace jpet_options_tools
{
std::pair <std::string, boost::any>appendSlash(boost::any option);
std::pair <std::string, boost::any>setInputFileType(boost::any option);
std::pair <std::string, boost::any>generateLowerEventBound(boost::any option);
std::pair <std::string, boost::any>generateHigherEventBound(boost::any option);
}
#endif /*  !JPETOPTIONSTRANSFORMATORS_H */
