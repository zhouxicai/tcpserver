/**
* net_protocol_command.h : 服务器的命令字定义文件.
* @author：pengyuan
* @date：2011.10.22
* @备注：
* */

#ifndef    __NET_PROTOCOL_COMMAND_H__
#define    __NET_PROTOCOL_COMMAND_H__

#pragma warning(once:4996)
//////////////////////////////////////////////////////////////////////////
// 常量定义
#define    MAX_NICKNAME_LENGTH              32             //昵称最大长度

#define    MAX_SLAVE_COUNT                  12             //拥有的最大奴隶数

#define    BATTLE_RESULT_WIN                1              //游戏结果为胜利
#define    BATTLE_RESULT_LOSE               2              //游戏结果为失败

#define    PACKET_HEAD_LENGTH               24             //彭渊2014.8.15 在lua下面包头长度改为24个字节

#define    MAX_ITEM_COUNT                   256            //pengyuan 2014.8.20 一个玩家拥有的最多道具数目
#define    MAX_GENERAL_IN_BATTLE            4              //一个主角出战能携带的最大将领数
#define    MAX_GENERAL_COUNT_PER_PLAYER     30             //每个将领所能拥有的最大将领数目
#define    MAX_EQUIP_COUNT_PER_PLAYER       6              //一个主角或者将领身上能穿的最大装备数目

//////////////////////////////////////////////////////////////////////////
// 以下是服务器之间通信的协议定义
#define    MSG_ID_NEW_PLAYER_CONNECT        101            //新连接连上来了，login到game
#define    MSG_ID_PLAYER_BASE_INFO          103            //login发送玩家基本数据给game服务器

//////////////////////////////////////////////////////////////////////////
// 以下是登录服务器定义
#define    MSG_ID_REQUEST_LOGIN             1001           //请求登录
#define    MSG_ID_RESPONSE_LOGIN            1002           //请求登录回应
#define    MSG_ID_NOTIFY_PLAYER_BASEINFO    1003           //通知玩家基本信息
#define    MSG_ID_REQUEST_REGISTER          1005           //请求注册
#define    MSG_ID_RESPONSE_REGISTER     	1006           //回应注册
#define    MSG_ID_REQUEST_CREATE_CHARACTER  1007           //请求创建角色
#define    MSG_ID_RESPONSE_CREATE_CHARACTER 1008           //回应角色创建



//////////////////////////////////////////////////////////////////////////
//以下是跟游戏服务器通信的命令字
#define    MSG_ID_REQUEST_GAME_LOGIN                       2001         //请求登录游戏服务器
#define    MSG_ID_RESPONSE_GAME_LOGIN                      2002         //请求登录游戏服务器回应

#define    MSG_ID_REQUEST_GAME_HEARTBEAT                   2003         //客户端发送心跳包请求
#define    MSG_ID_RESPONSE_GAME_HEARTBEAT                  2004         //对客户端发送的心跳包的回应

#define    MSG_ID_REQUEST_CHAT                             2011         //请求聊天
#define    MSG_ID_NOTIFY_CHAT                              2012         //通知聊天消息

#define    MSG_ID_REQUEST_WALK                             2013         //请求玩家行走信息
#define    MSG_ID_RESPONSE_WALK                            2014			//请求玩家行走信息回应
#define    MSG_ID_NOTIFY_WALK                              2015	     	//通知玩家行走信息


#define    MSG_ID_NOTIFY_PLAYER_ENTER_GAME                 2017         //通知有玩家进入

#define    MSG_ID_NOTIFY_PLAYER_ENTER_REGION               2019         //广播消息，通知新玩家进到同步域

#define    MSG_ID_NOTIFY_PLAYER_LEAVE_REGION               2021         //广播消息，通知新玩家离开同步域

#define    MSG_ID_NOTIFY_PLAYER_LOGOUT                     2023         //广播消息，通知有玩家离开游戏

#define    MSG_ID_NOTIFY_ALL_NPC_INFO                      2025         //通知地图上所有npc的信息

#define    MSG_ID_REQUEST_TELEPORT                         2027         //请求地图跳转
#define    MSG_ID_RESPONSE_TELEPORT                        2028         //回应地图跳转


#define    MSG_ID_NOTIFY_ROLE_TASK_DATA                    2032			//玩家登陆游戏时发送该玩家的任务数据
#define    MSG_ID_NOTIFY_ROLE_TASK_STATUS                  2034			//通知玩家任务更新
#define    MSG_ID_NOTIFY_ROLE_FINISH_TASK_INFO             2036         //通知玩家完成任务的信息
#define    MSG_ID_REQUEST_GET_TASK                         2041			//请求接任务消息
#define    MSG_ID_RESPONSE_GET_TASK                        2042			//请求接任务返回消息
#define    MSG_ID_REQUEST_FINISH_TASK                      2043			//请求提交任务消息
#define    MSG_ID_RESPONSE_FINISH_TASK                     2044			//请求提交任务消息返回
#define    MSG_ID_REQUEST_DROP_TASK                        2045 		//请求放弃任务消息
#define    MSG_ID_RESPONSE_DROP_TASK                       2046			//请求放弃任务消息返回

#define    MSG_ID_NOTIFY_ATTRIBUTE_UPDATE                  2051         //广播消息，通知玩家属性更新

#define    MSG_ID_REQUEST_CHALLENGE                        2053         //一个玩家请求挑战另外一个玩家
#define    MSG_ID_RESPONSE_CHALLENGE                       2054         //对这个玩家请求的回应

#define    MSG_ID_REQUEST_ROUND                            2055         //请求某回合开始
#define    MSG_ID_RESPONSE_ROUND                           2056         //服务器对请求回合的回应

#define    MSG_ID_NOTIFY_ROUND_END                         2057         //通知回合结束

#define    MSG_ID_REQUEST_BATTLE                           2059         //请求战斗
#define    MSG_ID_RESPONSE_BATTLE                          2060         //回应战斗

#define    MSG_ID_NOTIFY_PLAYER_ITEM_INFO                  2061			//下发玩家道具信息

#define    MSG_ID_NOTIFY_PLAYER_ITEM_UPDATE                2063		    //下发玩家道具信息数量的更新

#define    MSG_ID_REQUEST_BUY_ITEM                         2065  		//请求购买道具
#define    MSG_ID_RESPONSE_BUY_ITEM                        2066			//回应购买道具结果

#define    MSG_ID_REQUEST_USE_ITEM                         2067 		//请求使用道具
#define    MSG_ID_RESPONSE_USE_ITEM                        2068		    //回应使用道具结果


#define    MSG_ID_REQUEST_SELL_ITEM                        2069          //请求出售道具
#define    MSG_ID_RESPONSE_SELL_ITEM                       2070          //请求出售道具的回应

#define    MSG_ID_REQUEST_RANDOM_EVENTS                    2073      	 //请求随机事件
#define    MSG_ID_RESPONSE_RANDOM_EVENTS                   2074          //回应随机事件

#define    MSG_ID_REQUEST_CHALLENGE_INFO                   2075          //请求挑战玩家数据
#define    MSG_ID_RESPONSE_CHALLENGE_INFO                  2076          //获取单个挑战玩家数据
#define    MSG_ID_REQUEST_CHALLENGE_INFOS                  2077          //请求挑战玩家数据
#define    MSG_ID_RESPONSE_CHALLENGE_INFOS                 2078          //获取6个挑战玩家数据

#define    MSG_ID_NOTIFY_FRIEND_INFOS 			           2081			 //服务器下发所有好友数据
#define    MSG_ID_REQUEST_FRIEND_INFOS 		               2083			 //刷新好友列表
#define    MSG_ID_RESPONSE_FRIEND_INFOS 		           2084			 //回应好友列表
#define    MSG_ID_REQUEST_ADD_FRIEND 			           2085			 //请求添加好友
#define    MSG_ID_RESPONSE_ADD_FRIEND 			           2086			 //回应添加好友	
#define    MSG_ID_REQUEST_DELETE_FRIEND 		           2087			 //请求删除好友
#define    MSG_ID_RESPONSE_DELETE_FRIEND 		           2088			 //回应删除好友
#define    MSG_ID_REQUEST_FRIEND_INFO 		               2089			 //请求单个好友信息
#define    MSG_ID_RESPONSE_FRIEND_INFO 		               2090			 //回应单个好友数据的结构体

#define    MSG_ID_NOTIFY_DECORATIVE_INFOS                  2091          //装饰

#define    MSG_ID_REQUEST_FEEDING                          2093	         //请求喂食
#define    MSG_ID_RESPONSE_FEEDING                         2094	         //回应喂食

#define    MSG_ID_REQUEST_CLEANING                         2095          //请求喂食
#define    MSG_ID_RESPONSE_CLEANING                        2096          //回应喂食

#define    MSG_ID_REQUEST_PLAYING                          2097          //请求玩耍
#define    MSG_ID_RESPONSE_PLAYING                         2098          //回应玩耍

#define    MSG_ID_NOTIFY_EQUIP_INFOS                       2111          //广播装备信息
#define    MSG_ID_REQUEST_UNEQUIP                          2113          //请求脱装备
#define    MSG_ID_RESPONSE_UNEQUIP                         2114          //回应脱装备
#define    MSG_ID_NOTIFY_EQUIP_CHANGE                      2117          //通知穿装备

#define    MSG_ID_REQUEST_PICK_SHIT                        2121          //请求捡屎的协议
#define    MSG_ID_RESPONSE_PICK_SHIT                       2122          //请求捡屎的回应

#define    MSG_ID_REQUEST_VISIT_HOME                       2123          //互访数据
#define    MSG_ID_RESPONSE_VISIT_HOME                      2124          //回应互访
#define    MSG_ID_NOTIFY_VISIT_HOME                        2125          //下发互相玩家的数据
#define    MSG_ID_NOTIFY_HOME_DECORATE_INFO                2127          //下发互相玩家装饰协议

#define    MSG_ID_REQUEST_GOHOME                           2131          //请求回家
#define    MSG_ID_RESPONSE_GOHOME                          2132          //回应回家

#define    MSG_ID_REQUEST_WALKDOG                          2133          //请求遛狗
#define    MSG_ID_RESPONSE_WALKDOG                         2134          //回应遛狗
#define    MSG_ID_REQUEST_DICE                             2135          //请求掷骰子
#define    MSG_ID_RESPONSE_DICE                            2136          //回应掷骰子
#define    MSG_ID_REQUEST_DICE_REWARD                      2137          //请求掷骰子奖励
#define    MSG_ID_RESOPNSE_DICE_REWARD                     2138          //回应掷骰子奖励
#define    MSG_ID_REQUEST_REDICE                           2139          //请求重掷，选点
#define    MSG_ID_RESPONSE_REDICE                          2140          //回应重掷，选点

#define    MSG_ID_REQUEST_PVE_MAPINFOS                     2141          //请求PVE的占领者
#define    MSG_ID_RESPONSE_PVE_MAPINFOS                    2142          //回应PVE的占领者

#define    MSG_ID_REQUEST_OCCUPY_BATTLE                    2143          //请求抢占
#define    MSG_ID_RESPONSE_OCCUPY_BATTLE                   2144          //回应抢占
#define    MSG_ID_NOTIFY_OCCUPY_CHANGE                     2145          //广播抢占

#define    MSG_ID_NOTIFY_PLAYER_GENERAL_INFOS              2153          //通知玩家所有的将领信息

#define    MSG_ID_REQUEST_GENERAL_POSITION                 2161			 //发送将领站位信息到服务器
#define    MSG_ID_RESPONSE_GENERAL_POSITION                2162          //站位信息回复

#define    MSG_ID_REQUEST_GENERAL_EQUIP_CHANGE             2165          //将领装备更改请求
#define    MSG_ID_RESPONSE_GENERAL_EQUIP_CHANGE            2166          //将领装备更改回应

#define    MSG_ID_NOTIFY_BATTLE_RESULT                     2251          //广播战斗奖励

#define    MSG_ID_REQUEST_EQUIP_COMPOUND                   2253          //请求制造装备
#define    MSG_ID_RESPONSE_EQUIP_COMPOUND                  2254          //回应制造装备
#define    MSG_ID_REQUEST_EQUIP_ENFORCE                    2255          //请求强化装备
#define    MSG_ID_RESPONSE_EQUIP_ENFORCE                   2256          //回应强化装备

#define    MSG_ID_REQUEST_ADD_ATTRPOINT                    2261          //请求加属性点
#define    MSG_ID_RESPONSE_ADD_ATTRPOINT                   2262          //回应加属性点

#define    MSG_ID_REQUEST_WORK_BEGIN                       2263          //请求打工
#define    MSG_ID_RESPONSE_WORK_BEGIN                      2264          //回应打工
#define    MSG_ID_REQUEST_WORK_END                         2265          //请求结束打工
#define    MSG_ID_RESPONSE_WORK_END                        2266          //回应结束打工

#define    MSG_ID_NOTIFY_SLAVE_INFOS                       2271          //广播奴隶改变信息
#define    MSG_ID_REQUEST_ADD_SLAVE                        2273          //请求获取奴隶信息
#define    MSG_ID_RESPONSE_ADD_SLAVE                       2274          //回应获取奴隶信息
#define    MSG_ID_REQUEST_DELETE_SLAVE                     2275          //请求删除奴隶
#define    MSG_ID_RESPONSE_DELETE_SLAVE                    2276          //请求删除奴隶

#define    MSG_ID_REQUEST_CLEAR_CD                         2281          //请求秒CD
#define    MSG_ID_RESPONSE_CLEAR_CD                        2282          //回应秒CD

#define    MSG_ID_NOTIFY_HUNTING_END                       2291          //广播捕猎结束
#define    MSG_ID_REQUEST_BEGIN_HUNTING                    2293          //请求开始捕猎
#define    MSG_ID_RESPONSE_BEGIN_HUNTING                   2294          //回应捕猎
#define    MSG_ID_REQUEST_HUNTING_MONSTER                  2295          //请求抓怪
#define    MSG_ID_RESPONSE_HUNTING_MONSTER                 2296          //回应抓怪

#define    MSG_ID_NOTIFY_SYSTEM_INFOS                      2333          //登录广播信息
#define    MSG_ID_NOTIFY_SYSTEM_INFO                       2335          //单个广播信息

#define    MSG_ID_NOTIFY_PET_INFOS                         2341          //通知宠物信息
#define    MSG_ID_NOTIFY_ADD_PET                           2343          //通知增加宠物
#define    MSG_ID_NOTIFY_UPDATE_PET_INFOS				   2345			 //通知宠物信息更新

#define    MSG_ID_REQUEST_PET_FIGHT                        2351			 //请求出战
#define    MSG_ID_RESPONSE_PET_FIGHT					   2352			 //回应出战
#define    MSG_ID_REQUEST_PET_UNFIGHT					   2353			 //请求召回
#define    MSG_ID_RESPONSE_PET_UNFIGHT					   2354			 //回应召回 
#define    MSG_ID_REQUEST_PET_RELEASE					   2355			 //请求放生
#define    MSG_ID_RESPONSE_PET_RELEASE					   2356			 //回应放生
#define    MSG_ID_REQUEST_PET_SUCCINCT					   2357			 //请求洗练
#define    MSG_ID_RESPONSE_PET_SUCCINCT					   2358			 //回应洗练


#define    MSG_ID_REQUEST_BATTLE_ROUND                     2361           //请求单回合
#define    MSG_ID_RESPONSE_BATTLE_ROUND                    2362           //回应单回合
#define    MSG_ID_NOTIFY_BATTLE_END                        2363           //通知战斗结束

#define    MSG_ID_REQUEST_EQUIP_PUNCH                            2371           //请求打孔
#define    MSG_ID_RESPONSE_EQUIP_PUNCH					       2372           //回应打孔
#define    MSG_ID_REQUEST_EQUIP_MOSAIC						   2373           //请求镶嵌
#define    MSG_ID_RESPONSE_EQUIP_MOSAIC					       2374           //回应镶嵌

#define    MSG_ID_REQUEST_EXIT_DUPLICATE                   2601           //请求退出副本地图
#define    MSG_ID_RESPONSE_EXIT_DUPLICATE                  2602           //回应退出副本地图


//////////////////////////////////////////////////////////////////////////
//随机事件系统的功能枚举定义
#define    EVENT_FUNCTION_ATTR                             1             //随机事件功能是改变属性
#define    EVENT_FUNCTION_ITEM                             2             //随机事件功能是改变道具
#define    EVENT_FUNCTION_MYSTERY_SHOP                     3             //神秘商店
#define    EVENT_FUNCTION_RANDOM_REWARD                    4             //随机翻牌奖励

//////////////////////////////////////////////////////////////////////////
//以下是各种属性最大值定义
#define    MAX_HUNGRY_VALUE                                100           //饥饿值最大值
#define    MAX_CLEAN_VALUE                                 100           //清洁值最大值
#define    MAX_MOOD_VALUE                                  100           //心情值最大值

//////////////////////////////////////////////////////////////////////////
//以下是人物属性枚举类型定义
#define    ATTR_EXPERIENCE                                 1            //经验值
#define    ATTR_GOLD                                       2            //金币
#define    ATTR_HONOR                                      3            //声望
#define    ATTR_YUANBAO                                    4            //元宝
#define    ATTR_ATTACK                                     5            //攻击
#define    ATTR_DEFENSE                                    6            //防御
#define    ATTR_AGILE                                      7            //敏捷
#define    ATTR_INTELLIGENCE                               8            //智力
#define    ATTR_STRENGTH                                   9            //体力
#define    ATTR_VIGOR                                      10           //活力
#define    ATTR_HUNGER                                     11           //饥饿
#define    ATTR_CLEAN                                      12           //清洁
#define    ATTR_MOOD                                       13           //心情
#define    ATTR_LEVEL                                      14           //等级
#define    ATTR_FLOURISH                                   15           //繁荣度
#define    ATTR_ATTRPOINT                                  16           //属性点
#define    ATTR_HOME_LEVELUP                               17           //狗窝升级
#define    ATTR_DOUBLEHIT                                  20           //暴击
#define    ATTR_TOUGHNESS                                  21           //韧性
#define    ATTR_HIT_VALUE                                  22           //命中数值
#define    ATTR_HP_VALUE                                   23           //气血数值
#define    ATTR_RUNAROUND_VALUE                            24           //闪避数值
#define    ATTR_SPEED_VALUE                                25           //速度数值

#define    ATTR_DECO_VALUE_BASE                            30           //所有的装饰数值的基准点
#define    ATTR_ADD_FEED_VALUE                             31           //狗盆加数值
#define    ATTR_ADD_CLEAN_VALUE                            32           //浴室加数值
#define    ATTR_ADD_PLAY_VALUE                             33           //玩耍加数值

#define    ATTR_EQUIP_COMPOUND                             40           //zhuangbaizhizuojuan 

#define    ATTR_ADD_SELECT_DICE                            50           //选点
#define    ATTR_ADD_REDICE                                 51           //重掷

#define    ITEM_FUNCTION_ADD_PET                           60           //新增宠物

//////////////////////////////////////////////////////////////////////////
//以下是npc对话框功能定义
#define    NPC_DIALOG_FUNC_SHOP                            1             //商店
#define    NPC_DIALOG_FUNC_HUNTING                         2             //打猎

//////////////////////////////////////////////////////////////////////////
//以下是错误码枚举定义
#define    ERROR_MSG_INSUFFICIENT                           1            //金币不足
#define    ERROR_MSG_ITEM_NOTFOUND                          2            //道具数目不足
#define    ERROR_MSG_USEITEM_ERROR                          3            //使用道具失败
#define    ERROR_MSG_ITEM_INFO_ERROR                        4            //道具信息错误
#define    ERROR_MSG_IDORCOUNT_ERROR                        5            //道具ID错误或者数目不够
#define    ERROR_MSG_BAG_FULL                               6            //背包满了
#define    ERROR_MSG_YUANBAO_INSUFFICIENT                   7            //元宝不足


//任务相关错误码
#define    ERROR_MSG_TASK_ALREADY_EXIST                     10           //该任务已存在
#define    ERROR_MSG_TASK_NOT_EXIST                         11           //该任务不存在
#define    ERROR_MSG_TASK_ACCEPT_ERROR                      12           //任务接取条件错误
#define    ERROR_MSG_TASK_UNACCEPTED                        13           //该任务未接取
#define    ERROR_MSG_TASK_CANNOT_FINISH                     14           //该任务完成条件未达到
#define    ERROR_MSG_TASK_DAILY_NOTOK                       15           //日常任务全部完成或已存在

//好友相关错误码
#define    ERROR_MSG_FRIEND_COUNT_MAX                       20           //好友数目达到最大
#define    ERROR_MSG_FRIEND_ALREADY_EXIST                   21           //好友已经存在

//奴隶操作相关错误码
#define    ERROR_MSG_SLAVE_COUNT_MAX                        30           //奴隶数目达到最大
#define    ERROR_MSG_SLAVE_ALREADY_EXIST                    31           //奴隶已经存在
#define    ERROR_MSG_SLAVE_NOT_EXIST                        32           //该奴隶不存在
#define    ERROR_MSG_SLAVE_WORKID_ERROR                     33           //打工类型不存在
#define    ERROR_MSG_SLAVE_LEVEL_LOW                        34           //该奴隶等级不足
#define    ERROR_MSG_SLAVE_WORKINFO_ERROR                   35           //该奴隶打工信息错误
#define    ERROR_MSG_SLAVE_WORKTIME_NOTOVER                 36           //打工还未结束
#define    ERROR_MSG_CLEARCD_NOT_NEED                       37           //CD时间已到，不需要清除

#define    ERROR_MSG_USER_EXIST                             100          //该用户名已存在
#define    ERROR_MSG_USER_NOTEXIST                          101          //该用户不存在
#define    ERROR_MSG_LOGIN_FAIL                             102          //登陆失败
#define    ERROR_MSG_USER_OR_PWD_ERROR                      103          //用户名或密码错
#define    ERROR_MSG_CONNECT_OUTTIME                        104          //注册超时，
#define    ERROR_MSG_LOGIN_OUTTIME                          105          //登陆超时
#define    ERROR_MSG_QUERY_FAIL                             106          //查询失败

#define    ERROR_MSG_INSUFFICIENT_ATTRPOINT                 110          //属性点不足

//日常操作相关错误码
#define    ERROR_MSG_MODEL_UNEXIST                          150          //该模型不存在
#define    ERROR_MSG_FEED_NOTENOUGH                         151          //食物不足
#define    ERROR_MSG_CLEAN_NOTENOUGH                        152          //清洁不足
#define    ERROR_MSG_PLAYING_NOTENOUGH                      153          //玩耍不足

//遛狗相关错误码
#define    ERROR_MSG_WALKDOG_FINISHED                       160          //遛狗地图结束
#define    ERROR_MSG_INSUFFICIENT_STRENGTH                  161          //体力不足

//装备相关错误码
#define    ERROR_MSG_EQUIP_UNEXIST                          161          //不存在该类型的装备

#define    ERROR_MSG_EQUIP_EXIST                            163          //装备已存在

//pve相关错误码
#define    ERROR_MSG_MAPID_INDEX_ERROR                      170          //地图id或者索引错误

//装备打造合成相关错误码
#define    ERROR_MSG_COMPOUND_INFO_ERROR                    180          //装备打造信息上传错误
#define    ERROR_MSG_INSUFFICIENT_MATERIAL                  181          //材料不足
#define    ERROR_MSG_EQUIPENFORCE_INFO_ERROR                183          //装备信息错误
#define    ERROR_MSG_EQUIP_PUNCH_ERROR                      184          //装备打孔信息错误
#define    ERROR_MSG_EQUIP_ALREADY_PUNCHED                  185          //该位置已开孔
#define    ERROR_MSG_EQUIP_ALREADY_MOASICED                 186          //该位置已镶嵌
#define    ERROR_MSG_EQUIP_MAX_MOASICED                     187          //孔数目不够，请先开孔再镶嵌

//捕猎相关错误码
#define    ERROR_MSG_MONSTER_NOTEXIST                       190          //该怪物不存在
//pengyuan 2012.10.25 通用提示字符
#define    PROMPT_MSG_FINISHED                              200
#define    PROMPT_MSG_ENTER_MAP                             201
#define    PROMPT_MSG_LOADING_MAP                           202
#define    PROMPT_MSG_CONNECT_SERVER                        203
#define    PROMPT_ATTR_BASE									210
#define	   PROMPT_MSG_USE_LV								226
#define	   PROMPT_TASK_ACCEPTED								227
#define	   PROMPT_TASK_FINISHED								228
#define	   PROMPT_TASK_NONE									229
#define    PROMPT_ITEM_PRICE							    230  //装备售价
#define    PROMPT_ITEM_ATTR							        231  //装备属性
#define    PROMPT_EXTRA_ATTR							    232  //附加属性
#define    PROMPT_GEMSTONE							        233  //镶嵌宝石

#define    ERROR_RESULT                                     254          //通用错误，具体错误类型见后面的错误码

#define    OCCUPY_NPC                                       1            //抢占NPC
#define    OCCUPY_PLAYER                                    2            //抢占玩家

//pengyuan 2012.9.6 清除CD类别定义
#define    CLEAR_CD_WORK                                    1            //清除打工cd
#define    CLEAR_CD_EQUIP                                   2            //清除强化装备的cd
#define    CLEAR_CD_PVE                                     3            //清除PVEcd


//pengyuan 2012.9.19 
#define    MAX_HUNTING_MONSTER_COUNT                        8             //捕猎地图中最大的怪物数目


//pengyuan 2012.11.20
#define    MAX_PET_COUNT                                    3
#define    MAX_PET_SKILL_COUNT                              8

#define    EFFECT_LEVEL_UP                                  1            //升级特效
#define    EFFECT_FINISH_TASK                               2            //完成任务特效
#define    EFFECT_ACCEPT_TASK                               3            //接取任务特效
#define    EFFECT_ATTACK_1                                  4            //攻击特效1
#define    EFFECT_ATTACK_2                                  5            //攻击特效2
#define    EFFECT_ATTACK_PROMPT                             6            //攻击提示

/////////////////////////////////////////////////////////////////////////
// 以下是一些loginserver和gameserver共用的结构体的定义
typedef struct tagModelInfo
{
	unsigned int model_id;
	int          pos_x;
	int          pos_y;
	unsigned int dwValue;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &model_id, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &pos_x, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &pos_y, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &dwValue, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&model_id, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&pos_x, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&pos_y, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&dwValue, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}MODEL_INFO, *pMODEL_INFO;


typedef struct tagNPCInfo
{
	unsigned int   dwID;                      //唯一标识
	int            nModelID;                   //模型ID
	unsigned char  nLevel;                     //等级
	char   nCareer;                    //职业
	char   byNickNameLength;           //昵称长度
	char   szNickName[16];             //昵称
	char   byGender;                   //性别
	int    nMapID;                     //地图ID
	int    nMapPosX;                 //地图位置X
	int    nMapPosY;                 //地图位置Y
	unsigned int dwHP;                 //生命值
	unsigned int dwAttack;             //攻击
	unsigned int dwDefense;            //防御
	unsigned int dwAgile;              //敏捷
	unsigned int dwIntelligence;       //智力
	unsigned int dwStrength;           //体力
	unsigned int dwDoubleHit;          //暴击
	unsigned int dwToughness;          //韧性
	unsigned int dwHit;                //命中
	unsigned int dwRunaround;          //闪避
}NPC_INFO, *pNPC_INFO;


typedef struct tagPVEPointInfo
{
	int    nID;
	unsigned int dwNPCID;
	int    nLevelMin;
	int    nLevelMax;
	int    nPosX;
	int    nPosY;
	int    nMat1;
	int    nMat2;
	int    nMat3;
	int    nScroll;
	unsigned int    dwOccupyer;        //占有者Uin
	unsigned int    dwFlourish;        //繁荣度

#ifdef __WINDOWS__
	unsigned int   dwLastHarvestTime; //上次征收时间
#endif

#ifdef __LINUX__
	unsigned int   dwLastHarvestTime; //上次征收时间
#endif

	
}PVE_POINT_INFO, *pPVE_POINT_INFO;

//pengyuan 2012.7.18 pve信息
typedef struct tagPVEMapInfo
{
	int    nMapID;
	int    nPointCount;
	PVE_POINT_INFO  szPointInfos[16];
}PVE_MAP_INFO, *pPVE_MAP_INFO;


#define    MAX_MY_BATTLE_COUNT          2
#define    MAX_OFFENDER_BATTLE_COUNT    4

#define    MAX_PUNCH_COUNT              4
#define    GOLD_FOR_FIRST_PUNCH         500

#endif