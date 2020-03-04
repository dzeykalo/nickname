cmake_minimum_required(VERSION 3.5)

set( PRO_PATCH $ENV{TRAVIS_BUILD_NUMBER})
if (NOT "${PRO_PATCH}")
    set(PRO_PATCH "1")
endif (NOT "${PRO_PATCH}")

project(nickname VERSION 0.0.${PRO_PATCH})

add_executable(nickname main.cpp radix_trie.h)

set_target_properties(
        nickname PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)

install(TARGETS nickname RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_NAME nickname)
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_CONTACT mr.alligator@yandex.ru)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
include(CPack)