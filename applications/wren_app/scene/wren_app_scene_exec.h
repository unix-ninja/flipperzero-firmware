#pragma once
#include "../wren_app.h"

//#ifndef _LUA
//#define _LUA 1
//extern "C" {
//#include "../wren/lua.h"
//#include "../wren/lualib.h"
//#include "../wren/lauxlib.h"
//}
//#endif

class WrenAppSceneExec : public GenericScene<WrenApp> {
public:
    void on_enter(WrenApp* app, bool need_restore) final;
    bool on_event(WrenApp* app, WrenApp::Event* event) final;
    void on_exit(WrenApp* app) final;

private:
    void result_callback(void* context);

    uint8_t data[4] = {
        0x01,
        0xA2,
        0xF4,
        0xD3,
    };
};
