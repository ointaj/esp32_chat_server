set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Get a list of all .cpp files from helpers
file(GLOB_RECURSE EXTRA_SOURCES1 "helpers/*.cpp")

# Get a list of all .cpp files from storage
file(GLOB_RECURSE EXTRA_SOURCES2 "storage/*.cpp")

# Get a list of all .cpp files from wifi
file(GLOB_RECURSE EXTRA_SOURCES3 "wifi/*.cpp")

idf_component_register(
    SRCS 
                "system_run.cpp"
                "main.cpp"
                ${EXTRA_SOURCES1}
                ${EXTRA_SOURCES2}
                ${EXTRA_SOURCES3}
    INCLUDE_DIRS "."
                 "conf"
                 "helpers"
                 "storage"
                 "storage/data_defintion"
                 "wifi"
                 "threading"
                 "threading/locking"
)