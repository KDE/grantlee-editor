add_executable(contactprintthemeeditor)
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
if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(contactprintthemeeditor PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(contactprintthemeeditor
    KF6::DBusAddons
    KPim6::AkonadiContactWidgets
    KPim6::PimCommon
    grantleethemeeditor
    KF6::I18n
    Qt::WebEngineWidgets
    KF6::XmlGui
    KF6::Crash
)

install(TARGETS contactprintthemeeditor ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(PROGRAMS org.kde.contactprintthemeeditor.desktop DESTINATION ${KDE_INSTALL_APPDIR})
