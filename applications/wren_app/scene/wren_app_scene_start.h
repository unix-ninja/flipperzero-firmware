#pragma once
#include "../wren_app.h"

class WrenAppSceneStart : public GenericScene<WrenApp> {
public:
    void on_enter(WrenApp* app, bool need_restore) final;
    bool on_event(WrenApp* app, WrenApp::Event* event) final;
    void on_exit(WrenApp* app) final;

private:
    void submenu_callback(void* context, uint32_t index);
    uint32_t submenu_item_selected = 0;
};
