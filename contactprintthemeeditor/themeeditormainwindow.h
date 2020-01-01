/*
   Copyright (C) 2015-2020 Laurent Montel <montel@kde.org>

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

#ifndef THEMEEDITORMAINWINDOW_H
#define THEMEEDITORMAINWINDOW_H

#include <KXmlGuiWindow>

class ThemeEditorPage;
class QAction;
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
    bool slotSaveTheme();
    void slotConfigure();
    void slotInstallTheme();
    void slotInsertFile();
    void slotManageTheme();
    void slotUpdateView();
    void slotCanInsertFile(bool b);
    void slotThemeSelected(const QUrl &);
    void slotSaveAsTheme();

private:
    enum ActionSaveTheme {
        SaveOnly = 0,
        SaveAndCloseTheme,
        SaveAndCreateNewTheme
    };

    Q_REQUIRED_RESULT bool loadTheme(const QString &directory);
    void writeConfig();
    void readConfig();
    void updateActions();
    Q_REQUIRED_RESULT bool saveCurrentProject(ActionSaveTheme act);
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
    KRecentFilesAction *mRecentFileAction = nullptr;
};

#endif // THEMEEDITORMAINWINDOW_H
