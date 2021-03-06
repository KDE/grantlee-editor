set(headerthemeeditor_SRCS
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
    )

ecm_qt_declare_logging_category(headerthemeeditor_SRCS HEADER headerthemeeditor_debug.h IDENTIFIER HEADERTHEMEEDITOR_LOG CATEGORY_NAME org.kde.pim.headerthemeeditor
        DESCRIPTION "grantleeeditor (headerthemeeditor)"
        OLD_CATEGORY_NAMES log_headerthemeeditor
        EXPORT GRANTLEEEDITOR
    )

add_executable(headerthemeeditor ${headerthemeeditor_SRCS} )
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(headerthemeeditor PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(headerthemeeditor
    KF5::Mime
    KF5::NewStuff
    KF5::PimCommon
    KF5::MessageViewer
    grantleethemeeditor
    KF5::DBusAddons
    KF5::GrantleeTheme
    KF5::PimTextEdit
    KF5::I18n
    KF5::XmlGui
    KF5::Crash
    )

install(TARGETS headerthemeeditor ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(PROGRAMS org.kde.headerthemeeditor.desktop DESTINATION ${KDE_INSTALL_APPDIR})
