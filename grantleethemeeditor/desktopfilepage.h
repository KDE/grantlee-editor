/*
   SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "grantleethemeeditor_export.h"
#include <QWidget>
class QLineEdit;
class KZip;
class KEditListWidget;
namespace TextCustomEditor
{
class PlainTextEditorWidget;
}
namespace GrantleeThemeEditor
{
class GRANTLEETHEMEEDITOR_EXPORT DesktopFilePage : public QWidget
{
    Q_OBJECT
public:
    enum DesktopFileOption {
        None = 1,
        ExtraDisplayVariables = 2,
        SpecifyFileName = 4
    };
    Q_DECLARE_FLAGS(DesktopFileOptions, DesktopFileOption)

    explicit DesktopFilePage(const QString &defaultFileName, DesktopFilePage::DesktopFileOptions options, QWidget *parent = nullptr);
    ~DesktopFilePage() override;

    void saveTheme(const QString &path);
    void loadTheme(const QString &path);

    void setThemeName(const QString &themeName);
    [[nodiscard]] QString filename() const;

    [[nodiscard]] QString description() const;

    [[nodiscard]] QString themeName() const;
    void createZip(const QString &themeName, KZip *zip);
    void installTheme(const QString &themePath);
    void setDefaultDesktopName(const QString &name);

Q_SIGNALS:
    void mainFileNameChanged(const QString &filename);
    void extraDisplayHeaderChanged(const QStringList &headers);
    void changed();

private:
    void slotFileNameChanged(const QString &);
    void slotExtraDisplayHeadersChanged();
    void saveAsFilename(const QString &filename);
    QString mDefaultDesktopName;
    QLineEdit *mName = nullptr;
    TextCustomEditor::PlainTextEditorWidget *mDescription = nullptr;
    QLineEdit *mFilename = nullptr;
    QLineEdit *mAuthor = nullptr;
    QLineEdit *mEmail = nullptr;
    QLineEdit *mVersion = nullptr;
    KEditListWidget *mExtraDisplayHeaders = nullptr;
};
}
