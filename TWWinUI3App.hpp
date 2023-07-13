
#include "TWWinUI3Includes.hpp"
using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::XamlTypeInfo;
using namespace Microsoft::UI::Xaml::Markup;
using namespace Microsoft::UI::Dispatching;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::Foundation::Collections;
// Custom WinUI3 application class which in derived from WinUI3 applcation template
// The App parameter is a class that provides the basic functionality for a WinUI 3 application
// The IXamlMetadataProvider parameter is an interface that provides metadata for the XAML UI framework.
class TWWinUI3App : public ApplicationT<TWWinUI3App, IXamlMetadataProvider>
{

public:

    // Initializes invisible window

                                       TWWinUI3App();

    // This function is called when the application is launched. It takes in a
    // LaunchActivatedEventArgs object that contains information about the launch,
    // such as whether the app was activated by the user or by a notification.
    // The function does not return anything, but is responsible for setting up
    // the application's initial state.

    void                                OnLaunched(LaunchActivatedEventArgs const&);

    // This function takes a TypeName/hstring object as input and returns an IXamlType
    // object that represents the type in XAML. This is useful when you need to
    // work with XAML types in code, such as when you need to create an instance
    // of a XAML type or retrieve its properties.
    // We have to implement it as we are using IXamlMetadataProvider

    IXamlType                           GetXamlType(TypeName const& type);
    IXamlType                           GetXamlType(hstring const& fullname);

    // This function returns an array of XmlnsDefinition objects, which represent
    // XML namespace definitions that are used in XAML. This can be useful when
    // you need to work with multiple XML namespaces in XAML. This is not used but we
    // have to implement it as we are using IXamlMetadataProvider

    com_array<XmlnsDefinition> GetXmlnsDefinitions();

    // To post to the main thread we need dispatcher Queue, which we can get from WinUI3 Window
    // This funtion returns dispatcher queue from invisible windowtea

    DispatcherQueue                     GetDispatcherQueue();

    // The WinUI3 event loop stops when all the windows in the Application class are closed
    // This function will close the invisible window which kept event loop running

    void                                CloseInvisibleWindow();

private:

    // To post to the main thread we need dispatcher Queue, which we can get from WinUI3 Window
    // And The WinUI3 event loop stops when all the windows in the Application class are closed
    // This invisible window gives the dispatcher queue and keeps the event loop alive when
    // all visible Windows are closed

    Window                              vInvisibleWindow{ nullptr };

    // Gives XAML metadata for WinUI3 XAML controls

    XamlControlsXamlMetaDataProvider    vXamlMetaDataProvider;
};

 