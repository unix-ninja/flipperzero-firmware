#include "wren_app_scene_start.h"
#include <stdio.h>
#include <storage/storage.h>
#include <storage/storage_sd_api.h>
#include <string>

char submenu_name[255][MAX_NAME_LENGTH];

typedef enum {
    ExecScript,
} SubmenuIndex;

void WrenAppSceneStart::on_enter(WrenApp* app, bool need_restore) {
    auto submenu = app->view_controller.get<SubmenuVM>();
    auto callback = cbc::obtain_connector(this, &WrenAppSceneStart::submenu_callback);

    // open our file handles for accessing scripts
    Storage* api = (Storage*)furi_record_open("storage");
    File* file = storage_file_alloc(api);

    // Let's populate the submenu with file names
    if(storage_dir_open(file, "/ext/scripts")) {
        FileInfo fileinfo;
        char name[MAX_NAME_LENGTH];
        //bool readed = false;

        int i = 0;
        while(storage_dir_read(file, &fileinfo, name, MAX_NAME_LENGTH)) {
            //readed = true;
            if(fileinfo.flags & FSF_DIRECTORY) {
                // skip directories for now
            } else {
                // copy our strings into persistent memory.
                // there's probably a better way to do this.
                strcpy(submenu_name[i], name);
                // make our submenu item
                submenu->add_item(submenu_name[i], i, callback, app);
                i++;
            }
        }
    } else {
      // TODO: warn no files
    }

    storage_dir_close(file);
    storage_file_free(file);
    furi_record_close("storage");

    if(need_restore) {
        submenu->set_selected_item(submenu_item_selected);
    }
    app->view_controller.switch_to<SubmenuVM>();
}

bool WrenAppSceneStart::on_event(WrenApp* app, WrenApp::Event* event) {
    bool consumed = false;

    if(event->type == WrenApp::EventType::MenuSelected) {
        submenu_item_selected = event->payload.menu_index;
        strcpy(app->file_name, submenu_name[submenu_item_selected]);
        app->scene_controller.switch_to_next_scene(WrenApp::SceneType::ExecScene);
        /*
        switch(event->payload.menu_index) {
        case ExecScript:
            app->scene_controller.switch_to_next_scene(WrenApp::SceneType::ByteInputScene);
            break;
        }
        */
        consumed = true;
    }

    return consumed;
}

void WrenAppSceneStart::on_exit(WrenApp* app) {
    app->view_controller.get<SubmenuVM>()->clean();
}

void WrenAppSceneStart::submenu_callback(void* context, uint32_t index) {
    WrenApp* app = static_cast<WrenApp*>(context);
    WrenApp::Event event;

    event.type = WrenApp::EventType::MenuSelected;
    event.payload.menu_index = index;

    app->view_controller.send_event(&event);
}
