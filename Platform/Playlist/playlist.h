// Copyright 2025 Margarita Kanukova

<<<<<<< HEAD
#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <iostream>
#include "/Github/Individual_project_Playlist/Platform/Date/date.h"
#include "/Github/Individual_project_Playlist/Platform/User/user.h"
#include "/Github/Individual_project_Playlist/Platform/Time/ctime.h"
#include "/Github/Individual_project_Playlist/Platform/Song/song.h"

class User;

enum States { Private, Public };
class Playlist {
	std::string _name;
	Date _date_of_creation;
	User* _username;
	int _number_of_songs;
	CTime _druation_of_songs;
	States _state;
	Song** _songs;
=======
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
>>>>>>> 5b0996b27230fded92803b14194277f607c7b82e
};

#endif  // PLATFORM_PLAYLIST_PLAYLIST_H_
