project(libfiles_tests)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE PRIVATE libs::libfiles)