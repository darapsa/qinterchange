cmake_minimum_required(VERSION 3.5)
project(qicclient)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Core)

set(HDRS
	${PROJECT_NAME}/product.hxx
	${PROJECT_NAME}/catalog.hxx
	${PROJECT_NAME}/ord.hxx
	${PROJECT_NAME}/member.hxx
	${PROJECT_NAME}/admin.hxx
	${PROJECT_NAME}/client.hxx
	)

set(SRCS
	${HDRS}
	catalog.cxx
	ord.cxx
	member.cxx
	admin.cxx
	client.cxx
	)

if (EMSCRIPTEN OR IOS)
	add_library(${PROJECT_NAME} STATIC ${SRCS})
else()
	add_library(${PROJECT_NAME} SHARED ${SRCS})
endif()

target_link_libraries(${PROJECT_NAME}
	Qt5::Core
	icclient
	)

target_compile_definitions(${PROJECT_NAME} PRIVATE QICCLIENT)
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HDRS} DESTINATION include/${PROJECT_NAME})
