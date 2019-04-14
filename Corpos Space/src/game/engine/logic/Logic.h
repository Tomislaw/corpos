#ifndef	LOGIC_H
#define LOGIC_H

#include <SFML/Graphics.hpp>
#include "game/utility/TextFileData.hpp"
#include "game/engine/Entity.hpp"
using std::string;

class Counter : public Entity {

	Counter(TextElement * element);

public:
	int count = 0;
	int maxCount = -1;
	int minCount = 0;
protected:
	virtual void initializeActionManager() override;
};

#endif