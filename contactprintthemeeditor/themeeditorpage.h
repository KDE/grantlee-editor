/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>

namespace GrantleeThemeEditor
{
class ThemeEditorTabWidget;
class ThemeSession;
class DesktopFilePage;
}
class EditorPage;
class KZip;

class ThemeEditorPage : public QWidget
{
    Q_OBJECT
public:
    explicit ThemeEditorPage(const QString &projectDir, const QString &themeName, QWidget *parent = nullptr);
    ~ThemeEditorPage() override;

    void saveThemeAs(const QString &directory);
    [[nodiscard]] bool saveTheme(bool withConfirmation = true);
    void loadTheme(const QString &filename);

    void addExtraPage();

    void uploadTheme();
    void installTheme(const QString &themePath);

    bool themeWasChanged() const;

    void reloadConfig();

    void insertFile();

    void updatePreview();

    void slotChanged();

Q_SIGNALS:
    void changed(bool);
    void canInsertFile(bool);

private:
    void slotUpdateViewer();
    void slotCloseTab(int);
    void slotCurrentWidgetChanged(int);

private:
    void setChanged(bool b);
    void storeTheme(const QString &directory = QString());
    [[nodiscard]] QString projectDirectory() const;
    void createZip(const QString &themeName, KZip *zip);
    EditorPage *createExtraPage(const QString &filename);
    QList<EditorPage *> mExtraPage;
    GrantleeThemeEditor::ThemeEditorTabWidget *mTabWidget = nullptr;
    EditorPage *mEditorPage = nullptr;
    GrantleeThemeEditor::DesktopFilePage *mDesktopPage = nullptr;
    GrantleeThemeEditor::ThemeSession *const mThemeSession;
    bool mChanged = false;
};
