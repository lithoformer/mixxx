#ifndef MIXXX_SOUNDSOURCEMODPLUG_H
#define MIXXX_SOUNDSOURCEMODPLUG_H

#include "sources/soundsource.h"

namespace ModPlug {
#include <libmodplug/modplug.h>
}

#include <vector>

namespace Mixxx {

// Class for reading tracker files using libmodplug.
// The whole file is decoded at once and saved
// in RAM to allow seeking and smooth operation in Mixxx.
class SoundSourceModPlug: public Mixxx::SoundSource {
public:
    static QList<QString> supportedFileExtensions();

    static const SINT kChannelCount;
    static const SINT kBitsPerSample;
    static const SINT kFrameRate;

    // apply settings for decoding
    static void configure(unsigned int bufferSizeLimit,
            const ModPlug::ModPlug_Settings &settings);

    explicit SoundSourceModPlug(QUrl url);
    ~SoundSourceModPlug();

    Result parseTrackMetadata(Mixxx::TrackMetadata* pMetadata) const /*override*/;

    QImage parseCoverArt() const /*override*/;

    void close() /*override*/;

    SINT seekSampleFrame(SINT frameIndex) /*override*/;

    SINT readSampleFrames(SINT numberOfFrames,
            CSAMPLE* sampleBuffer) /*override*/;

private:
    Result tryOpen(SINT channelCountHint) /*override*/;

    static unsigned int s_bufferSizeLimit; // max track buffer length (bytes)

    ModPlug::ModPlugFile *m_pModFile; // modplug file descriptor
    QByteArray m_fileBuf; // original module file data

    typedef std::vector<SAMPLE> SampleBuffer;
    SampleBuffer m_sampleBuf;

    SINT m_seekPos; // current read position
};

} // namespace Mixxx

#endif // MIXXX_SOUNDSOURCEMODPLUG_H
