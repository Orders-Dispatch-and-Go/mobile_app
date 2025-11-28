cmake_minimum_required(VERSION 3.16)

project(untitled VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Qml Gui Widgets)
find_package(KF6Kirigami2 REQUIRED)   # главный модуль Kirigami

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appuntitled
    main.cpp

    model/include/backend.hpp
    model/include/theme_provider.hpp
    model/include/screens.hpp

    model/include/auth/userinfo.hpp
    model/include/auth/iauth.hpp
    model/include/auth/moc_auth.hpp

    model/include/profile/iprofile.hpp
    model/include/profile/moc_profile.hpp

    model/src/backend.cpp
    model/src/theme_provider.cpp
    model/src/auth/userinfo.cpp
)

target_include_directories(appuntitled PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/model/include
)

qt_add_qml_module(appuntitled
    URI untitled
    VERSION 1.0
    QML_FILES
        Main.qml
        view/screens/LoginScreen.qml
        view/screens/MainScreen.qml
        view/screens/ProfileScreen.qml
        view/screens/StockScreen.qml
        view/screens/WayScreen.qml

        view/components/Login/EmailField.qml
        view/components/Login/PasswordField.qml

        view/components/common/ActionButton.qml

        view/components/Orders/Order.qml
    RESOURCES
        res.qrc
)

target_link_libraries(appuntitled
    PRIVATE
        Qt6::Quick
        Qt6::Gui
        Qt6::Qml
        KF6::Kirigami2
)

set_target_properties(appuntitled PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

include(GNUInstallDirs)
install(TARGETS appuntitled
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
