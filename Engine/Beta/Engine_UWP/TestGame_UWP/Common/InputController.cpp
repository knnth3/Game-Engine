#include "pch.h"
#include "InputController.h"

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Platform;
using namespace std;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::UI;
using namespace Windows::Foundation;
using namespace Windows::Devices::Input;
using namespace Windows::Gaming::Input;
using namespace Windows::System;

// Analog control deadzone definitions. Tune these values to adjust the size of the deadzone.
// Thumbstick range in each dimension is defined as [-1, 1].
#define THUMBSTICK_DEADZONE 0.25f

// Trigger range is defined as [0, 1].
#define TRIGGER_DEADZONE 0.1f

InputController::InputController(_In_ CoreWindow^ window) :
	m_bActive(true),
	m_activeGamepad(nullptr),
	m_gamepadStartButtonInUse(false),
	m_gamepadTriggerInUse(false),
	m_gamepadsChanged(true)
{
	InitWindow(window);
	m_inputManager = std::shared_ptr<InputManager>(new InputManager());
}

void InputController::AttatchCamera(std::shared_ptr<Graphics::Camera>& camera)
{
	m_inputManager->Initialize(camera);
}

std::shared_ptr<InputManager> InputController::GetManager()
{
	return m_inputManager;
}

void InputController::InitWindow(_In_ CoreWindow^ window)
{

	window->PointerPressed +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &InputController::OnPointerPressed);

	window->PointerMoved +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &InputController::OnPointerMoved);

	window->PointerReleased +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &InputController::OnPointerReleased);

	window->PointerExited +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &InputController::OnPointerExited);

	window->KeyDown +=
		ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &InputController::OnKeyDown);

	window->KeyUp +=
		ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &InputController::OnKeyUp);

	// Detect gamepad connection and disconnection events.
	Gamepad::GamepadAdded +=
		ref new EventHandler<Gamepad^>(this, &InputController::OnGamepadAdded);

	Gamepad::GamepadRemoved +=
		ref new EventHandler<Gamepad^>(this, &InputController::OnGamepadRemoved);
}

//----------------------------------------------------------------------

void InputController::OnPointerPressed(
	_In_ CoreWindow^ /* sender */,
	_In_ PointerEventArgs^ args
)
{
	PointerPoint^ point = args->CurrentPoint;
	uint32 pointerID = point->PointerId;
	Point pointerPosition = point->Position;
	PointerPointProperties^ pointProperties = point->Properties;
	auto pointerDevice = point->PointerDevice;
	auto pointerDeviceType = pointerDevice->PointerDeviceType;

	XMFLOAT2 position = XMFLOAT2(pointerPosition.X, pointerPosition.Y);
	if (m_bActive)
	{
		bool rightButton = pointProperties->IsRightButtonPressed;
		bool leftButton = pointProperties->IsLeftButtonPressed;
	}
}

//----------------------------------------------------------------------

void InputController::OnPointerMoved(
	_In_ CoreWindow^ /* sender */,
	_In_ PointerEventArgs^ args
)
{
	PointerPoint^ point = args->CurrentPoint;
	uint32 pointerID = point->PointerId;
	Point pointerPosition = point->Position;
	PointerPointProperties^ pointProperties = point->Properties;
	auto pointerDevice = point->PointerDevice;
	XMFLOAT2 position = XMFLOAT2(pointerPosition.X, pointerPosition.Y);     // convert to allow math

	if (m_bActive)
	{
		m_inputManager->SetMouseCoords(position.x, position.y);
	}
#ifdef MOVELOOKCONTROLLER_TRACE
	DebugTrace(L"%-7s (%d) at (%4.0f, %4.0f)", L"Moved", pointerID, position.x, position.y);
#endif

#ifdef MOVELOOKCONTROLLER_TRACE
	DebugTrace(L"\n");
#endif
}

//----------------------------------------------------------------------

void InputController::OnPointerReleased(
	_In_ CoreWindow^ /* sender */,
	_In_ PointerEventArgs^ args
)
{
	PointerPoint^ point = args->CurrentPoint;
	uint32 pointerID = point->PointerId;
	Point pointerPosition = point->Position;
	PointerPointProperties^ pointProperties = point->Properties;

	XMFLOAT2 position = XMFLOAT2(pointerPosition.X, pointerPosition.Y);

	if (m_bActive)
	{
		bool rightButton = pointProperties->IsRightButtonPressed;
		bool leftButton = pointProperties->IsLeftButtonPressed;
	}
}

//----------------------------------------------------------------------

void InputController::OnPointerExited(
	_In_ CoreWindow^ /* sender */,
	_In_ PointerEventArgs^ args
)
{
	PointerPoint^ point = args->CurrentPoint;
	uint32 pointerID = point->PointerId;
	Point pointerPosition = point->Position;
	PointerPointProperties^ pointProperties = point->Properties;

	XMFLOAT2 position = XMFLOAT2(pointerPosition.X, pointerPosition.Y);

	if (m_bActive)
	{
		m_inputManager->SetMouseCoords(position.x, position.y);
	}
}

//----------------------------------------------------------------------

void InputController::OnKeyDown(
	_In_ CoreWindow^ /* sender */,
	_In_ KeyEventArgs^ args
)
{
	Windows::System::VirtualKey Key;
	Key = args->VirtualKey;

	if (m_bActive)
		m_inputManager->SetKeyDown((int)Key);

}

//----------------------------------------------------------------------

void InputController::OnKeyUp(
	_In_ CoreWindow^ /* sender */,
	_In_ KeyEventArgs^ args
)
{
	Windows::System::VirtualKey Key;
	Key = args->VirtualKey;

	if (m_bActive)
		m_inputManager->SetKeyUp((int)Key);
}

//----------------------------------------------------------------------

void InputController::UpdatePollingDevices()
{
	if (m_gamepadsChanged)
	{
		m_gamepadsChanged = false;
		unsigned int index = 0;

		// Capture the list of gamepads so it won't change while we are studying it.
		auto gamepads = Gamepad::Gamepads;

		if (gamepads->Size == 0)
		{
			m_activeGamepad = nullptr;
		}
		// Check if the cached gamepad is still connected.
		else if (!gamepads->IndexOf(m_activeGamepad, &index))
		{
			// InputController is intended to handle input for a single player, so it
			// defaults to the first active gamepad.
			m_activeGamepad = gamepads->GetAt(0);
		}
	}

	if (m_activeGamepad == nullptr)
	{
		return;
	}

	GamepadReading reading = m_activeGamepad->GetCurrentReading();
}

//----------------------------------------------------------------------
// Turn on mouse cursor, which also disables relative mouse movement tracking.
void InputController::ShowCursor()
{
	auto window = CoreWindow::GetForCurrentThread();
	if (window)
	{
		// Protect case where there isn't a window associated with the current thread.
		// This happens on initialization or when being called from a background thread.
		window->PointerCursor = ref new CoreCursor(CoreCursorType::Arrow, 0);
	}
}

//----------------------------------------------------------------------

// Turn mouse cursor off (hidden), which also enables relative mouse movement tracking.
void InputController::HideCursor()
{
	auto window = CoreWindow::GetForCurrentThread();
	if (window)
	{
		// Protect case where there isn't a window associated with the current thread.
		// This happens on initialization or when being called from a background thread.
		window->PointerCursor = nullptr;
	}
}

void InputController::Active(_In_ bool active)
{
#ifdef MOVELOOKCONTROLLER_TRACE
	DebugTrace(L"Active = %s\n", active ? L"true" : L"false");
#endif
	m_bActive = active;
}

//----------------------------------------------------------------------

bool InputController::Active()
{
	return m_bActive;
}

void InputController::Update()
{
	UpdatePollingDevices();

}

//----------------------------------------------------------------------

void InputController::OnGamepadAdded(_In_ Object^ sender, _In_ Gamepad^ gamepad)
{
	// OnGamepadAdded and OnGamepadRemoved can be called from a worker thread. For simplicity,
	// defer updating the active gamepad until Update().
	m_gamepadsChanged = true;
}

//----------------------------------------------------------------------

void InputController::OnGamepadRemoved(_In_ Object^ sender, _In_ Gamepad^ gamepad)
{
	// OnGamepadAdded and OnGamepadRemoved can be called from a worker thread. For simplicity,
	// defer updating the active gamepad until Update().
	m_gamepadsChanged = true;
}

#ifdef MOVELOOKCONTROLLER_TRACE
void InputController::DebugTrace(const wchar_t *format, ...)
{
	// Generate the message string.
	va_list args;
	va_start(args, format);
	wchar_t message[1024];
	vswprintf_s(message, 1024, format, args);
	OutputDebugStringW(message);
}
#endif

//----------------------------------------------------------------------
