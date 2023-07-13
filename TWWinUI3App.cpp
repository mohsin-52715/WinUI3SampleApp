
#if         (TW_KERNEL_WINDOWS)

#include "TWWinUI3App.hpp"

TWWinUI3App::TWWinUI3App()
{
    vInvisibleWindow = Window();
    vInvisibleWindow.Activate();
}

void
TWWinUI3App::OnLaunched(LaunchActivatedEventArgs const&)
{

    // Get the application's resources and append a dictionary of XAML control resources.
    // The XAML control resources contain styles and templates that define the appearance
    // and behavior of common UI controls, such as buttons and text boxes. By adding
    // these resources to the merged dictionaries collection, the application can use these
    // styles and templates throughout its UI.

    // Resources().MergedDictionaries().Append(XamlControlsResources());
}

IXamlType
TWWinUI3App::GetXamlType(TypeName const& type)
{
    return vXamlMetaDataProvider.GetXamlType(type);
}

IXamlType
TWWinUI3App::GetXamlType(hstring const& fullname)
{
    return vXamlMetaDataProvider.GetXamlType(fullname);
}

com_array<XmlnsDefinition>
TWWinUI3App::GetXmlnsDefinitions()
{
    return vXamlMetaDataProvider.GetXmlnsDefinitions();
}

DispatcherQueue
TWWinUI3App::GetDispatcherQueue()
{
    return vInvisibleWindow.DispatcherQueue();
}

void
TWWinUI3App::CloseInvisibleWindow()
{
    return vInvisibleWindow.Close();
}

#endif // TW_KERNEL_WINDOWS
