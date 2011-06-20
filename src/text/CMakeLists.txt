set(HDRS 
   algoMaxRects.h
algoMaxRects.h
myBox.h
myVector2.h
pixelAlgo.h
text.h
      
   )
 
set(SRCS
   text.cpp
   algoMaxRects.cpp
   myBox.cpp
   myVector2.cpp
)
 
add_library(textUtil ${HDRS} ${SRCS})
target_link_libraries(textUtil glUtil ${GLEW_LIBRARY} ${FREETYPE_LIBRARIES} ${OPENGL_LIBRARY})

install(TARGETS textUtil ARCHIVE DESTINATION lib/GLUtil)
install(FILES ${HDRS} DESTINATION include/GLUtil)
