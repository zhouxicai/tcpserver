/**
* net_protocol_command.h : �������������ֶ����ļ�.
* @author��pengyuan
* @date��2011.10.22
* @��ע��
* */

#ifndef    __NET_PROTOCOL_COMMAND_H__
#define    __NET_PROTOCOL_COMMAND_H__

#pragma warning(once:4996)
//////////////////////////////////////////////////////////////////////////
// ��������
#define    MAX_NICKNAME_LENGTH              32             //�ǳ���󳤶�

#define    MAX_SLAVE_COUNT                  12             //ӵ�е����ū����

#define    BATTLE_RESULT_WIN                1              //��Ϸ���Ϊʤ��
#define    BATTLE_RESULT_LOSE               2              //��Ϸ���Ϊʧ��

#define    PACKET_HEAD_LENGTH               24             //��Ԩ2014.8.15 ��lua�����ͷ���ȸ�Ϊ24���ֽ�

#define    MAX_ITEM_COUNT                   256            //pengyuan 2014.8.20 һ�����ӵ�е���������Ŀ
#define    MAX_GENERAL_IN_BATTLE            4              //һ�����ǳ�ս��Я�����������
#define    MAX_GENERAL_COUNT_PER_PLAYER     30             //ÿ����������ӵ�е��������Ŀ
#define    MAX_EQUIP_COUNT_PER_PLAYER       6              //һ�����ǻ��߽��������ܴ������װ����Ŀ

//////////////////////////////////////////////////////////////////////////
// �����Ƿ�����֮��ͨ�ŵ�Э�鶨��
#define    MSG_ID_NEW_PLAYER_CONNECT        101            //�������������ˣ�login��game
#define    MSG_ID_PLAYER_BASE_INFO          103            //login������һ������ݸ�game������

//////////////////////////////////////////////////////////////////////////
// �����ǵ�¼����������
#define    MSG_ID_REQUEST_LOGIN             1001           //�����¼
#define    MSG_ID_RESPONSE_LOGIN            1002           //�����¼��Ӧ
#define    MSG_ID_NOTIFY_PLAYER_BASEINFO    1003           //֪ͨ��һ�����Ϣ
#define    MSG_ID_REQUEST_REGISTER          1005           //����ע��
#define    MSG_ID_RESPONSE_REGISTER     	1006           //��Ӧע��
#define    MSG_ID_REQUEST_CREATE_CHARACTER  1007           //���󴴽���ɫ
#define    MSG_ID_RESPONSE_CREATE_CHARACTER 1008           //��Ӧ��ɫ����



//////////////////////////////////////////////////////////////////////////
//�����Ǹ���Ϸ������ͨ�ŵ�������
#define    MSG_ID_REQUEST_GAME_LOGIN                       2001         //�����¼��Ϸ������
#define    MSG_ID_RESPONSE_GAME_LOGIN                      2002         //�����¼��Ϸ��������Ӧ

#define    MSG_ID_REQUEST_GAME_HEARTBEAT                   2003         //�ͻ��˷�������������
#define    MSG_ID_RESPONSE_GAME_HEARTBEAT                  2004         //�Կͻ��˷��͵��������Ļ�Ӧ

#define    MSG_ID_REQUEST_CHAT                             2011         //��������
#define    MSG_ID_NOTIFY_CHAT                              2012         //֪ͨ������Ϣ

#define    MSG_ID_REQUEST_WALK                             2013         //�������������Ϣ
#define    MSG_ID_RESPONSE_WALK                            2014			//�������������Ϣ��Ӧ
#define    MSG_ID_NOTIFY_WALK                              2015	     	//֪ͨ���������Ϣ


#define    MSG_ID_NOTIFY_PLAYER_ENTER_GAME                 2017         //֪ͨ����ҽ���

#define    MSG_ID_NOTIFY_PLAYER_ENTER_REGION               2019         //�㲥��Ϣ��֪ͨ����ҽ���ͬ����

#define    MSG_ID_NOTIFY_PLAYER_LEAVE_REGION               2021         //�㲥��Ϣ��֪ͨ������뿪ͬ����

#define    MSG_ID_NOTIFY_PLAYER_LOGOUT                     2023         //�㲥��Ϣ��֪ͨ������뿪��Ϸ

#define    MSG_ID_NOTIFY_ALL_NPC_INFO                      2025         //֪ͨ��ͼ������npc����Ϣ

#define    MSG_ID_REQUEST_TELEPORT                         2027         //�����ͼ��ת
#define    MSG_ID_RESPONSE_TELEPORT                        2028         //��Ӧ��ͼ��ת


#define    MSG_ID_NOTIFY_ROLE_TASK_DATA                    2032			//��ҵ�½��Ϸʱ���͸���ҵ���������
#define    MSG_ID_NOTIFY_ROLE_TASK_STATUS                  2034			//֪ͨ����������
#define    MSG_ID_NOTIFY_ROLE_FINISH_TASK_INFO             2036         //֪ͨ�������������Ϣ
#define    MSG_ID_REQUEST_GET_TASK                         2041			//�����������Ϣ
#define    MSG_ID_RESPONSE_GET_TASK                        2042			//��������񷵻���Ϣ
#define    MSG_ID_REQUEST_FINISH_TASK                      2043			//�����ύ������Ϣ
#define    MSG_ID_RESPONSE_FINISH_TASK                     2044			//�����ύ������Ϣ����
#define    MSG_ID_REQUEST_DROP_TASK                        2045 		//�������������Ϣ
#define    MSG_ID_RESPONSE_DROP_TASK                       2046			//�������������Ϣ����

#define    MSG_ID_NOTIFY_ATTRIBUTE_UPDATE                  2051         //�㲥��Ϣ��֪ͨ������Ը���

#define    MSG_ID_REQUEST_CHALLENGE                        2053         //һ�����������ս����һ�����
#define    MSG_ID_RESPONSE_CHALLENGE                       2054         //������������Ļ�Ӧ

#define    MSG_ID_REQUEST_ROUND                            2055         //����ĳ�غϿ�ʼ
#define    MSG_ID_RESPONSE_ROUND                           2056         //������������غϵĻ�Ӧ

#define    MSG_ID_NOTIFY_ROUND_END                         2057         //֪ͨ�غϽ���

#define    MSG_ID_REQUEST_BATTLE                           2059         //����ս��
#define    MSG_ID_RESPONSE_BATTLE                          2060         //��Ӧս��

#define    MSG_ID_NOTIFY_PLAYER_ITEM_INFO                  2061			//�·���ҵ�����Ϣ

#define    MSG_ID_NOTIFY_PLAYER_ITEM_UPDATE                2063		    //�·���ҵ�����Ϣ�����ĸ���

#define    MSG_ID_REQUEST_BUY_ITEM                         2065  		//���������
#define    MSG_ID_RESPONSE_BUY_ITEM                        2066			//��Ӧ������߽��

#define    MSG_ID_REQUEST_USE_ITEM                         2067 		//����ʹ�õ���
#define    MSG_ID_RESPONSE_USE_ITEM                        2068		    //��Ӧʹ�õ��߽��


#define    MSG_ID_REQUEST_SELL_ITEM                        2069          //������۵���
#define    MSG_ID_RESPONSE_SELL_ITEM                       2070          //������۵��ߵĻ�Ӧ

#define    MSG_ID_REQUEST_RANDOM_EVENTS                    2073      	 //��������¼�
#define    MSG_ID_RESPONSE_RANDOM_EVENTS                   2074          //��Ӧ����¼�

#define    MSG_ID_REQUEST_CHALLENGE_INFO                   2075          //������ս�������
#define    MSG_ID_RESPONSE_CHALLENGE_INFO                  2076          //��ȡ������ս�������
#define    MSG_ID_REQUEST_CHALLENGE_INFOS                  2077          //������ս�������
#define    MSG_ID_RESPONSE_CHALLENGE_INFOS                 2078          //��ȡ6����ս�������

#define    MSG_ID_NOTIFY_FRIEND_INFOS 			           2081			 //�������·����к�������
#define    MSG_ID_REQUEST_FRIEND_INFOS 		               2083			 //ˢ�º����б�
#define    MSG_ID_RESPONSE_FRIEND_INFOS 		           2084			 //��Ӧ�����б�
#define    MSG_ID_REQUEST_ADD_FRIEND 			           2085			 //������Ӻ���
#define    MSG_ID_RESPONSE_ADD_FRIEND 			           2086			 //��Ӧ��Ӻ���	
#define    MSG_ID_REQUEST_DELETE_FRIEND 		           2087			 //����ɾ������
#define    MSG_ID_RESPONSE_DELETE_FRIEND 		           2088			 //��Ӧɾ������
#define    MSG_ID_REQUEST_FRIEND_INFO 		               2089			 //���󵥸�������Ϣ
#define    MSG_ID_RESPONSE_FRIEND_INFO 		               2090			 //��Ӧ�����������ݵĽṹ��

#define    MSG_ID_NOTIFY_DECORATIVE_INFOS                  2091          //װ��

#define    MSG_ID_REQUEST_FEEDING                          2093	         //����ιʳ
#define    MSG_ID_RESPONSE_FEEDING                         2094	         //��Ӧιʳ

#define    MSG_ID_REQUEST_CLEANING                         2095          //����ιʳ
#define    MSG_ID_RESPONSE_CLEANING                        2096          //��Ӧιʳ

#define    MSG_ID_REQUEST_PLAYING                          2097          //������ˣ
#define    MSG_ID_RESPONSE_PLAYING                         2098          //��Ӧ��ˣ

#define    MSG_ID_NOTIFY_EQUIP_INFOS                       2111          //�㲥װ����Ϣ
#define    MSG_ID_REQUEST_UNEQUIP                          2113          //������װ��
#define    MSG_ID_RESPONSE_UNEQUIP                         2114          //��Ӧ��װ��
#define    MSG_ID_NOTIFY_EQUIP_CHANGE                      2117          //֪ͨ��װ��

#define    MSG_ID_REQUEST_PICK_SHIT                        2121          //�����ʺ��Э��
#define    MSG_ID_RESPONSE_PICK_SHIT                       2122          //�����ʺ�Ļ�Ӧ

#define    MSG_ID_REQUEST_VISIT_HOME                       2123          //��������
#define    MSG_ID_RESPONSE_VISIT_HOME                      2124          //��Ӧ����
#define    MSG_ID_NOTIFY_VISIT_HOME                        2125          //�·�������ҵ�����
#define    MSG_ID_NOTIFY_HOME_DECORATE_INFO                2127          //�·��������װ��Э��

#define    MSG_ID_REQUEST_GOHOME                           2131          //����ؼ�
#define    MSG_ID_RESPONSE_GOHOME                          2132          //��Ӧ�ؼ�

#define    MSG_ID_REQUEST_WALKDOG                          2133          //�����޹�
#define    MSG_ID_RESPONSE_WALKDOG                         2134          //��Ӧ�޹�
#define    MSG_ID_REQUEST_DICE                             2135          //����������
#define    MSG_ID_RESPONSE_DICE                            2136          //��Ӧ������
#define    MSG_ID_REQUEST_DICE_REWARD                      2137          //���������ӽ���
#define    MSG_ID_RESOPNSE_DICE_REWARD                     2138          //��Ӧ�����ӽ���
#define    MSG_ID_REQUEST_REDICE                           2139          //����������ѡ��
#define    MSG_ID_RESPONSE_REDICE                          2140          //��Ӧ������ѡ��

#define    MSG_ID_REQUEST_PVE_MAPINFOS                     2141          //����PVE��ռ����
#define    MSG_ID_RESPONSE_PVE_MAPINFOS                    2142          //��ӦPVE��ռ����

#define    MSG_ID_REQUEST_OCCUPY_BATTLE                    2143          //������ռ
#define    MSG_ID_RESPONSE_OCCUPY_BATTLE                   2144          //��Ӧ��ռ
#define    MSG_ID_NOTIFY_OCCUPY_CHANGE                     2145          //�㲥��ռ

#define    MSG_ID_NOTIFY_PLAYER_GENERAL_INFOS              2153          //֪ͨ������еĽ�����Ϣ

#define    MSG_ID_REQUEST_GENERAL_POSITION                 2161			 //���ͽ���վλ��Ϣ��������
#define    MSG_ID_RESPONSE_GENERAL_POSITION                2162          //վλ��Ϣ�ظ�

#define    MSG_ID_REQUEST_GENERAL_EQUIP_CHANGE             2165          //����װ����������
#define    MSG_ID_RESPONSE_GENERAL_EQUIP_CHANGE            2166          //����װ�����Ļ�Ӧ

#define    MSG_ID_NOTIFY_BATTLE_RESULT                     2251          //�㲥ս������

#define    MSG_ID_REQUEST_EQUIP_COMPOUND                   2253          //��������װ��
#define    MSG_ID_RESPONSE_EQUIP_COMPOUND                  2254          //��Ӧ����װ��
#define    MSG_ID_REQUEST_EQUIP_ENFORCE                    2255          //����ǿ��װ��
#define    MSG_ID_RESPONSE_EQUIP_ENFORCE                   2256          //��Ӧǿ��װ��

#define    MSG_ID_REQUEST_ADD_ATTRPOINT                    2261          //��������Ե�
#define    MSG_ID_RESPONSE_ADD_ATTRPOINT                   2262          //��Ӧ�����Ե�

#define    MSG_ID_REQUEST_WORK_BEGIN                       2263          //�����
#define    MSG_ID_RESPONSE_WORK_BEGIN                      2264          //��Ӧ��
#define    MSG_ID_REQUEST_WORK_END                         2265          //���������
#define    MSG_ID_RESPONSE_WORK_END                        2266          //��Ӧ������

#define    MSG_ID_NOTIFY_SLAVE_INFOS                       2271          //�㲥ū���ı���Ϣ
#define    MSG_ID_REQUEST_ADD_SLAVE                        2273          //�����ȡū����Ϣ
#define    MSG_ID_RESPONSE_ADD_SLAVE                       2274          //��Ӧ��ȡū����Ϣ
#define    MSG_ID_REQUEST_DELETE_SLAVE                     2275          //����ɾ��ū��
#define    MSG_ID_RESPONSE_DELETE_SLAVE                    2276          //����ɾ��ū��

#define    MSG_ID_REQUEST_CLEAR_CD                         2281          //������CD
#define    MSG_ID_RESPONSE_CLEAR_CD                        2282          //��Ӧ��CD

#define    MSG_ID_NOTIFY_HUNTING_END                       2291          //�㲥���Խ���
#define    MSG_ID_REQUEST_BEGIN_HUNTING                    2293          //����ʼ����
#define    MSG_ID_RESPONSE_BEGIN_HUNTING                   2294          //��Ӧ����
#define    MSG_ID_REQUEST_HUNTING_MONSTER                  2295          //����ץ��
#define    MSG_ID_RESPONSE_HUNTING_MONSTER                 2296          //��Ӧץ��

#define    MSG_ID_NOTIFY_SYSTEM_INFOS                      2333          //��¼�㲥��Ϣ
#define    MSG_ID_NOTIFY_SYSTEM_INFO                       2335          //�����㲥��Ϣ

#define    MSG_ID_NOTIFY_PET_INFOS                         2341          //֪ͨ������Ϣ
#define    MSG_ID_NOTIFY_ADD_PET                           2343          //֪ͨ���ӳ���
#define    MSG_ID_NOTIFY_UPDATE_PET_INFOS				   2345			 //֪ͨ������Ϣ����

#define    MSG_ID_REQUEST_PET_FIGHT                        2351			 //�����ս
#define    MSG_ID_RESPONSE_PET_FIGHT					   2352			 //��Ӧ��ս
#define    MSG_ID_REQUEST_PET_UNFIGHT					   2353			 //�����ٻ�
#define    MSG_ID_RESPONSE_PET_UNFIGHT					   2354			 //��Ӧ�ٻ� 
#define    MSG_ID_REQUEST_PET_RELEASE					   2355			 //�������
#define    MSG_ID_RESPONSE_PET_RELEASE					   2356			 //��Ӧ����
#define    MSG_ID_REQUEST_PET_SUCCINCT					   2357			 //����ϴ��
#define    MSG_ID_RESPONSE_PET_SUCCINCT					   2358			 //��Ӧϴ��


#define    MSG_ID_REQUEST_BATTLE_ROUND                     2361           //���󵥻غ�
#define    MSG_ID_RESPONSE_BATTLE_ROUND                    2362           //��Ӧ���غ�
#define    MSG_ID_NOTIFY_BATTLE_END                        2363           //֪ͨս������

#define    MSG_ID_REQUEST_EQUIP_PUNCH                            2371           //������
#define    MSG_ID_RESPONSE_EQUIP_PUNCH					       2372           //��Ӧ���
#define    MSG_ID_REQUEST_EQUIP_MOSAIC						   2373           //������Ƕ
#define    MSG_ID_RESPONSE_EQUIP_MOSAIC					       2374           //��Ӧ��Ƕ

#define    MSG_ID_REQUEST_EXIT_DUPLICATE                   2601           //�����˳�������ͼ
#define    MSG_ID_RESPONSE_EXIT_DUPLICATE                  2602           //��Ӧ�˳�������ͼ


//////////////////////////////////////////////////////////////////////////
//����¼�ϵͳ�Ĺ���ö�ٶ���
#define    EVENT_FUNCTION_ATTR                             1             //����¼������Ǹı�����
#define    EVENT_FUNCTION_ITEM                             2             //����¼������Ǹı����
#define    EVENT_FUNCTION_MYSTERY_SHOP                     3             //�����̵�
#define    EVENT_FUNCTION_RANDOM_REWARD                    4             //������ƽ���

//////////////////////////////////////////////////////////////////////////
//�����Ǹ����������ֵ����
#define    MAX_HUNGRY_VALUE                                100           //����ֵ���ֵ
#define    MAX_CLEAN_VALUE                                 100           //���ֵ���ֵ
#define    MAX_MOOD_VALUE                                  100           //����ֵ���ֵ

//////////////////////////////////////////////////////////////////////////
//��������������ö�����Ͷ���
#define    ATTR_EXPERIENCE                                 1            //����ֵ
#define    ATTR_GOLD                                       2            //���
#define    ATTR_HONOR                                      3            //����
#define    ATTR_YUANBAO                                    4            //Ԫ��
#define    ATTR_ATTACK                                     5            //����
#define    ATTR_DEFENSE                                    6            //����
#define    ATTR_AGILE                                      7            //����
#define    ATTR_INTELLIGENCE                               8            //����
#define    ATTR_STRENGTH                                   9            //����
#define    ATTR_VIGOR                                      10           //����
#define    ATTR_HUNGER                                     11           //����
#define    ATTR_CLEAN                                      12           //���
#define    ATTR_MOOD                                       13           //����
#define    ATTR_LEVEL                                      14           //�ȼ�
#define    ATTR_FLOURISH                                   15           //���ٶ�
#define    ATTR_ATTRPOINT                                  16           //���Ե�
#define    ATTR_HOME_LEVELUP                               17           //��������
#define    ATTR_DOUBLEHIT                                  20           //����
#define    ATTR_TOUGHNESS                                  21           //����
#define    ATTR_HIT_VALUE                                  22           //������ֵ
#define    ATTR_HP_VALUE                                   23           //��Ѫ��ֵ
#define    ATTR_RUNAROUND_VALUE                            24           //������ֵ
#define    ATTR_SPEED_VALUE                                25           //�ٶ���ֵ

#define    ATTR_DECO_VALUE_BASE                            30           //���е�װ����ֵ�Ļ�׼��
#define    ATTR_ADD_FEED_VALUE                             31           //�������ֵ
#define    ATTR_ADD_CLEAN_VALUE                            32           //ԡ�Ҽ���ֵ
#define    ATTR_ADD_PLAY_VALUE                             33           //��ˣ����ֵ

#define    ATTR_EQUIP_COMPOUND                             40           //zhuangbaizhizuojuan 

#define    ATTR_ADD_SELECT_DICE                            50           //ѡ��
#define    ATTR_ADD_REDICE                                 51           //����

#define    ITEM_FUNCTION_ADD_PET                           60           //��������

//////////////////////////////////////////////////////////////////////////
//������npc�Ի����ܶ���
#define    NPC_DIALOG_FUNC_SHOP                            1             //�̵�
#define    NPC_DIALOG_FUNC_HUNTING                         2             //����

//////////////////////////////////////////////////////////////////////////
//�����Ǵ�����ö�ٶ���
#define    ERROR_MSG_INSUFFICIENT                           1            //��Ҳ���
#define    ERROR_MSG_ITEM_NOTFOUND                          2            //������Ŀ����
#define    ERROR_MSG_USEITEM_ERROR                          3            //ʹ�õ���ʧ��
#define    ERROR_MSG_ITEM_INFO_ERROR                        4            //������Ϣ����
#define    ERROR_MSG_IDORCOUNT_ERROR                        5            //����ID���������Ŀ����
#define    ERROR_MSG_BAG_FULL                               6            //��������
#define    ERROR_MSG_YUANBAO_INSUFFICIENT                   7            //Ԫ������


//������ش�����
#define    ERROR_MSG_TASK_ALREADY_EXIST                     10           //�������Ѵ���
#define    ERROR_MSG_TASK_NOT_EXIST                         11           //�����񲻴���
#define    ERROR_MSG_TASK_ACCEPT_ERROR                      12           //�����ȡ��������
#define    ERROR_MSG_TASK_UNACCEPTED                        13           //������δ��ȡ
#define    ERROR_MSG_TASK_CANNOT_FINISH                     14           //�������������δ�ﵽ
#define    ERROR_MSG_TASK_DAILY_NOTOK                       15           //�ճ�����ȫ����ɻ��Ѵ���

//������ش�����
#define    ERROR_MSG_FRIEND_COUNT_MAX                       20           //������Ŀ�ﵽ���
#define    ERROR_MSG_FRIEND_ALREADY_EXIST                   21           //�����Ѿ�����

//ū��������ش�����
#define    ERROR_MSG_SLAVE_COUNT_MAX                        30           //ū����Ŀ�ﵽ���
#define    ERROR_MSG_SLAVE_ALREADY_EXIST                    31           //ū���Ѿ�����
#define    ERROR_MSG_SLAVE_NOT_EXIST                        32           //��ū��������
#define    ERROR_MSG_SLAVE_WORKID_ERROR                     33           //�����Ͳ�����
#define    ERROR_MSG_SLAVE_LEVEL_LOW                        34           //��ū���ȼ�����
#define    ERROR_MSG_SLAVE_WORKINFO_ERROR                   35           //��ū������Ϣ����
#define    ERROR_MSG_SLAVE_WORKTIME_NOTOVER                 36           //�򹤻�δ����
#define    ERROR_MSG_CLEARCD_NOT_NEED                       37           //CDʱ���ѵ�������Ҫ���

#define    ERROR_MSG_USER_EXIST                             100          //���û����Ѵ���
#define    ERROR_MSG_USER_NOTEXIST                          101          //���û�������
#define    ERROR_MSG_LOGIN_FAIL                             102          //��½ʧ��
#define    ERROR_MSG_USER_OR_PWD_ERROR                      103          //�û����������
#define    ERROR_MSG_CONNECT_OUTTIME                        104          //ע�ᳬʱ��
#define    ERROR_MSG_LOGIN_OUTTIME                          105          //��½��ʱ
#define    ERROR_MSG_QUERY_FAIL                             106          //��ѯʧ��

#define    ERROR_MSG_INSUFFICIENT_ATTRPOINT                 110          //���Ե㲻��

//�ճ�������ش�����
#define    ERROR_MSG_MODEL_UNEXIST                          150          //��ģ�Ͳ�����
#define    ERROR_MSG_FEED_NOTENOUGH                         151          //ʳ�ﲻ��
#define    ERROR_MSG_CLEAN_NOTENOUGH                        152          //��಻��
#define    ERROR_MSG_PLAYING_NOTENOUGH                      153          //��ˣ����

//�޹���ش�����
#define    ERROR_MSG_WALKDOG_FINISHED                       160          //�޹���ͼ����
#define    ERROR_MSG_INSUFFICIENT_STRENGTH                  161          //��������

//װ����ش�����
#define    ERROR_MSG_EQUIP_UNEXIST                          161          //�����ڸ����͵�װ��

#define    ERROR_MSG_EQUIP_EXIST                            163          //װ���Ѵ���

//pve��ش�����
#define    ERROR_MSG_MAPID_INDEX_ERROR                      170          //��ͼid������������

//װ������ϳ���ش�����
#define    ERROR_MSG_COMPOUND_INFO_ERROR                    180          //װ��������Ϣ�ϴ�����
#define    ERROR_MSG_INSUFFICIENT_MATERIAL                  181          //���ϲ���
#define    ERROR_MSG_EQUIPENFORCE_INFO_ERROR                183          //װ����Ϣ����
#define    ERROR_MSG_EQUIP_PUNCH_ERROR                      184          //װ�������Ϣ����
#define    ERROR_MSG_EQUIP_ALREADY_PUNCHED                  185          //��λ���ѿ���
#define    ERROR_MSG_EQUIP_ALREADY_MOASICED                 186          //��λ������Ƕ
#define    ERROR_MSG_EQUIP_MAX_MOASICED                     187          //����Ŀ���������ȿ�������Ƕ

//������ش�����
#define    ERROR_MSG_MONSTER_NOTEXIST                       190          //�ù��ﲻ����
//pengyuan 2012.10.25 ͨ����ʾ�ַ�
#define    PROMPT_MSG_FINISHED                              200
#define    PROMPT_MSG_ENTER_MAP                             201
#define    PROMPT_MSG_LOADING_MAP                           202
#define    PROMPT_MSG_CONNECT_SERVER                        203
#define    PROMPT_ATTR_BASE									210
#define	   PROMPT_MSG_USE_LV								226
#define	   PROMPT_TASK_ACCEPTED								227
#define	   PROMPT_TASK_FINISHED								228
#define	   PROMPT_TASK_NONE									229
#define    PROMPT_ITEM_PRICE							    230  //װ���ۼ�
#define    PROMPT_ITEM_ATTR							        231  //װ������
#define    PROMPT_EXTRA_ATTR							    232  //��������
#define    PROMPT_GEMSTONE							        233  //��Ƕ��ʯ

#define    ERROR_RESULT                                     254          //ͨ�ô��󣬾���������ͼ�����Ĵ�����

#define    OCCUPY_NPC                                       1            //��ռNPC
#define    OCCUPY_PLAYER                                    2            //��ռ���

//pengyuan 2012.9.6 ���CD�����
#define    CLEAR_CD_WORK                                    1            //�����cd
#define    CLEAR_CD_EQUIP                                   2            //���ǿ��װ����cd
#define    CLEAR_CD_PVE                                     3            //���PVEcd


//pengyuan 2012.9.19 
#define    MAX_HUNTING_MONSTER_COUNT                        8             //���Ե�ͼ�����Ĺ�����Ŀ


//pengyuan 2012.11.20
#define    MAX_PET_COUNT                                    3
#define    MAX_PET_SKILL_COUNT                              8

#define    EFFECT_LEVEL_UP                                  1            //������Ч
#define    EFFECT_FINISH_TASK                               2            //���������Ч
#define    EFFECT_ACCEPT_TASK                               3            //��ȡ������Ч
#define    EFFECT_ATTACK_1                                  4            //������Ч1
#define    EFFECT_ATTACK_2                                  5            //������Ч2
#define    EFFECT_ATTACK_PROMPT                             6            //������ʾ

/////////////////////////////////////////////////////////////////////////
// ������һЩloginserver��gameserver���õĽṹ��Ķ���
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
	unsigned int   dwID;                      //Ψһ��ʶ
	int            nModelID;                   //ģ��ID
	unsigned char  nLevel;                     //�ȼ�
	char   nCareer;                    //ְҵ
	char   byNickNameLength;           //�ǳƳ���
	char   szNickName[16];             //�ǳ�
	char   byGender;                   //�Ա�
	int    nMapID;                     //��ͼID
	int    nMapPosX;                 //��ͼλ��X
	int    nMapPosY;                 //��ͼλ��Y
	unsigned int dwHP;                 //����ֵ
	unsigned int dwAttack;             //����
	unsigned int dwDefense;            //����
	unsigned int dwAgile;              //����
	unsigned int dwIntelligence;       //����
	unsigned int dwStrength;           //����
	unsigned int dwDoubleHit;          //����
	unsigned int dwToughness;          //����
	unsigned int dwHit;                //����
	unsigned int dwRunaround;          //����
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
	unsigned int    dwOccupyer;        //ռ����Uin
	unsigned int    dwFlourish;        //���ٶ�

#ifdef __WINDOWS__
	unsigned int   dwLastHarvestTime; //�ϴ�����ʱ��
#endif

#ifdef __LINUX__
	unsigned int   dwLastHarvestTime; //�ϴ�����ʱ��
#endif

	
}PVE_POINT_INFO, *pPVE_POINT_INFO;

//pengyuan 2012.7.18 pve��Ϣ
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