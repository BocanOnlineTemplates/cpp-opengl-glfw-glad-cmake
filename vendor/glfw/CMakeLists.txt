include(FetchContent)

option(BUILD_SHARED_LIBS "Build shared libraries." OFF)
option(GLFW_BUILD_EXAMPLES "" OFF)
option(GLFW_BUILD_TESTS "" OFF)
option(GLFW_BUILD_DOCS "" OFF)
option(GLFW_INSTALL "" OFF)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY  https://github.com/glfw/glfw.git
    GIT_TAG         3.4
    GIT_SHALLOW     TRUE
    GIT_PROGRESS    TRUE
)

message("Fetching GLFW...")
FetchContent_MakeAvailable(glfw)
