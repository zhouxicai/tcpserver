/**
* ConstDefines.h : ��һЩ�������ж���
* @author��zhouxicai
* @date��2011.10.09
* @��ע��
* */

#ifndef __CONST_DEFINES_H__
#define __CONST_DEFINES_H__

#define CloudLog  printf;

//#define S_OK                                   0x00000000L

//�����ļ�����
//const char* g_szPolicyContent = "<?xml version=\"1.0\"?>\n<cross-domain-policy>\n<allow-access-from domain=\"*\" to-ports=\"12345\"/>\n</cross-domain-policy>\0";

//#define    MAX_CLIENT_NUM        4096                      //�ͻ��������������ʵ��ʹ��ʱ����Ҫ��ȥ��game����db��������
#define    MAX_CLIENT_NUM        1024                      //�ͻ��������������ʵ��ʹ��ʱ����Ҫ��ȥ��game����db��������
#define    SEND_BUFFER_LENGTH    64*1024                   //���ͻ�������С
#define    RECV_BUFFER_LENGTH    64*1024                   //���ܻ�������С
#define    MAX_PACKAGE_LENGTH    4096                      //�����Ĵ�С

#define    SERVER_SEND_BUFFER_LENGTH    10*1024*1024       //������֮��ͨ�ŵ���󻺳�����С
#define    SERVER_RECV_BUFFER_LENGTH    10*1024*1024       //������֮��ͨ�ŵ���󻺳�����С

#define    INVALID_SESSION_ID    0xFFFFFFFF                //��Ч�Ļ���ID
#define    INVALID_PLAYER_UIN    0xFFFFFFFF                //��Ч�����ID

#define    MAX_ITEM_TYPE         1024                      //�����ļ����������ĵ�����Ŀ
#define    INVALID_ITEM_ID       0xFFFF                    //��Ч�ĵ���ID����ʼ����ʱ��ʹ��
#define    MAX_ITEM_NUMBER       64                        //һ����ɫ��ӵ�е���������Ŀ���ݶ�

#define    MAX_EQUIP_NUMBER      6                         //һ����ɫ��ӵ�е�װ����Ŀ
#define    EQUIP_ID_BASE         20000                     //װ��ID��ʼ
#define    EQUIP_ID_CEILING      29999                     //װ��ID����

#define    MAX_TASK_COUNT        1024                      //�����ļ�������������Ŀ
#define    MAX_LEVEL             256                       //��ߵȼ����ݶ�
#define    MAX_SLAVE_WORK_TYPES  32                        //pengyuan 2012.9.5 ū������๤��
#define    SLAVE_WORK_INTERVAL   14400                     //pengyuan 2012.9.5 ū��һ�δ򹤵�ʱ��
#define    MAX_EVENT_COUNT       1024                      //�¼�������Ŀ

#define    MAX_DECORATE_NUMBER   16                        //���װ����Ŀ

#define    MAX_FRIEND_NUMBER     48                        //��������Ŀ
#define    MAX_NPC_COUNT         1024                      //���npc��Ŀ

#define    MAX_MATERIAL_COUNT          6                   //װ����������Ҫ������������
#define    MAX_EQUIP_COMPOUND_COUNT    256                 //װ���������ñ�������ɵ���Ŀ

#define    MAX_EQUIP_ATTRS             3                   //װ�����ӵ������������
#define    MAX_EQUIP_ENFORCE_COUNT     256                 //�ܹ����Դ����װ����Ŀ

#define    MAX_EXTRA_ATTRS             4				   //װ���ĸ��������������
#define    MAX_GEMSTONE				   4                   //��Ƕ��ʯ���������
#define    MAX_EXTRA_ATTR_CONFIG       256                 //���ĸ���������Ŀ

///////////////////////////////////////////////////////////////////////////////////////////////////
// ���涨���������λ�õ�ö��
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

//ս��Ŀ�꣬��ս����ռ��
enum enmBattleTarget
{
	ENM_BATTLE_TARGET_NONE = 0,
	ENM_BATTLE_TARGET_CHALLENGE,
	ENM_BATTLE_TARGET_OCCUPY,
};

//pengyuan 2012.9.4 ��Ӵ�����
enum enmSlaveStatus
{
	ENM_SLAVE_STATUS_NONE = 0,
	ENM_SLAVE_STATUS_IDLE,       //����
	ENM_SLAVE_STATUS_WORK,       //��
};

enum enmPetStatus
{
	ENM_PET_STATUS_NONE = 0,
	ENM_PET_STATUS_IDLE,         //�ջ�
	ENM_PET_STATUS_BATTLE,       //��ս
};

//������������Ҫ�ĵ���������Ϣ
typedef struct tagItemBaseInfo
{
	short         shItemID;
	unsigned char byType;
	int           nPrice;
	int           nLevel;
	unsigned char byDuplicate;
	int           nCanSell;             //0�����߲��ɳ��ۣ�1����������ͨ�̵�����򵽣�2�������������̵������
	unsigned char byFunction;
	int           nArg1;
	int           nArg2;
	int			  nSort;//���ߵ�����
	int           nExtraAttr;
	int           nExtraType;
	int           nGemstone;
}ITEM_BASE_INFO, *pITEM_BASE_INFO;


//pengyuan 2014.8.20 ����������Ϣ
typedef struct tagItemConfigInfo
{
	unsigned int    dwItemID;
	unsigned int    dwType;
	unsigned int    dwTypeValue;
	unsigned int    dwCanSell;
	unsigned int    dwCurrency;           //���߳��۵Ľ������,0Ϊ����,1ΪԪ��
	unsigned int    dwPrice;
	unsigned int    dwColor;
}ITEM_CONFIG_INFO, *pITEM_CONFIG_INFO;


//pengyuan 2014.8.23 װ��������Ϣ
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


#define    MAX_SKILL_COUNT_PER_PLAYER       5              //һ�����ǻ��߽������ϵ��������Ŀ
#define MAX_STAR_LEVEL        5           //���������Ǽ�

typedef struct tagGeneralConfigInfo
{
	unsigned int    dwGeneralID;          //����DI
	unsigned int    dwJobType;            //����ְҵ
	unsigned int    dwLife;               //��������ֵ
	unsigned int    dwAttack;
	unsigned int    dwDefense;
	unsigned int    dwIntelligence;
	unsigned int    dwHitRate;
	unsigned int    dwEvade;
	unsigned int    dwCritical;
	unsigned int    dwTenacity;           //
	float           fRestoreLife;
	float           fAttackInterval;
	//����ȱ����ļ��������Ϣ
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


//pengyuan 2014.8.20 �������������Ϣ
#define    MAX_DROP_ITEM_COUNT    6        //һ�����������Ե���ĵ�������

typedef struct tagDropItemInfo
{
	unsigned int    dwItemID;              //����ĵ���ID
	int             nDropRate;             //�������0-100
}DROP_ITEM_INFO, *pDROP_ITEM_INFO;

//pengyuan 2014.8.20 ���������������Ϣ
typedef struct tagDropInfo
{
	unsigned int    dwDuplicateID;
	unsigned int    dwGeneralExp;          //��������ڵ�ǰ����������õľ���
	unsigned int    dwSilver;              //������õ�����
	DROP_ITEM_INFO  szDropItems[MAX_DROP_ITEM_COUNT];
}DROP_INFO, *pDROP_INFO;



//���������Ϣ
typedef struct tagLevelUpInfo
{
	unsigned int  dwLevel;            //��ǰ�ȼ�
	unsigned int  dwRoleNeedExp;      //��ɫ��������һ������Ҫ�ľ���
	unsigned int  dwGeneralNeedExp;   //��ɫ��������һ������Ҫ�ľ���
	unsigned int  dwCommonDupExp;     //��ɫ����ͨ�����л�ȡ�ľ���
	unsigned int  dwEliteDupExp;      //��ɫ�ھ�Ӣ�����л�ȡ�ľ���
	//unsigned int  dwAttrPoint;        //����������ȡ�����Ե�
}LEVEL_UP_INFO, *pLEVEL_UP_INFO;


//��������
typedef struct tagExtraAttrInfo
{
	unsigned int  dwID;			  //id
	unsigned int  dwType;		  //����
	unsigned int  dwFunc;         //����
	unsigned int  dwArg;          //��ֵ
}EXTRA_ATTR_INFO, *pEXTRA_ATTR_INFO;


//pengyuan 2012.9.5 �������ļ���Ϣ
typedef struct tagSlaveWorkLevel
{
	unsigned int dwWorkId;        //����ID
	unsigned int dwMinLevel;      //��͵ȼ�����
	unsigned int dwPrice;         //��������
}SLAVE_WORK_LEVEL, *pSLAVE_WORK_LEVEL;


//����¼�������Ϣ
typedef struct tagRandomEventInfo
{
	unsigned int dwEventID;
	unsigned int dwType;
	unsigned int dwFunc;
	int          nArg1;
	int          nArg2;
}RANDOM_EVENT_INFO, *pRANDOM_EVENT_INFO;


//pengyuan 2012.6.27 �޹���ͼ���Ӻ�λ�õ���Ϣ
typedef struct tagDieBoxInfo
{
	int    nPosX;
	int    nPosY;
	int    nWidth;
	int    nHeight;
}DIE_BOX_INFO, *pDIE_BOX_INFO;

//pengyuan 2012.6.27 �޹���ͼÿ��������ݽṹ�Ķ���
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

//pengyuan 2012.7.23 ս��Ŀ�����Ϣ����
typedef struct tagBattleTarget
{
	enmBattleTarget battleTarget;
	enmPlayerType   offenderType;
	int             nMapID;
	int             nMapIndex;
}BATTLE_TARGET, *pBATTLE_TARGET;


//һ�������������������Ҫ�Ĳ���ID������Ҫ�Ĳ�����Ŀ
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