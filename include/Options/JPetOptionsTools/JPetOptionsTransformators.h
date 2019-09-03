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
 *  @file JPetOptionsTransformators.h
 */

#ifndef JPETOPTIONSTRANSFORMATORS_H
#define JPETOPTIONSTRANSFORMATORS_H

#include <boost/algorithm/string/predicate.hpp>
#include <boost/any.hpp>
#include <functional>
#include <map>

namespace jpet_options_tools
{
using OptNameValPair = std::pair<std::string, boost::any>;
using Transformer = std::function<OptNameValPair(boost::any opt)>;
std::pair <std::string, boost::any>appendSlash(boost::any option);
std::pair <std::string, boost::any>generateLowerEventBound(boost::any option);
std::pair <std::string, boost::any>generateHigherEventBound(boost::any option);
Transformer generateSetFileTypeTransformator(const std::map<std::string, boost::any>& options);
}
#endif /* !JPETOPTIONSTRANSFORMATORS_H */
