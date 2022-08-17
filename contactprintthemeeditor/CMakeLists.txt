set(contactprintthemeeditor_SRCS
    main.cpp
    defaultcompletion.cpp
    editorpage.cpp
    contactprintthemeconfiguredialog.cpp
    themedefaulttemplate.cpp
    themeeditormainwindow.cpp
    themeeditorpage.cpp
    contactprintthemeeditorutil.cpp
    themeeditorwidget.cpp
    themetemplatewidget.cpp
    contactprintthemepreview.cpp
    defaultcompletion.h
    editorpage.h
    contactprintthemeconfiguredialog.h
    themedefaulttemplate.h
    themeeditormainwindow.h
    themeeditorpage.h
    contactprintthemeeditorutil.h
    themeeditorwidget.h
    themetemplatewidget.h
    contactprintthemepreview.h
    contactprintthemeeditor.qrc
    )

ecm_qt_declare_logging_category(contactprintthemeeditor_SRCS HEADER contactprintthemeeditor_debug.h IDENTIFIER CONTACTPRINTTHEMEEDITOR_LOG CATEGORY_NAME org.kde.pim.contactprintthemeeditor
        DESCRIPTION "grantleeeditor (contactprintthemeeditor)"
        OLD_CATEGORY_NAMES log_contactprintthemeeditor
        EXPORT GRANTLEEEDITOR
    )
add_executable(contactprintthemeeditor ${contactprintthemeeditor_SRCS} )
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(contactprintthemeeditor PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(contactprintthemeeditor
    KF5::DBusAddons
    KF5::NewStuff
    KF5::AkonadiContact
    KF5::PimCommon
    grantleethemeeditor
    KF5::PimTextEdit
    KF5::I18n
    Qt::WebEngineWidgets
    KF5::Crash
    )

install(TARGETS contactprintthemeeditor ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(PROGRAMS org.kde.contactprintthemeeditor.desktop DESTINATION ${KDE_INSTALL_APPDIR})
