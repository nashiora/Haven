#ifndef KSHCHART_H
#define KSHCHART_H

#include <QString>
#include <QTextStream>
#include <QList>
#include <QMap>

// :LOCAL
// This implementation uses QVariant a lot for value storage.
// Not everything in the KSH format is a string, often they are numeric values.
// Using QVariant allows simple construction from a string (straight from the file)
//  as well as simple consumption (variant.toInt()) where the type is known.
// Variant conversion functions also allow a bool flag to be passed in for
//  verification later.
//
// For data types which cannot be converted easily through a variant,
//  we would need a custom implementation anyway.
// Type suffixes in the files cannot be parsed by means of a library anyway,
//  and an instant transision between two values separated by a `;` requires two parses.

struct KshTickSetting
{
    QString key;
    QVariant value;
};

struct KshTick
{
    QVector<KshTickSetting> settings;
    QString btState, fxState, volState;
    QString add;
};

struct KshBlock
{
    QVector<KshTick> ticks;
};

struct KshEffectDef
{
    QString typeName;
    QHash<QString, QVariant> parameters;
};

class KshTime
{
public:
    KshTime() : block(-1), tick(-1) { }
    KshTime(int block, int tick) : block(block), tick(tick) { }

    inline operator bool() const { return block >= 0 && tick >= 0; }

    int block, tick;
};

class KshChart
{
public:
    KshChart(QString filePath, bool loadImmediately = false);

    bool load();

    int blockCount() const { return m_blocks.size(); }

    bool getBlock(int index, KshBlock *&block) const { return getBlock(KshTime(index, 0), block); }
    bool getBlock(const KshTime &time, KshBlock *&block)
    {
        if (!time) return false;
        if (time.block >= m_blocks.count())
            return false;
        block = &m_blocks[time.block];
        return block->ticks.count() > 0;
    }

    bool getTick(const KshTime &time, KshTick *&tick)
    {
        if (!time) return false;
        if (time.block >= m_blocks.count())
            return false;
        KshBlock &block = m_blocks[time.block];
        if (time.tick >= block.ticks.size())
            return false;
        tick = &block.ticks[time.tick];
        return true;
    }

    QVariant operator [](QString key) const { return m_settings[key]; }

private:
    bool m_loaded = false;
    QString m_filePath;

    QHash<QString, QVariant> m_settings;
    QVector<KshBlock> m_blocks;
    QHash<QString, KshEffectDef> m_fxDefines;
    QHash<QString, KshEffectDef> m_filterDefines;
};

#endif // KSHCHART_H
