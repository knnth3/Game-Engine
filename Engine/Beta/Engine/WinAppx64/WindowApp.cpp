#include "WindowApp.h"

using namespace std;
using namespace Engine;


WindowApp::WindowApp(std::string appName, float width, float height):
	GraphicsWindow(appName, width, height)
{
	m.Scale(20, 20, 20);
	m.SetColor(0.0f, 0.0f, 1.0f);
	s.SetDimensions(100, 100);
	t = "Loading...";
	t.SetBounds(800, 30);
	mouset = "Loading...";
	mouset.SetBounds(800, 600);
	mouset.SetPosition(0, 30);
}

void WindowApp::Update()
{
	auto timer = WindowResources::GetTimer();
	//Color
	static bool wf = false;
	static int red = 0;
	static int green = 0;
	static int blue = 0;
	static int rrel = 1;
	static int grel = 2;
	static int brel = 4;
	red += rrel;
	green += grel;
	blue += brel;
	if (red > 255 || red < 0)
		rrel = -rrel;
	if (green > 255 || green < 0)
		grel = -grel;
	if (blue > 255 || blue < 0)
		brel = -brel;
	float redf = (float)red / 255.0f;
	float greenf = (float)green / 255.0f;
	float bluef = (float)blue / 255.0f;
	m.SetColor(redf, greenf, bluef);

	//Rotation
	float speed = 4.9f;
	float seconds = (float)timer->elapsed() / 1000.0f;
	float rotation = speed * seconds;
	m.RotateRelative(0.0f, rotation, 0.0f);

	//Mouse
	auto input = WindowResources::GetInput()->GetMouse();
	glm::vec2 pos = input->GetPositon();
	mouset = std::string("Mouse:\n x=") + std::to_string(pos.x) + std::string("\ny= ") + std::to_string(pos.y);

	//Keyboard
	auto keyboard = WindowResources::GetInput()->GetKeyboard();
	bool value = keyboard->ButtonPressed('S');
	if (value)
	{
		ToggleFullscreen();
	}
}

void WindowApp::Render(const std::shared_ptr<Engine::GraphicsDevice>& graphics)
{
	graphics->Draw(m);
	graphics->Draw(t);
	graphics->Draw(mouset);
}

void WindowApp::Resume()
{
	t = WindowResources::GetGraphics()->GetVideoCardInfo().at(0).name;
}

void WindowApp::Suspend()
{
}
