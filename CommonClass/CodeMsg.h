#ifndef CODEMSG_H
#define CODEMSG_H

#include <string>

using namespace std;

// 定义一个PackageCode及其表示的意思
#ifndef DEFINE_PACK_CODE
#define DEFINE_PACK_CODE(code,msg)\
	 {CodeMsg::code,(msg)}
#endif 


// 控制包类型（可以根据需要往里面添加自己的类型）
struct CodeMsg
{
    

	enum PackageCode
	{
		code_unknown,								// 未知

		// 控制类型的代码- begin
		code_login,									// 登陆
		code_login_ret_ok,						// 登陆成功
		code_login_ret_failed,					// 登陆失败

		code_logout,									// 注销

		code_begin_game,						// 开始游戏
		code_begin_game_notification,		// 通知玩家开始游戏

		code_suspend_game,					// 暂停游戏
		code_suspend_game_notification,// 通知玩家暂停游戏

		code_continue_game,					// 继续游戏
		code_continue_game_notification,//通知玩家继续游戏

		code_stop_game,							// 停止游戏
		code_stop_game_notification,		// 通知玩家停止游戏

		code_player_born,
		code_player_request_all_online_players,
		code_player_request_all_online_players_ret,
		code_player_get_player_state,
		code_player_send_state,
		code_player_static,														// 静止
		code_player_walk,															// 走动
		code_player_run,															// 跑动
		code_player_attack,														// 攻击
		code_player_skillattack,													// 特效攻击
		code_player_throwoff = code_player_skillattack,			// 
		code_player_beaten,														// 挨打
		code_player_die,															// 死亡
		code_player_test,															// 测试
		code_monster_static,													// 静止
		code_monster_walk,														// 走动
		code_monster_run,														// 跑动
		code_monster_attack,													// 攻击
		code_monster_bellow,													// 吼叫
		code_monster_bellow2,												// 大声吼叫
		code_monster_dying,													// 正在死亡
		code_monster_die,															// 死亡
		code_monster_test,														// 测试
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
