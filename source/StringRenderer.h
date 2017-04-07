#pragma once

class ResourceLoader;

class StringRenderer {
public:
	static StringRenderer* getInstance();
	void draw(int x, int y, const char* string, unsigned color = 0xffffff) const;

	static void create();
	static void destroy();

private:
	StringRenderer();
	StringRenderer(StringRenderer&);
	~StringRenderer();
	ResourceLoader* rl;
	static StringRenderer* mInstance;
};