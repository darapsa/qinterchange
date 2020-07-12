cmake_minimum_required(VERSION 3.5)

project(qicclient)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)

add_library(${PROJECT_NAME} SHARED
	${PROJECT_NAME}/member.hxx
	${PROJECT_NAME}/catalog.hxx
	${PROJECT_NAME}/basket.hxx
	${PROJECT_NAME}/client.hxx
	member.cxx
	catalog.cxx
	basket.cxx
	client.cxx
	)

target_link_libraries(${PROJECT_NAME}
	Qt5::Core
	icclient
	)

target_compile_definitions(${PROJECT_NAME} PRIVATE QICCLIENT)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES
	${PROJECT_NAME}/member.hxx
	${PROJECT_NAME}/product.hxx
	${PROJECT_NAME}/catalog.hxx
	${PROJECT_NAME}/basket.hxx
	${PROJECT_NAME}/client.hxx
	DESTINATION include/${PROJECT_NAME}
	)
