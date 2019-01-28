# Check OpenCV
if(NOT USE_OPENCV OR NOT OpenCV_FOUND OR OpenCV_VERSION_MAJOR LESS 3)
    message(WARNING "\
OpenCV version >= 3 should be enabled and found to build image classification example, skipping...")
    return()
endif()

if(NOT MSVC)
    set(ELIXIR_MXNET_STATIC_LINK ON CACHE BOOL "\
Link mxnet library statically in the c++ image classification example")
else()
    # disable static linking on Windows
    set(ELIXIR_MXNET_STATIC_LINK OFF)
endif()

add_custom_target(ElixirMXNet
        COMMAND mix compile.elixir_make
        COMMENT "Building For Elixir"
        )

include_directories(/usr/local/Cellar/erlang/21.0.9/lib/erlang/erts-10.0.8/)
set(elixirSource ${CMAKE_CURRENT_SOURCE_DIR}/*)

file(GLOB elixirFiles ${elixirSource})
foreach(elixirFile ${elixirFiles})
    file(COPY ${elixirFile} DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
endforeach(elixirFile)

include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS})

if(ELIXIR_MXNET_STATIC_LINK)
    add_dependencies(ElixirMXNet mxnet_static)
else()
    add_dependencies(elixirMXNet mxnet)
endif()


