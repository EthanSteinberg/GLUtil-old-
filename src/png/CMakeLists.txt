set(HDRS 
      
   pngUtil.h
   pngList.h
   pngJson.h
   )
 
set(SRCS
   pngUtil.cpp
   pngList.cpp
   pngJson.cpp
)
 
add_library(pngUtil ${HDRS} ${SRCS})
target_link_libraries(pngUtil glUtil jsoncpp ${PNG_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARY})

install(TARGETS pngUtil ARCHIVE DESTINATION lib/GLUtil)
install(FILES ${HDRS} DESTINATION include/GLUtil)
