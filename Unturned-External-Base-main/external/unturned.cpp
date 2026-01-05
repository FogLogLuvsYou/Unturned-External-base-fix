#include "unturned.h"

namespace Classes
{
	mono_class_t* Provider;
	mono_class_t* Player;
	mono_class_t* SteamChannel;
	mono_class_t* SteamPlayer;

	mono_class_t* PlayerEquipment;
	mono_class_t* ItemAsset;
	mono_class_t* ItemGunAsset;


	void init()
	{
		Provider = mono::find_class("Assembly-CSharp", "SDG.Unturned.Provider");

		Player = mono::find_class("Assembly-CSharp", "SDG.Unturned.Player");
		SteamChannel = mono::find_class("Assembly-CSharp", "SDG.Unturned.SteamChannel");
		SteamPlayer = mono::find_class("Assembly-CSharp", "SDG.Unturned.SteamPlayer");

		PlayerEquipment = mono::find_class("Assembly-CSharp", "SDG.Unturned.PlayerEquipment");
		ItemAsset = mono::find_class("Assembly-CSharp", "SDG.Unturned.ItemAsset");
		ItemGunAsset = mono::find_class("Assembly-CSharp", "SDG.Unturned.ItemGunAsset");
	}
}

namespace Offsets
{
	uintptr_t _player;

	uintptr_t _isConnected;
	uintptr_t isWaitingForWorkshopResponse;
	uintptr_t _clients;

	uintptr_t channel;
	uintptr_t owner;

	uintptr_t _isAdmin;
	uintptr_t _splayer; //SteamPlayer's player field (you can see this way of doing offsets isnt very scalable as many classes have the same field name)
	uintptr_t _joined;

	uintptr_t _equipment;
	uintptr_t _asset;

	uintptr_t recoilMin_x;
	uintptr_t recoilMax_x;
	uintptr_t recoilMin_y;
	uintptr_t recoilMax_y;

	uintptr_t baseSpreadAngleRadians;

	void init()
{
    _player = Classes::Player->find_field("_localPlayer")->offset();
    printf("[OK] _localPlayer offset: 0x%zX\n", _player);

    auto f = Classes::Player->find_field("_channel");
    if (f) { channel = f->offset(); printf("[OK] channel offset: 0x%zX\n", channel); }
    else { printf("[FAIL] _channel not found!\n"); }

    f = Classes::Player->find_field("_equipment");
    if (f) { _equipment = f->offset(); printf("[OK] _equipment offset: 0x%zX\n", _equipment); }
    else { printf("[FAIL] _equipment not found!\n"); }

    f = Classes::Provider->find_field("_isConnected");
    if (f) { _isConnected = f->offset(); printf("[OK] _isConnected offset: 0x%zX\n", _isConnected); }
    else { printf("[FAIL] _isConnected not found! (try <isConnected>k__BackingField)\n"); }

    f = Classes::Provider->find_field("isWaitingForWorkshopResponse");
    if (f) { isWaitingForWorkshopResponse = f->offset(); printf("[OK] isWaitingForWorkshopResponse offset: 0x%zX\n", isWaitingForWorkshopResponse); }
    else { printf("[FAIL] isWaitingForWorkshopResponse not found!\n"); }

    f = Classes::Provider->find_field("_clients");
    if (f) { _clients = f->offset(); printf("[OK] _clients offset: 0x%zX\n", _clients); }
    else { printf("[FAIL] _clients not found! (try <clients>k__BackingField)\n"); }

    f = Classes::SteamPlayer->find_field("_isAdmin");
    if (f) { _isAdmin = f->offset(); printf("[OK] _isAdmin offset: 0x%zX\n", _isAdmin); }
    else { printf("[FAIL] _isAdmin not found!\n"); }

    f = Classes::SteamPlayer->find_field("_joined");
    if (f) { _joined = f->offset(); printf("[OK] _joined offset: 0x%zX\n", _joined); }
    else { printf("[FAIL] _joined not found!\n"); }

    f = Classes::SteamPlayer->find_field("_player");
    if (f) { _splayer = f->offset(); printf("[OK] _splayer offset: 0x%zX\n", _splayer); }
    else { printf("[FAIL] _player not found in SteamPlayer!\n"); }

    f = Classes::SteamChannel->find_field("owner");
    if (f) { owner = f->offset(); printf("[OK] owner offset: 0x%zX\n", owner); }
    else { printf("[FAIL] owner not found!\n"); }

    f = Classes::PlayerEquipment->find_field("_asset");
    if (f) { _asset = f->offset(); printf("[OK] _asset offset: 0x%zX\n", _asset); }
    else { printf("[FAIL] _asset not found!\n"); }

    f = Classes::ItemGunAsset->find_field("recoilMin_x");
    if (f) { recoilMin_x = f->offset(); printf("[OK] recoilMin_x offset: 0x%zX\n", recoilMin_x); }
    else { printf("[FAIL] recoilMin_x not found!\n"); }

    f = Classes::ItemGunAsset->find_field("recoilMax_x");
    if (f) { recoilMax_x = f->offset(); printf("[OK] recoilMax_x offset: 0x%zX\n", recoilMax_x); }
    else { printf("[FAIL] recoilMax_x not found!\n"); }

    f = Classes::ItemGunAsset->find_field("recoilMin_y");
    if (f) { recoilMin_y = f->offset(); printf("[OK] recoilMin_y offset: 0x%zX\n", recoilMin_y); }
    else { printf("[FAIL] recoilMin_y not found!\n"); }

    f = Classes::ItemGunAsset->find_field("recoilMax_y");
    if (f) { recoilMax_y = f->offset(); printf("[OK] recoilMax_y offset: 0x%zX\n", recoilMax_y); }
    else { printf("[FAIL] recoilMax_y not found!\n"); }

    f = Classes::ItemGunAsset->find_field("<baseSpreadAngleRadians>k__BackingField");
    if (f) { baseSpreadAngleRadians = f->offset(); printf("[OK] baseSpreadAngleRadians offset: 0x%zX\n", baseSpreadAngleRadians); }
    else { printf("[FAIL] <baseSpreadAngleRadians>k__BackingField not found!\n"); }

    printf("[DONE] All offsets processed\n");
}
}