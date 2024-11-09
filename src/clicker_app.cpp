//
// Created by Patryk Szczypień on 07/11/2024.
//

#include <clicker_app.hpp>

void ClickerApp::run() {
    Core core;
    RaylibContext ctx;

    ctx.pre_loop_func = [](Core &core) {
        auto initial_resources = std::unordered_map<uint8_t, BigNum>{{static_cast<uint8_t>(Resource::Gold), BigNum(0)}};
        core.registry.ctx().emplace<ResourceMap>(initial_resources);
        core.registry.ctx().emplace<Generator<Resource::Gold>>(4.0f, 1.07f, 1.67f, 1.0f);
    };
    ctx.loop_func = [](Core &core){
        BeginDrawing();
        ClearBackground(BLACK);
        if (auto *resources = core.registry.ctx().find<ResourceMap>()) {
            auto gold = resources->values[static_cast<uint8_t>(Resource::Gold)];
            DrawText(TextFormat("Gold: %s", gold.toString().c_str()), 100, 100, 50, YELLOW);
            if (auto *generators = core.registry.ctx().find<Generator<Resource::Gold>>()) {
                DrawText(TextFormat("Generators: %d - gold production rate %.2f", generators->amount(), generators->production_rate()), 100, 150, 50, WHITE);
                DrawText(TextFormat("Press A to buy a generator for : %s gold.", generators->amount() == 0 ? "0.00" : generators->next_cost().toString().c_str()), 100, 250, 50, WHITE);
                DrawText(TextFormat("Left mouse click to generate gold."), 100, 350, 50, WHITE);
                if (IsKeyReleased(KEY_A)) {
                    if (generators->amount() == 0) {
                        generators->add();
                    }
                    if (gold.compare(generators->next_cost()) >= 0) {
                        resources->values[static_cast<uint8_t>(Resource::Gold)] = resources->values[static_cast<uint8_t>(Resource::Gold)].subtract(generators->next_cost());
                        generators->add();
                    }
                }
                if (IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT)) {
                    resources->values[static_cast<uint8_t>(Resource::Gold)] = resources->values[static_cast<uint8_t>(Resource::Gold)].add(generators->production_rate());
                }
            }
        }


        EndDrawing();
    };

    ctx.run(core);
}