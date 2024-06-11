#pragma once

#include <map>
#include <stdexcept>
#include <optional>
#include <ranges>

#include <entt/entt.hpp>

#include "components.h"

template <typename F>
concept IsFunction = requires(const F& function) { function(entt::entity()); };

class MaxTaskPositionException : public std::runtime_error {
public:
	MaxTaskPositionException(std::string msg) : std::runtime_error(msg) {}
};

class TaskQueue {
public:
	TaskQueue(){};
	// TaskQueue(TaskQueue& taskQueue) : m_tasks(taskQueue.m_tasks) {}
	// TaskQueue(TaskQueue&& taskQueue) : m_tasks(std::move(taskQueue.m_tasks)) {}

	[[nodiscard]] bool push(entt::entity task);
	template <IsFunction F> void forEach(F&& function);
	std::optional<entt::entity> getFront();
	void insert(unsigned int position, entt::entity task);
	void pop();
	void clear();

private:
	void shiftRight(unsigned int startPosition);
	void shiftLeft(unsigned int startPosition);

	static const int MAX_TASKS = 5;

	std::map<unsigned int, entt::entity> m_tasks;
};

template <IsFunction F> inline void TaskQueue::forEach(F&& function) {
	for (auto& v : m_tasks | std::views::values) {
		function(v);
	}
}
