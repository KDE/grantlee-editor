/*
   Copyright (C) 2015-2019 Montel Laurent <montel@kde.org>

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
#ifndef CONTACTPRINTTHEMEPREVIEW_H
#define CONTACTPRINTTHEMEPREVIEW_H

#include <QWidget>

#include <KContacts/Addressee>
#include "grantleethemeeditor/previewwidget.h"

namespace KAddressBookGrantlee {
class GrantleePrint;
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
    KAddressBookGrantlee::GrantleePrint *mGrantleePrint = nullptr;
    QWebEngineView *mViewer = nullptr;
};

#endif // CONTACTPRINTTHEMEPREVIEW_H
