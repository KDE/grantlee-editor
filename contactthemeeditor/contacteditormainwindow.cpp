/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "contacteditormainwindow.h"
#include "contactconfigurationdialog.h"
#include "contacteditorpage.h"
#include "managethemes.h"
#include "newthemedialog.h"

#include <KActionCollection>
#include <KAuthorized>
#include <KConfigGroup>
#include <KLocalizedString>
#include <KMessageBox>
#include <KRecentFilesAction>
#include <KStandardAction>
#include <QAction>
#include <QApplication>
#include <QFileDialog>

#include <KSharedConfig>
#include <QCloseEvent>
#include <QPointer>
#include <QStandardPaths>

ContactEditorMainWindow::ContactEditorMainWindow()
    : KXmlGuiWindow()
{
    setupActions();
    setupGUI();
    updateActions();
    readConfig();
}

ContactEditorMainWindow::~ContactEditorMainWindow() = default;

void ContactEditorMainWindow::writeConfig()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();

    KConfigGroup group = config->group(QStringLiteral("ContactEditorMainWindow"));
    group.writeEntry("Size", size());
    mRecentFileAction->saveEntries(group);
}

void ContactEditorMainWindow::readConfig()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    KConfigGroup group = KConfigGroup(config, QStringLiteral("ContactEditorMainWindow"));
    const QSize sizeDialog = group.readEntry("Size", QSize(600, 400));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}

void ContactEditorMainWindow::updateActions()
{
    const bool projectDirectoryIsEmpty = (mContactEditor != nullptr);
    mAddExtraPage->setEnabled(projectDirectoryIsEmpty);
    mCloseAction->setEnabled(projectDirectoryIsEmpty);
    if (mUploadTheme) {
        mUploadTheme->setEnabled(projectDirectoryIsEmpty);
    }
    mSaveAction->setEnabled(projectDirectoryIsEmpty);
    mInstallTheme->setEnabled(projectDirectoryIsEmpty);
    mInsertFile->setEnabled(projectDirectoryIsEmpty);
    mUpdateView->setEnabled(projectDirectoryIsEmpty);
    mSaveAsAction->setEnabled(projectDirectoryIsEmpty);
}

void ContactEditorMainWindow::setupActions()
{
    mRecentFileAction = new KRecentFilesAction(i18n("Load Recent Theme..."), this);
    connect(mRecentFileAction, &KRecentFilesAction::urlSelected, this, &ContactEditorMainWindow::slotThemeSelected);
    actionCollection()->addAction(QStringLiteral("load_recent_theme"), mRecentFileAction);
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    KConfigGroup groupConfig = config->group(QStringLiteral("ContactEditorMainWindow"));
    mRecentFileAction->loadEntries(groupConfig);

    mAddExtraPage = new QAction(i18nc("@action", "Add Extra Page..."), this);
    connect(mAddExtraPage, &QAction::triggered, this, &ContactEditorMainWindow::slotAddExtraPage);
    actionCollection()->addAction(QStringLiteral("add_extra_page"), mAddExtraPage);

    if (KAuthorized::authorize(QStringLiteral("ghns"))) {
        mUploadTheme = new QAction(QIcon::fromTheme(QStringLiteral("get-hot-new-stuff")), i18n("Upload theme..."), this);
        connect(mUploadTheme, &QAction::triggered, this, &ContactEditorMainWindow::slotUploadTheme);
        actionCollection()->addAction(QStringLiteral("upload_theme"), mUploadTheme);
    }

    mNewThemeAction = KStandardActions::openNew(this, &ContactEditorMainWindow::slotNewTheme, actionCollection());
    mNewThemeAction->setText(i18n("New theme..."));

    mOpenAction = KStandardActions::open(this, &ContactEditorMainWindow::slotOpenTheme, actionCollection());
    mOpenAction->setText(i18n("Open theme..."));
    mSaveAction = KStandardActions::save(this, &ContactEditorMainWindow::slotSaveTheme, actionCollection());
    mSaveAction->setText(i18n("Save theme"));
    mSaveAsAction = KStandardActions::saveAs(this, &ContactEditorMainWindow::slotSaveAsTheme, actionCollection());
    mSaveAsAction->setText(i18n("Save theme as..."));

    mCloseAction = KStandardActions::close(this, &ContactEditorMainWindow::slotCloseTheme, actionCollection());
    KStandardActions::quit(this, &ContactEditorMainWindow::slotQuitApp, actionCollection());
    KStandardActions::preferences(this, &ContactEditorMainWindow::slotConfigure, actionCollection());

    mInstallTheme = new QAction(i18nc("@action", "Install theme"), this);
    actionCollection()->addAction(QStringLiteral("install_theme"), mInstallTheme);
    connect(mInstallTheme, &QAction::triggered, this, &ContactEditorMainWindow::slotInstallTheme);

    mInsertFile = new QAction(i18nc("@action", "Insert File..."), this);
    actionCollection()->addAction(QStringLiteral("insert_file"), mInsertFile);
    connect(mInsertFile, &QAction::triggered, this, &ContactEditorMainWindow::slotInsertFile);

    mManageTheme = new QAction(i18nc("@action", "Manage themes..."), this);
    connect(mManageTheme, &QAction::triggered, this, &ContactEditorMainWindow::slotManageTheme);
    actionCollection()->addAction(QStringLiteral("manage_themes"), mManageTheme);

    mUpdateView = new QAction(QIcon::fromTheme(QStringLiteral("view-refresh")), i18n("Update view"), this);
    actionCollection()->setDefaultShortcut(mUpdateView, QKeySequence(Qt::Key_F5));
    connect(mUpdateView, &QAction::triggered, this, &ContactEditorMainWindow::slotUpdateView);
    actionCollection()->addAction(QStringLiteral("update_view"), mUpdateView);
}

void ContactEditorMainWindow::slotConfigure()
{
    QPointer<ContactConfigureDialog> dialog = new ContactConfigureDialog(this);
    if (dialog->exec()) {
        if (mContactEditor) {
            mContactEditor->reloadConfig();
        }
    }
    delete dialog;
}

void ContactEditorMainWindow::slotManageTheme()
{
    QPointer<GrantleeThemeEditor::ManageThemes> dialog = new GrantleeThemeEditor::ManageThemes(QStringLiteral("kaddressbook/viewertemplates/"), this);
    dialog->exec();
    delete dialog;
}

void ContactEditorMainWindow::slotInsertFile()
{
    mContactEditor->insertFile();
}

void ContactEditorMainWindow::slotInstallTheme()
{
    // Save before installing :)
    if (slotSaveTheme()) {
        const QString localThemePath =
            QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1StringView("/kaddressbook/viewertemplates/");
        QDir().mkpath(localThemePath);
        mContactEditor->installTheme(localThemePath);
    }
}

void ContactEditorMainWindow::slotUploadTheme()
{
    // Save before upload :)
    if (slotSaveTheme()) {
        mContactEditor->uploadTheme();
    }
}

bool ContactEditorMainWindow::slotSaveTheme()
{
    bool result = false;
    if (mContactEditor) {
        result = mContactEditor->saveTheme(false);
        mSaveAction->setEnabled(result);
    }
    return result;
}

void ContactEditorMainWindow::slotCloseTheme()
{
    (void)saveCurrentProject(SaveAndCloseTheme);
}

void ContactEditorMainWindow::slotOpenTheme()
{
    if (!saveCurrentProject(SaveOnly)) {
        return;
    }

    const QString directory = QFileDialog::getExistingDirectory(this, i18n("Select theme directory"));
    if (directory.isEmpty()) {
        return;
    }
    closeThemeEditor();
    if (loadTheme(directory)) {
        mRecentFileAction->addUrl(QUrl::fromLocalFile(directory));
    }
    mSaveAction->setEnabled(false);
}

bool ContactEditorMainWindow::loadTheme(const QString &directory)
{
    if (!directory.isEmpty()) {
        const QString filename = directory + QLatin1StringView("/theme.themerc");
        if (!QFileInfo::exists(filename)) {
            KMessageBox::error(this, i18n("Directory does not contain a theme file. We cannot load theme."));
            return false;
        }

        mContactEditor = new ContactEditorPage(QString(), QString());
        connect(mContactEditor, &ContactEditorPage::changed, mSaveAction, &QAction::setEnabled);
        connect(mContactEditor, &ContactEditorPage::canInsertFile, this, &ContactEditorMainWindow::slotCanInsertFile);
        mContactEditor->loadTheme(filename);
        setCentralWidget(mContactEditor);
        updateActions();
    }
    return true;
}

void ContactEditorMainWindow::slotAddExtraPage()
{
    if (mContactEditor) {
        mContactEditor->addExtraPage();
    }
}

void ContactEditorMainWindow::closeThemeEditor()
{
    delete mContactEditor;
    mContactEditor = nullptr;
    setCentralWidget(nullptr);
    updateActions();
}

bool ContactEditorMainWindow::saveCurrentProject(ActionSaveTheme act)
{
    if (mContactEditor) {
        if (!mContactEditor->saveTheme()) {
            return false;
        }
    }
    switch (act) {
    case SaveOnly:
        break;
    case SaveAndCloseTheme:
        closeThemeEditor();
        break;
    case SaveAndCreateNewTheme: {
        delete mContactEditor;
        mContactEditor = nullptr;
        QPointer<GrantleeThemeEditor::NewThemeDialog> dialog = new GrantleeThemeEditor::NewThemeDialog(this);
        QString newTheme;
        QString projectDirectory;
        if (dialog->exec()) {
            newTheme = dialog->themeName();
            projectDirectory = dialog->directory();
        }
        if (!projectDirectory.isEmpty()) {
            mRecentFileAction->addUrl(QUrl::fromLocalFile(projectDirectory));
            mContactEditor = new ContactEditorPage(projectDirectory, newTheme);
            connect(mContactEditor, &ContactEditorPage::changed, mSaveAction, &QAction::setEnabled);
            connect(mContactEditor, &ContactEditorPage::canInsertFile, this, &ContactEditorMainWindow::slotCanInsertFile);
            setCentralWidget(mContactEditor);
        } else {
            setCentralWidget(nullptr);
        }
        delete dialog;
        updateActions();
        break;
    }
    }
    return true;
}

void ContactEditorMainWindow::slotNewTheme()
{
    (void)saveCurrentProject(SaveAndCreateNewTheme);
}

void ContactEditorMainWindow::closeEvent(QCloseEvent *e)
{
    if (!saveCurrentProject(SaveAndCloseTheme)) {
        e->ignore();
    } else {
        writeConfig();
        e->accept();
    }
}

void ContactEditorMainWindow::slotQuitApp()
{
    if (saveCurrentProject(SaveAndCloseTheme)) {
        writeConfig();
        qApp->quit();
    }
}

void ContactEditorMainWindow::slotUpdateView()
{
    if (mContactEditor) {
        (void)mContactEditor->saveTheme(false);
        mContactEditor->updatePreview();
    }
}

void ContactEditorMainWindow::slotCanInsertFile(bool b)
{
    mInsertFile->setEnabled(b);
}

void ContactEditorMainWindow::slotThemeSelected(const QUrl &url)
{
    if (!saveCurrentProject(SaveAndCloseTheme)) {
        return;
    }
    (void)loadTheme(url.path());
    mSaveAction->setEnabled(false);
}

void ContactEditorMainWindow::slotSaveAsTheme()
{
    const QString directory = QFileDialog::getExistingDirectory(this, i18n("Select theme directory"));
    if (!directory.isEmpty()) {
        if (mContactEditor) {
            mContactEditor->saveThemeAs(directory);
        }
    }
}

#include "moc_contacteditormainwindow.cpp"
