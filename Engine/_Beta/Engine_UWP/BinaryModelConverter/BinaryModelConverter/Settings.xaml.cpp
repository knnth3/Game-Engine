﻿//
// Settings.xaml.cpp
// Implementation of the Settings class
//

#include "pch.h"
#include "Settings.xaml.h"

using namespace BinaryModelConverter;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The User Control item template is documented at https://go.microsoft.com/fwlink/?LinkId=234236

Settings::Settings()
{
	InitializeComponent();
	rootPage = MainPage::Current;
	LoadDefaults();
}

void BinaryModelConverter::Settings::LoadDefaults()
{
	Overwrite->IsOn = rootPage->GetOverwriteProperty();
}

void BinaryModelConverter::Settings::Overwrite_Toggled(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ToggleSwitch^ toggleSwitch = static_cast<ToggleSwitch^>(sender);
	if (toggleSwitch != nullptr)
	{
		rootPage->SetOverwriteProperty(toggleSwitch->IsOn);
	}
}
