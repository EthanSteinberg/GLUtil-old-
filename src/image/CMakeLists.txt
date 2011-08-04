set(HDRS 
      
   imageUtil.h
   jsonList.h
   imageList.h
   imageJson.h
   )
 
set(SRCS
   imageUtil.cpp
   jsonList.cpp
   imageList.cpp
   imageJson.cpp
)
 
add_library(imageUtil ${HDRS} ${SRCS})
target_link_libraries(imageUtil glUtil jsoncpp ${PNG_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARY})

install(TARGETS imageUtil ARCHIVE DESTINATION lib/GLUtil)
install(FILES ${HDRS} DESTINATION include/GLUtil)
