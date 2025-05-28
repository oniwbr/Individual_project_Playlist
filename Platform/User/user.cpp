<<<<<<< HEAD
#include "../User/user.h"
#include <string>

User::User() : _username("username"), _password("password"){}

User::User(const std::string& username, const std::string& password) {
	set_username(username);
	set_password(password);
}

User::User(const User& other) {
	if (&other == NULL) throw std::logic_error("The object doesn`t recieve!\n");
	_username = other._username;
	_password = other._password;
}

void User::set_username(const std::string& username) {
	if (!check_correct_username(username)) throw std::logic_error("Incorrect username!\n");
	_username = username;
}

void User::set_password(const std::string& password) {
	if (!check_correct_password(password)) throw std::logic_error("Incorrect password!\n");
	_password = password;
}

const std::string User::get_username() const noexcept { return _username; }

const std::string User::get_password() const noexcept { return _password; }

bool User::operator==(const User& other) const noexcept {
	if (_username != other._username) return false;
	if (_password != other._password) return false;
	return true;
}

bool User::check_correct_username(const std::string& username) {
	if (username.length() == 0) {
		throw std::invalid_argument("The username can`t be empty!\n");
		return false;
	}
	if (username.length() < 4 || username.length() > 15) {
		throw std::invalid_argument("The length of username can be from 4 to 15!\n");
		return false;
	}
	if (username.find(' ') != std::string::npos) {
		throw std::invalid_argument("The spaces can`t be in username!\n");
		return false;
	}
	return true;
}

bool User::check_correct_password(const std::string& password) {
	if (password.length() == 0) {
		throw std::invalid_argument("The password can`t be empty!\n");
		return false;
	}
	if (password.length() < 6 || password.length() > 15) {
		throw std::invalid_argument("The length of password can be from 6 to 15!\n");
		return false;
	}
	if (password.find(' ') != std::string::npos) {
		throw std::invalid_argument("The spaces can`t be in password!\n");
		return false;
	}
	return true;
}
=======
// Copyright 2025 Kanukova Margarita

#include "/Github/Individual_project_Playlist/Platform/User/user.h"
>>>>>>> 5b0996b27230fded92803b14194277f607c7b82e
