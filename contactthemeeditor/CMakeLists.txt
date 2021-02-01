set(contactthemeeditor_SRCS
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
    contactthemeeditor.qrc
    )
ecm_qt_declare_logging_category(contactthemeeditor_SRCS HEADER contactthemeeditor_debug.h IDENTIFIER CONTACTTHEMEEDITOR_LOG CATEGORY_NAME org.kde.pim.contactthemeeditor
        DESCRIPTION "grantleeeditor (contactthemeeditor)"
        OLD_CATEGORY_NAMES log_contactthemeeditor
        EXPORT GRANTLEEEDITOR
    )

add_executable(contactthemeeditor ${contactthemeeditor_SRCS} )
target_link_libraries(contactthemeeditor
    PRIVATE
    KF5::DBusAddons
    KF5::NewStuff
    KF5::AkonadiContact
    KF5::PimCommon
    grantleethemeeditor
    KF5::PimTextEdit
    KF5::I18n
    KF5::Crash
    )
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(contactthemeeditor PROPERTIES UNITY_BUILD ON)
endif()

install(TARGETS contactthemeeditor ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(PROGRAMS org.kde.contactthemeeditor.desktop DESTINATION ${KDE_INSTALL_APPDIR})
