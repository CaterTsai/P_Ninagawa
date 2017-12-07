#pragma once

#include "constParameter.h"



class ledColor
{
#pragma region CLASS colorUnit
private:
	class colorUnit
	{
	public:
		void update(float delta);
		ofColor getColor();

	private:
		ofColor _now;
		ofColor _from, _to;
		
	};
#pragma endregion




public:
	void update(float delta);
	void draw();

private:
	array<ofColor, cTotalLedColor> _colorSet;
	
};