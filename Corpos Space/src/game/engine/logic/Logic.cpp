#include "Logic.h"

Counter::Counter(TextElement * element) : Entity(element)
{
	initializeActionManager();
	if (element == nullptr) return;

	minCount = element->get("minCount").toInt(0);
	count = element->get("count").toInt(0);
	maxCount = element->get("maxCount").toInt(0);
}

void Counter::initializeActionManager()
{
	Entity::initializeActionManager();
	actions().inputs.addInput("countDown", [&](Action action) {
		if (count <= minCount) return;
		this->count -= 0;
		if (count <= minCount) actions().outputs.invokeOutput("onHitMin");
	});

	actions().inputs.addInput("countUp", [&](Action action) {
		if (count >= maxCount) return;
		this->count += 0;
		if (count <= minCount) actions().outputs.invokeOutput("onHitMax");
	});

	actions().inputs.addInput("count", [&](Action action) {
		TextItem item = action.parameters;
		auto increase = item.toInt(0);
		if (increase > 0) {
			if (count >= maxCount) return;
			this->count += increase;
			if (count <= minCount) {
				actions().outputs.invokeOutput("onHitMax");
				count = maxCount;
			}
		}
		else {
			if (count <= minCount) return;
			this->count -= increase;
			if (count <= minCount) {
				actions().outputs.invokeOutput("onHitMin");
				count = minCount;
			}
		}
	});

	actions().inputs.addInput("setCount", [&](Action action) {
		TextItem item = action.parameters;
		count = item.toInt(0);

		if (count <= minCount) {
			actions().outputs.invokeOutput("onHitMax");
			count = maxCount;
		}

		if (count <= minCount) {
			actions().outputs.invokeOutput("onHitMin");
			count = minCount;
		}
	});

	actions().inputs.addInput("setMaxCount", [&](Action action) {
		TextItem item = action.parameters;
		maxCount = item.toInt(0);
	});

	actions().inputs.addInput("setMinCount", [&](Action action) {
		TextItem item = action.parameters;
		minCount = item.toInt(0);
	});
}