cmake_minimum_required(VERSION 3.16)

project(RDtask VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set OpenSSL directories
set(OPENSSL_ROOT_DIR "C:/Program Files/OpenSSL")
set(OPENSSL_INCLUDE_DIR "C:/Program Files/OpenSSL/include")
set(OPENSSL_SSL_LIBRARY "C:/Program Files/OpenSSL/lib/libssl.lib")
set(OPENSSL_CRYPTO_LIBRARY "C:/Program Files/OpenSSL/lib/libcrypto.lib")

# Find OpenSSL package
find_package(OpenSSL REQUIRED)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Widgets)

qt_standard_project_setup()

qt_add_executable(appRDtask
    main.cpp
    FileHandler.cpp
    FileHandler.h
)

qt_add_qml_module(appRDtask
    URI RDtask
    VERSION 1.0
    QML_FILES
        Main.qml
        CustomButton.qml
        CustomTextInput.qml
)

set_target_properties(appRDtask PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Link OpenSSL libraries
target_link_libraries(appRDtask
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Widgets
    PRIVATE ${OPENSSL_SSL_LIBRARY}
    PRIVATE ${OPENSSL_CRYPTO_LIBRARY}
)

# Include OpenSSL headers
include_directories(${OPENSSL_INCLUDE_DIR})

include(GNUInstallDirs)
install(TARGETS appRDtask
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
