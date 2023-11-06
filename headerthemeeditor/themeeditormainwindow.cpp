/*
   SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "themeeditormainwindow.h"
#include "managethemes.h"
#include "newthemedialog.h"
#include "themeconfiguredialog.h"
#include "themeeditorpage.h"

#include <KActionCollection>
#include <KAuthorized>
#include <KConfigGroup>
#include <KLocalizedString>
#include <KMessageBox>
#include <KRecentFilesAction>
#include <KStandardAction>
#include <KToggleAction>
#include <QAction>
#include <QFileDialog>

#include <KSharedConfig>
#include <QActionGroup>
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

    KConfigGroup group = config->group(QStringLiteral("ThemeEditorMainWindow"));
    group.writeEntry("Size", size());
    mRecentFileAction->saveEntries(group);
}

void ThemeEditorMainWindow::readConfig()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    KConfigGroup group = KConfigGroup(config, QStringLiteral("ThemeEditorMainWindow"));
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
    mPrintingMode->setEnabled(projectDirectoryIsEmpty);
    mNormalMode->setEnabled(projectDirectoryIsEmpty);
    mUpdateView->setEnabled(projectDirectoryIsEmpty);
    mSaveAsAction->setEnabled(projectDirectoryIsEmpty);
}

void ThemeEditorMainWindow::setupActions()
{
    mRecentFileAction = new KRecentFilesAction(i18n("Load Recent Theme..."), this);
    connect(mRecentFileAction, &KRecentFilesAction::urlSelected, this, &ThemeEditorMainWindow::slotThemeSelected);
    actionCollection()->addAction(QStringLiteral("load_recent_theme"), mRecentFileAction);
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    KConfigGroup groupConfig = config->group(QStringLiteral("ThemeEditorMainWindow"));
    mRecentFileAction->loadEntries(groupConfig);

    mAddExtraPage = new QAction(i18n("Add Extra Page..."), this);
    connect(mAddExtraPage, &QAction::triggered, this, &ThemeEditorMainWindow::slotAddExtraPage);
    actionCollection()->addAction(QStringLiteral("add_extra_page"), mAddExtraPage);

    if (KAuthorized::authorize(QStringLiteral("ghns"))) {
        mUploadTheme = new QAction(QIcon::fromTheme(QStringLiteral("get-hot-new-stuff")), i18n("Upload theme..."), this);
        connect(mUploadTheme, &QAction::triggered, this, &ThemeEditorMainWindow::slotUploadTheme);
        actionCollection()->addAction(QStringLiteral("upload_theme"), mUploadTheme);
    }

    mNewThemeAction = KStandardAction::openNew(this, &ThemeEditorMainWindow::slotNewTheme, actionCollection());
    mNewThemeAction->setText(i18n("New theme..."));

    mOpenAction = KStandardAction::open(this, &ThemeEditorMainWindow::slotOpenTheme, actionCollection());
    mOpenAction->setText(i18n("Open theme..."));
    mSaveAction = KStandardAction::save(this, &ThemeEditorMainWindow::slotSaveTheme, actionCollection());
    mSaveAction->setText(i18n("Save theme"));

    mSaveAsAction = KStandardAction::saveAs(this, &ThemeEditorMainWindow::slotSaveAsTheme, actionCollection());
    mSaveAsAction->setText(i18n("Save theme as..."));

    mCloseAction = KStandardAction::close(this, &ThemeEditorMainWindow::slotCloseTheme, actionCollection());
    KStandardAction::quit(this, &ThemeEditorMainWindow::slotQuitApp, actionCollection());
    KStandardAction::preferences(this, &ThemeEditorMainWindow::slotConfigure, actionCollection());

    mInstallTheme = new QAction(i18n("Install theme"), this);
    actionCollection()->addAction(QStringLiteral("install_theme"), mInstallTheme);
    connect(mInstallTheme, &QAction::triggered, this, &ThemeEditorMainWindow::slotInstallTheme);

    mInsertFile = new QAction(i18n("Insert File..."), this);
    actionCollection()->addAction(QStringLiteral("insert_file"), mInsertFile);
    connect(mInsertFile, &QAction::triggered, this, &ThemeEditorMainWindow::slotInsertFile);

    auto group = new QActionGroup(this);

    mPrintingMode = new KToggleAction(i18n("Printing mode"), this);
    actionCollection()->addAction(QStringLiteral("printing_mode"), mPrintingMode);
    connect(mPrintingMode, &KToggleAction::triggered, this, &ThemeEditorMainWindow::slotPrintingMode);
    group->addAction(mPrintingMode);

    mNormalMode = new KToggleAction(i18n("Normal mode"), this);
    mNormalMode->setChecked(true);
    actionCollection()->addAction(QStringLiteral("normal_mode"), mNormalMode);
    connect(mNormalMode, &KToggleAction::triggered, this, &ThemeEditorMainWindow::slotNormalMode);
    group->addAction(mNormalMode);

    mManageTheme = new QAction(i18n("Manage themes..."), this);
    connect(mManageTheme, &QAction::triggered, this, &ThemeEditorMainWindow::slotManageTheme);
    actionCollection()->addAction(QStringLiteral("manage_themes"), mManageTheme);

    mUpdateView = new QAction(QIcon::fromTheme(QStringLiteral("view-refresh")), i18n("Update view"), this);
    actionCollection()->setDefaultShortcut(mUpdateView, QKeySequence(Qt::Key_F5));
    connect(mUpdateView, &QAction::triggered, this, &ThemeEditorMainWindow::slotUpdateView);
    actionCollection()->addAction(QStringLiteral("update_view"), mUpdateView);
}

void ThemeEditorMainWindow::slotManageTheme()
{
    QPointer<GrantleeThemeEditor::ManageThemes> dialog = new GrantleeThemeEditor::ManageThemes(QStringLiteral("messageviewer/themes/"), this);
    dialog->exec();
    delete dialog;
}

void ThemeEditorMainWindow::slotNormalMode()
{
    mThemeEditor->setPrinting(false);
}

void ThemeEditorMainWindow::slotPrintingMode()
{
    mThemeEditor->setPrinting(true);
}

void ThemeEditorMainWindow::slotInsertFile()
{
    mThemeEditor->insertFile();
}

void ThemeEditorMainWindow::slotConfigure()
{
    QPointer<ThemeConfigureDialog> dialog = new ThemeConfigureDialog(this);
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
        const QString localThemePath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1String("/messageviewer/themes/");
        QDir().mkpath(localThemePath);
        mThemeEditor->installTheme(localThemePath);
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
        const QString filename = directory + QLatin1String("/theme.themerc");
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
