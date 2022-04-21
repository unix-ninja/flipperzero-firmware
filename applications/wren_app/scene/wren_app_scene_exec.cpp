#include "wren_app_scene_exec.h"
#include <storage/storage.h>
#include "fatfs.h"

#include "../wren/wren.h"

ViewPort* view_port = (ViewPort*) view_port_alloc();
Gui* gui = (Gui*) malloc(sizeof(Gui*));

void WrenAppSceneExec::on_enter(WrenApp* app, bool need_restore) {
    // set the script to be executed
    char* filename = app->file_name;
    char path[MAX_PATH_LENGTH] = "/ext/scripts/";
    strncat(path, filename, (MAX_PATH_LENGTH-strlen(path)-1));
    printf("Script: %s\r\n", path);

    // initialize wren vm
    wren_initialize();

    // Open GUI and register view_port
    //gui = (Gui*) furi_record_open("gui");
    //gui_add_view_port(gui, view_port, GuiLayerFullscreen);
    //canvas_draw_frame((Canvas*) view_port, 0, 0, 128, 64);

    // Let's load our script!
    Storage* storage = (Storage*) furi_record_open("storage");
    File* file = storage_file_alloc(storage);
    if(storage_file_open(file, path, FSAM_READ, FSOM_OPEN_EXISTING))
    {
      printf("Size: %lu\r\n", (uint32_t)storage_file_size(file));

      wren_load_file(file);
      storage_file_close(file);
    }
    else
    {
      printf("Error! Unable to open script.\r\n");
    }

    debug("cleaning...");
    // cleanup
    storage_file_free(file);
    debug("store free");
    furi_record_close("storage");
    debug("record free");
}

bool WrenAppSceneExec::on_event(WrenApp* app, WrenApp::Event* event) {
    bool consumed = false;

    //printf("Event %d\r\n", (int) event->type);
    if(event->type == WrenApp::EventType::ByteEditResult) {
        debug("switing to previous...");
        app->scene_controller.switch_to_previous_scene();
        consumed = true;
    }

    return consumed;
}

void WrenAppSceneExec::on_exit(WrenApp* app) {
    //gui_remove_view_port(gui, view_port);
    //furi_record_close("gui");
    //view_port_free(view_port);

    app->view_controller.get<ByteInputVM>()->clean();
}

void WrenAppSceneExec::result_callback(void* context) {
    WrenApp* app = static_cast<WrenApp*>(context);
    WrenApp::Event event;

    event.type = WrenApp::EventType::ByteEditResult;

    app->view_controller.send_event(&event);
}
