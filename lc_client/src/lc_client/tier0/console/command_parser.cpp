#include "command_parser.h"

#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

#include "ldk_client/local_engine/scene_controlling.h"
#include "lc_client/eng_scene/entt/components.h"

#include "lc_client/exceptions/command_exceptions.h"


CommandParser::CommandParser(std::string text) {

	// std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c) { return std::tolower(c); });

	std::stringstream ss(text);
	std::string item;
	std::vector<std::string> tokens;

	while (std::getline(ss, item, ' ')) {
		tokens.push_back(item);
	}

	if (tokens.size() == 0) {
		throw IncorrectCommandException(text);
	}

	// if (tokens.size() > 3) {
	//	throw IncorrectCommandException(text);
	// }

	if (tokens.at(0) == "set") {
		m_type = CommandType::SET;

		try {
			m_operator = tokens.at(1);

			m_argument = tokens.at(2);
		}
		catch (std::out_of_range&) {
			throw IncorrectCommandException(text);
		}
	}
	//else if (tokens.at(0) == "+rot") {
	//	auto view = SceneControlling::getScene()->getSceneRegistry().view<Transform, Properties>();

	//	for (auto& entity : view) {
	//		if (tokens.at(1) == view.get<Properties>(entity).id) {
	//			if (tokens.size() == 5) {
	//				Transform& transform = view.get<Transform>(entity);
	//				float x = std::stof(tokens.at(2));
	//				float y = std::stof(tokens.at(3));
	//				float z = std::stof(tokens.at(4));

	//				transform.rotation *= glm::angleAxis(glm::radians(x), glm::vec3(1.f, 0.f, 0.f));
	//				transform.rotation *= glm::angleAxis(glm::radians(y), glm::vec3(0.f, 1.f, 0.f));
	//				transform.rotation *= glm::angleAxis(glm::radians(z), glm::vec3(0.f, 0.f, 1.f));
	//			}
	//		}
	//	}
	//}
	else if (tokens.at(0) == "get") {
		m_type = CommandType::GET;

		try {
			m_operator = tokens.at(1);
		}
		catch (std::out_of_range&) {
			throw IncorrectCommandException(text);
		}
	}
	else if (tokens.at(0) == "execute") {
		m_type = CommandType::EXECUTE;
	}
	else if ((tokens.at(0) == "exit") || (tokens.at(0) == "quit")) {
		exit(0);
	}
	else {
		throw IncorrectCommandException(text);
	}
}

CommandType CommandParser::getType() { return m_type; }

std::string CommandParser::getOperator() { return m_operator; }

std::string CommandParser::getArgument() { return m_argument; }
