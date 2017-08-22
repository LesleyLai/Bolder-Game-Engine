#pragma once

/**
 * @file input.hpp
 * Interface of the input handler.
 */

#include "bitset"

namespace bolder { namespace platform {

class Keyboard {
public:
    enum Key {
        unknown = -1, ///< Unhandled key
        a,        ///< The A key
        b,            ///< The B key
        c,            ///< The C key
        d,            ///< The D key
        e,            ///< The E key
        f,            ///< The F key
        g,            ///< The G key
        h,            ///< The H key
        i,            ///< The I key
        j,            ///< The J key
        k,            ///< The K key
        l,            ///< The L key
        m,            ///< The M key
        n,            ///< The N key
        o,            ///< The O key
        p,            ///< The P key
        q,            ///< The Q key
        r,            ///< The R key
        s,            ///< The S key
        t,            ///< The T key
        u,            ///< The U key
        v,            ///< The V key
        w,            ///< The W key
        x,            ///< The X key
        y,            ///< The Y key
        z,            ///< The Z key

        num0,         ///< The 0 key
        num1,         ///< The 1 key
        num2,         ///< The 2 key
        num3,         ///< The 3 key
        num4,         ///< The 4 key
        num5,         ///< The 5 key
        num6,         ///< The 6 key
        num7,         ///< The 7 key
        num8,         ///< The 8 key
        num9,         ///< The 9 key
        escape,       ///< The Escape key

        left_control,     ///< The left Control key
        left_shift,       ///< The left Shift key
        left_alt,         ///< The left Alt key
        left_system,      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
        right_control,    ///< The right Control key
        right_shift,      ///< The right Shift key
        right_alt,        ///< The right Alt key
        right_system,     ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...

        menu,         ///< The Menu key

        left_bracket,    ///< The [ key
        right_bracket,    ///< The ] key

        semi_colon,    ///< The ; key

        comma,        ///< The , key
        period,       ///< The . key
        quote,        ///< The ' key
        slash,        ///< The / key
        back_slash,    ///< The \ key
        tilde,        ///< The ~ key
        equal,        ///< The = key
        dash,         ///< The - key

        space,        ///< The Space key
        return_key,       ///< The Return key
        back_space,    ///< The Backspace key
        tab,          ///< The Tabulation key
        page_up,       ///< The Page up key
        page_down,     ///< The Page down key
        end,          ///< The End key
        home,         ///< The Home key
        insert,       ///< The Insert key
        delete_key,       ///< The Delete key

        add,          ///< The + key
        subtract,     ///< The - key
        multiply,     ///< The * key
        divide,       ///< The / key

        left,         ///< Left arrow
        right,        ///< Right arrow
        up,           ///< Up arrow
        down,         ///< Down arrow

        numpad0,      ///< The numpad 0 key
        numpad1,      ///< The numpad 1 key
        numpad2,      ///< The numpad 2 key
        numpad3,      ///< The numpad 3 key
        numpad4,      ///< The numpad 4 key
        numpad5,      ///< The numpad 5 key
        numpad6,      ///< The numpad 6 key
        numpad7,      ///< The numpad 7 key
        numpad8,      ///< The numpad 8 key
        numpad9,      ///< The numpad 9 key

        F1,           ///< The F1 key
        F2,           ///< The F2 key
        F3,           ///< The F3 key
        F4,           ///< The F4 key
        F5,           ///< The F5 key
        F6,           ///< The F6 key
        F7,           ///< The F7 key
        F8,           ///< The F8 key
        F9,           ///< The F9 key
        F10,          ///< The F10 key
        F11,          ///< The F11 key
        F12,          ///< The F12 key

        pause, ///< The Pause key

        key_count, ///< Count of the keys
    };

private:
    std::bitset<key_count> keys_;
};

}}
