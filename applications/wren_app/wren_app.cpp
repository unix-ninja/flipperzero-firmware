#include "wren_app.h"
#include "scene/wren_app_scene_start.h"
#include "scene/wren_app_scene_exec.h"

WrenApp::WrenApp()
    : scene_controller{this}
    , text_store{128}
    , notification{"notification"} {
}

WrenApp::~WrenApp() {
}

void WrenApp::run() {
    scene_controller.add_scene(SceneType::Start, new WrenAppSceneStart());
    scene_controller.add_scene(SceneType::ExecScene, new WrenAppSceneExec());

    notification_message(notification, &sequence_blink_green_10);
    scene_controller.process(100);
}

void WrenApp::render(Canvas* canvas) {
    // here you dont need to call acquire_state or release_state
    // to read or write app state, that already handled by caller
    canvas_set_color(canvas, ColorBlack);
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str(canvas, 2, 12, "Example app");
}
