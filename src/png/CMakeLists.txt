set(HDRS 
      
   pngUtil.h
   pngList.h
   )
 
set(SRCS
   pngUtil.cpp
   pngList.cpp
)
 
add_library(pngUtil ${HDRS} ${SRCS})
target_link_libraries(pngUtil glUtil jsoncpp ${PNG_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARY})

