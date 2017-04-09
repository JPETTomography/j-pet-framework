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
 *  @file JPetJsonGetter.h
 */


#ifndef JPETJSONGETTER_H
#define JPETJSONGETTER_H

#include <boost/asio.hpp>
#include <string>

class JPetJsonGetter
{
public:
  JPetJsonGetter(std::string host, std::string port);
  ~JPetJsonGetter();
  std::string getJsonByMD5(const std::string& md5Hash);

private:
  JPetJsonGetter(const JPetJsonGetter&) = delete;
  JPetJsonGetter& operator=(const JPetJsonGetter&) = delete;

  std::string fHost;
  std::string fPort;
};

#endif /*  !JPETJSONGETTER_H */