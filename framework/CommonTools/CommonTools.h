// Common tools
#ifndef COMMON_TOOLS_H
#define COMMON_TOOLS_H
#include <boost/noncopyable.hpp>
#include <ctime>


class CommonTools : public boost::noncopyable
{
public:
  static const std::string currentDateTime() 
  {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return buf;
  }
};

#endif // COMMON_TOOLS_H