#include "external/types/game.h"
#include <thread>
#include <chrono>

using namespace std;

int main()
{
    Memory::init();
    Classes::init();
    Offsets::init();

    Log("Waiting for connection to a server...");
    while (!SDG::Provider::isConnected()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    Log("Connected! Running weapon mod loop...");

    while (true)
    {
        auto localPlayer = SDG::Player::player();
        if (localPlayer)
        {
            auto equipment = localPlayer->equipment();
            if (equipment) {
                auto asset = (SDG::ItemGunAsset*)(equipment->asset());

                // If holding a gun, force recoil to 0 constantly
                if (asset && Offsets::recoilMax_x != 0)
                {
                    asset->recoilMax_x_set(0);
                    asset->recoilMin_x_set(0);
                    asset->recoilMax_y_set(0);
                    asset->recoilMin_y_set(0);
                    asset->baseSpreadAngleRadians_set(0);
                }
            }
        }
        // Small sleep to keep CPU usage low
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}