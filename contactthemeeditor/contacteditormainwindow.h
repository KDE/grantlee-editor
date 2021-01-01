/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef CONTACTEDITORMAINWINDOW_H
#define CONTACTEDITORMAINWINDOW_H

#include <KXmlGuiWindow>

class ContactEditorPage;
class QAction;
class KRecentFilesAction;
class QUrl;

class ContactEditorMainWindow : public KXmlGuiWindow
{
    Q_OBJECT
public:
    explicit ContactEditorMainWindow();
    ~ContactEditorMainWindow() override;

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
    void slotInstallTheme();
    void slotInsertFile();
    void slotManageTheme();
    void slotUpdateView();
    void slotConfigure();
    void slotCanInsertFile(bool b);
    void slotThemeSelected(const QUrl &);
    void slotSaveAsTheme();

private:
    enum ActionSaveTheme {
        SaveOnly = 0,
        SaveAndCloseTheme,
        SaveAndCreateNewTheme
    };

    void writeConfig();
    bool loadTheme(const QString &directory);
    void readConfig();
    void updateActions();
    Q_REQUIRED_RESULT bool saveCurrentProject(ActionSaveTheme act);
    void setupActions();
    void closeThemeEditor();
    ContactEditorPage *mContactEditor = nullptr;
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
    KRecentFilesAction *mRecentFileAction = nullptr;
};

#endif // CONTACTEDITORMAINWINDOW_H
