// Copyright 2025 Margarita Kanukova

#include "../Date/date.h"
#include "../User/user.h"
#include "../Time/time.h"
#include "../Song/song.h"

#ifndef PLATFORM_PLAYLIST_PLAYLIST_H_
#define PLATFORM_PLAYLIST_PLAYLIST_H_

enum State { Private, Public };
class PLaylist {
    int _id;
    char* _name;
    Date _date_of_creation;
    User* _author;
    int _number_of_songs;
    Time _druation_of_songs;
    State _state;
    Song** _songs;
    
};

#endif  // PLATFORM_PLAYLIST_PLAYLIST_H_