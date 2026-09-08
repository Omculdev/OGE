#pragma once
#include <chrono>
#include <fstream>
#include <functional>
#include <ratio>
#include <string>
#include <type_traits>
#include <utility>
class Logger {
private:
	std::ofstream log_file = {};
	std::string log_file_title = {};
	std::string get_current_system_time() const;
	void basic_log(const std::string& string, const std::string& additional);
	void create_logs_folder();
	void create_logs_archive_subfolder();
	void move_old_logs_to_archive();
	Logger() = default;
	Logger(Logger& other) = delete;
	Logger& operator=(const Logger& other) = delete;
public:
	static inline Logger& getInstance() {
		static Logger logger;
		return logger;
	}
	static inline const Logger& getConstInstance() {
		return getInstance();
	}
	void init();
	void logInfo(const std::string& string);
	void logWarning(const std::string& string);
	void logFatal(const std::string& string);
	template <typename Func, typename... Args>
	auto logPerformance(const std::string& string, Func&& func, Args&&... args) {
		using ReturnType = std::invoke_result_t<Func, Args...>;
		auto start = std::chrono::high_resolution_clock::now();
		if constexpr (!std::is_void_v<ReturnType>) {
			auto returnvalue = std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
			auto end = std::chrono::high_resolution_clock::now();
			double duration_milliseconds = std::chrono::duration<double, std::milli>(end - start).count();
			basic_log(string + std::to_string(duration_milliseconds) + " milliseconds", " [PERFORMANCE] ");
			return returnvalue;
		}
		else {
			std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
			auto end = std::chrono::high_resolution_clock::now();
			double duration_milliseconds = std::chrono::duration<double, std::milli>(end - start).count();
			basic_log(string + std::to_string(duration_milliseconds) + " milliseconds", " [PERFORMANCE] ");
		}
	}
};