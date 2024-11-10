//
// Created by Patryk Szczypień on 07/11/2024.
//

#include <clicker_app.hpp>

void ClickerApp::run() {
    Core core;
    RaylibContext ctx;

    EnttTavernRepositoryAdapter tavern_repository{ core.registry };
    TavernService tavern_service{ tavern_repository };
    RaylibTavernServiceAdapter raylib_tavern_adapter{ tavern_service };

    ctx.loop_func = [&raylib_tavern_adapter](Core &core) {

        BeginDrawing();
        ClearBackground(BLACK);
        raylib_tavern_adapter.render_gold_amount();
        DrawText(TextFormat("Left mouse click to generate gold."), 100, 350, 50, WHITE);

        if (IsKeyReleased(KEY_A)) {
            raylib_tavern_adapter.increase_food_price();
        }
        if (IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT)) {
            raylib_tavern_adapter.sell_food();
        }
        EndDrawing();
    };

    ctx.run(core);
}