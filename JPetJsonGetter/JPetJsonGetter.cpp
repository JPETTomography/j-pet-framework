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
 *  @file JPetJsonGetter.cpp
 */

#include "JPetJsonGetter.h"

JPetJsonGetter::JPetJsonGetter(std::string host, std::string port)
    : fHost(host), fPort(port)
{
}

JPetJsonGetter::~JPetJsonGetter() {}

std::string JPetJsonGetter::getJsonByMD5(const std::string &md5Hash)
{
  boost::system::error_code ec;
  boost::asio::io_service service;
  boost::asio::ip::tcp::resolver resolver(service);
  boost::asio::ip::tcp::resolver::query query(fHost, fPort);
  boost::asio::ip::tcp::resolver::iterator endpoint_it =
      resolver.resolve(query);
  boost::asio::ip::tcp::socket sock(service);
  boost::asio::connect(sock, endpoint_it);
  std::string request("GET /api?checksum=" + md5Hash + " HTTP/1.1\r\n\r\n");
  sock.send(boost::asio::buffer(request));
  std::string response;
  static char buf[1024];
  size_t responseLenght = 0;
  while ((responseLenght = sock.receive(boost::asio::buffer(buf), {}, ec)) > 0)
  {
    response.append(buf, buf + responseLenght);
  }
  return response;
}