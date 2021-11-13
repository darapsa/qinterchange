cmake_minimum_required(VERSION 3.5)
project(qicclient)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Core)
set(HDRS
	${PROJECT_NAME}/catalog.hxx
	${PROJECT_NAME}/product.hxx
	${PROJECT_NAME}/ord.hxx
	${PROJECT_NAME}/member.hxx
	${PROJECT_NAME}/admin.hxx
	)
set(SRCS
	${PROJECT_NAME}.hxx
	${HDRS}
	client.cxx
	catalog.cxx
	ord.cxx
	member.cxx
	admin.cxx
	)
if (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
	include_directories(/usr/local/include)
	link_directories(/usr/local/lib)
endif()
if (EMSCRIPTEN OR IOS)
	add_library(${PROJECT_NAME} STATIC ${SRCS})
else()
	add_library(${PROJECT_NAME} SHARED ${SRCS})
endif()
target_link_libraries(${PROJECT_NAME}
	Qt5::Core
	icclient
	)
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${PROJECT_NAME}.hxx DESTINATION include)
install(FILES ${HDRS} DESTINATION include/${PROJECT_NAME})
