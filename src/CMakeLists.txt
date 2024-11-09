set(INCLUDE_DIRS
        .
        ${PROJECT_SOURCE_DIR}/extern
)

set(SOURCE_FILES
        kernel/bignum.cpp
        raylib_context.cpp
        clicker_app.cpp
)

add_library(clicker_app ${SOURCE_FILES})
target_link_libraries(clicker_app raylib EnTT nlohmann_json::nlohmann_json imgui rlimgui fmt::fmt imgui)
target_include_directories(clicker_app PUBLIC ${INCLUDE_DIRS})