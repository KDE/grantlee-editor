/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "themeeditormainwindow.h"
using namespace Qt::Literals::StringLiterals;

#include "contactprintthemeconfiguredialog.h"
#include "managethemes.h"
#include "newthemedialog.h"
#include "themeeditorpage.h"

#include <KActionCollection>
#include <KConfigGroup>
#include <KLocalizedString>
#include <KMessageBox>
#include <KRecentFilesAction>
#include <KStandardAction>
#include <QAction>
#include <QFileDialog>

#include <KAuthorized>
#include <KSharedConfig>
#include <QApplication>
#include <QCloseEvent>
#include <QPointer>
#include <QStandardPaths>

ThemeEditorMainWindow::ThemeEditorMainWindow()
    : KXmlGuiWindow()
{
    setupActions();
    setupGUI();
    updateActions();
    readConfig();
}

ThemeEditorMainWindow::~ThemeEditorMainWindow() = default;

void ThemeEditorMainWindow::writeConfig()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();

    KConfigGroup group = config->group(u"ThemeEditorMainWindow"_s);
    group.writeEntry("Size", size());
    mRecentFileAction->saveEntries(group);
}

void ThemeEditorMainWindow::readConfig()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    KConfigGroup group = KConfigGroup(config, u"ThemeEditorMainWindow"_s);
    const QSize sizeDialog = group.readEntry("Size", QSize(600, 400));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}

void ThemeEditorMainWindow::updateActions()
{
    const bool projectDirectoryIsEmpty = (mThemeEditor != nullptr);
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

void ThemeEditorMainWindow::setupActions()
{
    mRecentFileAction = new KRecentFilesAction(i18n("Load Recent Theme..."), this);
    connect(mRecentFileAction, &KRecentFilesAction::urlSelected, this, &ThemeEditorMainWindow::slotThemeSelected);
    actionCollection()->addAction(u"load_recent_theme"_s, mRecentFileAction);
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    KConfigGroup groupConfig = config->group(u"ThemeEditorMainWindow"_s);
    mRecentFileAction->loadEntries(groupConfig);

    mAddExtraPage = new QAction(i18nc("@action", "Add Extra Page..."), this);
    connect(mAddExtraPage, &QAction::triggered, this, &ThemeEditorMainWindow::slotAddExtraPage);
    actionCollection()->addAction(u"add_extra_page"_s, mAddExtraPage);
    if (KAuthorized::authorize(u"ghns"_s)) {
        mUploadTheme = new QAction(QIcon::fromTheme(u"get-hot-new-stuff"_s), i18n("Upload theme..."), this);
        connect(mUploadTheme, &QAction::triggered, this, &ThemeEditorMainWindow::slotUploadTheme);
        actionCollection()->addAction(u"upload_theme"_s, mUploadTheme);
    }

    mNewThemeAction = KStandardActions::openNew(this, &ThemeEditorMainWindow::slotNewTheme, actionCollection());
    mNewThemeAction->setText(i18n("New theme..."));

    mOpenAction = KStandardActions::open(this, &ThemeEditorMainWindow::slotOpenTheme, actionCollection());
    mOpenAction->setText(i18n("Open theme..."));
    mSaveAction = KStandardActions::save(this, &ThemeEditorMainWindow::slotSaveTheme, actionCollection());
    mSaveAction->setText(i18n("Save theme"));

    mSaveAsAction = KStandardActions::saveAs(this, &ThemeEditorMainWindow::slotSaveAsTheme, actionCollection());
    mSaveAsAction->setText(i18n("Save theme as..."));

    mCloseAction = KStandardActions::close(this, &ThemeEditorMainWindow::slotCloseTheme, actionCollection());
    KStandardActions::quit(this, &ThemeEditorMainWindow::slotQuitApp, actionCollection());
    KStandardActions::preferences(this, &ThemeEditorMainWindow::slotConfigure, actionCollection());

    mInstallTheme = new QAction(i18nc("@action", "Install theme"), this);
    actionCollection()->addAction(u"install_theme"_s, mInstallTheme);
    connect(mInstallTheme, &QAction::triggered, this, &ThemeEditorMainWindow::slotInstallTheme);

    mInsertFile = new QAction(i18nc("@action", "Insert File..."), this);
    actionCollection()->addAction(u"insert_file"_s, mInsertFile);
    connect(mInsertFile, &QAction::triggered, this, &ThemeEditorMainWindow::slotInsertFile);

    mManageTheme = new QAction(i18nc("@action", "Manage themes..."), this);
    connect(mManageTheme, &QAction::triggered, this, &ThemeEditorMainWindow::slotManageTheme);
    actionCollection()->addAction(u"manage_themes"_s, mManageTheme);

    mUpdateView = new QAction(QIcon::fromTheme(u"view-refresh"_s), i18n("Update view"), this);
    actionCollection()->setDefaultShortcut(mUpdateView, QKeySequence(Qt::Key_F5));
    connect(mUpdateView, &QAction::triggered, this, &ThemeEditorMainWindow::slotUpdateView);
    actionCollection()->addAction(u"update_view"_s, mUpdateView);
}

void ThemeEditorMainWindow::slotManageTheme()
{
    QPointer<GrantleeThemeEditor::ManageThemes> dialog = new GrantleeThemeEditor::ManageThemes(u"kaddressbook/printing/themes/"_s, this);
    dialog->exec();
    delete dialog;
}

void ThemeEditorMainWindow::slotInsertFile()
{
    mThemeEditor->insertFile();
}

void ThemeEditorMainWindow::slotConfigure()
{
    QPointer<ContactPrintThemeConfigureDialog> dialog = new ContactPrintThemeConfigureDialog(this);
    if (dialog->exec()) {
        if (mThemeEditor) {
            mThemeEditor->reloadConfig();
        }
    }
    delete dialog;
}

void ThemeEditorMainWindow::slotInstallTheme()
{
    // Save before installing :)
    if (slotSaveTheme()) {
        const QString localThemePath =
            QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1StringView("/kaddressbook/printing/themes");
        if (QDir().mkpath(localThemePath)) {
            mThemeEditor->installTheme(localThemePath);
        }
    }
}

void ThemeEditorMainWindow::slotUploadTheme()
{
    // Save before upload :)
    if (slotSaveTheme()) {
        mThemeEditor->uploadTheme();
    }
}

bool ThemeEditorMainWindow::slotSaveTheme()
{
    bool result = false;
    if (mThemeEditor) {
        mThemeEditor->slotChanged();
        result = mThemeEditor->saveTheme(false);
        mSaveAction->setEnabled(!result);
    }
    return result;
}

void ThemeEditorMainWindow::slotCloseTheme()
{
    saveCurrentProject(SaveAndCloseTheme);
}

void ThemeEditorMainWindow::slotOpenTheme()
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

bool ThemeEditorMainWindow::loadTheme(const QString &directory)
{
    if (!directory.isEmpty()) {
        const QString filename = directory + QLatin1StringView("/theme.themerc");
        if (!QFileInfo::exists(filename)) {
            KMessageBox::error(this, i18n("Directory does not contain a theme file. We cannot load theme."));
            return false;
        }

        mThemeEditor = new ThemeEditorPage(QString(), QString());
        connect(mThemeEditor, &ThemeEditorPage::changed, mSaveAction, &QAction::setEnabled);
        connect(mThemeEditor, &ThemeEditorPage::canInsertFile, this, &ThemeEditorMainWindow::slotCanInsertFile);
        mThemeEditor->loadTheme(filename);
        setCentralWidget(mThemeEditor);
        updateActions();
    }
    return true;
}

void ThemeEditorMainWindow::slotAddExtraPage()
{
    if (mThemeEditor) {
        mThemeEditor->addExtraPage();
    }
}

void ThemeEditorMainWindow::closeThemeEditor()
{
    delete mThemeEditor;
    mThemeEditor = nullptr;
    setCentralWidget(nullptr);
    updateActions();
}

bool ThemeEditorMainWindow::saveCurrentProject(ActionSaveTheme act)
{
    if (mThemeEditor) {
        if (!mThemeEditor->saveTheme()) {
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
        delete mThemeEditor;
        mThemeEditor = nullptr;
        QPointer<GrantleeThemeEditor::NewThemeDialog> dialog = new GrantleeThemeEditor::NewThemeDialog(this);
        QString newTheme;
        QString projectDirectory;
        if (dialog->exec()) {
            newTheme = dialog->themeName();
            projectDirectory = dialog->directory();
        }
        if (!projectDirectory.isEmpty()) {
            mRecentFileAction->addUrl(QUrl::fromLocalFile(projectDirectory));
            mThemeEditor = new ThemeEditorPage(projectDirectory, newTheme);
            connect(mThemeEditor, &ThemeEditorPage::changed, mSaveAction, &QAction::setEnabled);
            connect(mThemeEditor, &ThemeEditorPage::canInsertFile, this, &ThemeEditorMainWindow::slotCanInsertFile);
            setCentralWidget(mThemeEditor);
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

void ThemeEditorMainWindow::slotNewTheme()
{
    saveCurrentProject(SaveAndCreateNewTheme);
}

void ThemeEditorMainWindow::closeEvent(QCloseEvent *e)
{
    if (!saveCurrentProject(SaveAndCloseTheme)) {
        e->ignore();
    } else {
        writeConfig();
        e->accept();
    }
}

void ThemeEditorMainWindow::slotQuitApp()
{
    if (saveCurrentProject(SaveAndCloseTheme)) {
        writeConfig();
        qApp->quit();
    }
}

void ThemeEditorMainWindow::slotUpdateView()
{
    if (mThemeEditor) {
        mThemeEditor->saveTheme(false);
        mThemeEditor->updatePreview();
    }
}

void ThemeEditorMainWindow::slotCanInsertFile(bool b)
{
    mInsertFile->setEnabled(b);
}

void ThemeEditorMainWindow::slotThemeSelected(const QUrl &url)
{
    if (!saveCurrentProject(SaveAndCloseTheme)) {
        return;
    }
    loadTheme(url.path());
    mSaveAction->setEnabled(false);
}

void ThemeEditorMainWindow::slotSaveAsTheme()
{
    const QString directory = QFileDialog::getExistingDirectory(this, i18n("Select theme directory"));
    if (!directory.isEmpty()) {
        if (mThemeEditor) {
            mThemeEditor->saveThemeAs(directory);
        }
    }
}

#include "moc_themeeditormainwindow.cpp"
