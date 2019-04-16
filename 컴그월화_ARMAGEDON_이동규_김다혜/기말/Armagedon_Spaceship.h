#pragma once

class Spaceship {
private:
	float x, y;
public:
	Spaceship() {}
	~Spaceship() {}
	void Render();
	void WireRender();
};