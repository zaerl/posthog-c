set(SOURCES
    init.c
)

# Build as shared or static library based on BUILD_SHARED option
if(BUILD_SHARED)
    add_library(posthog_lib SHARED ${SOURCES})
else()
    add_library(posthog_lib STATIC ${SOURCES})
endif()

target_include_directories(posthog_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(posthog_lib PRIVATE CURL::libcurl)
