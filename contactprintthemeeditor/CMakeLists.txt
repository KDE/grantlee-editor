add_executable(contactprintthemeeditor )
target_sources(contactprintthemeeditor PRIVATE
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

ecm_qt_declare_logging_category(contactprintthemeeditor HEADER contactprintthemeeditor_debug.h IDENTIFIER CONTACTPRINTTHEMEEDITOR_LOG CATEGORY_NAME org.kde.pim.contactprintthemeeditor
        DESCRIPTION "grantleeeditor (contactprintthemeeditor)"
        OLD_CATEGORY_NAMES log_contactprintthemeeditor
        EXPORT GRANTLEEEDITOR
    )
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(contactprintthemeeditor PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(contactprintthemeeditor
    KF${KF_MAJOR_VERSION}::DBusAddons
    KF${KF_MAJOR_VERSION}::NewStuff
    KPim${KF_MAJOR_VERSION}::AkonadiContact
    KF5::PimCommon
    grantleethemeeditor
    KPim${KF_MAJOR_VERSION}::PimTextEdit
    KF${KF_MAJOR_VERSION}::I18n
    Qt::WebEngineWidgets
    KF${KF_MAJOR_VERSION}::XmlGui
    KF${KF_MAJOR_VERSION}::Crash
    )

install(TARGETS contactprintthemeeditor ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(PROGRAMS org.kde.contactprintthemeeditor.desktop DESTINATION ${KDE_INSTALL_APPDIR})
