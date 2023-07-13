#include "App.xaml.h"

#include "MainWindow.xaml.h"

namespace winrt::DemoApp::implementation {

    App::App() {
        InitializeComponent();
#ifdef DEBUG
        UnhandledException(
            [this](IInspectable const&, UnhandledExceptionEventArgs const& e) {
                if (IsDebuggerPresent()) {
                    auto errorMessage = e.Message();
                    __debugbreak();
                }
        throw;
            });
#endif
    }

    void App::OnLaunched(
        Microsoft::UI::Xaml::LaunchActivatedEventArgs const&
    ) noexcept {
        window = make<MainWindow>();
        window.Activate();
    }

}
int CALLBACK
WinMain([[maybe_unused]] HINSTANCE pInstance, [[maybe_unused]] HINSTANCE pPrevInstance, [[maybe_unused]] LPSTR pCmdLine, [[maybe_unused]] int pShowCmd) {
    return 0;
}
//int CALLBACK
//WinMain([[maybe_unused]] HINSTANCE pInstance, [[maybe_unused]] HINSTANCE pPrevInstance, [[maybe_unused]] LPSTR pCmdLine, [[maybe_unused]] int pShowCmd) {
//
//    winrt::init_apartment(winrt::apartment_type::single_threaded);
//
//    Application::Start([](auto&&) {
//        make<App>();
//        }
//    );
//
//}
