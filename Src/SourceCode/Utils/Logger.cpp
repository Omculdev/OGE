#include "Utils/Logger.hpp"
#include <fstream>
#include <format>
#include <iostream>
#include <windows.h>
#include <filesystem>
using namespace std;
using namespace filesystem;
string Logger::get_current_system_time() const {
	auto now = chrono::system_clock::now();
	return format("{:%Y-%m-%d %H-%M-%S}", now);
}
void Logger::basic_log(const string& logdata, const string& additional) {
	if (!log_file.is_open()) {
		cerr << additional + "log failed: Failed to open log file: " + log_file_title;
		return;
	}
	string logstring = "<" + get_current_system_time() + ">" + additional + logdata;
	log_file << logstring << "\n";
}
void Logger::logInfo(const string& logdata) {
	basic_log(logdata, " [INFO] ");
}
void Logger::logWarning(const string& logdata) {
	basic_log(logdata, " [WARNING] ");
}
void Logger::logFatal(const string& logdata) {
	basic_log(logdata, " [FATAL] ");
}
void Logger::create_logs_folder() {
	logInfo("create_logs_folder: Attemptring to create logs folder");
	try {
		create_directories("logs");
	}
	catch (filesystem_error&) {
		logFatal("create_logs_folder: Failed to create logs folder");
		throw;
	}
	logInfo("create_logs_folder: Successfully created logs folder");
}
void Logger::create_logs_archive_subfolder() {
	logInfo("create_logs_archive_subfolder: Attemptring to create logs archive subfolder");
	try {
		create_directories("logs/archive");
	}
	catch (filesystem_error&) {
		logFatal("create_logs_archive_subfolder: Failed to create logs archive subfolder");
		throw;
	}
	logInfo("create_logs_archive_subfolder: Successfully created logs archive subfolder");
}
void Logger::move_old_logs_to_archive() {
	if (!exists("logs")) {
		logWarning("move_old_logs_to_archive: Logs folder not found");
		create_logs_folder();
	}
	if (!exists("logs/archive")) {
		logWarning("move_old_logs_to_archive: Logs archive subfolder not found");
		create_logs_archive_subfolder();
	}
	for (const auto& file : directory_iterator("logs")) {
		if (file.is_regular_file() && file.path().extension() == ".log") {
			rename(file.path(), "logs/archive/" + file.path().filename().string());
		}
	}
}
void Logger::init() {
	move_old_logs_to_archive();
	auto now = chrono::system_clock::now();
	log_file_title = "GraphicsEngineLog " + get_current_system_time() + ".log";
	log_file.open("logs/" + log_file_title, ios::app);
	if (!log_file.is_open()) {
		cerr << "init failed: Failed to create log file: " + log_file_title;
		return;
	}
}