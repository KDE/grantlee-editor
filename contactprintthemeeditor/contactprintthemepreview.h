/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef CONTACTPRINTTHEMEPREVIEW_H
#define CONTACTPRINTTHEMEPREVIEW_H

#include <QWidget>

#include <KContacts/Addressee>
#include "grantleethemeeditor/previewwidget.h"

namespace KAddressBookGrantlee {
}
class QWebEngineView;

class ContactPrintThemePreview : public GrantleeThemeEditor::PreviewWidget
{
    Q_OBJECT
public:
    explicit ContactPrintThemePreview(const QString &projectDirectory, QWidget *parent = nullptr);
    ~ContactPrintThemePreview() override;

    void updateViewer() override;
    void createScreenShot(const QStringList &fileName) override;
    void setThemePath(const QString &projectDirectory, const QString &mainPageFileName) override;
    void loadConfig() override;

Q_SIGNALS:
    void needUpdateViewer();

private:
    KContacts::Addressee mContact;
    QString mThemePath;
    QWebEngineView *mViewer = nullptr;
};

#endif // CONTACTPRINTTHEMEPREVIEW_H
