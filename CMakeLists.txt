
# basis
cmake_minimum_required(VERSION 3.1)

set(project_name "OpencastIngest")

project(${project_name})

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake ${CMAKE_MODULE_PATH})

message("================================================")
message("Project: ${project_name}")
message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")


# curl
message("================================================")
if(WIN32)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		find_package(CURL REQUIRED PATHS "/c/Program Files/")
	else()
		find_package(CURL REQUIRED PATHS "/c/Program Files (x86)/")
	endif()
else()
	find_package(CURL REQUIRED)
endif()
message("Found Curl version: ${CURL_VERSION_STRING}")
if(WIN32)
	message("Libraries (before adjustment): ${CURL_LIBRARIES}")
	set(CURL_LIBRARIES CURL::libcurl)
endif()
message("Libraries: ${CURL_LIBRARIES}")
if(WIN32)
	message("Other Settings (like includes) are set by adding the lib")
else()
	message("Include dirs: ${CURL_INCLUDE_DIRS}")
endif()

set(libraries ${CURL_LIBRARIES} ${libraries})
if(!WIN32)
	set(includedirs ${CURL_INCLUDE_DIRS} ${includedirs})
endif()

# tinyxml2
message("================================================")
if(WIN32)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		find_package(TinyXML2 REQUIRED PATHS "/c/Program Files/")
	else()
		find_package(TinyXML2 REQUIRED PATHS "/c/Program Files (x86)/")
	endif()
else()
	find_package(TinyXML2 REQUIRED)
endif()
message("Using: tinyxml2")
if(WIN32)
	message("Libraries (before adjustment): ${TINYXML2_LIBRARIES}")
	set(TINYXML2_LIBRARIES tinyxml2)
endif()
message("Libraries: ${TINYXML2_LIBRARIES}")
if(WIN32)
	message("Other Settings (like includes) are set by adding the lib")
else()
	message("Include dirs: ${TINYXML2_INCLUDE_DIR}")
endif()

set(libraries ${TINYXML2_LIBRARIES} ${libraries})
if(!WIN32)
	set(includedirs ${TINYXML2_INCLUDE_DIR} ${includedirs})
endif()

# git version

message("================================================")
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)
	find_package(Git)
	if(GIT_FOUND)
		execute_process(COMMAND ${GIT_EXECUTABLE} describe
		    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
		    OUTPUT_VARIABLE ${project_name}_VERSION
		    ERROR_QUIET
		    OUTPUT_STRIP_TRAILING_WHITESPACE
		)
	else()
		set(${project_name}_VERSION "VERSION_NOT_FOUND")
	endif()
else()
	set(${project_name}_VERSION "VERSION_NOT_FOUND")
endif()
message("Build Version: ${${project_name}_VERSION}" )


# main

set(main_gnucxx_warn_err_compile_flags "-Wall -Wextra -pedantic-errors")

set(headers "src/libOpencastIngest.hpp" "src/libOpencastIngest.h")
set(source "src/libOpencastIngest.cpp" ${headers})

message("================================================")
message("Name (lib using C++11): ${project_name}")
message("Used source: ${source}")
message("Using libs: ${libraries}")
message("Using includedirs: ${includedirs}")

add_library(${project_name} SHARED ${source})

target_include_directories(${project_name} PRIVATE ${includedirs})
if(CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties(${project_name} PROPERTIES COMPILE_FLAGS ${main_gnucxx_warn_err_compile_flags})
endif()
set_target_properties(${project_name} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE ON
)
target_compile_definitions(${project_name} PRIVATE -DLIBOPENCASTINGEST_AS_DYNAMIC_LIB)
target_link_libraries(${project_name} ${libraries})

# main static version

set(name_static_lib ${project_name}_static)
message("Name (lib_static using C++11): ${name_static_lib}")

add_library(${name_static_lib} STATIC ${source})

target_include_directories(${name_static_lib} PRIVATE ${includedirs})
if(CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties(${name_static_lib} PROPERTIES COMPILE_FLAGS ${main_gnucxx_warn_err_compile_flags})
endif()
set_target_properties(${name_static_lib} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE ON
)
target_link_libraries(${name_static_lib} ${libraries})


# test

set(test_source "src/test.cpp")

set(test_name "testLibOpencastIngest")
set(test_libs "${project_name}" ${test_libs})

message("================================================")
message("Name (exe using C++11): ${test_name}")
message("Used source: ${test_source}")
message("Using libs: ${test_libs}")

add_executable(${test_name} ${test_source})

set_target_properties(${test_name} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
target_compile_definitions(${test_name} PRIVATE -DLIBOPENCASTINGEST_AS_DYNAMIC_LIB)
target_link_libraries(${test_name} ${test_libs})

message("================================================")
# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "lib${project_name}")
set(CPACK_PACKAGE_VERSION "${${project_name}_VERSION}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/license")
set(CPACK_PACKAGING_INSTALL_PREFIX "/")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}.${CMAKE_SYSTEM_PROCESSOR}")
if(WIN32)
set(CPACK_GENERATOR "ZIP")
message("Packaging type: ZIP")
message("Packaging output: ${CPACK_PACKAGE_FILE_NAME}.zip")
else()
set(CPACK_GENERATOR "TGZ")
message("Packaging type: TGZ")
message("Packaging output: ${CPACK_PACKAGE_FILE_NAME}.tar.gz")
endif()
include(CPack)

install(FILES ${headers} DESTINATION include)
install(TARGETS ${project_name} DESTINATION lib)
install(TARGETS ${name_static_lib} DESTINATION lib)
