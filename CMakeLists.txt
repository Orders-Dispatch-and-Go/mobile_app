cmake_minimum_required(VERSION 3.16)

project(untitled VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Qml Gui Widgets Location Positioning)
find_package(Qt6Keychain REQUIRED)
find_package(KF6Kirigami2 REQUIRED)

qt_standard_project_setup(REQUIRES 6.8)

set(ADDRESS_FILE ${CMAKE_SOURCE_DIR}/address.txt)

file(READ ${ADDRESS_FILE} BACKEND_ADDRESS)
string(STRIP "${BACKEND_ADDRESS}" BACKEND_ADDRESS)

set(GENERATED_DIR ${CMAKE_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_DIR})

configure_file(
    ${CMAKE_SOURCE_DIR}/backend_address.h.in
    ${GENERATED_DIR}/backend_address.h
    @ONLY
)

qt_add_executable(appuntitled
    main.cpp

    model/include/dto/abstract_dto.hpp
    model/include/dto/station_dto.hpp
    model/include/dto/order_dto.hpp
    model/include/dto/route_dto.hpp
    model/include/dto/user_dto.hpp

    model/include/backend.hpp
    model/include/theme_provider.hpp
    model/include/screens.hpp

    model/include/auth/userinfo.hpp
    model/include/auth/iauth.hpp
    model/include/auth/auth.hpp

    model/include/utils/http_client.hpp
    model/include/utils/reply.hpp

    model/include/profile/iprofile.hpp
    model/include/profile/moc_profile.hpp

    model/include/state.hpp

    model/include/trip/icurrent_trip.hpp
    model/include/trip/current_trip.hpp

    model/src/backend.cpp
    model/src/theme_provider.cpp

    model/src/auth/userinfo.cpp
    model/src/auth/auth.cpp

    model/src/utils/http_client.cpp

    model/src/state.cpp

    model/src/trip/icurrent_trip.cpp
    model/src/trip/current_trip.cpp
)

target_include_directories(appuntitled PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/model/include
    ${GENERATED_DIR}
)

qt_add_qml_module(appuntitled
    URI untitled
    VERSION 1.0
    QML_FILES
        Main.qml
        view/screens/LoginScreen.qml
        view/screens/ProfileScreen.qml
        view/screens/StartRouteScreen.qml
        view/screens/GetOrdersScreen.qml
        view/screens/FinishRouteScreen.qml
        view/screens/FinishOrderScreen.qml
        view/screens/RouteScreen.qml

        view/components/Map/RouteDialog.qml
        view/components/Map/Marker.qml
        view/components/Map/WayPoint.qml
        view/components/Map/ZoomButton.qml

        view/components/Login/EmailField.qml
        view/components/Login/PasswordField.qml

        view/components/common/ActionButton.qml

        view/components/Orders/AddressButton.qml
        view/components/Orders/Order.qml
        view/components/Orders/OrderCard.qml
        view/components/Orders/OrderDialog.qml
        view/components/Orders/Dimension.qml
        view/components/Orders/ShowSizes.qml
        view/components/Orders/MinPrice.qml
        view/components/Orders/Sizes.qml
        view/components/Orders/Filter.qml
        view/components/Orders/RouteDate.qml
        view/components/Orders/RouteHighlight.qml

    RESOURCES
        res.qrc
)

target_link_libraries(appuntitled
    PRIVATE
        Qt6::Quick
        Qt6::Location
        Qt6::Positioning
        Qt6::Gui
        Qt6::Qml
        Qt6Keychain::Qt6Keychain
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
