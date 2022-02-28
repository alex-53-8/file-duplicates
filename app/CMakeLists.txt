project(app)

add_compile_definitions("CLI_COMMAND_NAME=\"${CLI_COMMAND_NAME}\"")
add_compile_definitions("CLI_VERSION=\"${CLI_VERSION}\"")
add_compile_definitions("CLI_DATE=\"${CLI_DATE}\"")
add_compile_definitions("CLI_AUTHOR=\"${CLI_AUTHOR}\"")

add_executable(${PROJECT_NAME}
	main.cpp
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		libs::libfiles libs::libcli
)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${CLI_COMMAND_NAME})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
