#include <pebble.h>

static Window *window;
static TextLayer *textLayer;

static Layer *renderLayer;

static void window_load(Window *window) {
    Layer *windowLayer = window_get_root_layer(window);
    GRect windowBounds = layer_get_bounds(windowLayer);

    renderLayer = layer_create(windowBounds);

    layer_add_child(windowLayer, renderLayer);

    GRect textBounds =
	{
	    .origin = { 0, 72 },
	    .size = { windowBounds.size.w, 20 }
	};
    textLayer = text_layer_create(textBounds);

    text_layer_set_text(textLayer, "chomp!");
    text_layer_set_text_alignment(textLayer, GTextAlignmentCenter);

    layer_add_child(windowLayer, text_layer_get_layer(textLayer));
}

static void window_unload(Window *window) {
    layer_destroy(renderLayer);
    text_layer_destroy(textLayer);
}

static void init() {
    window = window_create();
    WindowHandlers windowHandlers =
	{
	    .load = window_load,
	    .unload = window_unload
	};
    window_set_window_handlers(window, windowHandlers);
    window_stack_push(window, true);
}

static void deinit() {
    window_destroy(window);
}

int main() {
    init();

    app_event_loop();

    deinit();
}
