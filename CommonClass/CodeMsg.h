#ifndef CODEMSG_H
#define CODEMSG_H

#include <string>

using namespace std;

// ����һ��PackageCode�����ʾ����˼
#ifndef DEFINE_PACK_CODE
#define DEFINE_PACK_CODE(code,msg)\
	 {CodeMsg::code,(msg)}
#endif 


// ���ư����ͣ����Ը�����Ҫ����������Լ������ͣ�
struct CodeMsg
{
    

	enum PackageCode
	{
		code_unknown,								// δ֪

		// �������͵Ĵ���- begin
		code_login,									// ��½
		code_login_ret_ok,						// ��½�ɹ�
		code_login_ret_failed,					// ��½ʧ��

		code_logout,									// ע��

		code_begin_game,						// ��ʼ��Ϸ
		code_begin_game_notification,		// ֪ͨ��ҿ�ʼ��Ϸ

		code_suspend_game,					// ��ͣ��Ϸ
		code_suspend_game_notification,// ֪ͨ�����ͣ��Ϸ

		code_continue_game,					// ������Ϸ
		code_continue_game_notification,//֪ͨ��Ҽ�����Ϸ

		code_stop_game,							// ֹͣ��Ϸ
		code_stop_game_notification,		// ֪ͨ���ֹͣ��Ϸ

		code_player_born,
		code_player_request_all_online_players,
		code_player_request_all_online_players_ret,
		code_player_get_player_state,
		code_player_send_state,
		code_player_static,														// ��ֹ
		code_player_walk,															// �߶�
		code_player_run,															// �ܶ�
		code_player_attack,														// ����
		code_player_skillattack,													// ��Ч����
		code_player_throwoff = code_player_skillattack,			// 
		code_player_beaten,														// ����
		code_player_die,															// ����
		code_player_test,															// ����
		code_monster_static,													// ��ֹ
		code_monster_walk,														// �߶�
		code_monster_run,														// �ܶ�
		code_monster_attack,													// ����
		code_monster_bellow,													// ���
		code_monster_bellow2,												// �������
		code_monster_dying,													// ��������
		code_monster_die,															// ����
		code_monster_test,														// ����
		code_boss_static,									
		code_boss_walk,
		code_boss_run,
		code_boss_attack,
	};

	PackageCode				m_nCode;
	string							m_strMsg;

	static string					CodeToMsg(int code);
};

//extern CodeMsg G_CodeMsgMap[];


#endif // CODEMSG_H
