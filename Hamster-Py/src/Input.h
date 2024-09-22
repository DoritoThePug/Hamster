#ifndef INPUT_H
#define INPUT_H

#include <pybind11/pybind11.h>

#include <Utils/InputManager.h>

void KeyCodeEnumBinding(pybind11::module_ &m) {
  pybind11::enum_<Hamster::KeyCodes>(m, "key_code")
      .value("key_not_pressed", Hamster::KeyCodes::NOT_PRESSED)
      .value("key_space", Hamster::KeyCodes::KEY_SPACE)
      .value("key_apostrophe", Hamster::KeyCodes::KEY_APOSTROPHE) /* ' */
      .value("key_comma", Hamster::KeyCodes::KEY_COMMA)           /* , */
      .value("key_minus", Hamster::KeyCodes::KEY_MINUS)           /* - */
      .value("key_period", Hamster::KeyCodes::KEY_PERIOD)         /* . */
      .value("key_slash", Hamster::KeyCodes::KEY_SLASH)           /* / */
      .value("key_0", Hamster::KeyCodes::KEY_0)
      .value("key_1", Hamster::KeyCodes::KEY_1)
      .value("key_2", Hamster::KeyCodes::KEY_2)
      .value("key_3", Hamster::KeyCodes::KEY_3)
      .value("key_4", Hamster::KeyCodes::KEY_4)
      .value("key_5", Hamster::KeyCodes::KEY_5)
      .value("key_6", Hamster::KeyCodes::KEY_6)
      .value("key_7", Hamster::KeyCodes::KEY_7)
      .value("key_8", Hamster::KeyCodes::KEY_8)
      .value("key_9", Hamster::KeyCodes::KEY_9)
      .value("key_semicolon", Hamster::KeyCodes::KEY_SEMICOLON) /* ; */
      .value("key_equal", Hamster::KeyCodes::KEY_EQUAL)         /* = */
      .value("key_a", Hamster::KeyCodes::KEY_A)
      .value("key_b", Hamster::KeyCodes::KEY_B)
      .value("key_c", Hamster::KeyCodes::KEY_C)
      .value("key_d", Hamster::KeyCodes::KEY_D)
      .value("key_e", Hamster::KeyCodes::KEY_E)
      .value("key_f", Hamster::KeyCodes::KEY_F)
      .value("key_g", Hamster::KeyCodes::KEY_G)
      .value("key_h", Hamster::KeyCodes::KEY_H)
      .value("key_i", Hamster::KeyCodes::KEY_I)
      .value("key_j", Hamster::KeyCodes::KEY_J)
      .value("key_k", Hamster::KeyCodes::KEY_K)
      .value("key_l", Hamster::KeyCodes::KEY_L)
      .value("key_m", Hamster::KeyCodes::KEY_M)
      .value("key_n", Hamster::KeyCodes::KEY_N)
      .value("key_o", Hamster::KeyCodes::KEY_O)
      .value("key_p", Hamster::KeyCodes::KEY_P)
      .value("key_q", Hamster::KeyCodes::KEY_Q)
      .value("key_r", Hamster::KeyCodes::KEY_R)
      .value("key_s", Hamster::KeyCodes::KEY_S)
      .value("key_t", Hamster::KeyCodes::KEY_T)
      .value("key_u", Hamster::KeyCodes::KEY_U)
      .value("key_v", Hamster::KeyCodes::KEY_V)
      .value("key_w", Hamster::KeyCodes::KEY_W)
      .value("key_x", Hamster::KeyCodes::KEY_X)
      .value("key_y", Hamster::KeyCodes::KEY_Y)
      .value("key_z", Hamster::KeyCodes::KEY_Z)
      .value("key_left_bracket", Hamster::KeyCodes::KEY_LEFT_BRACKET) /* [
                                                                       */
      .value("key_backslash", Hamster::KeyCodes::KEY_BACKSLASH)       /*
 \ */.value("key_right_bracket", Hamster::KeyCodes::KEY_RIGHT_BRACKET)
      /* ] */
      .value("key_grave_accent", Hamster::KeyCodes::KEY_GRAVE_ACCENT)
      /* ` */
      .value("key_world_1", Hamster::KeyCodes::KEY_WORLD_1) /* non-US
#1 */.value("key_world_2", Hamster::KeyCodes::KEY_WORLD_2)  /* non-US
#2 */

      .value("key_escape", Hamster::KeyCodes::KEY_ESCAPE)
      .value("key_enter", Hamster::KeyCodes::KEY_ENTER)
      .value("key_tab", Hamster::KeyCodes::KEY_TAB)
      .value("key_backspace", Hamster::KeyCodes::KEY_BACKSPACE)
      .value("key_insert", Hamster::KeyCodes::KEY_INSERT)
      .value("key_delete", Hamster::KeyCodes::KEY_DELETE)
      .value("key_right", Hamster::KeyCodes::KEY_RIGHT)
      .value("key_left", Hamster::KeyCodes::KEY_LEFT)
      .value("key_down", Hamster::KeyCodes::KEY_DOWN)
      .value("key_up", Hamster::KeyCodes::KEY_UP)
      .value("key_page_up", Hamster::KeyCodes::KEY_PAGE_UP)
      .value("key_page_down", Hamster::KeyCodes::KEY_PAGE_DOWN)
      .value("key_home", Hamster::KeyCodes::KEY_HOME)
      .value("key_end", Hamster::KeyCodes::KEY_END)
      .value("key_caps_lock", Hamster::KeyCodes::KEY_CAPS_LOCK)
      .value("key_scroll_lock", Hamster::KeyCodes::KEY_SCROLL_LOCK)
      .value("key_num_lock", Hamster::KeyCodes::KEY_NUM_LOCK)
      .value("key_print_screen", Hamster::KeyCodes::KEY_PRINT_SCREEN)
      .value("key_pause", Hamster::KeyCodes::KEY_PAUSE)
      .value("key_f1", Hamster::KeyCodes::KEY_F1)
      .value("key_f2", Hamster::KeyCodes::KEY_F2)
      .value("key_f3", Hamster::KeyCodes::KEY_F3)
      .value("key_f4", Hamster::KeyCodes::KEY_F4)
      .value("key_f5", Hamster::KeyCodes::KEY_F5)
      .value("key_f6", Hamster::KeyCodes::KEY_F6)
      .value("key_f7", Hamster::KeyCodes::KEY_F7)
      .value("key_f8", Hamster::KeyCodes::KEY_F8)
      .value("key_f9", Hamster::KeyCodes::KEY_F9)
      .value("key_f10", Hamster::KeyCodes::KEY_F10)
      .value("key_f11", Hamster::KeyCodes::KEY_F11)
      .value("key_f12", Hamster::KeyCodes::KEY_F12)
      .value("key_f13", Hamster::KeyCodes::KEY_F13)
      .value("key_f14", Hamster::KeyCodes::KEY_F14)
      .value("key_f15", Hamster::KeyCodes::KEY_F15)
      .value("key_f16", Hamster::KeyCodes::KEY_F16)
      .value("key_f17", Hamster::KeyCodes::KEY_F17)
      .value("key_f18", Hamster::KeyCodes::KEY_F18)
      .value("key_f19", Hamster::KeyCodes::KEY_F19)
      .value("key_f20", Hamster::KeyCodes::KEY_F20)
      .value("key_f21", Hamster::KeyCodes::KEY_F21)
      .value("key_f22", Hamster::KeyCodes::KEY_F22)
      .value("key_f23", Hamster::KeyCodes::KEY_F23)
      .value("key_f24", Hamster::KeyCodes::KEY_F24)
      .value("key_f25", Hamster::KeyCodes::KEY_F25)

      .value("key_kp_0", Hamster::KeyCodes::KEY_KP_0)
      .value("key_kp_1", Hamster::KeyCodes::KEY_KP_1)
      .value("key_kp_2", Hamster::KeyCodes::KEY_KP_2)
      .value("key_kp_3", Hamster::KeyCodes::KEY_KP_3)
      .value("key_kp_4", Hamster::KeyCodes::KEY_KP_4)
      .value("key_kp_5", Hamster::KeyCodes::KEY_KP_5)
      .value("key_kp_6", Hamster::KeyCodes::KEY_KP_6)
      .value("key_kp_7", Hamster::KeyCodes::KEY_KP_7)
      .value("key_kp_8", Hamster::KeyCodes::KEY_KP_8)
      .value("key_kp_9", Hamster::KeyCodes::KEY_KP_9)
      .value("key_kp_decimal", Hamster::KeyCodes::KEY_KP_DECIMAL)
      .value("key_kp_divide", Hamster::KeyCodes::KEY_KP_DIVIDE)
      .value("key_kp_multiply", Hamster::KeyCodes::KEY_KP_MULTIPLY)
      .value("key_kp_subtract", Hamster::KeyCodes::KEY_KP_SUBTRACT)
      .value("key_kp_add", Hamster::KeyCodes::KEY_KP_ADD)
      .value("key_kp_enter", Hamster::KeyCodes::KEY_KP_ENTER)
      .value("key_kp_equal", Hamster::KeyCodes::KEY_KP_EQUAL)
      .value("key_left_shift", Hamster::KeyCodes::KEY_LEFT_SHIFT)
      .value("key_left_control", Hamster::KeyCodes::KEY_LEFT_CONTROL)
      .value("key_left_alt", Hamster::KeyCodes::KEY_LEFT_ALT)
      .value("key_left_super", Hamster::KeyCodes::KEY_LEFT_SUPER)
      .value("key_right_shift", Hamster::KeyCodes::KEY_RIGHT_SHIFT)
      .value("key_right_control", Hamster::KeyCodes::KEY_RIGHT_CONTROL)
      .value("key_right_alt", Hamster::KeyCodes::KEY_RIGHT_ALT)
      .value("key_right_super", Hamster::KeyCodes::KEY_RIGHT_SUPER)
      .value("key_menu", Hamster::KeyCodes::KEY_MENU);
}

#endif // !INPUT_H
