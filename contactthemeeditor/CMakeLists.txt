add_executable(contactthemeeditor)
target_sources(contactthemeeditor PRIVATE
    main.cpp
    defaultcompletion.cpp
    contactdefaulttemplate.cpp
    contacteditorwidget.cpp
    contacttemplatewidget.cpp
    contacteditormainwindow.cpp
    previewwidget.cpp
    editorpage.cpp
    contacteditorpage.cpp
    contactconfigurationdialog.cpp
    contacteditorutil.cpp
    contactpreviewwidget.cpp
    defaultcompletion.h
    contactdefaulttemplate.h
    contacteditorwidget.h
    contacttemplatewidget.h
    contacteditormainwindow.h
    previewwidget.h
    editorpage.h
    contacteditorpage.h
    contactconfigurationdialog.h
    contacteditorutil.h
    contactpreviewwidget.h
    contactthemeeditor.qrc
    )
ecm_qt_declare_logging_category(contactthemeeditor HEADER contactthemeeditor_debug.h IDENTIFIER CONTACTTHEMEEDITOR_LOG CATEGORY_NAME org.kde.pim.contactthemeeditor
        DESCRIPTION "grantleeeditor (contactthemeeditor)"
        OLD_CATEGORY_NAMES log_contactthemeeditor
        EXPORT GRANTLEEEDITOR
    )

target_link_libraries(contactthemeeditor
    PRIVATE
    KF${KF_MAJOR_VERSION}::DBusAddons
    KF${KF_MAJOR_VERSION}::NewStuff
    KPim${KF_MAJOR_VERSION}::AkonadiContact
    KF5::PimCommon
    grantleethemeeditor
    KPim${KF_MAJOR_VERSION}::PimTextEdit
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::Crash
    KF${KF_MAJOR_VERSION}::XmlGui
    )
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(contactthemeeditor PROPERTIES UNITY_BUILD ON)
endif()

install(TARGETS contactthemeeditor ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(PROGRAMS org.kde.contactthemeeditor.desktop DESTINATION ${KDE_INSTALL_APPDIR})
