//
//  imgui_lua.cpp
//  imguix
//
//  Created by Jimmy Yin on 4/17/16.
//
//

#include "imgui_lua.hpp"

#if IMGUI_LUA > 0

// Main
static int imgui_showStyleEditor(lua_State *L) {
    int show = luaL_checkinteger(L, 1);
    CCIMGUI::getInstance()->setShowStyleEditor(show);
    return 0;
}

// window
static int imgui_begin(lua_State *L) {
    int args = lua_gettop(L);
    if (args == 1) {
        bool ret = ImGui::Begin(luaL_checkstring(L, 1));
        lua_pushboolean(L, ret);
        return 1;
    } else if (args == 3) {
        bool p_opened = lua_toboolean(L, 2);

        ImGuiWindowFlags flags = 0;
        if (lua_istable(L, 3)) {
            lua_pushnil(L);
            while (lua_next(L, 3)) {
                int flag = lua_tointeger(L, -1);
                flags |= flag;
                lua_pop(L, 1);
            }
        }

        bool ret = ImGui::Begin(luaL_checkstring(L, 1), &p_opened, flags);
        lua_pushboolean(L, ret);
        lua_pushboolean(L, p_opened);
        return 2;
    }

    lua_pushboolean(L, false);
    return 1;
}
static int imgui_end(lua_State *L) {
    ImGui::End();
    return 0;
}
static int imgui_beginChild(lua_State *L) {
    switch (lua_type(L, 1)) {
        case LUA_TSTRING:
            ImGui::BeginChild(luaL_checkstring(L, 1));
            break;
        case LUA_TNUMBER:
            ImGui::BeginChild(luaL_checkinteger(L, 1));
            break;
    }
    return 0;
}
static int imgui_endChild(lua_State *L) {
    ImGui::EndChild();
    return 0;
}
static int imgui_setNextWindowPos(lua_State *L) {
    ImGui::SetNextWindowPos(ImVec2(luaL_checknumber(L, 1), luaL_checknumber(L, 2)));
    return 0;
}
static int imgui_setNextWindowPosCenter(lua_State *L) {
    ImGui::SetNextWindowPosCenter();
    return 0;
}
static int imgui_setNextWindowSize(lua_State *L) {
    ImGui::SetNextWindowSize(ImVec2(luaL_checknumber(L, 1), luaL_checknumber(L, 2)));
    return 0;
}
static int imgui_setNextWindowContentSize(lua_State *L) {
    ImGui::SetNextWindowContentSize(ImVec2(luaL_checknumber(L, 1), luaL_checknumber(L, 2)));
    return 0;
}
static int imgui_setWindowPos(lua_State *L) {
    ImGui::SetWindowPos(ImVec2(luaL_checknumber(L, 1), luaL_checknumber(L, 2)));
    return 0;
}
static int imgui_setWindowSize(lua_State *L) {
    ImGui::SetWindowSize(ImVec2(luaL_checknumber(L, 1), luaL_checknumber(L, 2)));
    return 0;
}

// Cursor / Layout

static int imgui_beginGroup(lua_State *L) {
    ImGui::BeginGroup();
    return 0;
}
static int imgui_endGroup(lua_State *L) {
    ImGui::EndGroup();
    return 0;
}
static int imgui_separator(lua_State *L) {
    ImGui::Separator();
    return 0;
}
static int imgui_sameLine(lua_State *L) {
    float pos_x = 0.0f;
    float spacing_w = -1.0f;

    int args = lua_gettop(L);
    if (args > 0) {
        pos_x = luaL_checknumber(L, 1);
    }
    if (args > 1) {
        spacing_w = luaL_checknumber(L, 2);
    }
    ImGui::SameLine(pos_x, spacing_w);
    return 0;
}
static int imgui_spacing(lua_State *L) {
    ImGui::Spacing();
    return 0;
}
static int imgui_dummy(lua_State *L) {
    ImGui::Dummy(ImVec2(luaL_checknumber(L, 1), luaL_checknumber(L, 2)));
    return 0;
}
static int imgui_indent(lua_State *L) {
    ImGui::Indent();
    return 0;
}
static int imgui_unident(lua_State *L) {
    ImGui::Unindent();
    return 0;
}
static int imgui_getCursorPos(lua_State *L) {
    ImVec2 pos = ImGui::GetCursorPos();
    lua_pushnumber(L, pos.x);
    lua_pushnumber(L, pos.y);
    return 2;
}
static int imgui_getCursorScreenPos(lua_State *L) {
    ImVec2 pos = ImGui::GetCursorScreenPos();
    lua_pushnumber(L, pos.x);
    lua_pushnumber(L, pos.y);
    return 2;
}

// Widgets

static int imgui_text(lua_State *L) {
    ImGui::Text("%s", luaL_checkstring(L, 1));
    return 0;
}
static int imgui_textColored(lua_State *L) {
    ImVec4 col(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4));
    ImGui::TextColored(col, "%s", luaL_checkstring(L, 5));
    return 0;
}
static int imgui_textDisabled(lua_State *L) {
    ImGui::TextDisabled("%s", luaL_checkstring(L, 1));
    return 0;
}
static int imgui_textWrapped(lua_State *L) {
    ImGui::TextWrapped("%s", luaL_checkstring(L, 1));
    return 0;
}
static int imgui_labelText(lua_State *L) {
    ImGui::LabelText(luaL_checkstring(L, 1), "%s", luaL_checkstring(L, 2));
    return 0;
}
static int imgui_bullet(lua_State *L) {
    ImGui::Bullet();
    return 0;
}
static int imgui_bulletText(lua_State *L) {
    ImGui::BulletText("%s", luaL_checkstring(L, 1));
    return 0;
}
static int imgui_button(lua_State *L) {
    lua_pushboolean(L, ImGui::Button(luaL_checkstring(L, 1)));
    return 1;
}
static int imgui_smallButton(lua_State *L) {
    lua_pushboolean(L, ImGui::SmallButton(luaL_checkstring(L, 1)));
    return 1;
}
static int imgui_image(lua_State *L) {
#ifdef COCOS2D_VERSION
    int args = lua_gettop(L);
    std::string fn(luaL_checkstring(L, 1));
    cocos2d::Texture2D *texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(fn);
    ImVec2 size(texture->getPixelsWide(), texture->getPixelsHigh());
    if (args == 3) {
        size.x = luaL_checknumber(L, 2);
        size.y = luaL_checknumber(L, 3);
    }
    if (texture) {
        ImGui::Image((void*)texture->getName(), size);
    }
#endif
    return 0;
}
static int imgui_imageButton(lua_State *L) {
#ifdef COCOS2D_VERSION
    int args = lua_gettop(L);
    std::string fn(luaL_checkstring(L, 1));
    cocos2d::Texture2D *texture = NULL;
    ImVec2 uv0(0, 0);
    ImVec2 uv1(1, 1);
    ImVec2 size(0, 0);

    if (fn.at(0) == '#') {
        fn = fn.substr(1, fn.size());
        SpriteFrame *sf = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(fn);
        if (sf) {
            float atlasWidth = (float)sf->getTexture()->getPixelsWide();
            float atlasHeight = (float)sf->getTexture()->getPixelsHigh();

            const Rect& rect = sf->getRect();
            texture = sf->getTexture();
            if (sf->isRotated()) {
                // FIXME:
                uv0.x = rect.origin.x / atlasWidth;
                uv0.y = rect.origin.y / atlasHeight;
                uv1.x = (rect.origin.x + rect.size.width) / atlasWidth;
                uv1.y = (rect.origin.y + rect.size.height) / atlasHeight;
            } else {
                uv0.x = rect.origin.x / atlasWidth;
                uv0.y = rect.origin.y / atlasHeight;
                uv1.x = (rect.origin.x + rect.size.width) / atlasWidth;
                uv1.y = (rect.origin.y + rect.size.height) / atlasHeight;
            }

            size.x = sf->getRect().size.width;
            size.y = sf->getRect().size.height;
        }
    } else {
        texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(fn);
        size.x = texture->getPixelsWide();
        size.y = texture->getPixelsHigh();
    }

    if (args == 3) {
        size.x = luaL_checknumber(L, 2);
        size.y = luaL_checknumber(L, 3);
    }
    if (texture) {
        lua_pushboolean(L, ImGui::ImageButton((ImTextureID)texture->getName(), size, uv0, uv1));
    } else {
        lua_pushboolean(L, false);
    }
#else
    lua_pushboolean(L, false);
#endif
    return 1;
}
static int imgui_collapsingHeader(lua_State *L) {
    lua_pushboolean(L, ImGui::CollapsingHeader(luaL_checkstring(L, 1)));
    return 1;
}
static int imgui_checkbox(lua_State *L) {
    bool v = luaL_checkinteger(L, 2);
    bool ret = ImGui::Checkbox(luaL_checkstring(L, 1), &v);
    lua_pushboolean(L, ret);
    lua_pushboolean(L, v);
    return 2;
}
static int imgui_checkboxFlags(lua_State *L) {
    const char* label = luaL_checkstring(L, 1);
    unsigned int flags = luaL_checkinteger(L, 2);
    unsigned int flags_value = luaL_checkinteger(L, 3);
    bool ret = ImGui::CheckboxFlags(label, &flags, flags_value);
    lua_pushboolean(L, ret);
    lua_pushinteger(L, flags);
    return 2;
}
static int imgui_radioButton(lua_State *L) {
    int args = lua_gettop(L);
    if (args == 2) {
        lua_pushboolean(L, ImGui::RadioButton(luaL_checkstring(L, 1), luaL_checkinteger(L, 2)));
        return 1;
    } else if (args == 3) {
        int v = luaL_checkinteger(L, 2);
        lua_pushboolean(L, ImGui::RadioButton(luaL_checkstring(L, 1), &v, luaL_checkinteger(L, 3)));
        lua_pushinteger(L, v);
        return 2;
    }
    return 0;
}
static int imgui_combo(lua_State *L) {
    // only support "items_separated_by_zeros"
    int current_item = luaL_checkinteger(L, 2);
    const char *items_separated_by_zeros = luaL_checkstring(L, 3);
    lua_pushboolean(L, ImGui::Combo(luaL_checkstring(L, 1), &current_item, items_separated_by_zeros));
    lua_pushinteger(L, current_item);
    return 2;
}
static int imgui_colorButton(lua_State *L) {
    ImVec4 col(luaL_checkinteger(L, 1), luaL_checkinteger(L, 2), luaL_checkinteger(L, 3), luaL_checkinteger(L, 4));
    bool ret = ImGui::ColorButton(col);
    lua_pushboolean(L, ret);
    return 1;
}

// Menus

static int imgui_beginMainMenuBar(lua_State *L) {
    bool ret = ImGui::BeginMainMenuBar();
    lua_pushboolean(L, ret);
    return 1;
}
static int imgui_endMainMenuBar(lua_State *L) {
    ImGui::EndMainMenuBar();
    return 0;
}
static int imgui_beginMenuBar(lua_State *L) {
    bool ret = ImGui::BeginMenuBar();
    lua_pushboolean(L, ret);
    return 1;
}
static int imgui_endMenuBar(lua_State *L) {
    ImGui::EndMenuBar();
    return 0;
}
static int imgui_beginMenu(lua_State *L) {
    bool ret = ImGui::BeginMenu(luaL_checkstring(L, 1));
    lua_pushboolean(L, ret);
    return 1;
}
static int imgui_endMenu(lua_State *L) {
    ImGui::EndMenu();
    return 0;
}
static int imgui_menuItem(lua_State *L) {
    bool ret = ImGui::MenuItem(luaL_checkstring(L, 1));
    lua_pushboolean(L, ret);
    return 1;
}

// Widgets: Drags
static int imgui_dragFloat(lua_State *L) {
    const char* label = luaL_checkstring(L, 1);
    float v = luaL_checknumber(L, 2);
    float v_speed = 1.0f;
    float v_min = 0.0f;
    float v_max = 0.0f;
    const char* display_format = "%.3f";
    float power = 1.0f;

    int args = lua_gettop(L);
    if (args > 2) {
        v_speed = luaL_checknumber(L, 3);
    }
    if (args > 3) {
        v_min = luaL_checknumber(L, 4);
    }
    if (args > 4) {
        v_max = luaL_checknumber(L, 5);
    }
    if (args > 5) {
        display_format = luaL_checkstring(L, 6);
    }
    if (args > 6) {
        power = luaL_checknumber(L, 7);
    }

    bool ret = ImGui::DragFloat(label, &v, v_speed, v_min, v_max, display_format, power);
    lua_pushboolean(L, ret);
    lua_pushnumber(L, v);
    return 2;
}
static int imgui_dragFloat2(lua_State *L) {
    int args = lua_gettop(L);
    const char *label = luaL_checkstring(L, 1);
    float v[2] = { (float)luaL_checknumber(L, 2), (float)(luaL_checknumber(L, 3)) };
    float v_speed = 1.0f;   // 4
    float v_min = 0.0f;     // 5
    float v_max = 0.0f;     // 6
    const char* display_format = "%.3f"; // 7
    float power = 1.0f;     // 8

    if (args > 3) {
        v_speed = luaL_checknumber(L, 4);
    }
    if (args > 4) {
        v_min = luaL_checknumber(L, 5);
    }
    if (args > 5) {
        v_max = luaL_checknumber(L, 6);
    }
    if (args > 6) {
        display_format = luaL_checkstring(L, 7);
    }
    if (args > 7) {
        power = luaL_checknumber(L, 8);
    }

    bool ret = ImGui::DragFloat2(label, v, v_speed, v_min, v_max, display_format, power);
    lua_pushboolean(L, ret);
    lua_pushnumber(L, v[0]);
    lua_pushnumber(L, v[1]);
    return 3;
}
static int imgui_dragInt(lua_State *L) {
    const char* label = luaL_checkstring(L, 1);
    int v = luaL_checkinteger(L, 2);
    float v_speed = 1.0f;   // 3
    int v_min = 0;          // 4
    int v_max = 0;          // 5
    const char* display_format = "%.0f"; // 6

    int args = lua_gettop(L);
    if (args > 2) {
        v_speed = luaL_checknumber(L, 3);
    }
    if (args > 3) {
        v_min = luaL_checkinteger(L, 4);
    }
    if (args > 4) {
        v_max = luaL_checkinteger(L, 5);
    }
    if (args > 5) {
        display_format = luaL_checkstring(L, 6);
    }

    bool ret = ImGui::DragInt(label, &v, v_speed, v_min, v_max, display_format);
    lua_pushboolean(L, ret);
    lua_pushinteger(L, v);
    return 2;
}
static int imgui_dragInt2(lua_State *L) {
    const char* label = luaL_checkstring(L, 1);
    int v[2] = { (int)(luaL_checkinteger(L, 2)), (int)luaL_checkinteger(L, 3) };
    float v_speed = 1.0f;   // 4
    int v_min = 0;          // 5
    int v_max = 0;          // 6
    const char* display_format = "%.0f"; // 7

    int args = lua_gettop(L);
    if (args > 3) {
        v_speed = luaL_checknumber(L, 4);
    }
    if (args > 4) {
        v_min = luaL_checkinteger(L, 5);
    }
    if (args > 5) {
        v_max = luaL_checkinteger(L, 6);
    }
    if (args > 6) {
        display_format = luaL_checkstring(L, 7);
    }

    bool ret = ImGui::DragInt2(label, v, v_speed, v_min, v_max, display_format);
    lua_pushboolean(L, ret);
    lua_pushinteger(L, v[0]);
    lua_pushinteger(L, v[1]);
    return 2;
}

// Widgets: Input with Keyboard
static int imgui_inputText(lua_State *L) {
    int buf_size = luaL_checkinteger(L, 3);
    char buf[256] = { 0 };    // @FIXME
    memmove(buf, luaL_checkstring(L, 2), buf_size);
    bool ret = ImGui::InputText(luaL_checkstring(L, 1), buf, buf_size);
    lua_pushboolean(L, ret);
    lua_pushstring(L, buf);
    return 2;
}
static int imgui_inputMultiline(lua_State *L) {
    char buf[512] = { 0 };
    bool ret = ImGui::InputTextMultiline(luaL_checkstring(L, 1), buf, sizeof(buf));
    lua_pushboolean(L, ret);
    lua_pushstring(L, buf);
    return 2;
}
static int imgui_inputFloat(lua_State *L) {
    const char* label = luaL_checkstring(L, 1);
    float v = luaL_checknumber(L, 2);
    float step = 0.0f;          // 3
    float step_fast = 0.0f;     // 4
    int decimal_precision = -1; // 5

    int args = lua_gettop(L);
    if (args > 2) {
        step = luaL_checknumber(L, 3);
    }
    if (args > 3) {
        step_fast = luaL_checknumber(L, 4);
    }
    if (args > 4) {
        decimal_precision = luaL_checkinteger(L, 5);
    }

    bool ret = ImGui::InputFloat(label, &v, step, step_fast, decimal_precision);
    lua_pushboolean(L, ret);
    lua_pushnumber(L, v);
    return 2;
}
static int imgui_inputFloat2(lua_State *L) {
    const char* label = luaL_checkstring(L, 1);
    float v[2] = { (float)luaL_checknumber(L, 2), (float)luaL_checknumber(L, 3) };
    int decimal_precision = -1; // 4

    int args = lua_gettop(L);
    if (args > 3) {
        decimal_precision = luaL_checkinteger(L, 4);
    }

    bool ret = ImGui::InputFloat2(label, v, decimal_precision);
    lua_pushboolean(L, ret);
    lua_pushnumber(L, v[0]);
    lua_pushnumber(L, v[1]);
    return 3;
}
static int imgui_inputInt(lua_State *L) {
    const char* label = luaL_checkstring(L, 1);
    int v = luaL_checkinteger(L, 2);
    int step = 1;   // 3
    int step_fast = 100; // 4

    int args = lua_gettop(L);
    if (args > 2) {
        step = luaL_checkinteger(L, 3);
    }
    if (args > 3) {
        step_fast = luaL_checkinteger(L, 4);
    }

    bool ret = ImGui::InputInt(label, &v, step, step_fast);
    lua_pushboolean(L, ret);
    lua_pushinteger(L, v);
    return 2;
}
static int imgui_inputInt2(lua_State *L) {
    const char* label = luaL_checkstring(L, 1);
    int v[2] = { (int)luaL_checkinteger(L, 2), (int)luaL_checkinteger(L, 3) };

    bool ret = ImGui::InputInt(label, v);
    lua_pushboolean(L, ret);
    lua_pushinteger(L, v[0]);
    lua_pushinteger(L, v[1]);
    return 3;
}

// Widgets: Sliders

static int imgui_sliderFloat(lua_State *L) {
    const char *label = luaL_checkstring(L, 1);
    float f = luaL_checknumber(L, 2);
    float v_min = luaL_checknumber(L, 3);
    float v_max = luaL_checknumber(L, 4);

    const char* display_format = "%.3f";
    float power = 1.0f;
    int args = lua_gettop(L);
    if (args > 4) {
        display_format = luaL_checkstring(L, 5);
    }
    if (args > 5) {
        power = luaL_checknumber(L, 6);
    }

    bool ret = ImGui::SliderFloat(label, &f, v_min, v_max, display_format, power);

    lua_pushboolean(L, ret);
    lua_pushnumber(L, f);
    return 2;
}
static int imgui_sliderFloat2(lua_State *L) {
    const char *label = luaL_checkstring(L, 1);
    float f[2] = { (float)luaL_checknumber(L, 2), (float)luaL_checknumber(L, 3) };
    float v_min = luaL_checknumber(L, 4);
    float v_max = luaL_checknumber(L, 5);

    const char* display_format = "%.3f";
    float power = 1.0f;
    int args = lua_gettop(L);
    if (args > 5) {
        display_format = luaL_checkstring(L, 6);
    }
    if (args > 6) {
        power = luaL_checknumber(L, 7);
    }

    bool ret = ImGui::SliderFloat2(label, f, v_min, v_max, display_format, power);

    lua_pushboolean(L, ret);
    lua_pushnumber(L, f[0]);
    lua_pushnumber(L, f[1]);
    return 3;
}
static int imgui_sliderAngle(lua_State *L) {
    const char* label = luaL_checkstring(L, 1);
    float v_rad = luaL_checknumber(L, 2);
    float v_degrees_min = -360.0f;
    float v_degrees_max = +360.0f;
    int args = lua_gettop(L);
    if (args > 2) {
        v_degrees_min = luaL_checknumber(L, 3);
    }
    if (args > 3) {
        v_degrees_max = luaL_checknumber(L, 4);
    }

    bool ret = ImGui::SliderAngle(label, &v_rad, v_degrees_min, v_degrees_max);
    lua_pushboolean(L, ret);
    lua_pushnumber(L, v_rad);
    return 2;
}
static int imgui_sliderInt(lua_State *L) {
    int v = luaL_checkinteger(L, 2);
    int v_min = luaL_checkinteger(L, 3);
    int v_max = luaL_checkinteger(L, 4);
    const char* display_format = "%.0f";
    if (lua_gettop(L) > 4) {
        display_format = luaL_checkstring(L, 5);
    }

    bool ret = ImGui::SliderInt(luaL_checkstring(L, 1), &v, v_min, v_max);
    lua_pushboolean(L, ret);
    lua_pushinteger(L, v);
    return 2;
}
static int imgui_sliderInt2(lua_State *L) {
    int v[2] = { (int)luaL_checkinteger(L, 2), (int)luaL_checkinteger(L, 3) };
    int v_min = luaL_checkinteger(L, 4);
    int v_max = luaL_checkinteger(L, 5);
    const char* display_format = "%.0f";
    if (lua_gettop(L) > 5) {
        display_format = luaL_checkstring(L, 6);
    }

    bool ret = ImGui::SliderInt2(luaL_checkstring(L, 1), v, v_min, v_max);
    lua_pushboolean(L, ret);
    lua_pushinteger(L, v[0]);
    lua_pushinteger(L, v[1]);
    return 3;
}
static int imgui_vSliderFloat(lua_State *L) {
    ImVec2 size(luaL_checknumber(L, 2), luaL_checknumber(L, 3));
    float v = luaL_checknumber(L, 4);
    float v_min = luaL_checknumber(L, 5);
    float v_max = luaL_checknumber(L, 6);
    const char* display_format = "%.3f"; // 7
    float power = 1.0f;                  // 8
    int args = lua_gettop(L);

    if (args > 6) {
        display_format = luaL_checkstring(L, 7);
    }
    if (args > 7) {
        power = luaL_checknumber(L, 8);
    }

    bool ret = ImGui::VSliderFloat(luaL_checkstring(L, 1), size, &v, v_min, v_max, display_format, power);
    lua_pushboolean(L, ret);
    lua_pushnumber(L, v);
    return 2;
}
static int imgui_vSliderInt(lua_State *L) {
    ImVec2 size(luaL_checkinteger(L, 1), luaL_checkinteger(L, 2));
    int v = luaL_checkinteger(L, 3);
    int v_min = luaL_checkinteger(L, 4);
    int v_max = luaL_checkinteger(L, 5);
    const char* display_format = "%.0f";
    if (lua_gettop(L) > 5) {
        display_format = luaL_checkstring(L, 6);
    }

    bool ret = ImGui::VSliderInt(luaL_checkstring(L, 1), size, &v, v_min, v_max, display_format);
    lua_pushboolean(L, ret);
    lua_pushinteger(L, v);
    return 2;
}

#define M(n) {#n, imgui_##n}
static const luaL_Reg imgui_methods[] = {
    // Main
    M(showStyleEditor),

    // Window
    {"endToLua", imgui_end},
    M(begin), M(beginChild), M(endChild),
    M(setNextWindowPos),
    M(setNextWindowPosCenter),
    M(setNextWindowSize),
    M(setNextWindowContentSize),
    M(setWindowPos),
    M(setWindowSize),

    // Cursor / Layout
    M(beginGroup),
    M(endGroup),
    M(separator),
    M(sameLine),
    M(spacing),
    M(dummy),
    M(indent),
    M(unident),
    M(getCursorPos),
    M(getCursorScreenPos),

    // Widgets
    M(text),
    M(textColored),
    M(textDisabled),
    M(textWrapped),
    M(labelText),
    M(bullet),
    M(bulletText),
    M(button),
    M(smallButton),
    M(image),
    M(imageButton),
    M(collapsingHeader),
    M(checkbox),
    M(checkboxFlags),
    M(radioButton),
    M(combo),
    M(colorButton),

    // Widgets: Drags
    M(dragFloat),
    M(dragFloat2),
    M(dragInt),
    M(dragInt2),

    // Widgets: Input with Keyboard
    M(inputText),
    M(inputMultiline),
    M(inputFloat),
    M(inputFloat2),
    M(inputInt),
    M(inputInt2),

    // Widgets: Sliders

    M(sliderFloat),
    M(sliderFloat2),
    M(sliderAngle),
    M(sliderInt),
    M(sliderInt2),
    M(vSliderFloat),
    M(vSliderInt),

    // Menus
    M(beginMainMenuBar),
    M(endMainMenuBar),
    M(beginMenuBar),
    M(endMenuBar),
    M(beginMenu),
    M(endMenu),
    M(menuItem),

    {NULL,  NULL}
};

int luaopen_imgui(lua_State *L)
{
    luaL_register(L, "imgui", imgui_methods);
    lua_pushstring(L, ImGui::GetVersion());
    lua_setfield(L, -2, "version");

#define FIELD(field) \
    lua_pushinteger(L, field); \
    lua_setfield(L, -2, #field);

    FIELD(ImGuiWindowFlags_NoTitleBar)
    FIELD(ImGuiWindowFlags_NoResize)
    FIELD(ImGuiWindowFlags_NoMove)
    FIELD(ImGuiWindowFlags_NoScrollbar)
    FIELD(ImGuiWindowFlags_NoScrollWithMouse)
    FIELD(ImGuiWindowFlags_NoCollapse)
    FIELD(ImGuiWindowFlags_AlwaysAutoResize)
    FIELD(ImGuiWindowFlags_ShowBorders)
    FIELD(ImGuiWindowFlags_NoSavedSettings)
    FIELD(ImGuiWindowFlags_NoInputs)
    FIELD(ImGuiWindowFlags_MenuBar)
    FIELD(ImGuiWindowFlags_HorizontalScrollbar)
    FIELD(ImGuiWindowFlags_NoFocusOnAppearing)
    FIELD(ImGuiWindowFlags_NoBringToFrontOnFocus)
    FIELD(ImGuiWindowFlags_AlwaysVerticalScrollbar)
    FIELD(ImGuiWindowFlags_AlwaysHorizontalScrollbar)
    FIELD(ImGuiWindowFlags_AlwaysUseWindowPadding)

    lua_pushinteger(L, ImGuiWindowFlags_MenuBar);
    lua_setfield(L, -2, "ImGuiWindowFlags_MenuBar");


    CCIMGUI::getInstance()->addImGUI([=]() {
        lua_getglobal(L, "imgui");
        lua_getfield(L, -1, "draw");
        if (lua_pcall(L, 0, 0, 0)) {
            CCLOG("__luadraw__ error: %s", lua_tostring(L, -1));
        }

    }, "__luadraw__");

    return 0;
}

#endif // IMGUI_LUA
