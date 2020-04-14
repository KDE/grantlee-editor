cmake_minimum_required(VERSION 3.5)
set(PIM_VERSION "5.14.40")
project(grantlee-editor VERSION ${PIM_VERSION})
set(RELEASE_SERVICE_VERSION "20.07.40")
set(KF5_MIN_VERSION "5.69.0")

find_package(ECM ${KF5_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(ECMInstallIcons)


include(ECMSetupVersion)
include(ECMAddTests)

include(GenerateExportHeader)
include(ECMGenerateHeaders)

include(FeatureSummary)
include(CheckFunctionExists)
include(ECMGeneratePriFile)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMAddAppIcon)
include(ECMQtDeclareLoggingCategory)

# Do NOT add quote
set(KDEPIM_DEV_VERSION alpha)

# add an extra space
if(DEFINED KDEPIM_DEV_VERSION)
    set(KDEPIM_DEV_VERSION " ${KDEPIM_DEV_VERSION}")
endif()

set(KDEPIM_VERSION "${PIM_VERSION}${KDEPIM_DEV_VERSION} (${RELEASE_SERVICE_VERSION})")

set(KDEPIM_LIB_VERSION "${PIM_VERSION}")
set(KDEPIM_LIB_SOVERSION "5")
set(MESSAGELIB_LIB_VERSION_LIB "5.14.40")

set(AKONADI_MIMELIB_VERSION "5.14.40")
set(KPIMTEXTEDIT_LIB_VERSION "5.14.40")
set(KDEPIM_APPS_LIB_VERSION_LIB "5.14.40")
set(LIBGRANTLEETHEME_LIB_VERSION_LIB "5.14.40")
set(LIBKLEO_LIB_VERSION_LIB "5.14.40")
set(QT_REQUIRED_VERSION "5.11.0")
set(KIMAP_LIB_VERSION "5.14.40")
set(PIMCOMMON_LIB_VERSION_LIB "5.14.40")
find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets WebEngine WebEngineWidgets)

# Find KF5 package
find_package(KF5Crash ${KF5_MIN_VERSION} REQUIRED)
find_package(KF5DBusAddons ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5DocTools ${KF5_MIN_VERSION} REQUIRED)
find_package(KF5XmlGui ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5TextEditor ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5NewStuff ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Archive ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5PimCommonAkonadi ${PIMCOMMON_LIB_VERSION_LIB} CONFIG REQUIRED)
find_package(KF5MessageViewer ${MESSAGELIB_LIB_VERSION_LIB} CONFIG REQUIRED)
find_package(KF5GrantleeTheme ${LIBGRANTLEETHEME_LIB_VERSION_LIB} CONFIG REQUIRED)
find_package(KF5AkonadiMime ${AKONADI_MIMELIB_VERSION} CONFIG REQUIRED)
find_package(KF5Libkleo ${LIBKLEO_LIB_VERSION_LIB} CONFIG REQUIRED)
find_package(KF5IMAP ${KIMAP_LIB_VERSION} CONFIG REQUIRED)

# Find KdepimLibs Package
find_package(KF5KaddressbookGrantlee ${KDEPIM_APPS_LIB_VERSION_LIB} CONFIG REQUIRED)
find_package(KF5PimTextEdit ${KPIMTEXTEDIT_LIB_VERSION} CONFIG REQUIRED)


find_package(KF5SyntaxHighlighting ${KF5_MIN_VERSION} CONFIG REQUIRED)


include_directories(${grantlee-editor_SOURCE_DIR} ${grantlee-editor_BINARY_DIR})

if (EXISTS "${CMAKE_SOURCE_DIR}/.git")
   add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x050e00)
   add_definitions(-DKF_DISABLE_DEPRECATED_BEFORE_AND_AT=0x054400)
endif()

add_definitions(-DQT_NO_FOREACH)

configure_file(grantleeeditor-version.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/grantleeeditor-version.h @ONLY)

add_subdirectory(headerthemeeditor)
add_subdirectory(contactthemeeditor)
add_subdirectory(grantleethemeeditor)
add_subdirectory(contactprintthemeeditor)

ecm_qt_install_logging_categories(
        EXPORT GRANTLEEEDITOR
        FILE grantleeditor.categories
        DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
        )

add_subdirectory(doc)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
