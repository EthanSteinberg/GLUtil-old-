set(HDRS 
   algoMaxRects.h
algoMaxRects.h
myBox.h
myVector2.h
pixelAlgo.h
text.h
textList.h

distanceMap.h
      
   )
 
set(SRCS
   text.cpp
   textList.cpp
   algoMaxRects.cpp
   myBox.cpp
   myVector2.cpp

   distanceMap.cpp

)
 
add_library(textUtil ${HDRS} ${SRCS})
target_link_libraries(textUtil glUtil ${GLEW_LIBRARY} ${FREETYPE_LIBRARIES} ${OPENGL_LIBRARY})

install(TARGETS textUtil ARCHIVE DESTINATION lib/GLUtil)
install(FILES ${HDRS} DESTINATION include/GLUtil)
