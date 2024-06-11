#include "task_queue.h"

bool TaskQueue::push(entt::entity task) {
	if (m_tasks.size() >= MAX_TASKS) {
		return false;
	}

	if (m_tasks.empty()) {
		m_tasks.emplace(0, task);
	}
	else {
		m_tasks.emplace(m_tasks.rbegin()->first + 1, task);
	}

	return true;
}

std::optional<entt::entity> TaskQueue::getFront() {
	if (m_tasks.empty()) {
		return std::nullopt;
	}
	else {
		return m_tasks.begin()->second;
	}
}

void TaskQueue::insert(unsigned int position, entt::entity task) {
	// if (position + 1 > m_tasks.size()) {
	//	throw MaxTaskPositionException("Task position is too high.");
	// }
	if (m_tasks.contains(position)) {
		shiftRight(position);
	}
	m_tasks.emplace(position, task);
}

void TaskQueue::pop() {
	if (!m_tasks.empty()) {
		m_tasks.erase(m_tasks.begin());
		if (!m_tasks.empty()) {
			shiftLeft(0);
		}
	}
}

void TaskQueue::clear() { m_tasks.clear(); }

void TaskQueue::shiftRight(unsigned int startPosition) {
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

void TaskQueue::shiftLeft(unsigned int startPosition) {
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
