cmake_minimum_required (VERSION 2.6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -pedantic)

file(GLOB SRC_FILES
    "*.h"
    "*.cpp"
    "operations/*.h"
    "operations/*.cpp"
)

find_package(SDL2)
if(SDL2_FOUND)
	#find_package(SDL2_image)
	#find_package(SDL2IMAGE)
	#if (SDL2_IMAGE_FOUND)
		set(SDL2_SRC_FILES graphics/SdlGraphics.cpp snake-sdl.cpp)
		include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
		#add_executable(snake-sdl $<TARGET_OBJECTS:shareobjects> ${SDL2_SRC_FILES} )
		#add_executable(bk0010  $<TARGET_OBJECTS:SRC_FILES> ${SDL2_SRC_FILES} )
		add_executable(bk0010 ${SRC_FILES} )
		#target_link_libraries(snake-sdl ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
		#target_link_libraries(snake-sdl ${SDL2_LIBRARIES} -lSDL2_image)
		target_link_libraries(bk0010 ${SDL2_LIBRARIES}) # -lSDL2_image)
	#else()
	#	message(WARNING "SDL2_image is not found.")
	#endif()
else()
    message(WARNING "SDL2 is not found.")
endif()

