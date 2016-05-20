set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(oopengl_SRCS
    main.cpp
)

add_executable(OOpenGL ${oopengl_SRCS})

target_link_libraries(OOpenGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )