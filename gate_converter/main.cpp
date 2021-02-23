#include <iostream>
#include <string>

#include "GateHit.h"
#include "Reader.h"
#include "Writer.h"

std::string g_input_file_name = "";
std::string g_output_file_name = "";
Reader::DetectorGeometry g_detector_geometry = Reader::DetectorGeometry::Unknown;

bool read_options(char* argv[])
{
  g_input_file_name = std::string(argv[1]);
  g_output_file_name = std::string(argv[2]);
  std::string str_detector_geometry(argv[3]);
  if (str_detector_geometry == "3layers")
    g_detector_geometry = Reader::DetectorGeometry::ThreeLayers;
  else if (str_detector_geometry == "24modules")
    g_detector_geometry = Reader::DetectorGeometry::TwentyFourModules;
  else
    return false;
  return true;
}

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cout << "[ERROR] Required 3 arguments: input_file_path output_file_path detector_geometry" << std::endl;
    std::cout << "detector_geometry = { 3layers, 24modules } " << std::endl;
    return 1;
  }

  if (!read_options(argv))
  {
    std::cout << "[ERROR] Unknown detector geometry. detector_geometry = { 3layers, 24modules }" << std::endl;
    return 2;
  }

  Writer w;
  w.set_output_file_path(g_output_file_name);
  w.init();
  Reader r;
  r.set_geometry(g_detector_geometry);
  r.set_input_file_path(g_input_file_name);
  r.init();
  while (r.read())
  {
    GateHit* p_gh = r.get();
    if (p_gh != nullptr)
      w.write(*p_gh);
  }
  r.close();
  w.close();
}
