
#include "TWWinUI3App.hpp"

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace winrt::Microsoft::UI::Xaml::XamlTypeInfo;
using namespace winrt::Microsoft::UI::Xaml::Markup;
using namespace winrt::Windows::UI::Xaml::Interop;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Management::Deployment;

UINT32 majorMinorVersion{ 0x00010003 };
PCWSTR versionTag{ L"" };

// #include "App.xaml."
//#include "mddbootstrap.h"
#include <MddBootstrap.h>
#include <WindowsAppSDK-VersionInfo.h>
PACKAGE_VERSION    minVersion{};


void  startapp() {

    // auto a = WINDOWSAPPSDK_RELEASE_MAJORMINOR;
    // auto b = WINDOWSAPPSDK_RELEASE_VERSION_TAG_W;
    // auto c = WINDOWSAPPSDK_RUNTIME_VERSION_UINT64;
    // 
    // PackageManager packageManager;
    // auto packageUserInformation = packageManager.FindPackagesForUser(L"");
    // 
    // for (const auto& package : packageUserInformation)
    // {
    //     // Access package information
    //     hstring packageName = package.Id().FullName();
    //     hstring packageFamilyName = package.Id().FamilyName();
    //     winrt::Windows::ApplicationModel::PackageVersion packageVersion = package.Id().Version();
    // 
    // 
    //     std::string PackName = to_string(packageName);
    //     if (PackName.find("Microsoft.WindowsAppRuntime.1.3") != std::string::npos) {
    //         majorMinorVersion = 0x00010003;
    //     }
    //     else if (PackName.find("Microsoft.WindowsAppRuntime.1.2") != std::string::npos) {
    //         majorMinorVersion = 0x00010002;
    //     }
    // }
    // 
    MddBootstrapInitialize2(majorMinorVersion, WINDOWSAPPSDK_RELEASE_VERSION_TAG_W, minVersion, MddBootstrapInitializeOptions::MddBootstrapInitializeOptions_OnNoMatch_ShowUI);

    winrt::init_apartment(winrt::apartment_type::single_threaded);

    Application::Start([](auto&&) {
        // Create a new instance of the App class

        make<TWWinUI3App>();  // TWWinUI3App is defined and the execution did not reach TWWinUI3App constructor or Onlaunched 
        });
}