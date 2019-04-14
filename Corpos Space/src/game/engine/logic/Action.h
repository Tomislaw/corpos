#ifndef ACTION_H
#define ACTION_H

#include <SFML/Graphics.hpp>
#include "game/utility/TextFileData.hpp"

using std::string;
using std::vector;
using std::multimap;
using std::map;
using std::pair;
using std::function;
using std::shared_ptr;

class Entity;

class Action {
public:
	shared_ptr<Entity> invoker;
	string targetName;
	string actionType;
	vector<string> parameters;
};

class InputManager {
public:
	void addInput(string name, function<void(Action)> action) {
		inputs.insert(pair<string, function<void(Action)>>(name, action));
	}
	void invokeInput(Action action) {

		auto range = inputs.equal_range(action.actionType);
		for (auto iter = range.first; iter != range.second; ++iter)
			iter->second(action);
	}
private:
	map<string, function<void(Action)>> inputs;
};

class OutputManager {
public:
	vector<Action> pendingActions;

	void addOutput(std::string name, Action action) {
		outputs.insert(pair<string, Action>(name, action));
	}
	void invokeOutput(string output) {
		auto range = outputs.equal_range(output);
		for (auto iter = range.first; iter != range.second; ++iter)
			pendingActions.push_back(iter->second);
	}
private:
	multimap<string, Action> outputs;
};

class ActionManager {
	ActionManager() {};
	ActionManager(TextItem item);
public:
	InputManager inputs;
	OutputManager outputs;
};

#endif