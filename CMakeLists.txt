cmake_minimum_required(VERSION 3.0.0)

project(qicclient)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)

qt5_generate_moc(user.cxx user.moc TARGET ${PROJECT_NAME})
qt5_generate_moc(catalog.cxx catalog.moc TARGET ${PROJECT_NAME})
qt5_generate_moc(basket.cxx basket.moc TARGET ${PROJECT_NAME})
qt5_generate_moc(client.cxx client.moc TARGET ${PROJECT_NAME})

add_library(${PROJECT_NAME} SHARED
	user.moc
	catalog.moc
	basket.moc
	client.moc
	)

target_link_libraries(${PROJECT_NAME}
	Qt5::Core
	icclient
	)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES
	${PROJECT_NAME}/user.hxx
	${PROJECT_NAME}/product.hxx
	${PROJECT_NAME}/catalog.hxx
	${PROJECT_NAME}/basket.hxx
	${PROJECT_NAME}/client.hxx
	DESTINATION include/${PROJECT_NAME}
	)
