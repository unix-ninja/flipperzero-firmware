#pragma once
#include <furi.h>
#include <furi_hal.h>

#include <generic_scene.hpp>
#include <scene_controller.hpp>
#include <view_controller.hpp>
#include <record_controller.hpp>
#include <text_store.h>

#include <view_modules/submenu_vm.h>
#include <view_modules/byte_input_vm.h>

#include <notification/notification_messages.h>

#ifndef LUA_32BITS
#define LUA_32BITS
#endif

#ifndef MAX_NAME_LENGTH
#define MAX_NAME_LENGTH 17
#endif

#ifndef MAX_PATH_LENGTH
#define MAX_PATH_LENGTH 255
#endif

class WrenApp {
public:
    enum class EventType : uint8_t {
        GENERIC_EVENT_ENUM_VALUES,
        MenuSelected,
        ByteEditResult,
    };

    enum class SceneType : uint8_t {
        GENERIC_SCENE_ENUM_VALUES,
        ExecScene,
    };

    char file_name[MAX_NAME_LENGTH];

    class Event {
    public:
        union {
            int32_t menu_index;
        } payload;

        EventType type;
    };

    SceneController<GenericScene<WrenApp>, WrenApp> scene_controller;
    TextStore text_store;
    ViewController<WrenApp, SubmenuVM, ByteInputVM> view_controller;
    RecordController<NotificationApp> notification;

    ~WrenApp();
    WrenApp();

    void run();
    void render(Canvas* canvas);
};
