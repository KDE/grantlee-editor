/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef GRANTLEEEDITOREDITORPAGE_H
#define GRANTLEEEDITOREDITORPAGE_H

#include "grantleethemeeditor_export.h"
#include <QWidget>

class KZip;

namespace GrantleeThemeEditor
{
class EditorWidget;
class PreviewWidget;
class GRANTLEETHEMEEDITOR_EXPORT EditorPage : public QWidget
{
    Q_OBJECT
public:
    enum PageType { MainPage = 0, SecondPage, ExtraPage };
    explicit EditorPage(GrantleeThemeEditor::EditorPage::PageType type, QWidget *parent = nullptr);
    ~EditorPage();

    EditorPage::PageType pageType() const;

    void setPageFileName(const QString &filename);
    Q_REQUIRED_RESULT QString pageFileName() const;

    GrantleeThemeEditor::EditorWidget *editor() const;

    void insertFile(const QString &filename);
    void loadTheme(const QString &path);
    void saveTheme(const QString &path);
    void saveAsFilename(const QString &filename);

    void createZip(const QString &themeName, KZip *zip);
    void installTheme(const QString &themePath);

Q_SIGNALS:
    void needUpdateViewer();
    void changed();

protected:
    const PageType mType;
    QString mPageFileName;
    GrantleeThemeEditor::PreviewWidget *mPreview = nullptr;
    GrantleeThemeEditor::EditorWidget *mEditor = nullptr;
};
}

#endif // GRANTLEEEDITOREDITOREDITORPAGE_H
