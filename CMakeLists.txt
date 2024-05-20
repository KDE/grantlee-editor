cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(PIM_VERSION "6.1.40")
project(grantlee-editor VERSION ${PIM_VERSION})
set(RELEASE_SERVICE_VERSION "24.07.40")
set(KF_MIN_VERSION "6.2.0")
set(QT_REQUIRED_VERSION "6.6.0")
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
include(ECMFeatureSummary)

# Do NOT add quote
set(KDEPIM_DEV_VERSION alpha)

# add an extra space
if(DEFINED KDEPIM_DEV_VERSION)
    set(KDEPIM_DEV_VERSION " ${KDEPIM_DEV_VERSION}")
endif()

set(KDEPIM_VERSION "${PIM_VERSION}${KDEPIM_DEV_VERSION} (${RELEASE_SERVICE_VERSION})")

set(KDEPIM_LIB_VERSION "${PIM_VERSION}")
set(KDEPIM_LIB_SOVERSION "6")
set(MESSAGELIB_LIB_VERSION "6.1.40")

set(AKONADI_CONTACT_VERSION "6.1.40")
set(KPIMTEXTEDIT_LIB_VERSION "6.1.40")
set(LIBGRANTLEETHEME_LIB_VERSION "6.1.40")
set(KIMAP_LIB_VERSION "6.1.40")
set(PIMCOMMON_LIB_VERSION "6.1.40")
set(KPIM_MIME_VERSION "6.1.40")
set(KTEXTADDONS_MIN_VERSION "1.5.4")
find_package(Qt6 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets WebEngineWidgets)

# Find KF6 package
find_package(KF6Crash ${KF_MIN_VERSION} REQUIRED)
find_package(KF6DBusAddons ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6DocTools ${KF_MIN_VERSION} REQUIRED)
find_package(KF6XmlGui ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6Archive ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KPim6PimCommon ${PIMCOMMON_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6MessageViewer ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6GrantleeTheme ${LIBGRANTLEETHEME_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6AkonadiContactWidgets ${AKONADI_CONTACT_VERSION} CONFIG REQUIRED)
find_package(KPim6IMAP ${KIMAP_LIB_VERSION} CONFIG REQUIRED)

# Find KdepimLibs Package
find_package(KPim6Mime ${KPIM_MIME_VERSION} CONFIG REQUIRED)

find_package(KF6SyntaxHighlighting ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6TextCustomEditor ${KTEXTADDONS_MIN_VERSION} CONFIG REQUIRED)


include_directories(${grantlee-editor_SOURCE_DIR} ${grantlee-editor_BINARY_DIR})

add_definitions(-DQT_NO_CONTEXTLESS_CONNECT)
ecm_set_disabled_deprecation_versions(QT 6.7.0 KF 6.2.0)



configure_file(grantleeeditor-version.h.in ${CMAKE_CURRENT_BINARY_DIR}/grantleeeditor-version.h @ONLY)
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
ecm_feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
