add_executable(headerthemeeditor ${headerthemeeditor_SRCS})
target_sources(headerthemeeditor PRIVATE
    main.cpp
    themeeditormainwindow.cpp
    themeeditorpage.cpp
    previewwidget.cpp
    editorpage.cpp
    themetemplatewidget.cpp
    themedefaulttemplate.cpp
    defaultcompletion.cpp
    themeconfiguredialog.cpp
    themeeditorutil.cpp
    themeeditorwidget.cpp
    headerthemeeditor.qrc
    themeeditormainwindow.h
    themeeditorpage.h
    previewwidget.h
    editorpage.h
    themetemplatewidget.h
    themedefaulttemplate.h
    defaultcompletion.h
    themeconfiguredialog.h
    themeeditorutil.h
    themeeditorwidget.h
)

ecm_qt_declare_logging_category(headerthemeeditor HEADER headerthemeeditor_debug.h IDENTIFIER HEADERTHEMEEDITOR_LOG CATEGORY_NAME org.kde.pim.headerthemeeditor
        DESCRIPTION "grantleeeditor (headerthemeeditor)"
        OLD_CATEGORY_NAMES log_headerthemeeditor
        EXPORT GRANTLEEEDITOR
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(headerthemeeditor PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(headerthemeeditor
    KPim6::Mime
    KPim6::PimCommon
    KPim6::MessageViewer
    grantleethemeeditor
    KF6::DBusAddons
    KPim6::GrantleeTheme
    KF6::I18n
    KF6::XmlGui
    KF6::Crash
)

install(TARGETS headerthemeeditor ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(PROGRAMS org.kde.headerthemeeditor.desktop DESTINATION ${KDE_INSTALL_APPDIR})
