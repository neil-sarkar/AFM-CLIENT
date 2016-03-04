#ifndef AFMOBJECT_H
#define AFMOBJECT_H

#include <QObject>
#include <QSettings>
#include "command_node.h"
#include <QSettings>

class AFMObject : public QObject
{
    Q_OBJECT
public:
    explicit AFMObject();
    virtual void init();
    typedef std::function<void(QByteArray paylaod)> callback_return_type;
    quint16 bytes_to_word(quint8 low, quint8 high); // maybe move this to a byte manipulation class
    QSettings settings;
    virtual void set_settings();
    virtual void update_settings(QString settings_group_name, QString settings_key, QVariant settings_value);

signals:
    void command_generated(CommandNode* command);

private:

public slots:
};

#endif // AFMOBJECT_H
