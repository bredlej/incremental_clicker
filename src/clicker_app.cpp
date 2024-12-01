//
// Created by Patryk Szczypień on 07/11/2024.
//

#include <clicker_app.hpp>

void ClickerApp::run() {
    Core core;
    RaylibContext ctx;

    EnttTavernRepositoryAdapter tavern_repository{core};
    TavernService tavern_service{tavern_repository};
    RaylibTavernServiceAdapter raylib_tavern_adapter{tavern_service};

    Scheduler<std::chrono::milliseconds> scheduler(core);
    scheduler.builder()
            .after(500, [](Core &core) {
                core.scheduler.update(500);
            })
            .repeating()
            .run();

    ctx.loop_func = [&raylib_tavern_adapter](Core &core) {

        BeginDrawing();
        ClearBackground(BLACK);
        raylib_tavern_adapter.render_gold_amount();
        DrawText(TextFormat("Left mouse click to generate gold."), 100, 350, 50, WHITE);
        raylib_tavern_adapter.render_gold_generator_info();
        if (IsKeyReleased(KEY_A)) {
            raylib_tavern_adapter.increase_food_sales();
        }
        if (IsKeyReleased(KEY_H)) {
            raylib_tavern_adapter.hire_food_helper();
        }
        if (IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT)) {
            raylib_tavern_adapter.sell_food();
        }

        EndDrawing();
    };

    Persistence persistence(core, tavern_repository);
    ctx.pre_loop_func = [&persistence](Core &core) {
        persistence.restore_state();
    };
    ctx.post_loop_func = [&persistence](Core &core) {
        persistence.save_state();
    };

    ctx.run(core);
}