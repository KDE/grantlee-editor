add_definitions(-DTRANSLATION_DOMAIN=\"libgrantleethemeeditor\")


set(libgrantleethemeeditor_SRCS 
    newthemedialog.cpp
    themeeditortabwidget.cpp
    managethemes.cpp
    themesession.cpp
    editorwidget.cpp
    desktopfilepage.cpp
    editorpage.cpp
    previewwidget.cpp
    configurewidget.cpp
    grantleeplaintexteditor.cpp
    newthemedialog.h
    themeeditortabwidget.h
    managethemes.h
    themesession.h
    editorwidget.h
    desktopfilepage.h
    editorpage.h
    previewwidget.h
    configurewidget.h
    grantleeplaintexteditor.h
)

kconfig_add_kcfg_files(libgrantleethemeeditor_SRCS
    settings/globalsettings_base.kcfgc
)

ki18n_wrap_ui(libgrantleethemeeditor_SRCS
    ui/configurewidget.ui
)

ecm_qt_declare_logging_category(libgrantleethemeeditor_SRCS HEADER grantleethemeeditor_debug.h IDENTIFIER GRANTLEETHEMEEDITOR_LOG CATEGORY_NAME org.kde.pim.grantleethemeeditor
        DESCRIPTION "grantleeeditor (grantleethemeeditor)"
        OLD_CATEGORY_NAMES log_grantleethemeeditor
        EXPORT GRANTLEEEDITOR
)


add_library(grantleethemeeditor ${libgrantleethemeeditor_SRCS})
if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(grantleethemeeditor PROPERTIES UNITY_BUILD ON)
endif()

generate_export_header(grantleethemeeditor BASE_NAME grantleethemeeditor)

target_include_directories(grantleethemeeditor PUBLIC "$<BUILD_INTERFACE:${grantleeditor_SOURCE_DIR};${grantleethemeeditor_SOURCE_DIR};${grantleethemeeditor_BINAY_DIR}>")

target_link_libraries(grantleethemeeditor
    PUBLIC
    KF6::Archive
    PRIVATE
    KF6::KIOWidgets
    KPim6::PimCommon
    KF6::I18n
    KF6::SyntaxHighlighting
    KF6::TextCustomEditor
)

install(FILES settings/grantleethemeeditor.kcfg DESTINATION ${KDE_INSTALL_KCFGDIR})

set_target_properties(grantleethemeeditor PROPERTIES VERSION ${KDEPIM_LIB_VERSION} SOVERSION ${KDEPIM_LIB_SOVERSION})
install(TARGETS grantleethemeeditor ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}  LIBRARY NAMELINK_SKIP)
