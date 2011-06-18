set(HDRS 
      
   text.h
   )
 
set(SRCS
   text.cpp
   algoMaxRects.cpp
   myBox.cpp
   myVector2.cpp
)
 
add_library(text ${HDRS} ${SRCS})
target_link_libraries(text glUtil ${GLEW_LIBRARY} ${FREETYPE_LIBRARIES} ${OPENGL_LIBRARY})

