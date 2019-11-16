cmake_minimum_required(VERSION 3.1)

project(QDoorBirdViewer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick DBus REQUIRED)

qt5_add_dbus_adaptor(ADAPTER_SRC dbus_interface.xml CDBusAdapter.h CDBusAdapter)
qt5_add_dbus_interface(IFC_SRC dbus_interface.xml DBifc)

add_executable(${PROJECT_NAME} "main.cpp" "CDBusAdapter.cpp" "CDBusIfc.cpp" "qml.qrc" ${ADAPTER_SRC} ${IFC_SRC})
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick Qt5::DBus)
