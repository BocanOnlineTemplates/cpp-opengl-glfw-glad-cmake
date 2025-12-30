include(FetchContent)

option(GLM_BUILD_LIBRARY "" OFF)
option(GLM_BUILD_TESTS "" OFF)
option(GLM_BUILD_INSTALL "" OFF)

option(GLM_ENABLE_CXX_17 "Enable C++ 17" ON)
option(GLM_ENABLE_CXX_20 "Enable C++ 20" OFF)

FetchContent_Declare(
    glm
    GIT_REPOSITORY  https://github.com/g-truc/glm.git
    GIT_TAG         1.0.2
    GIT_SHALLOW     TRUE
    GIT_PROGRESS    TRUE
)

message("Fetching GLM...")
FetchContent_MakeAvailable(glm)
