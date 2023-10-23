cmake_minimum_required (VERSION 3.13)

project(lc_client)

    #this is heuristically generated, and may not be correct
    #find_package(Qt6 CONFIG REQUIRED)
    # note: 42 additional targets are not displayed.
    #target_link_libraries(lc_client PRIVATE DB2::DB2 PPS::PPS Oracle::OCI Libb2::Libb2)

    #find_package(Qt6Concurrent CONFIG REQUIRED)
    #target_link_libraries(lc_client PRIVATE Qt::Concurrent Qt6::Concurrent Qt::ConcurrentPrivate Qt6::ConcurrentPrivate)

    #find_package(Qt6Core CONFIG REQUIRED)
    #target_link_libraries(lc_client PRIVATE Qt::Core Qt6::Core Qt::CorePrivate Qt6::CorePrivate)

    #find_package(Qt6DBus CONFIG REQUIRED)
    #target_link_libraries(lc_client PRIVATE Qt::DBus Qt6::DBus Qt::DBusPrivate Qt6::DBusPrivate)

    #find_package(Qt6DeviceDiscoverySupportPrivate CONFIG REQUIRED)
   # target_link_libraries(lc_client PRIVATE Qt::DeviceDiscoverySupportPrivate Qt6::DeviceDiscoverySupportPrivate)

   # find_package(Qt6EntryPointPrivate CONFIG REQUIRED)
   # target_link_libraries(lc_client PRIVATE Qt::EntryPointPrivate Qt6::EntryPointPrivate Qt6::EntryPointImplementation)

   # find_package(Qt6ExampleIconsPrivate CONFIG REQUIRED)
    #target_link_libraries(lc_client PRIVATE Qt::ExampleIconsPrivate Qt6::ExampleIconsPrivate Qt6::ExampleIconsPrivate_resources_1)

    #find_package(Qt6FbSupportPrivate CONFIG REQUIRED)
    #target_link_libraries(lc_client PRIVATE Qt::FbSupportPrivate Qt6::FbSupportPrivate)

    #find_package(Qt6Gui CONFIG REQUIRED)
    # note: 8 additional targets are not displayed.
   # target_link_libraries(lc_client PRIVATE Qt::Gui Qt6::Gui Qt::GuiPrivate Qt6::GuiPrivate)
   #
    #find_package(Qt6Network CONFIG REQUIRED)
    # note: 4 additional targets are not displayed.
    #target_link_libraries(lc_client PRIVATE Qt::Network Qt6::Network Qt6::QNLMNIPlugin Qt::NetworkPrivate)

    #find_package(Qt6OpenGL CONFIG REQUIRED)
    #target_link_libraries(lc_client PRIVATE Qt::OpenGL Qt6::OpenGL Qt::OpenGLPrivate Qt6::OpenGLPrivate)

    #find_package(Qt6OpenGLWidgets CONFIG REQUIRED)
    #target_link_libraries(lc_client PRIVATE Qt::OpenGLWidgets Qt6::OpenGLWidgets Qt::OpenGLWidgetsPrivate Qt6::OpenGLWidgetsPrivate)

    #find_package(Qt6PrintSupport CONFIG REQUIRED)
    #target_link_libraries(lc_client PRIVATE Qt::PrintSupport Qt6::PrintSupport Qt::PrintSupportPrivate Qt6::PrintSupportPrivate)

    #find_package(Qt6Sql CONFIG REQUIRED)
    # note: 2 additional targets are not displayed.
   # target_link_libraries(lc_client PRIVATE Qt::Sql Qt6::Sql Qt::SqlPrivate Qt6::SqlPrivate)

    #find_package(Qt6Test CONFIG REQUIRED)
    #target_link_libraries(lc_client PRIVATE Qt::Test Qt6::Test Qt::TestPrivate Qt6::TestPrivate)

    #find_package(Qt6Widgets CONFIG REQUIRED)
    # note: 1 additional targets are not displayed.
    #target_link_libraries(lc_client PRIVATE Qt::Widgets Qt6::Widgets Qt::WidgetsPrivate Qt6::WidgetsPrivate)

    #find_package(Qt6Xml CONFIG REQUIRED)
    #target_link_libraries(lc_client PRIVATE Qt::Xml Qt6::Xml Qt::XmlPrivate Qt6::XmlPrivate)



find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_path(LUABRIDGE_INCLUDE_DIRS "LuaBridge/List.h")
find_package(Lua REQUIRED)
find_package(imgui CONFIG REQUIRED)




target_link_libraries(lc_client PUBLIC glfw glad::glad EnTT::EnTT)
target_link_libraries(lc_client PUBLIC glm::glm)
target_link_libraries(lc_client PRIVATE assimp::assimp)
target_link_libraries(lc_client PRIVATE pugixml::pugixml)
target_link_libraries(lc_client PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(lc_client PRIVATE ${LUABRIDGE_INCLUDE_DIRS})
target_include_directories(lc_client PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(lc_client PRIVATE ${LUA_LIBRARIES})
target_link_libraries(lc_client PRIVATE imgui::imgui)

#target_link_libraries(lc_client PRIVATE eng::rc)
target_link_libraries(lc_client PRIVATE stb)   

target_sources(lc_client 
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/lc_client/i_game_logic.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/src/lc_client/loop.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/lc_client/loop.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/src/lc_client/systems.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/lc_client/systems.h"
)

add_subdirectory("include/ldk_client/local_engine")

add_subdirectory("src/lc_client/local_engine")

add_subdirectory("src/lc_client/eng_graphics")
add_subdirectory("src/lc_client/eng_entties")
add_subdirectory("src/lc_client/eng_input")
add_subdirectory("src/lc_client/eng_procedures")
add_subdirectory("src/lc_client/eng_model")
add_subdirectory("src/lc_client/eng_scene")
add_subdirectory("src/lc_client/eng_lighting")
add_subdirectory("src/lc_client/eng_script")
add_subdirectory("src/lc_client/eng_gui")
add_subdirectory("src/lc_client/eng_cubemaps")
add_subdirectory("src/lc_client/tier0")
add_subdirectory("src/lc_client/tier1")
add_subdirectory("src/lc_client/exceptions")
add_subdirectory("src/lc_client/util")


#target_compile_definitions(lc_client PUBLIC USE_BARRY) #for preprocessor definitions
target_include_directories(lc_client
    PUBLIC
        $<INSTALL_INTERFACE:/include>
        $<INSTALL_INTERFACE:/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)
