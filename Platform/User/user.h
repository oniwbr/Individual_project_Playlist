// Copyright 2025 Margarita Kanukova 

#include "/Github/Individual_project_Playlist/Platform/Playlist/playlist.h"

#ifndef PLATFORM_USER_USER_H_
#define PLATFORM_USER_USER_H_

class User {
    char* _email;
    char* _username;
    int _id;
    char* _password;
    Playlist** _favorite;
    Playlist** _created;
};

#endif  // PLATFORM_USER_USER_H_
