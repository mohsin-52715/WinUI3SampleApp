include(HybridCRT.cmake NO_POLICY_SCOPE)

project("com.fredemmott.CmakeCppWinRTWinUI3")
cmake_minimum_required(VERSION 3.23)
#Patch up the generated vcxproj
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/Directory.Build.props"
  "${CMAKE_CURRENT_BINARY_DIR}/Directory.Build.props"
  COPYONLY
)
 # configure_file(
 #   "${CMAKE_CURRENT_SOURCE_DIR}/Directory.Build.targets"
 #   "${CMAKE_CURRENT_BINARY_DIR}/Directory.Build.targets"
 #   COPYONLY
 # )

set (TWBuildConfig "\$<CONFIG>")

add_library(
  WinUI3Lib
  STATIC
  TwWinUI3Includes.hpp
  dummy.hpp
  TWWinUI3App.hpp
  TwWinUI3Includes.hpp
  TWWinUI3App.cpp
)

add_library(
  RegularLib
  STATIC
  TWWinUIApp.cpp
)

target_precompile_headers (WinUI3Lib PRIVATE "TWWinUI3Includes.hpp")
message(NOTICE "${CMAKE_CURRENT_BINARY_DIR} ")
target_include_directories(WinUI3Lib PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/Generated Files")
target_include_directories(WinUI3Lib PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/WinUI3Lib.dir/${TWBuildConfig}/Generated Files")

set_property(
  TARGET WinUI3Lib
  PROPERTY VS_PACKAGE_REFERENCES
  "Microsoft.Windows.CppWinRT_2.0.220608.4"
  "Microsoft.WindowsAppSDK_1.3.230331000"
  "Microsoft.Windows.SDK.BuildTools_10.0.22621.1"
  "Microsoft.Windows.ImplementationLibrary_1.0.220201.1"
)

set_target_properties(
  WinUI3Lib   
  PROPERTIES
   # specifies whether to build a C++/WinRT application with optimizations that are specific to C++/WinRT
  VS_GLOBAL_CppWinRTOptimized true
  # specifies whether to build a C++/WinRT application using the WinUI 3 framework
  VS_GLOBAL_UseWinUI true
  VS_GLOBAL_AppxPackage false

  VS_GLOBAL_CppWinRTOptimized true
  VS_GLOBAL_CppWinRTRootNamespaceAutoMerge true
  VS_GLOBAL_MinimalCoreWin true
  VS_GLOBAL_TargetName WinUI3Lib
  VS_GLOBAL_AppContainerApplication false
  VS_GLOBAL_AppxPackage false
  VS_GLOBAL_WindowsPackageType None
  VS_GLOBAL_ApplicationType "Windows Store"
  VS_GLOBAL_WindowsTargetPlatformMinVersion 10.0.17763.0

)

add_executable(
  WinUI3LibTarget
  WIN32 
  main.cpp
 )


target_link_directories(WinUI3LibTarget PRIVATE "C:/Users/$ENV{USERNAME}/.nuget/packages/microsoft.windowsappsdk/1.3.230331000/lib/win10-x64")
target_include_directories(WinUI3LibTarget PRIVATE "C:/Users/$ENV{USERNAME}/.nuget/packages/microsoft.windowsappsdk/1.3.230331000/include")



target_link_libraries(WinUI3LibTarget PRIVATE WinUI3Lib)
target_link_libraries(WinUI3LibTarget PRIVATE Microsoft.WindowsAppRuntime.Bootstrap.dll)
