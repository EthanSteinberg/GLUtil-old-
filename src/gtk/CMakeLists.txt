set(HDRS 
   sfmlWidget.h
   )
 
set(SRCS
   sfmlWidget.cpp
   )
 
add_library(gtkUtil ${HDRS} ${SRCS})
target_link_libraries(gtkUtil ${SFML_LIBRARY} ${GTK3_LIBRARIES})

install(TARGETS gtkUtil ARCHIVE DESTINATION lib/GLUtil)
install(FILES ${HDRS} DESTINATION include/GLUtil)
