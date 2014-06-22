//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2014 Sanjiban Bairagya <sanjiban22393@gmail.com>
//

#ifndef PLAYBACKSOUNDCUEITEM_H
#define PLAYBACKSOUNDCUEITEM_H

#include "PlaybackItem.h"
#include "GeoDataSoundCue.h"

#include "config-phonon.h"

#ifdef HAVE_PHONON
#include <Phonon/MediaObject>
#include <Phonon/AudioOutput>
#endif

namespace Marble
{
class PlaybackSoundCueItem : public PlaybackItem
{
public:
    PlaybackSoundCueItem( const GeoDataSoundCue* soundCue );
    const GeoDataSoundCue* soundCue() const;
#ifdef HAVE_PHONON
    Phonon::MediaObject* mediaObject();
#endif
    double duration() const;
    void play();
    void pause();
    void seek( double position );
    void stop();
private:
    const GeoDataSoundCue* m_soundCue;
#ifdef HAVE_PHONON
    Phonon::MediaObject* m_mediaObject;
#endif
};
}
#endif