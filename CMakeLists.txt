cmake_minimum_required(VERSION 3.3.0 FATAL_ERROR)
project(qstyle-demo VERSION 5.12.0)

set(QT_MIN_VERSION "5.2.0")

find_package(ECM 5.42.0  NO_MODULE)
if (ECM_FOUND)
    set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_SOURCE_DIR}/cmake)

    include(KDEInstallDirs)
    include(KDECMakeSettings)
    include(KDECompilerSettings NO_POLICY_SCOPE)
endif()

include(FeatureSummary)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Core
    Gui
    Widgets
)

set(CMAKE_AUTOMOC ON)

########### next target ###############

# shouldn't be necessary?!
include_directories(${CMAKE_BINARY_DIR} "./")
# include_directories("./")
include_directories(kwidgetsaddons/src)

set(kwidgetsaddons_SOURCES
    kwidgetsaddons/src/kactionmenu.cpp
    kwidgetsaddons/src/kpagemodel.cpp
    kwidgetsaddons/src/kpageview.cpp
    kwidgetsaddons/src/kpageview_p.cpp
    kwidgetsaddons/src/kpagewidget.cpp
    kwidgetsaddons/src/kpagewidgetmodel.cpp
    kwidgetsaddons/src/ktitlewidget.cpp
    kwidgetsaddons/src/ktitlewidget.h
    kwidgetsaddons/src/loggingcategory.cpp
)
add_library(kwidgetsaddons STATIC ${kwidgetsaddons_SOURCES})
target_link_libraries(kwidgetsaddons PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets)

set(qstyle_demo_SOURCES
    oxygenbenchmarkwidget.cpp
    oxygenbuttondemowidget.cpp
    oxygendemodialog.cpp
    oxygendemowidget.cpp
    oxygenframedemowidget.cpp
    oxygeninputdemowidget.cpp
    oxygenlistdemowidget.cpp
    oxygenmdidemowidget.cpp
    oxygensimulator.cpp
    oxygensliderdemowidget.cpp
    oxygentabdemowidget.cpp
    oxygentabwidget.cpp
    oxygenstylechooser.cpp
    main.cpp
)

set(qstyle_demo_FORMS
    ui/oxygenbenchmarkwidget.ui
    ui/oxygenbuttondemowidget.ui
    ui/oxygendemodialog.ui
    ui/oxygenframedemowidget.ui
    ui/oxygeninputdemowidget.ui
    ui/oxygenlistdemowidget.ui
    ui/oxygenmdidemowidget.ui
    ui/oxygensliderdemowidget.ui
    ui/oxygentabdemowidget.ui
)

qt5_wrap_ui(qstyle_demo_ui ${qstyle_demo_FORMS})
qt5_add_resources(qstyle_demo_res resources.qrc)

add_executable(qstyle-demo WIN32 MACOSX_BUNDLE
  ${qstyle_demo_ui}
  ${qstyle_demo_res}
  ${qstyle_demo_SOURCES}
)

target_link_libraries(qstyle-demo kwidgetsaddons Qt5::Core Qt5::Gui Qt5::Widgets)

########### install files ###############
if(APPLE)
    if(NOT BUNDLE_INSTALL_DIR)
        set(BUNDLE_INSTALL_DIR "/Applications")
    endif()

    install(TARGETS qstyle-demo DESTINATION ${BUNDLE_INSTALL_DIR})
elseif(NOT WIN32)
    install(TARGETS qstyle-demo DESTINATION bin)
endif()

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
