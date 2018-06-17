#include "kshchart.h"

#include <QDebug>
#include <QFile>

KshChart::KshChart(QString filePath, bool loadImmediately)
    : m_filePath(filePath)
{
    if (loadImmediately) load();
}

bool split(const QString &str, const QString &sep, QString &a, QString &b)
{
    int index = str.indexOf(sep, Qt::CaseSensitivity::CaseSensitive);
    if (index < 0)
        return false;
    a = str.left(index);
    b = str.right(str.size() - index - 1);
    return true;
}

bool KshChart::load()
{
    if (m_loaded) return true;

    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    const QString SEP = "--";

    int lineNumber = 0;
    QTextStream in(&file);

    // header first
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();

        lineNumber++;
        if (line == SEP)
            break;
        else if (line.isEmpty())
            continue;

        QString key, value;
        if (split(line, "=", key, value))
            m_settings[key] = QVariant(value);
        else return false;
    }

    KshBlock block;
    KshTick tick;
    KshTime time(0, 0);

    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        lineNumber++;

        if (line == SEP)
        {
            m_blocks.append(block);
            block = KshBlock();

            time.block++;
            time.tick = 0;

            continue;
        }
        else if (line.isEmpty())
            continue;

        QString key, value;
        if (line.startsWith("#"))
        {
            QStringList pieces = line.split(" ", QString::SplitBehavior::SkipEmptyParts);
            if (pieces.count() != 3)
            {
                qInfo() << "Invalid define in .ksh file on line " << lineNumber;
                continue;
            }

            QString type = pieces[0];

            KshEffectDef def;
            def.typeName = pieces[1];

            QStringList params = pieces[2].split(';');
            foreach (QString param, params)
            {
                if (!split(param, "=", key, value))
                {
                    qInfo() << "Invalid parameter in custom effect definition in .ksh file on line " << lineNumber;
                    continue;
                }
                def.parameters[key] = QVariant(value);
            }

            if (type == "#define_fx")
                m_fxDefines[def.typeName] = def;
            else if (type == "#define_filter")
                m_filterDefines[def.typeName] = def;
            else qInfo() << "Unknown define in .ksh file on line " << lineNumber;
        }
        else if (split(line, "=", key, value))
        { // tick setting
            KshTickSetting setting { key, QVariant(value) };
            tick.settings.append(setting);
        }
        else
        {
            QStringList pieces = line.split("|", QString::SplitBehavior::SkipEmptyParts);
            if (pieces.count() != 3)
            {
                qInfo() << "Invalid playable state in .ksh file on line " << lineNumber;
                return false;
            }

            tick.btState = pieces[0];
            tick.fxState = pieces[1];

            if (tick.btState.count() != 4)
            {
                qInfo() << "Invalid BT state in .ksh file on line " << lineNumber;
                return false;
            }

            if (tick.fxState.count() != 2)
            {
                qInfo() << "Invalid FX state in .ksh file on line " << lineNumber;
                return false;
            }

            tick.volState = pieces[2];
            if (tick.fxState.count() < 2)
            {
                qInfo() << "Invalid VOL state in .ksh file on line " << lineNumber;
                return false;
            }
            else if (tick.volState.count() > 2)
            {
                tick.add = tick.volState.mid(2);
                tick.volState = tick.volState.left(2);
            }

            block.ticks.append(tick);
            tick = KshTick();
            time.tick++;
        }
    }

    m_loaded = true;
    return true;
}
