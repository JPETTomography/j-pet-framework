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
 *  @file JPetInputHandler.cpp
 */

#include "JPetTaskIO/JPetInputHandler.h"

JPetInputHandler::JPetInputHandler() {}

EntryRange JPetInputHandler::getEntryRange() const { return fEntryRange; }

long long JPetInputHandler::getCurrentEntryNumber() const { return fEntryRange.currentEntry; }

long long JPetInputHandler::getFirstEntryNumber() const { return fEntryRange.firstEntry; }

long long JPetInputHandler::getLastEntryNumber() const { return fEntryRange.lastEntry; }

JPetTreeHeader* JPetInputHandler::getHeaderClone() { return new JPetTreeHeader(); }
