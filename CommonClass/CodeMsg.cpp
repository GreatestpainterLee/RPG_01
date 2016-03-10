#include "CodeMsg.h"

CodeMsg G_CodeMsgMap[] =
{
	DEFINE_PACK_CODE(code_unknown,"code_unknown"),
	DEFINE_PACK_CODE(code_login,"code_login"),
	DEFINE_PACK_CODE(code_login_ret_ok,"code_login_ret_ok"),
	DEFINE_PACK_CODE(code_login_ret_failed,"code_login_ret_failed"),
	DEFINE_PACK_CODE(code_logout,"code_logout"),
	DEFINE_PACK_CODE(code_begin_game,"code_begin_game"),
	DEFINE_PACK_CODE(code_suspend_game,"code_suspend_game"),
	DEFINE_PACK_CODE(code_continue_game,"code_continue_game"),
	DEFINE_PACK_CODE(code_stop_game,"code_stop_game"),
	DEFINE_PACK_CODE(code_stop_game_notification,"code_stop_game_notification"),
	DEFINE_PACK_CODE(code_begin_game_notification,"code_begin_game_notification"),
	DEFINE_PACK_CODE(code_suspend_game_notification,"code_suspend_game_notification"),
	DEFINE_PACK_CODE(code_continue_game_notification,"code_continue_game_notification"),
};


string CodeMsg::CodeToMsg(int code)
{
    int count = sizeof(G_CodeMsgMap) / sizeof(CodeMsg);

    for(int i = 0; i < count; ++i)
    {
        if(code == G_CodeMsgMap[i].m_nCode)
        {
            return G_CodeMsgMap[i].m_strMsg;
            break;
        }
    }

    return G_CodeMsgMap[0].m_strMsg;
}
