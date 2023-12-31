set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Get a list of all .cpp files from helpers
file(GLOB_RECURSE EXTRA_SOURCES1 "helpers/*.cpp")

# Get a list of all .cpp files from storage
file(GLOB_RECURSE EXTRA_SOURCES2 "storage/*.cpp")

# Get a list of all .cpp files from wifi
file(GLOB_RECURSE EXTRA_SOURCES3 "wifi/*.cpp")

# Get a list of all .cpp files from thread
file(GLOB_RECURSE EXTRA_SOURCES4 "threading/*.cpp")

# Get a list of all .cpp files from communication
file(GLOB_RECURSE EXTRA_SOURCES5 "comm/*.cpp")

# Get a list of all .cpp files from commands
file(GLOB_RECURSE EXTRA_SOURCES6 "cmd/*.cpp")

# Get a list of all .cpp files from commands
file(GLOB_RECURSE EXTRA_SOURCES7 "events/*.cpp")

idf_component_register(
    SRCS 
                "system_run.cpp"
                "main.cpp"
                ${EXTRA_SOURCES1}
                ${EXTRA_SOURCES2}
                ${EXTRA_SOURCES3}
                ${EXTRA_SOURCES4}
                ${EXTRA_SOURCES5}
                ${EXTRA_SOURCES6}
                ${EXTRA_SOURCES7}
    INCLUDE_DIRS "."
                 "conf"
                 "helpers"
                 "storage"
                 "storage/data_definition"
                 "wifi"
                 "wifi/data_definition"
                 "threading"
                 "threading/data_definition"
                 "threading/locking"
                 "comm"
                 "cmd"
                 "peripherals"
                 "peripherals/uart"
                 "peripherals/uart/data_definition"
                 "events"
                 "events/data_definition"
)