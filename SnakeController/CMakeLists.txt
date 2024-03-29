set(TARGET_NAME SnakeController)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SNAKE_SOURCES
    SnakeController.cpp
)
set(SNAKE_HEADERS
    SnakeController.hpp
    SnakeInterface.hpp
)
add_library(${TARGET_NAME} STATIC ${SNAKE_SOURCES} ${SNAKE_HEADERS})
target_link_libraries(${TARGET_NAME} DynamicEvents)


enable_testing()
set(TEST_SOURCES
    Tests/SnakeControllerTestSuite.cpp
)
set(MOCK_LIST
    Tests/Mocks/PortMock.hpp
    Tests/Mocks/EventMatchers.hpp
)
set(UT_DRIVER ${TARGET_NAME}_UT)
add_executable(${UT_DRIVER} ${TEST_SOURCES} ${MOCK_LIST})
target_link_libraries(${UT_DRIVER} ${TARGET_NAME} gmock_main gtest gmock)

if (BUILD_COVERAGE_UNIT_TESTS)
    set_target_properties(${TARGET_NAME} PROPERTIES COMPILE_FLAGS ${CMAKE_CXX_FLAGS_COVERAGE})
    set_target_properties(${UT_DRIVER} PROPERTIES COMPILE_FLAGS ${CMAKE_CXX_FLAGS_COVERAGE})
    target_link_libraries(${UT_DRIVER} ${CMAKE_CXX_COVERAGE_LIBRARY})
    setup_target_for_coverage(${UT_DRIVER}_COV ${UT_DRIVER} ${COVERAGE_REPORT_LOCATION})
endif()

add_test(tests ${UT_DRIVER})
