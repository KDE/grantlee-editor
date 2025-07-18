add_executable(contactthemeeditor)
target_sources(
    contactthemeeditor
    PRIVATE
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

target_link_libraries(
    contactthemeeditor
    PRIVATE
        KF6::DBusAddons
        KPim6::AkonadiContactWidgets
        KPim6::PimCommon
        grantleethemeeditor
        KF6::I18n
        KF6::Crash
        KF6::XmlGui
)
if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        contactthemeeditor
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()

install(
    TARGETS
        contactthemeeditor
        ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
)

install(PROGRAMS org.kde.contactthemeeditor.desktop DESTINATION ${KDE_INSTALL_APPDIR})
