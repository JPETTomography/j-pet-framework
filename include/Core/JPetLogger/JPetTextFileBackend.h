/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetTextFileBackend.h
 */

#ifndef JPETTEXTFILEBACKEND_H
#define JPETTEXTFILEBACKEND_H
#include <boost/log/core.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/smart_ptr/detail/sp_forward.hpp>

class JPetTextFileBackend : public boost::log::sinks::text_file_backend
{
public:
  template <typename... ArgsT>
  explicit JPetTextFileBackend(ArgsT... args) : boost::log::sinks::text_file_backend(boost::detail::sp_forward<ArgsT>(args)...)
  {
  }
  ~JPetTextFileBackend() {}
  void consume(boost::log::record_view const& rec, string_type const& formatted_message)
  {
    if (!formatted_message.empty())
      boost::log::sinks::text_file_backend::consume(rec, formatted_message);
    return;
  }
};

#endif /* !JPETTEXTFILEBACKEND_H */
