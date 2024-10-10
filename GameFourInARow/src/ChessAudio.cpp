/*
 * Copyright (C) 2024 Arthur Zhang <arthur.zhang.cx@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "ChessAudio.h"
#include <QMediaPlaylist>

namespace GameFourInARow {
    ChessAudio::ChessAudio() {
        player_ = new QMediaPlayer;
        player_->setVolume(50);

        player_bk_ = new QMediaPlayer;
        player_bk_->setVolume(50);
    }
    ChessAudio *ChessAudio::instance() {
        static ChessAudio inst;
        return &inst;
    }

    void ChessAudio::play(AudioType type) {
        QUrl url;
        switch (type) {
            case AudioType::AudioBk: {
                auto play_list = new QMediaPlaylist;
                url = QUrl("qrc:///res/audio/audio_background.mp3");
                play_list->addMedia(url);
                play_list->setPlaybackMode(QMediaPlaylist::PlaybackMode::Loop);
                player_bk_->setPlaylist(play_list);
                player_bk_->play();
                return;
            }
            case AudioType::AudioChessDrop: {
                url = QUrl("qrc:///res/audio/audio_chess_drop.mp3");
                break;
            }
            default: {
                assert(false);
            }
        }

        player_->setMedia(url);
        player_->play();
    }

}