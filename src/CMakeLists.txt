message(STATUS "")
message(STATUS "Starting to configure libJPetFramework..")
message(STATUS "")
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Be nice and export compile commands by default, this is handy for clang-tidy
# and for other tools.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Helpful option enable build profiling to identify slowly compiling files
option(MEASURE_ALL "When enabled all commands will be passed through time command" OFF)
if(MEASURE_ALL)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "time")
endif()

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    Unpacker2ConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
    )

################################################################################
## Find Threads package
#
find_package(Threads REQUIRED)

################################################################################
## Find CERN ROOT
# first try to find ROOT 6 compiled with CMake
# if present, such ROOT should be possible to find without explicit setting of any paths
find_package(ROOT CONFIG REQUIRED)
if(ROOT_FOUND)
  message(STATUS "ROOT (version ${ROOT_VERSION}) was found using ROOTConfig")
endif()

include("${ROOT_DIR}/modules/RootNewMacros.cmake")
# fix missing include directories property in versions < ROOT 6.12
set_target_properties(ROOT::Core PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${ROOT_INCLUDE_DIRS}")


add_library(ROOT::Flags_CXX IMPORTED INTERFACE)

# Fix for ROOT_CXX_FLAGS not actually being a CMake list
separate_arguments(ROOT_CXX_FLAGS)
set_property(TARGET ROOT::Flags_CXX APPEND PROPERTY
    INTERFACE_COMPILE_OPTIONS ${ROOT_CXX_FLAGS})

# Add definitions
separate_arguments(ROOT_DEFINITIONS)
foreach(_flag ${ROOT_EXE_LINKER_FLAG_LIST})
    # Remove -D or /D if present
    string(REGEX REPLACE [=[^[-//]D]=] "" _flag ${_flag})
    set_property(TARGET ROOT::Flags APPEND PROPERTY INTERFACE_LINK_LIBRARIES ${_flag})
endforeach()

# This also fixes a bug in the linker flags
string(REPLACE "-L " "-L" ROOT_EXE_LINKER_FLAGS "${ROOT_EXE_LINKER_FLAGS}")
separate_arguments(ROOT_EXE_LINKER_FLAGS)
set_property(TARGET ROOT::Flags_CXX APPEND PROPERTY
    INTERFACE_LINK_LIBRARIES ${ROOT_EXE_LINKER_FLAGS})

################################################################################
## Find BOOST LIBs
#set(BOOST_LOG_DYN_LINK -DBOOST_LOG_DYN_LINK)
#add_definitions(${BOOST_LOG_DYN_LINK})

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.50 REQUIRED 
             COMPONENTS filesystem
                        program_options
                        regex
                        system
                        log_setup
                        log
                        date_time
                        thread
                        chrono
                        atomic
                        )

if(NOT TARGET Boost::filesystem)
    add_library(Boost::filesystem IMPORTED INTERFACE)
    set_property(TARGET Boost::filesystem PROPERTY
        INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
    set_property(TARGET Boost::filesystem PROPERTY
        INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
endif()

################################################################################
## Find Unpacker2
find_package(Unpacker2 CONFIG REQUIRED)
if(Unpacker2_FOUND)
  message(STATUS "Unpacker2 (version ${Unpacker2_VERSION}) was found using Unpacker2Config")
endif()

################################################################################
## Specify source folders
set(FOLDERS_WITH_SOURCE
  Options
  ParamObjects
  DataObjects
  Tasks
  Core
  ParametersTools
  MC
  GeantParser
  )

## Point sources and headers
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetAnalysisTools/JPetAnalysisTools.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetCmdParser/JPetCmdParser.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetCommonTools/JPetCommonTools.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetData/JPetData.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetDataInterface/JPetDataInterface.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetGeomMapping/JPetGeomMapping.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetLogger/JPetLogger.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetManager/JPetManager.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetParamAndDataFactory/JPetParamAndDataFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetProgressBarManager/JPetProgressBarManager.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetReader/JPetReader.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetScopeData/JPetScopeData.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetStatistics/JPetStatistics.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTask/JPetTask.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskChainExecutor/JPetTaskChainExecutor.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskFactory/JPetTaskFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskIO/JPetInputHandler.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskIO/JPetOutputHandler.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskIO/JPetTaskIO.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskIO/JPetTaskIOTools.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskLooper/JPetTaskLooper.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTimer/JPetTimer.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTreeHeader/JPetTreeHeader.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetUnpacker/JPetUnpacker.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetUserTask/JPetUserTask.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetWriter/JPetWriter.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetBaseSignal/JPetBaseSignal.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetEvent/JPetEvent.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetHit/JPetHit.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetHitUtils/JPetHitUtils.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetLOR/JPetLOR.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetPhysSignal/JPetPhysSignal.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetRawSignal/JPetRawSignal.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetRecoSignal/JPetRecoSignal.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetSigCh/JPetSigCh.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetTimeWindow/JPetTimeWindow.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/GeantParser/JPetGeantDecayTree/JPetGeantDecayTree.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/GeantParser/JPetGeantEventInformation/JPetGeantEventInformation.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/GeantParser/JPetGeantEventPack/JPetGeantEventPack.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/GeantParser/JPetGeantParser/JPetGeantParser.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/GeantParser/JPetGeantParser/JPetGeantParserTools.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/GeantParser/JPetGeantScinHits/JPetGeantScinHits.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/GeantParser/JPetRandom/JPetRandom.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/GeantParser/JPetSmearingFunctions/JPetSmearingFunctions.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/MC/JPetMCDecayTree/JPetMCDecayTree.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/MC/JPetMCHit/JPetMCHit.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/MC/JPetTimeWindowMC/JPetTimeWindowMC.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionValidator/JPetAdditionalValidators.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionValidator/JPetOptionValidator.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionsGenerator/JPetAdditionalTransformations.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionsGenerator/JPetOptionsGenerator.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionsGenerator/JPetOptionsGeneratorTools.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionsGenerator/JPetOptionsTypeHandler.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionsTools/JPetOptionsTools.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionsTools/JPetOptionsTransformators.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetBarrelSlot/JPetBarrelSlot.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetBarrelSlot/JPetBarrelSlotFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetFEB/JPetFEB.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetFEB/JPetFEBFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetFrame/JPetFrame.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetFrame/JPetFrameFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetLayer/JPetLayer.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetLayer/JPetLayerFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetPM/JPetPM.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetPM/JPetPMFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetScin/JPetScin.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetScin/JPetScinFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetTOMBChannel/JPetTOMBChannel.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetTOMBChannel/JPetTOMBChannelFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetTRB/JPetTRB.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetTRB/JPetTRBFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParametersTools/JPetParamBank/JPetParamBank.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParametersTools/JPetParamGetter/JPetParamGetter.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParametersTools/JPetParamGetterAscii/JPetParamGetterAscii.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParametersTools/JPetParamGetterAscii/JPetParamSaverAscii.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParametersTools/JPetParamManager/JPetParamManager.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParametersTools/JPetParamUtils/JPetParamUtils.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParametersTools/JPetParams/JPetParams.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/ParametersTools/JPetParamsFactory/JPetParamsFactory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Tasks/JPetParamBankHandlerTask/JPetParamBankHandlerTask.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Tasks/JPetScopeConfigParser/JPetScopeConfigParser.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Tasks/JPetScopeLoader/JPetScopeLoader.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Tasks/JPetScopeTask/JPetScopeTask.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Tasks/JPetSimplePhysSignalReco/JPetSimplePhysSignalReco.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Tasks/JPetUnzipAndUnpackTask/JPetUnzipAndUnpackTask.cpp)


get_target_property(DICTIONARY_INCLUDE_DIRS Unpacker2::Unpacker2 INTERFACE_INCLUDE_DIRECTORIES)
foreach(dir ${FOLDERS_WITH_SOURCE})
  list(APPEND DICTIONARY_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include/${dir})
endforeach()
list(APPEND DICTIONARY_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})

################################################################################
## Download test files with external script
## Does not do anything if data has been already downloaded
set(DOWNLOAD_DATA ${CMAKE_CURRENT_SOURCE_DIR}/download_data.sh ${CMAKE_CURRENT_SOURCE_DIR})
execute_process(COMMAND ${DOWNLOAD_DATA})

################################################################################
## Generating ROOT dictionaries
set(DICTIONARY_NAME G__JPetFramework)
set(HEADERS_WITH_DICTIONARY_REQUIRED
  JPetTimeWindow/JPetTimeWindow.h
  JPetSigCh/JPetSigCh.h
  JPetBaseSignal/JPetBaseSignal.h
  JPetRawSignal/JPetRawSignal.h
  JPetRecoSignal/JPetRecoSignal.h
  JPetPhysSignal/JPetPhysSignal.h
  JPetHit/JPetHit.h
  JPetLOR/JPetLOR.h
  JPetEvent/JPetEvent.h
  JPetStatistics/JPetStatistics.h
  JPetTreeHeader/JPetTreeHeader.h
  JPetUnpacker/JPetUnpacker.h
  JPetPM/JPetPM.h
  JPetScin/JPetScin.h
  JPetTRB/JPetTRB.h
  JPetTOMBChannel/JPetTOMBChannel.h
  JPetLayer/JPetLayer.h
  JPetBarrelSlot/JPetBarrelSlot.h
  JPetFrame/JPetFrame.h
  JPetFEB/JPetFEB.h
  JPetParamBank/JPetParamBank.h
  JPetMCHit/JPetMCHit.h
  JPetTimeWindowMC/JPetTimeWindowMC.h
  JPetMCDecayTree/JPetMCDecayTree.h
  JPetGeantScinHits/JPetGeantScinHits.h
  JPetGeantDecayTree/JPetGeantDecayTree.h
  JPetGeantEventPack/JPetGeantEventPack.h
  JPetGeantEventInformation/JPetGeantEventInformation.h
  )

set(LINKDEF_NAME JPetFramework_LinkDef.h)

foreach(dir ${DICTIONARY_INCLUDE_DIRS})
  list(APPEND DICTIONARY_INCLUDES -I${dir})
endforeach()

include_directories(ROOT_BUG) # Fix bug in NewMacros Root file
ROOT_GENERATE_DICTIONARY(${DICTIONARY_NAME} ${HEADERS_WITH_DICTIONARY_REQUIRED}
  LINKDEF ${LINKDEF_NAME}
  OPTIONS ${DICTIONARY_INCLUDES})

################################################################################
## Building Framework library
add_library(JPetFramework SHARED ${SOURCES} ${DICTIONARY_NAME}.cxx)
add_library(JPetFramework::JPetFramework ALIAS JPetFramework)
target_compile_options(JPetFramework PRIVATE -Wunused-parameter -Wall)
target_compile_definitions(JPetFramework PRIVATE BOOST_LOG_DYN_LINK=true)
foreach(dir ${FOLDERS_WITH_SOURCE})
  target_include_directories(JPetFramework PUBLIC
                             $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/${dir}>
                             $<INSTALL_INTERFACE:include/${dir}>
                            )
endforeach()
set_target_properties(JPetFramework PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(JPetFramework PUBLIC Unpacker2::Unpacker2
                                           Boost::filesystem
                                           Boost::program_options
                                           Boost::regex
                                           Boost::system
                                           Boost::log_setup
                                           Boost::log
                                           Boost::date_time
                                           Boost::thread
                                           Boost::chrono
                                           ROOT::Core 
                                           ROOT::Physics
                                           ROOT::Hist
                                           ROOT::RIO
                                           ROOT::Thread
                                           ROOT::HistPainter
                                           ROOT::Tree
                                           ROOT::Flags_CXX
                                           Threads::Threads
                                           )

################################################################################
## Read the version from git tag and git revision
exec_program(
  "git"
  ${CMAKE_CURRENT_SOURCE_DIR}
  ARGS "describe --tags --abbrev=0"
  OUTPUT_VARIABLE FRAMEWORK_VERSION
)
exec_program(
  "git"
  ${CMAKE_CURRENT_SOURCE_DIR}
  ARGS "rev-parse HEAD"
  OUTPUT_VARIABLE FRAMEWORK_REVISION
)

## Create the header file with framework version information
configure_file(${PROJECT_SOURCE_DIR}/version.h.in
  ${PROJECT_SOURCE_DIR}/include/Core/JPetTaskIO/version.h ESCAPE_QUOTES @ONLY)

## Create the thisframework.sh file with correct LD_LIBRARY_PATH information
configure_file(${PROJECT_SOURCE_DIR}/thisframework.sh.in
  ${CMAKE_CURRENT_BINARY_DIR}/thisframework.sh ESCAPE_QUOTES @ONLY)

include(GNUInstallDirs)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    JPetFrameworkConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
    )

install(TARGETS JPetFramework
        EXPORT JPetFramework
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )

install(DIRECTORY ../include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT JPetFramework
        FILE JPetFrameworkTargets.cmake
        NAMESPACE JPetFramework::
        DESTINATION lib/cmake/JPetFramework
         )

configure_file(JPetFrameworkConfig.cmake.in JPetFrameworkConfig.cmake @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/JPetFrameworkConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/JPetFrameworkConfigVersion.cmake"
        DESTINATION lib/cmake/JPetFramework
        )
        
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libJPetFramework_rdict.pcm"
              "${CMAKE_CURRENT_BINARY_DIR}/libJPetFramework.rootmap"
        DESTINATION lib
        )
