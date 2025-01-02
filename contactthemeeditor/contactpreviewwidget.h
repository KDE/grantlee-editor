/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>

#include <KContacts/Addressee>

class QTabWidget;

namespace Akonadi
{
class ContactViewer;
class ContactGroupViewer;
}

namespace KAddressBookGrantlee
{
class GrantleeContactFormatter;
class GrantleeContactGroupFormatter;
}

class ContactPreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContactPreviewWidget(const QString &projectDirectory, QWidget *parent = nullptr);
    ~ContactPreviewWidget() override;

    void updateViewer();
    void createScreenShot(const QStringList &fileName);
    void setThemePath(const QString &projectDirectory);
    void loadConfig();

private:
    KContacts::Addressee mContact;
    Akonadi::ContactViewer *mContactViewer = nullptr;
    Akonadi::ContactGroupViewer *mGroupViewer = nullptr;

    KAddressBookGrantlee::GrantleeContactFormatter *mFormatter = nullptr;
    KAddressBookGrantlee::GrantleeContactGroupFormatter *mGroupFormatter = nullptr;

    QTabWidget *mTabWidget = nullptr;
};
