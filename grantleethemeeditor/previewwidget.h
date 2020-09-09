/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef GRANTLEEPREVIEWWIDGET_H
#define GRANTLEEPREVIEWWIDGET_H
#include <QWidget>
#include "grantleethemeeditor_export.h"

namespace GrantleeThemeEditor {
class GRANTLEETHEMEEDITOR_EXPORT PreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PreviewWidget(QWidget *parent = nullptr);
    ~PreviewWidget();

    virtual void updateViewer();

    virtual void loadConfig();
    virtual void createScreenShot(const QStringList &lstFileName);
    virtual void setThemePath(const QString &projectDirectory, const QString &mainPageFileName);

    void setPrinting(bool printMode);
    Q_REQUIRED_RESULT bool printing() const;

public Q_SLOTS:
    virtual void slotMainFileNameChanged(const QString &);
    virtual void slotExtraHeaderDisplayChanged(const QStringList &headers);

Q_SIGNALS:
    void needUpdateViewer();

protected:
    bool mPrinting = false;
};
}

#endif // GRANTLEEPREVIEWWIDGET_H
