/*
 * winfrip_general.c - pointless frippery & tremendous amounts of bloat
 * Copyright (c) 2018 Lucio Andrés Illanes Albornoz <lucio@lucioillanes.de>
 */

#include "putty.h"
#include "dialog.h"
#include "FySTY/winfrip.h"
#include "FySTY/winfrip_priv.h"

/*
 * Public subroutines private to FySTY/winfrip*.c
 */

void winfripp_general_config_panel(struct controlbox *b)
{
    struct controlset *s;


    WINFRIPP_DEBUG_ASSERT(b);

    /*
     * The Frippery: general panel.
     */

    ctrl_settitle(b, "Frippery", "Configure pointless frippery: general frippery");
    s = ctrl_getset(b, "Frippery", "frip", "General pointless frippery");
    ctrl_radiobuttons(s, "Always on top:", NO_SHORTCUT, 4, P(WINFRIPP_HELP_CTX),
		      conf_radiobutton_handler, I(CONF_frip_general_always_on_top),
		      "Never",	NO_SHORTCUT,	I(WINFRIPP_GENERAL_ALWAYS_ON_TOP_NEVER),
		      "Always",	NO_SHORTCUT,	I(WINFRIPP_GENERAL_ALWAYS_ON_TOP_ALWAYS), NULL);
    ctrl_radiobuttons(s, "Filter U+202[89] separators on output:", NO_SHORTCUT, 4, P(WINFRIPP_HELP_CTX),
		      conf_radiobutton_handler, I(CONF_frip_general_filter_separators),
		      "No",	NO_SHORTCUT,	I(WINFRIPP_GENERAL_FILTER_SEPARATORS_NO),
		      "Yes",	NO_SHORTCUT,	I(WINFRIPP_GENERAL_FILTER_SEPARATORS_YES), NULL);
    ctrl_radiobuttons(s, "Storage backend:", NO_SHORTCUT, 2, P(WINFRIPP_HELP_CTX),
		      conf_radiobutton_handler, I(CONF_frip_general_store_backend),
		      "Registry",	NO_SHORTCUT,	I(WINFRIP_GENERAL_STORE_BACKEND_REGISTRY),
		      "Ephemeral",	NO_SHORTCUT,	I(WINFRIP_GENERAL_STORE_BACKEND_EPHEMERAL),
		      "File",		NO_SHORTCUT,	I(WINFRIP_GENERAL_STORE_BACKEND_FILE), NULL);
}

/*
 * Public subroutines
 */

void winfrip_general_op(WinFripGeneralOp op, Conf *conf, HWND hwnd, int reconfiguring)
{
    /*
     * XXX document
     */
    switch (op) {
    default:
	WINFRIPP_DEBUG_FAIL(); break;

    /*
     * XXX document
     */
    case WINFRIP_GENERAL_OP_CONFIG_DIALOG:
	switch (conf_get_int(conf, CONF_frip_general_always_on_top)) {
	default:
	    WINFRIPP_DEBUG_FAIL(); break;
	case WINFRIPP_GENERAL_ALWAYS_ON_TOP_NEVER:
	    break;
	case WINFRIPP_GENERAL_ALWAYS_ON_TOP_ALWAYS:
	    SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	    break;
	}
	break;

    /*
     * XXX document
     */
    case WINFRIP_GENERAL_OP_FOCUS_SET:
	if (reconfiguring) {
	    break;
	}
	switch (conf_get_int(conf, CONF_frip_general_always_on_top)) {
	default:
	    WINFRIPP_DEBUG_FAIL(); break;
	case WINFRIPP_GENERAL_ALWAYS_ON_TOP_NEVER:
	    SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	    break;
	case WINFRIPP_GENERAL_ALWAYS_ON_TOP_ALWAYS:
	    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	    break;
	}
	break;
    }
}
