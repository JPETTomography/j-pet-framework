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
 *  @file JPetCmdParser.h
 */

#ifndef _JPET_CMD_PARSER_H_
#define _JPET_CMD_PARSER_H_

#include "boost/program_options.hpp"
namespace po = boost::program_options;

/**
 * @brief Parser of the command line arguments provided by users.
 *
 * It is based on Boost library program_options.
 * The exception std::invalid_argument can be thrown in case of parsing error.
 */
class JPetCmdParser
{
public:
  JPetCmdParser();
  ~JPetCmdParser();
  po::variables_map parseCmdLineArgs(int argc, const char** argv) const;
  inline const po::options_description getOptionsDescription() const
  {
    return fOptionsDescriptions;
  }

protected:
  po::options_description fOptionsDescriptions;

private:
  JPetCmdParser(const JPetCmdParser& cmdParser);
  JPetCmdParser& operator=(const JPetCmdParser& cmdParser);
};

#endif /* _JPET_CMD_PARSER_H_ */
