#pragma once

#include <ctype.h>
#include <map>
#include <set>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <thread>

#include "cmd_def.h"


enum class DeviceState : int
{
    NONE = 0,
    INIT_CALLED = 1,
    INITIAL_CONNECTION = 2,
    OPEN_CALLED = 3,
    CONFIG_CALLED = 4,
    CLOSE_CALLED = 5,
    GET_DATA_CALLED = 6,
    WRITE_TO_CLIENT_CHAR = 7
};

class MuseBGLibHelper
{

private:
    static MuseBGLibHelper *instance;
    MuseBGLibHelper ()
    {
    }
    MuseBGLibHelper (const MuseBGLibHelper &other) = delete;
    MuseBGLibHelper &operator= (const MuseBGLibHelper &other) = delete;

    volatile bool should_stop_stream;
    std::thread read_characteristic_thread;

    void thread_worker ();


public:
    static MuseBGLibHelper *get_instance ();
    void reset ();
    int read_message (int timeout);
    int open_ble_dev ();
    int wait_for_callback ();
    int reset_ble_dev ();

    ~MuseBGLibHelper ()
    {
    }

    volatile int exit_code;
    char uart_port[1024];
    volatile int timeout;
    volatile bd_addr connect_addr;
    volatile uint8 connection;
    volatile uint16 muse_handle_start;
    volatile uint16 muse_handle_end;
    volatile int state;
    volatile bool initialized;
    std::set<uint16> ccids;
    std::map<std::string, uint16> characteristics;

    void start_stream ();
    void stop_stream ();
};
