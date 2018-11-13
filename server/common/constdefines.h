/**
* ConstDefines.h : 对一些常量进行定义
* @author：zhouxicai
* @date：2011.10.09
* @备注：
* */

#ifndef __CONST_DEFINES_H__
#define __CONST_DEFINES_H__

#define CloudLog  printf;

//#define S_OK                                   0x00000000L

//策略文件内容
//const char* g_szPolicyContent = "<?xml version=\"1.0\"?>\n<cross-domain-policy>\n<allow-access-from domain=\"*\" to-ports=\"12345\"/>\n</cross-domain-policy>\0";

//#define    MAX_CLIENT_NUM        4096                      //客户端最大连接数，实际使用时还需要减去和game服和db服的连接
#define    MAX_CLIENT_NUM        1024                      //客户端最大连接数，实际使用时还需要减去和game服和db服的连接
#define    SEND_BUFFER_LENGTH    64*1024                   //发送缓冲区大小
#define    RECV_BUFFER_LENGTH    64*1024                   //接受缓冲区大小
#define    MAX_PACKAGE_LENGTH    4096                      //最大包的大小

#define    SERVER_SEND_BUFFER_LENGTH    10*1024*1024       //服务器之间通信的最大缓冲区大小
#define    SERVER_RECV_BUFFER_LENGTH    10*1024*1024       //服务器之间通信的最大缓冲区大小

#define    INVALID_SESSION_ID    0xFFFFFFFF                //无效的会晤ID
#define    INVALID_PLAYER_UIN    0xFFFFFFFF                //无效的玩家ID

#define    MAX_ITEM_TYPE         1024                      //配置文件中最多允许的道具数目
#define    INVALID_ITEM_ID       0xFFFF                    //无效的道具ID，初始化的时候使用
#define    MAX_ITEM_NUMBER       64                        //一个角色能拥有的最大道具数目，暂定

#define    MAX_EQUIP_NUMBER      6                         //一个角色能拥有的装备数目
#define    EQUIP_ID_BASE         20000                     //装备ID起始
#define    EQUIP_ID_CEILING      29999                     //装备ID结束

#define    MAX_TASK_COUNT        1024                      //配置文件中最多的任务数目
#define    MAX_LEVEL             256                       //最高等级，暂定
#define    MAX_SLAVE_WORK_TYPES  32                        //pengyuan 2012.9.5 奴隶打工最多工种
#define    SLAVE_WORK_INTERVAL   14400                     //pengyuan 2012.9.5 奴隶一次打工的时长
#define    MAX_EVENT_COUNT       1024                      //事件的总数目

#define    MAX_DECORATE_NUMBER   16                        //最大装饰数目

#define    MAX_FRIEND_NUMBER     48                        //最大好友数目
#define    MAX_NPC_COUNT         1024                      //最大npc数目

#define    MAX_MATERIAL_COUNT          6                   //装备打造所需要的最大材料种类
#define    MAX_EQUIP_COMPOUND_COUNT    256                 //装备打造配置表最多容纳的数目

#define    MAX_EQUIP_ATTRS             3                   //装备增加的属性最大条数
#define    MAX_EQUIP_ENFORCE_COUNT     256                 //总共可以打造的装备数目

#define    MAX_EXTRA_ATTRS             4				   //装备的附加属性最大条数
#define    MAX_GEMSTONE				   4                   //镶嵌宝石的最大数量
#define    MAX_EXTRA_ATTR_CONFIG       256                 //最多的附加属性条目

///////////////////////////////////////////////////////////////////////////////////////////////////
// 下面定义玩家所处位置的枚举
enum enmPlayerLocation
{
	ENM_LOCATION_NONE = 0,
	ENM_LOCATION_ATHOME,
	ENM_LOCATION_VISITING,
	ENM_LOCATION_WALKINGDOG,
	ENM_LOCATION_BATTLING,
	ENM_LOCATION_HUNTING,
};

enum enmPlayerType
{
	ENM_PLAYER_TYPE_NONE = 0,
	ENM_PLAYER_TYPE_PLAYER,
	ENM_PLAYER_TYPE_NPC,
	ENM_PLAYER_TYPE_MONSTER,
	ENM_PLAYER_TYPE_PET,
};

//战斗目标，挑战还是占领
enum enmBattleTarget
{
	ENM_BATTLE_TARGET_NONE = 0,
	ENM_BATTLE_TARGET_CHALLENGE,
	ENM_BATTLE_TARGET_OCCUPY,
};

//pengyuan 2012.9.4 添加打工种类
enum enmSlaveStatus
{
	ENM_SLAVE_STATUS_NONE = 0,
	ENM_SLAVE_STATUS_IDLE,       //空闲
	ENM_SLAVE_STATUS_WORK,       //打工
};

enum enmPetStatus
{
	ENM_PET_STATUS_NONE = 0,
	ENM_PET_STATUS_IDLE,         //收回
	ENM_PET_STATUS_BATTLE,       //出战
};

//服务器端所需要的道具配置信息
typedef struct tagItemBaseInfo
{
	short         shItemID;
	unsigned char byType;
	int           nPrice;
	int           nLevel;
	unsigned char byDuplicate;
	int           nCanSell;             //0：道具不可出售，1：道具在普通商店可以买到，2：道具在神秘商店可以买到
	unsigned char byFunction;
	int           nArg1;
	int           nArg2;
	int			  nSort;//道具的种类
	int           nExtraAttr;
	int           nExtraType;
	int           nGemstone;
}ITEM_BASE_INFO, *pITEM_BASE_INFO;


//pengyuan 2014.8.20 道具配置信息
typedef struct tagItemConfigInfo
{
	unsigned int    dwItemID;
	unsigned int    dwType;
	unsigned int    dwTypeValue;
	unsigned int    dwCanSell;
	unsigned int    dwCurrency;           //道具出售的金币类型,0为银两,1为元宝
	unsigned int    dwPrice;
	unsigned int    dwColor;
}ITEM_CONFIG_INFO, *pITEM_CONFIG_INFO;


//pengyuan 2014.8.23 装备配置信息
typedef struct tagEquipConfigInfo
{
	unsigned int    dwEquipID;
	unsigned int    dwType;
	unsigned int    dwCareer;
	unsigned int    dwColor;
	unsigned int    dwLevel;
	unsigned int    dwGrade;
	unsigned int    dwCanSell;
	unsigned int    dwPrice;
}EQUIP_CONFIG_INFO, *pEQUIP_CONFIG_INFO;


#define    MAX_SKILL_COUNT_PER_PLAYER       5              //一个主角或者将领身上的最大技能数目
#define MAX_STAR_LEVEL        5           //将领的最高星级

typedef struct tagGeneralConfigInfo
{
	unsigned int    dwGeneralID;          //将领DI
	unsigned int    dwJobType;            //将领职业
	unsigned int    dwLife;               //将领生命值
	unsigned int    dwAttack;
	unsigned int    dwDefense;
	unsigned int    dwIntelligence;
	unsigned int    dwHitRate;
	unsigned int    dwEvade;
	unsigned int    dwCritical;
	unsigned int    dwTenacity;           //
	float           fRestoreLife;
	float           fAttackInterval;
	//这里缺将领的技能相关信息
	unsigned int    dwSkillIDs[MAX_SKILL_COUNT_PER_PLAYER];
	float           fLifeLevelGrowth;
	float           fAttackLevelGrowth;
	float           fDefenseLevelGrowth;
	float           fIntelligenceLevelGrowth;
	float           fLifeStarGrowth;
	float           fAttackStarGrowth;
	float           fDefenseStarGrowth;
	float           fIntelligenceStarGrowth;
	unsigned int    dwStarConsume[MAX_STAR_LEVEL];
	unsigned int    dwStarConsumeItem;
}GENERAL_CONFIG_INFO, *pGENERAL_CONFIG_INFO;


//pengyuan 2014.8.20 单个掉落物的信息
#define    MAX_DROP_ITEM_COUNT    6        //一个副本最多可以掉落的道具种类

typedef struct tagDropItemInfo
{
	unsigned int    dwItemID;              //掉落的道具ID
	int             nDropRate;             //掉落概率0-100
}DROP_ITEM_INFO, *pDROP_ITEM_INFO;

//pengyuan 2014.8.20 新增副本掉落表信息
typedef struct tagDropInfo
{
	unsigned int    dwDuplicateID;
	unsigned int    dwGeneralExp;          //将领可以在当前副本中所获得的经验
	unsigned int    dwSilver;              //副本获得的银两
	DROP_ITEM_INFO  szDropItems[MAX_DROP_ITEM_COUNT];
}DROP_INFO, *pDROP_INFO;



//升级相关信息
typedef struct tagLevelUpInfo
{
	unsigned int  dwLevel;            //当前等级
	unsigned int  dwRoleNeedExp;      //角色升级到下一级所需要的经验
	unsigned int  dwGeneralNeedExp;   //角色升级到下一级所需要的经验
	unsigned int  dwCommonDupExp;     //角色在普通副本中获取的经验
	unsigned int  dwEliteDupExp;      //角色在精英副本中获取的经验
	//unsigned int  dwAttrPoint;        //升级后所获取的属性点
}LEVEL_UP_INFO, *pLEVEL_UP_INFO;


//附加属性
typedef struct tagExtraAttrInfo
{
	unsigned int  dwID;			  //id
	unsigned int  dwType;		  //类型
	unsigned int  dwFunc;         //功能
	unsigned int  dwArg;          //数值
}EXTRA_ATTR_INFO, *pEXTRA_ATTR_INFO;


//pengyuan 2012.9.5 打工配置文件信息
typedef struct tagSlaveWorkLevel
{
	unsigned int dwWorkId;        //工种ID
	unsigned int dwMinLevel;      //最低等级限制
	unsigned int dwPrice;         //单次收益
}SLAVE_WORK_LEVEL, *pSLAVE_WORK_LEVEL;


//随机事件配置信息
typedef struct tagRandomEventInfo
{
	unsigned int dwEventID;
	unsigned int dwType;
	unsigned int dwFunc;
	int          nArg1;
	int          nArg2;
}RANDOM_EVENT_INFO, *pRANDOM_EVENT_INFO;


//pengyuan 2012.6.27 遛狗地图骰子盒位置等信息
typedef struct tagDieBoxInfo
{
	int    nPosX;
	int    nPosY;
	int    nWidth;
	int    nHeight;
}DIE_BOX_INFO, *pDIE_BOX_INFO;

//pengyuan 2012.6.27 遛狗地图每个块的数据结构的定义
typedef struct tagMapChunk
{
	int    nID;
	int    nPosX;
	int    nPosY;
	int    nWidth;
	int    nHeight;
	
	int    nFunc;
	int    nArg1;
	int    nArg2;
	int    nArg3;
}MAP_CHUNK, *pMAP_CHUNK;


typedef struct tagEffectPoint
{
	int    nEffectID;
	int    nTargetMap;
	int    nArg1;
	int    nArg2;
}EFFECT_POINT, *pEFFECT_POINT;

//pengyuan 2012.7.23 战斗目标等信息定义
typedef struct tagBattleTarget
{
	enmBattleTarget battleTarget;
	enmPlayerType   offenderType;
	int             nMapID;
	int             nMapIndex;
}BATTLE_TARGET, *pBATTLE_TARGET;


//一个材料项的描述，有需要的材料ID，和需要的材料数目
typedef struct tagCompoundInfo
{
	int    dwMaterialID;
	int    dwMaterialCount;
}COMPOUND_INFO, *pCOMPOUND_INFO;


typedef struct tagEquipCompoundInfo
{
	unsigned int    dwCompoundID;
	unsigned int    dwTargetItemID;
	int             nMatCount;
	COMPOUND_INFO   szMatInfos[MAX_MATERIAL_COUNT];
}EQUIP_COMPOUND_INFO, *pEQUIP_COMPOUND_INFO;

typedef struct tagEnforcePair
{
	unsigned int    dwFunc;
	unsigned int    dwValue;
}ENFORCE_PAIR, *pENFORCE_PAIR;

typedef struct tagEquipEnforceInfo
{
	unsigned int    dwEquipID;
	unsigned int    dwBasePrice;
	float           fRevisionCoef;
	ENFORCE_PAIR    szEnforceInfos[MAX_EQUIP_ATTRS];
}EQUIP_ENFORCE_INFO, *pEQUIP_ENFORCE_INFO;

#endif