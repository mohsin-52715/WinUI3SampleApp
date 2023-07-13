# Sri Ganeshji : Sri Balaji : Sri Pitreshwarji : Sri Durgaji : Sri Venkateshwara

set (tw_target_starts OFF)
set (tw_has_targets OFF)

math (EXPR argc_count "${CMAKE_ARGC}-1")

foreach (arg RANGE ${argc_count})
    if (NOT tw_target_starts AND ${CMAKE_ARGV${arg}} STREQUAL "--")
        set (tw_target_starts ON)
        continue()
    endif ()
    if (tw_target_starts)
        list (APPEND TW_BUILD_TARGETS  ${CMAKE_ARGV${arg}})
        set (tw_has_targets ON)
    endif ()
endforeach ()


if (tw_has_targets OR (DEFINED TW_BUILD_TARGETS AND NOT TW_BUILD_TARGETS STREQUAL ""))
    set (TW_TARGET_OPTION --target ${TW_BUILD_TARGETS})
endif ()

#Bulding targets
if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin" )
    execute_process (COMMAND ${CMAKE_COMMAND} --build --preset ${TW_BUILD_PRESET}  ${TW_TARGET_OPTION} -- -allowProvisioningUpdates
        RESULT_VARIABLE  retCode )
elseif (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows" AND ${TW_BUILD_PRESET} MATCHES "Windows")
      
    include(ProcessorCount)
    ProcessorCount(logicalCores)
    set(tw_cl_logical_cores "/p:CL_MPcount=${logicalCores}")
    math(EXPR tw_msbuild_instances_to_launch "${logicalCores} -3" ) 
   
    list(LENGTH TW_BUILD_TARGETS len)
message(NOTICE "TW_BUILD_TARGETS ${TW_BUILD_TARGETS}")
    #Doing special handling for multiple selected projects to build them in parallel using Msbuild.
    if(BUILD_PARALLEL AND len STRGREATER "1")
        set(winuiprojects)
        # Creating vcxproj list from target name as this is what MSBuild task understand.
        foreach (tgt ${TW_BUILD_TARGETS})
            list(APPEND projects ${tgt}.vcxproj)
        endforeach ()
        list(REVERSE projects)    
message(NOTICE "projects ${projects}")		
        #Splitting preset name to get os,arch and config
        string(REPLACE "-" ";" preset_tokens ${TW_BUILD_PRESET})
        list(GET preset_tokens 0 os_val)
        list(GET preset_tokens 1 arch_val)
        list(GET preset_tokens 2 config_val)

        #Constructing msbuild path by using cmake path.
        #TODO: Need to check if there is better way
        cmake_path(GET CMAKE_COMMAND PARENT_PATH  cmakepath)
        set(msbuildexepath ${cmakepath}/../../../../../../../MSBuild/Current/Bin/amd64/MSBuild.exe)

        #Setting up a target which in terns builds multiple msbuild target as MSBuild task.
        # https://learn.microsoft.com/en-us/visualstudio/msbuild/msbuild-task?view=vs-2022

        configure_file(targets.vcxproj.in $ENV{TWHome}/Builds/TWInt/${os_val}-${arch_val}/targets.vcxproj)
        
        #Running Msbuild directly to build targets
        separate_arguments(commandToBeExecuted NATIVE_COMMAND "${msbuildexepath} /m:${tw_msbuild_instances_to_launch} /p:Configuration=${config_val} ${tw_cl_logical_cores} /v:m /nologo targets.vcxproj")
        execute_process (COMMAND ${commandToBeExecuted}
            RESULT_VARIABLE  retCode WORKING_DIRECTORY $ENV{TWHome}/Builds/TWInt/${os_val}-${arch_val} COMMAND_ECHO STDOUT)

        foreach(tgt  ${winuitargets})
            execute_process (COMMAND ${CMAKE_COMMAND} --build --preset ${TW_BUILD_PRESET}  --target ${tgt}  -- /m:${tw_msbuild_instances_to_launch} ${tw_cl_logical_cores} /v:m /nologo
                RESULT_VARIABLE  retCode )
        endforeach()

   else()
        execute_process (COMMAND ${CMAKE_COMMAND} --build --preset ${TW_BUILD_PRESET}  ${TW_TARGET_OPTION} -- /m:${tw_msbuild_instances_to_launch} ${tw_cl_logical_cores} /v:m /nologo
            RESULT_VARIABLE  retCode COMMAND_ECHO STDOUT)
   endif()

else() 
    execute_process (COMMAND ${CMAKE_COMMAND} --build --preset ${TW_BUILD_PRESET}  --parallel  ${TW_TARGET_OPTION} 
        RESULT_VARIABLE  retCode )
endif ()


if (retCode STREQUAL "0")
    message (NOTICE "========= ${TW_BUILD_TYPE} Successful =========") 
else ()
    message (FATAL_ERROR "========= ${TW_BUILD_TYPE} Failed =========")
endif ()
