#include "wren_app.h"

// app enter function
extern "C" int32_t wren_app(void* p) {
    WrenApp* app = new WrenApp();
    app->run();
    delete app;

    return 0;
}
