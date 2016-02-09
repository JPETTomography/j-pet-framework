#ifndef _POST_UNPACKER_FILTER_
#define _POST_UNPACKER_FILTER_

class JPetPostUnpackerFilter{

 public:

  static int calculate_hits(int eventsNum, const char* fileName);

  static int calculate_times(int eventsNum, const char* fileName, int refChannelOffset, const char* calibFile);
  
 private:
  
};

#endif
