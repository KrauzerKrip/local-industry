module;

#include <map>
#include <stdexcept>
#include <optional>

#include <entt/entt.hpp>

export module character:task_queue;

import :components;

class MaxTaskPositionException : public std::runtime_error {
public:
	MaxTaskPositionException(std::string msg) : std::runtime_error(msg) {}
};

export class TaskQueue {
public:
	TaskQueue(){};
	//TaskQueue(TaskQueue& taskQueue) : m_tasks(taskQueue.m_tasks) {}
	//TaskQueue(TaskQueue&& taskQueue) : m_tasks(std::move(taskQueue.m_tasks)) {}

	void push(entt::entity task) {
		if (m_tasks.empty()) {
			m_tasks.emplace(0, task);
		}
		else {
			m_tasks.emplace(m_tasks.rbegin()->first + 1, task);
		}
	}


	std::optional<entt::entity> getFront() {
		if (m_tasks.empty()) {
			return std::nullopt;
		}
		else {
			return m_tasks.begin()->second;
		}
	}

	void insert(unsigned int position, entt::entity task) {
		// if (position + 1 > m_tasks.size()) {
		//	throw MaxTaskPositionException("Task position is too high.");
		// }
		if (m_tasks.contains(position)) {
			shiftRight(position);
		}
		m_tasks.emplace(position, task);
	}

	void pop() {
		if (!m_tasks.empty()) {
			m_tasks.erase(m_tasks.begin());
			if (!m_tasks.empty()) {
				shiftLeft(0);
			}
		}
	}

private:
	void shiftRight(unsigned int startPosition) { 
		auto iter = m_tasks.begin();

		std::advance(iter, startPosition);
		for (int i = 1; iter != m_tasks.end(); i++) {
			auto nodeHandler = m_tasks.extract(iter);
			nodeHandler.key() = nodeHandler.key() + 1;
			m_tasks.insert(std::move(nodeHandler));
			iter = m_tasks.begin();
			std::advance(iter, startPosition + i);
		}
	}

	void shiftLeft(unsigned int startPosition) {
		auto iter = m_tasks.begin();
		std::advance(iter, startPosition);

		for (int i = 1; iter != m_tasks.end(); i++) {
			auto nodeHandler = m_tasks.extract(iter);
			nodeHandler.key() = nodeHandler.key() - 1;
			m_tasks.insert(std::move(nodeHandler));
			iter = m_tasks.begin();
			std::advance(iter, startPosition + i);
		}
	}
 
	static const int MAX_TASKS = 20;

	std::map<unsigned int, entt::entity> m_tasks;
};