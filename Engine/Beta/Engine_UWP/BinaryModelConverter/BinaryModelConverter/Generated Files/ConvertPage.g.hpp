﻿//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"

#pragma warning(push)
#pragma warning(disable: 4100) // unreferenced formal parameter

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BINDING_DEBUG_OUTPUT
extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent();
#endif

#include "ConvertPage.xaml.h"

void ::BinaryModelConverter::ConvertPage::InitializeComponent()
{
    if (_contentLoaded)
    {
        return;
    }
    _contentLoaded = true;
    ::Windows::Foundation::Uri^ resourceLocator = ref new ::Windows::Foundation::Uri(L"ms-appx:///ConvertPage.xaml");
    ::Windows::UI::Xaml::Application::LoadComponent(this, resourceLocator, ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);
}

void ::BinaryModelConverter::ConvertPage::Connect(int __connectionId, ::Platform::Object^ __target)
{
    switch (__connectionId)
    {
    case 1:
        {
            this->LayoutRoot = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(__target);
        }
        break;
    case 2:
        {
            this->SelectedFileInfo = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(__target);
        }
        break;
    case 3:
        {
            this->SelectedFolderInfo = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(__target);
        }
        break;
    case 4:
        {
            this->OutputLog = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(__target);
        }
        break;
    case 5:
        {
            this->OutputTextBlock = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
        }
        break;
    case 6:
        {
            this->PickAFolderButtonResult = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
        }
        break;
    case 7:
        {
            this->PickAFileButtonResult = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
        }
        break;
    case 8:
        {
            this->Input = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(__target);
        }
        break;
    case 9:
        {
            this->Output = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(__target);
        }
        break;
    case 10:
        {
            this->Convert = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(__target);
        }
        break;
    case 11:
        {
            this->RunConversionButton = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
        }
        break;
    case 12:
        {
            this->PickAFolderButton = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
        }
        break;
    case 13:
        {
            this->PickAFileButton = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
        }
        break;
    }
    _contentLoaded = true;
}

::Windows::UI::Xaml::Markup::IComponentConnector^ ::BinaryModelConverter::ConvertPage::GetBindingConnector(int __connectionId, ::Platform::Object^ __target)
{
    __connectionId;         // unreferenced
    __target;               // unreferenced
    return nullptr;
}

#pragma warning(pop)

