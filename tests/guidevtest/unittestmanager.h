#ifndef UNITTESTMANAGER_H
#define UNITTESTMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QFile>

class UnitTestBase : public QObject
{
    Q_OBJECT
signals:
    void finished();
    void error();

public:
    enum UnitID {
        InfoUnitId,

    };

    explicit UnitTestBase(UnitID id, QObject *parent = 0);
    void setPorts(const QString &src, const QString &dst);
    void setEnable(bool enable);
    bool isEnabled() const;

    int id() const;
    QString name() const;
    QString description() const;

public slots:
    virtual void start() = 0;

protected:
    int m_id;
    QString m_name;
    QString m_description;
    QString m_enableParam;

    bool openLog();
    bool writeToLog(const QString &content);
    void closeLog();

    QString getDateTime() const;

private:
    QString m_srcPort;
    QString m_dstPort;
    QFile m_log;
};



class UnitTestFactory
{
public:
    static UnitTestBase *create(UnitTestBase::UnitID id);
};



class UnitTestManager : public QObject
{
    Q_OBJECT
signals:
    void started();
    void allFinished();

public:
    explicit UnitTestManager(QObject *parent = 0);
    void setPorts(const QString &src, const QString &dst);
    void setLogFile(const QString &log);

    QList<UnitTestBase *> units() const;

    static const QString logFileParam;

public slots:
    void start();
    void stop();

private slots:
    void step();

private:
    int m_count;
    int m_it;
    QString m_srcPort;
    QString m_dstPort;
    QList<UnitTestBase *> m_unitList;
};

#endif // UNITTESTMANAGER_H