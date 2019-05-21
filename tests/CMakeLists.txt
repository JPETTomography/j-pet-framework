message(STATUS "")
message(STATUS "Starting to configure libJPetFrameworkTests..")
message(STATUS "")
enable_testing()

set(CMAKE_CXX_STANDARD 11) # maybe not best solutio to set it globally? upgrate minimal cmake version to 3.8 or find another way to set it only for target with interface
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_PLATFORM_INDEPENDENT_CODE ON)

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include(../cmake/JPetFramework-Utilities.cmake)

set(UNIT_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetAnalysisTools/JPetAnalysisToolsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetCmdParser/JPetCmdParserTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetCommonTools/JPetCommonToolsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetGeomMapping/JPetGeomMappingTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetHadd/JPetHaddTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetManager/JPetManagerTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetParamAndDataFactory/JPetParamAndDataFactoryTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetProgressBarManager/JPetProgressBarTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetReader/JPetReaderTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTask/JPetTaskTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskChainExecutor/JPetTaskChainExecutorTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskFactory/JPetTaskFactoryTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskIO/JPetInputHandlerTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskIO/JPetTaskIOTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskIO/JPetTaskIOToolsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskLooper/JPetTaskLooperTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTimer/JPetTimerTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTreeHeader/JPetTreeHeaderTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetUnpacker/JPetUnpackerTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetWriter/JPetWriterTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetCachedFunction/JPetCachedFunctionTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetBaseSignal/JPetBaseSignalTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetEvent/JPetEventTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetEventType/JPetEventTypeTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetHit/JPetHitTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetLOR/JPetLORTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetPhysSignal/JPetPhysSignalTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetRawSignal/JPetRawSignalTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetRecoSignal/JPetRecoSignalTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetSigCh/JPetSigChTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetTimeWindow/JPetTimeWindowTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/GeantParser/JPetGeantEventInformation/JPetGeantEventInformationTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/GeantParser/JPetGeantEventPack/JPetGeantEventPackTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/GeantParser/JPetGeantParser/JPetGeantParserToolsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/GeantParser/JPetGeantScinHits/JPetGeantScinHitsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/GeantParser/JPetRandom/JPetRandomTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/MC/JPetMCHit/JPetMCHitTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionValidator/JPetOptionValidatorTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionsGenerator/JPetOptionsGeneratorTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionsGenerator/JPetOptionsGeneratorToolsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionsGenerator/JPetOptionsTypeHandlerTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionsTools/JPetOptionsToolsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionsTools/JPetOptionsTransformatorsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetBarrelSlot/JPetBarrelSlotTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetFEB/JPetFEBTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetFrame/JPetFrameTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetLayer/JPetLayerTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetPM/JPetPMTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetScin/JPetScinTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetTOMBChannel/JPetTOMBChannelTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetTRB/JPetTRBTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParametersTools/JPetParamBank/JPetParamBankTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParametersTools/JPetParamGetterAscii/JPetParamGetterAsciiTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParametersTools/JPetParamManager/JPetParamManagerTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParametersTools/JPetParamUtils/JPetParamUtilsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParametersTools/JPetParams/JPetParamsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParametersTools/JPetParamsFactory/JPetParamsFactoryTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Tasks/JPetParamBankHandlerTask/JPetParamBankHandlerTaskTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Tasks/JPetScopeConfigParser/JPetScopeConfigParserTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Tasks/JPetScopeLoader/JPetScopeLoaderTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Tasks/JPetSimplePhysSignalReco/HelperMathFunctionsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Tasks/JPetUnzipAndUnpackTask/JPetUnzipAndUnpackTaskTest.cpp
)

#Configure Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.50 REQUIRED COMPONENTS unit_test_framework)

if(NOT TARGET Boost::unit_test_framework)
    add_library(Boost::unit_test_framework IMPORTED INTERFACE)
    set_property(TARGET Boost::unit_test_framework PROPERTY
        INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
    set_property(TARGET Boost::unit_test_framework PROPERTY
        INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
endif()
#End of configuration of Boost

## Add custom target to create symlink from test dir to unitTestData
add_custom_target(link_target ALL
                  COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_SOURCE_DIR}/unitTestData ${CMAKE_CURRENT_BINARY_DIR}/unitTestData)


foreach(test_source IN ITEMS ${UNIT_TEST_SOURCES})
    get_filename_component(test ${test_source} NAME_WE)
    package_add_test(${test} ${test_source})
endforeach()

################################################################################
## Download test files with external script
## Does not do anything if data has been already downloaded
set(DOWNLOAD_DATA ${PROJECT_SOURCE_DIR}/download_data.sh ${PROJECT_SOURCE_DIR})
execute_process(COMMAND ${DOWNLOAD_DATA})
