/*
   Copyright (C) 2015-2017 Montel Laurent <montel@kde.org>

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
    ~ThemeEditorMainWindow();

protected:
    void closeEvent(QCloseEvent *) override;

private Q_SLOTS:
    void slotNewTheme();
    void slotCloseTheme();
    void slotAddExtraPage();
    void slotOpenTheme();
    void slotUploadTheme();
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

    bool loadTheme(const QString &directory);
    void writeConfig();
    void readConfig();
    void updateActions();
    bool saveCurrentProject(ActionSaveTheme act);
    void setupActions();
    void closeThemeEditor();
    ThemeEditorPage *mThemeEditor;
    QAction *mNewThemeAction;
    QAction *mCloseThemeAction;
    QAction *mAddExtraPage;
    QAction *mCloseAction;
    QAction *mOpenAction;
    QAction *mUploadTheme;
    QAction *mSaveAction;
    QAction *mInstallTheme;
    QAction *mInsertFile;
    QAction *mManageTheme;
    QAction *mUpdateView;
    QAction *mSaveAsAction;
    KRecentFilesAction *mRecentFileAction;
};

#endif // THEMEEDITORMAINWINDOW_H
