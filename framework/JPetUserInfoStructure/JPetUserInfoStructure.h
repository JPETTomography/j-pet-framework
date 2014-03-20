#ifndef _JPET_USERINFO_STRUCTURE_H_
#define _JPET_USERINFO_STRUCTURE_H_

namespace JPetUserInfoStructure{


/**
 * Enum UserInfoStructure refers to root file's UserInfo, which can contain any 
 * object that inherits from TObject. It is an indexed list, so the UserInfoStructure
 * enum below keeps what is saved on each position by JPetWriter and read by
 * JPetReader.
 *
 * -----IMPORTANT-----
 * If you want to add more things to it, add them at the end, to make sure,
 * that files saved by previous versions of JPetWriter will be still read properly.
 */
enum UserInfoStructure{
	kHeader
};

}

#endif