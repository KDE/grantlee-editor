/*
   SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <KXmlGuiWindow>

class ThemeEditorPage;
class QAction;
class KToggleAction;
class KRecentFilesAction;
class QUrl;

class ThemeEditorMainWindow : public KXmlGuiWindow
{
    Q_OBJECT
public:
    explicit ThemeEditorMainWindow();
    ~ThemeEditorMainWindow() override;

protected:
    void closeEvent(QCloseEvent *) override;

private Q_SLOTS:
    void slotUploadTheme();

private:
    void slotNewTheme();
    void slotCloseTheme();
    void slotAddExtraPage();
    void slotOpenTheme();
    void slotQuitApp();
    Q_REQUIRED_RESULT bool slotSaveTheme();
    void slotConfigure();
    void slotInstallTheme();
    void slotInsertFile();
    void slotPrintingMode();
    void slotNormalMode();
    void slotManageTheme();
    void slotUpdateView();
    void slotCanInsertFile(bool b);
    void slotThemeSelected(const QUrl &);
    void slotSaveAsTheme();

private:
    enum ActionSaveTheme { SaveOnly = 0, SaveAndCloseTheme, SaveAndCreateNewTheme };

    bool loadTheme(const QString &directory);
    void readConfig();
    void writeConfig();
    void updateActions();
    bool saveCurrentProject(ActionSaveTheme act);
    void setupActions();
    void closeThemeEditor();
    ThemeEditorPage *mThemeEditor = nullptr;
    QAction *mNewThemeAction = nullptr;
    QAction *mCloseThemeAction = nullptr;
    QAction *mAddExtraPage = nullptr;
    QAction *mCloseAction = nullptr;
    QAction *mOpenAction = nullptr;
    QAction *mUploadTheme = nullptr;
    QAction *mSaveAction = nullptr;
    QAction *mInstallTheme = nullptr;
    QAction *mInsertFile = nullptr;
    QAction *mManageTheme = nullptr;
    QAction *mUpdateView = nullptr;
    QAction *mSaveAsAction = nullptr;
    KToggleAction *mPrintingMode = nullptr;
    KToggleAction *mNormalMode = nullptr;
    KRecentFilesAction *mRecentFileAction = nullptr;
};
