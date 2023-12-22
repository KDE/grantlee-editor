cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(PIM_VERSION "5.24.5")
project(grantlee-editor VERSION ${PIM_VERSION})
set(RELEASE_SERVICE_VERSION "23.08.5")
set(KF_MIN_VERSION "5.105.0")

find_package(ECM ${KF_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(ECMInstallIcons)


include(ECMSetupVersion)
include(ECMAddTests)

include(GenerateExportHeader)
include(ECMGenerateHeaders)

include(FeatureSummary)
include(KDEGitCommitHooks)
include(KDEClangFormat)
file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES *.cpp *.h *.c)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})
include(CheckFunctionExists)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMAddAppIcon)
include(ECMQtDeclareLoggingCategory)
include(ECMDeprecationSettings)

# Do NOT add quote
set(KDEPIM_DEV_VERSION)

# add an extra space
if(DEFINED KDEPIM_DEV_VERSION)
    set(KDEPIM_DEV_VERSION " ${KDEPIM_DEV_VERSION}")
endif()

set(KDEPIM_VERSION "${PIM_VERSION}${KDEPIM_DEV_VERSION} (${RELEASE_SERVICE_VERSION})")

set(KDEPIM_LIB_VERSION "${PIM_VERSION}")
set(KDEPIM_LIB_SOVERSION "5")
set(MESSAGELIB_LIB_VERSION "5.24.4")

set(AKONADI_MIMELIB_VERSION "5.24.4")
set(AKONADI_CONTACT_VERSION "5.24.4")
set(KPIMTEXTEDIT_LIB_VERSION "5.24.4")
set(LIBGRANTLEETHEME_LIB_VERSION "5.24.4")
set(QT_REQUIRED_VERSION "5.15.2")
if (QT_MAJOR_VERSION STREQUAL "6")
    set(QT_REQUIRED_VERSION "6.4.0")
    set(KF_MIN_VERSION "5.240.0")
    set(KF_MAJOR_VERSION "6")
else()
    set(KF_MAJOR_VERSION "5")
endif()
set(KIMAP_LIB_VERSION "5.24.4")
set(PIMCOMMON_LIB_VERSION "5.24.4")
set(KPIM_MIME_VERSION "5.24.4")
find_package(Qt${QT_MAJOR_VERSION} ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets WebEngineWidgets)

# Find KF5 package
find_package(KF${KF_MAJOR_VERSION}Crash ${KF_MIN_VERSION} REQUIRED)
find_package(KF${KF_MAJOR_VERSION}DBusAddons ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}DocTools ${KF_MIN_VERSION} REQUIRED)
find_package(KF${KF_MAJOR_VERSION}XmlGui ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}Archive ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KPim${KF_MAJOR_VERSION}PimCommonAkonadi ${PIMCOMMON_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim${KF_MAJOR_VERSION}MessageViewer ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim${KF_MAJOR_VERSION}GrantleeTheme ${LIBGRANTLEETHEME_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim${KF_MAJOR_VERSION}AkonadiMime ${AKONADI_MIMELIB_VERSION} CONFIG REQUIRED)
find_package(KPim${KF_MAJOR_VERSION}AkonadiContact ${AKONADI_CONTACT_VERSION} CONFIG REQUIRED)
find_package(KPim${KF_MAJOR_VERSION}ContactEditor ${AKONADI_CONTACT_VERSION} CONFIG REQUIRED)
find_package(KPim${KF_MAJOR_VERSION}IMAP ${KIMAP_LIB_VERSION} CONFIG REQUIRED)

# Find KdepimLibs Package
find_package(KPim${KF_MAJOR_VERSION}TextEdit ${KPIMTEXTEDIT_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim${KF_MAJOR_VERSION}Mime ${KPIM_MIME_VERSION} CONFIG REQUIRED)

find_package(KF${KF_MAJOR_VERSION}SyntaxHighlighting ${KF_MIN_VERSION} CONFIG REQUIRED)


include_directories(${grantlee-editor_SOURCE_DIR} ${grantlee-editor_BINARY_DIR})

ecm_set_disabled_deprecation_versions(QT 6.4  KF 5.105.0)



configure_file(grantleeeditor-version.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/grantleeeditor-version.h @ONLY)
option(USE_UNITY_CMAKE_SUPPORT "Use UNITY cmake support (speedup compile time)" OFF)

set(COMPILE_WITH_UNITY_CMAKE_SUPPORT OFF)
if (USE_UNITY_CMAKE_SUPPORT)
    set(COMPILE_WITH_UNITY_CMAKE_SUPPORT ON)
endif()
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
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
ki18n_install(po)
kdoctools_install(po)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
