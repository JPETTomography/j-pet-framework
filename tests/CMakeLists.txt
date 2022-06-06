message(STATUS "")
message(STATUS "Starting to configure libJPetFrameworkTests..")
message(STATUS "")
enable_testing()

set(UNIT_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetAnalysisTools/JPetAnalysisToolsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetCmdParser/JPetCmdParserTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetCommonTools/JPetCommonToolsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetHadd/JPetHaddTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetManager/JPetManagerTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetProgressBarManager/JPetProgressBarTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetReader/JPetReaderTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTask/JPetTaskTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskChainExecutor/JPetTaskChainExecutorTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskFactory/JPetTaskFactoryTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskIO/JPetInputHandlerTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskIO/JPetTaskIOToolsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskStreamIO/JPetTaskStreamIOTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskIOLoopPerSubTask/JPetTaskIOLoopPerSubTaskTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTaskLooper/JPetTaskLooperTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTimer/JPetTimerTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetTreeHeader/JPetTreeHeaderTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetWriter/JPetWriterTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Core/JPetCachedFunction/JPetCachedFunctionTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/Hits/JPetBaseHit/JPetBaseHitTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/Hits/JPetMCRecoHit/JPetMCRecoHitTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/Hits/JPetPhysRecoHit/JPetPhysRecoHitTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/Hits/JPetRecoHit/JPetRecoHitTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetEvent/JPetEventTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetEventType/JPetEventTypeTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetLOR/JPetLORTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/JPetTimeWindow/JPetTimeWindowTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/Signals/JPetBaseSignal/JPetBaseSignalTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/Signals/JPetChannelSignal/JPetChannelSignalTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/Signals/JPetMatrixSignal/JPetMatrixSignalTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/Signals/JPetPhysSignal/JPetPhysSignalTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/Signals/JPetPMSignal/JPetPMSignalTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/Signals/JPetRecoSignal/JPetRecoSignalTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/DataObjects/Signals/JPetShapedSignal/JPetShapedSignalTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/GeantParser/JPetGeantEventInformation/JPetGeantEventInformationTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/GeantParser/JPetGeantEventPack/JPetGeantEventPackTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/GeantParser/JPetGeantParser/JPetGeantParserToolsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/GeantParser/JPetGeantScinHits/JPetGeantScinHitsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/GeantParser/JPetSmearingFunctions/JPetSmearingFunctionsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/GeantParser/JPetGeantDecayTree/JPetGeantDecayTreeTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/MC/JPetRawMCHit/JPetRawMCHitTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionValidator/JPetOptionValidatorTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionsGenerator/JPetOptionsGeneratorTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionsGenerator/JPetOptionsGeneratorToolsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionsGenerator/JPetOptionsTypeHandlerTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionsTools/JPetOptionsToolsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Options/JPetOptionsTools/JPetOptionsTransformatorsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetChannel/JPetChannelTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetDataModule/JPetDataModuleTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetDataSource/JPetDataSourceTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetLayer/JPetLayerTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetMatrix/JPetMatrixTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetPM/JPetPMTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetScin/JPetScinTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetSetup/JPetSetupTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParamObjects/JPetSlot/JPetSlotTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParametersTools/JPetParamBank/JPetParamBankTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParametersTools/JPetParamGetterAscii/JPetParamGetterAsciiTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParametersTools/JPetParamManager/JPetParamManagerTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParametersTools/JPetParams/JPetParamsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/ParametersTools/JPetParamsFactory/JPetParamsFactoryTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Tasks/JPetParamBankHandlerTask/JPetParamBankHandlerTaskTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Tasks/JPetScopeConfigParser/JPetScopeConfigParserTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Tasks/JPetScopeLoader/JPetScopeLoaderTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Tasks/JPetSimplePhysSignalReco/HelperMathFunctionsTest.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/Tasks/JPetUnzipTask/JPetUnzipTaskTest.cpp
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

set(TESTS_NAMES "")
foreach(test_source IN ITEMS ${UNIT_TEST_SOURCES})
    get_filename_component(test ${test_source} NAME_WE)
    package_add_test(${test} ${test_source})
    list(APPEND TESTS_NAMES ${test}.x)
endforeach()

################################################################################
## Download test files with external script
## Does not do anything if data has been already downloaded
option(DOWNLOAD_DATA "Download data" ON)
if(DOWNLOAD_DATA)
  set(DOWNLOAD_BASE_PATH ${PROJECT_SOURCE_DIR})
  set(SHA_FILENAME all_data.sha)

  file(DOWNLOAD "http://sphinx.if.uj.edu.pl/framework/${SHA_FILENAME}" ${DOWNLOAD_BASE_PATH}/${SHA_FILENAME})
  file(READ ${DOWNLOAD_BASE_PATH}/${SHA_FILENAME} SHA_HASHES)
  string(REGEX REPLACE "\n" ";" SHA_HASHES "${SHA_HASHES}") #create cmake array from hash + file path
  foreach(SHA_HASH ${SHA_HASHES})
    string(REGEX REPLACE "  " ";" SHA_HASH "${SHA_HASH}") #Split hash and file path
    list(GET SHA_HASH 0 SHA256) #get sha hash
    list(GET SHA_HASH 1 PATH) #get file path
    string(REPLACE "ExamplesReformed/" "" SAVE_PATH ${PATH})

    if(EXISTS "${DOWNLOAD_BASE_PATH}/${SAVE_PATH}")
      file(SHA256 ${DOWNLOAD_BASE_PATH}/${SAVE_PATH} CURRENT_SHA256)
    endif(EXISTS "${DOWNLOAD_BASE_PATH}/${SAVE_PATH}")
    if(NOT "${CURRENT_SHA256}" STREQUAL "${SHA256}")
      message(STATUS "SHA value of ${DOWNLOAD_BASE_PATH}/${SAVE_PATH} to not match! Downloading file..")
      file(DOWNLOAD "http://sphinx.if.uj.edu.pl/framework/${PATH}" ${DOWNLOAD_BASE_PATH}/${SAVE_PATH} EXPECTED_HASH SHA256=${SHA256})
    endif(NOT "${CURRENT_SHA256}" STREQUAL "${SHA256}")
  endforeach(SHA_HASH ${SHA_HASHES})
  file(REMOVE ${DOWNLOAD_BASE_PATH}/${SHA_FILENAME})
endif()

##Add tests target
add_custom_target(tests DEPENDS ${TESTS_NAMES})
