#include "Action.h"

ActionManager::ActionManager(TextItem & item)
{
	int currentPosition = 0;
	auto values = item.toString();

	while (currentPosition < values.size())
	{
		if (currentPosition + 3 >= values.size()) {
			if (item.parent == nullptr || item.parent->parent == nullptr) return;
			Logger::w("Incorrect action in {} in element {} in file {}",
				item.name, item.parent->name, item.parent->parent->filePath);
			return;
		}

		auto activateType = values[currentPosition];
		auto action = Action();

		currentPosition++;
		action.targetName = values[currentPosition];
		currentPosition++;
		action.actionType = values[currentPosition];
		currentPosition++;
		auto parametersCount = item.toInt(currentPosition);
		currentPosition++;

		if (currentPosition + parametersCount >= values.size()) {
			if (item.parent == nullptr || item.parent->parent == nullptr) return;
			Logger::w("Incorrect action in {} in element {} in file {}",
				item.name, item.parent->name, item.parent->parent->filePath);
		}

		for (int i = 0; i < parametersCount; i++) {
			action.parameters.push_back(values[currentPosition]);
			currentPosition++;
		}
			

		outputs.addOutput(activateType, action);
	}
}