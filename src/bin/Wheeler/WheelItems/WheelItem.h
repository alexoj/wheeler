#pragma once
#include "bin/Rendering/TextureManager.h"
#include "bin/Config.h"
#include "nlohmann/json.hpp"
class ImVec2;
class WheelItem
{
public:
	WheelItem(){};

	/// <summary>
	/// Check if the item contained is still valid, that is, that it still
	/// points to a valid game form.
	/// If not valid it should be disposed of as quickly as possible.
	/// </summary>
	virtual bool IsItemValid();

	
	/// <summary>
	/// Draw everything that's supposed to be in a wheel slot(entry)
	/// Currently, DrawSlot should draw an image of the item and its name.
	/// </summary>
	virtual void DrawSlot(ImVec2 a_center, bool a_hovered, RE::TESObjectREFR::InventoryItemMap& a_imap, DrawArgs a_drawArgs);
	
	/// <summary>
	/// Draw everything of the item that's supposed to be in the highlight region i.e. center of the wheel.
	/// Currently, DrawHighlight should draw an enlarged image of the item, item description, and item stats(if applicable).
	/// </summary>
	virtual void DrawHighlight(ImVec2 a_center, RE::TESObjectREFR::InventoryItemMap& a_imap, DrawArgs a_drawArgs);
	virtual bool IsActive(RE::TESObjectREFR::InventoryItemMap& a_inv);

	/// <summary>
	/// Whether the item is available. 
	/// An item is unavailable when the player lacks skill to use it, or the item is not in the player's inventory.
	/// </summary>
	virtual bool IsAvailable(RE::TESObjectREFR::InventoryItemMap& a_inv);

	virtual void ActivateItemPrimary();
	virtual void ActivateItemSecondary();
	virtual void ActivateItemSpecial();

	virtual void SerializeIntoJsonObj(nlohmann::json& a_json);
	static std::shared_ptr<WheelItem> SerializeFromJsonObj(nlohmann::json& a_json);

	static inline const char* ITEM_TYPE_STR = "WheelItem";


protected:
	Texture::Image _texture = Texture::Image();
	Texture::Image _stat_texture = Texture::Image();
	std::string _description = "";  // buffer for description.
	
	/// <summary>
	/// Draws stat icon and value of the item when the item is highlighted.
	/// Coordinates and scale of the icon texture and value text are determined by Config.
	/// </summary>
	void drawItemHighlightStatIconAndValue(ImVec2 a_center, Texture::Image& a_stat_icon, float a_stat_value, DrawArgs a_drawArgs);

	void drawHighlightDescription(ImVec2 a_center, const char* a_text, DrawArgs a_drawArgs);
	void drawHighlightTexture(ImVec2 a_center, DrawArgs a_drawArgs);
	void drawHighlightText(ImVec2 a_center, const char* a_text, DrawArgs a_drawArgs);
	void drawSlotTexture(ImVec2 a_center, DrawArgs a_drawArgs);
	void drawSlotText(ImVec2 a_center, const char* a_text, DrawArgs a_drawArgs);
};
