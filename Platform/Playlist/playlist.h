// Copyright 2025 Margarita Kanukova

#include "/Github/Individual_project_Playlist/Platform/Date/date.h"
#include "/Github/Individual_project_Playlist/Platform/User/user.h"
#include "/Github/Individual_project_Playlist/Platform/Time/time.h"
#include "/Github/Individual_project_Playlist/Platform/Song/song.h"

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
