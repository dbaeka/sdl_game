project(core)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
# adding the Google_Tests_run target
add_executable(core_tests_run TestExample.cpp FixtureExample.cpp)

# linking Google_Tests_run with DateConverter_lib which will be tested
#target_link_libraries(Google_Tests_run core_lib)

target_link_libraries(core_tests_run gtest gtest_main)
