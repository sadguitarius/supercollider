add_executable(sc_lexer_standalone main.cpp)
target_link_libraries(sc_lexer_standalone PRIVATE sc_lexer)

set_property(TARGET sc_lexer_standalone PROPERTY FOLDER Util)
