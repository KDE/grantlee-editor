add_executable(headerthemeeditor ${headerthemeeditor_SRCS} )
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

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(headerthemeeditor PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(headerthemeeditor
    KPim${KF_MAJOR_VERSION}::Mime
    KF${KF_MAJOR_VERSION}::NewStuff
    KF5::PimCommon
    KF5::MessageViewer
    grantleethemeeditor
    KF${KF_MAJOR_VERSION}::DBusAddons
    KPim${KF_MAJOR_VERSION}::GrantleeTheme
    KPim${KF_MAJOR_VERSION}::PimTextEdit
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::XmlGui
    KF${KF_MAJOR_VERSION}::Crash
    )

install(TARGETS headerthemeeditor ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(PROGRAMS org.kde.headerthemeeditor.desktop DESTINATION ${KDE_INSTALL_APPDIR})
