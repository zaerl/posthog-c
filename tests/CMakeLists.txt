set(TEST_SOURCES
    attractor/attractor.c
    http-client.c
    init.c
    test.c
)

if(BUILD_CPP)
    # Add C++ test sources
endif()

# Add getopt compatibility for Windows
#if(WIN32)
#    list(APPEND TEST_SOURCES ../src/shell/getopt/getopt.c)
#endif()

add_executable(posthog-test ${TEST_SOURCES})

target_link_libraries(posthog-test PRIVATE posthog_lib)

# Force C++ compilation if BUILD_CPP is enabled
if(BUILD_CPP)
    set_target_properties(posthog-test PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )
    set_source_files_properties(${TEST_SOURCES} PROPERTIES LANGUAGE CXX)
endif()

#if(WIN32)
    # Suppress warnings for Windows
#    target_compile_options(mojibake-test
#        PRIVATE
#        /wd4996 # Suppress 'the POSIX name for this item is deprecated'
#        /wd4245 # Suppress 'signed/unsigned mismatch'
#        /wd4702 # Suppress 'unreachable code'
#        /wd4701 # Suppress 'potentially uninitialized local variable'
#    )
#endif()

# Add test to CTest
add_test(NAME "Init" COMMAND posthog-test -f init)
