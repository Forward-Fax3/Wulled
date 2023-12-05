#pragma once
#include "app.h"


class SetAPILayer : public WLD::Layer
{
public:
	SetAPILayer(std::string name);
	~SetAPILayer();

	void OnImGuiDraw() override;
};

class SetAPI : public WLD::Application
{
public:
	SetAPI(bool* run);
	~SetAPI();
};