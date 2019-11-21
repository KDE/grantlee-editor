/*
   Copyright (C) 2013-2019 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
