#include "Utils/General/Logger.hpp"
#include <fstream>
#include <format>
#include <iostream>
#include <windows.h>
#include <filesystem>
std::string Logger::get_current_system_time() const {
	auto now = std::chrono::system_clock::now();
	return std::format("{:%Y-%m-%d %H-%M-%S}", now);
}
void Logger::basic_log(const std::string& logdata, const std::string& additional) {
	std::string logstring = "<" + get_current_system_time() + ">" + additional + logdata;
	log_file << logstring << "\n";
}
void Logger::logInfo(const std::string& logdata) {
	basic_log(logdata, " [INFO] ");
}
void Logger::logWarning(const std::string& logdata) {
	basic_log(logdata, " [WARNING] ");
}
void Logger::logFatal(const std::string& logdata) {
	basic_log(logdata, " [FATAL] ");
}
void Logger::create_logs_folder() {
	logInfo("create_logs_folder: Attemptring to create logs folder");
	try {
		std::filesystem::create_directories("logs");
	}
	catch (std::filesystem::filesystem_error& exception) {
		logFatal("create_logs_folder: Failed to create logs folder" + std::string(exception.what()));
		throw;
	}
	logInfo("create_logs_folder: Successfully created logs folder");
}
void Logger::create_logs_archive_subfolder() {
	logInfo("create_logs_archive_subfolder: Attemptring to create logs archive subfolder");
	try {
		std::filesystem::create_directories("logs/archive");
	}
	catch (std::filesystem::filesystem_error& exception) {
		logFatal("create_logs_archive_subfolder: Failed to create logs archive subfolder" + std::string(exception.what()));
		throw;
	}
	logInfo("create_logs_archive_subfolder: Successfully created logs archive subfolder");
}
void Logger::move_old_logs_to_archive() {
	if (!std::filesystem::exists("logs")) {
		logWarning("move_old_logs_to_archive: Logs folder not found");
		create_logs_folder();
	}
	if (!std::filesystem::exists("logs/archive")) {
		logWarning("move_old_logs_to_archive: Logs archive subfolder not found");
		create_logs_archive_subfolder();
	}
	for (const auto& file : std::filesystem::directory_iterator("logs")) {
		if (file.is_regular_file() && file.path().extension() == ".log") {
			rename(file.path(), "logs/archive/" + file.path().filename().string());
		}
	}
}
void Logger::init() {
	create_logs_folder();
	create_logs_archive_subfolder();
	move_old_logs_to_archive();
	auto now = std::chrono::system_clock::now();
	log_file_title = "GraphicsEngineLog " + get_current_system_time() + ".log";
	log_file.open("logs/" + log_file_title, std::ios::app);
	if (!log_file.is_open()) {
		std::cerr << "init failed: Failed to create log file: " + log_file_title;
		return;
	}
}