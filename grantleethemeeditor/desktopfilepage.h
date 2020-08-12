/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef DESKTOPFILEPAGE_H
#define DESKTOPFILEPAGE_H

#include <QWidget>
#include "grantleethemeeditor_export.h"
class QLineEdit;
class KZip;
class KEditListWidget;
namespace KPIMTextEdit {
class PlainTextEditorWidget;
}
namespace GrantleeThemeEditor {
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
    ~DesktopFilePage();

    void saveTheme(const QString &path);
    void loadTheme(const QString &path);

    void setThemeName(const QString &themeName);
    Q_REQUIRED_RESULT QString filename() const;

    Q_REQUIRED_RESULT QString description() const;

    Q_REQUIRED_RESULT QString themeName() const;
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
    KPIMTextEdit::PlainTextEditorWidget *mDescription = nullptr;
    QLineEdit *mFilename = nullptr;
    QLineEdit *mAuthor = nullptr;
    QLineEdit *mEmail = nullptr;
    QLineEdit *mVersion = nullptr;
    KEditListWidget *mExtraDisplayHeaders = nullptr;
};
}

#endif // DESKTOPFILEPAGE_H
