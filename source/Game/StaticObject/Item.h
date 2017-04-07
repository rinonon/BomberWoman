#pragma once

#include "Game\StaticObject\StaticObject.h"

class Item : public StaticObject{

public:
	enum Type {
		TYPE_BOMB,//爆弾アイテム
		TYPE_POWER,//火力upアイテム
		TYPE_SPEED,
		TYPE_KICK,

		TYPE_NONE,
	};

	Item(int x, int y, Type type);
	~Item();
	void draw() const;
	Item::Type getItemType() const;
	void remove();

private:
	int mGraphHd[4] = { 8, 9, -1 ,-1 };
	Item::Type mItemType;
};