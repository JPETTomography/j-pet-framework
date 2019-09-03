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
 *  @file JPetUserInfoStructure.h
 */

#ifndef _JPET_USERINFO_STRUCTURE_H_
#define _JPET_USERINFO_STRUCTURE_H_

namespace JPetUserInfoStructure
{
	/**
	 * Enum UserInfoStructure refers to root file's UserInfo, which can contain any
	 * object that inherits from TObject. It is an indexed list, so the UserInfoStructure
	 * enum below keeps what is saved on each position by JPetWriter and read by JPetReader.
	 * -----IMPORTANT-----
	 * If you want to add more things to it, add them at the end, to make sure,
	 * that files saved by previous versions of JPetWriter will be still read properly.
	 */
	enum UserInfoStructure{
		kHeader
	};
}

#endif /* !_JPET_USERINFO_STRUCTURE_H_ */
