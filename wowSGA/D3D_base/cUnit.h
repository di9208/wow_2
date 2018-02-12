#pragma once
struct TagUnit
{
	float		Max_HP;
	float		HP;		//Ã¼·Â
	float		MP;		//¿¥ÇÇ
	float		ATK;	//°ø°Ý·Â
	float		DEF;	//¹æ¾î·Â
	float		Speed;	//ÀÌµ¿¼Óµµ

	float		LV;		//·¹º§;

	float		Power;	//Èû
	float		Dex;	//¹ÎÃ¸
	float		Int;	//Áö´É

	bool		Death;	//»ç¸Á
	bool		Hurt;
	float		Exp;	//°æÇèÄ¡
	float		Gold;	//µ·
};

enum condition
{
	NONE,
	ATTACK,
	RUN,
	IDLE,
	BREATH,
	BUFF,
	DEATH,
	JUMP_START,
	JUMP_UP,
	JUMP_ING,
	JUMP_DOWN,
	WHIRLWIND,
	ROLL_START,
	ROLL,
	ROLL_1,
	ROLL_END,
	HURT,
	SKILL_1,
	SKILL_2,
	SKILL_3,
	BACKWALK
};


enum E_BOSS_STATE
{
	E_BOSS_SPELL1,
	E_BOSS_SPELL2,
	E_BOSS_WHIRLWIND,
	E_BOSS_ATT,
	E_BOSS_START,
	E_BOSS_DEATH,
	E_BOSS_WALK,
	E_BOSS_STAND,
	E_BOSS_ATT2,
	E_BOSS_STATE_END = 9
};

enum E_BOSS_RAG_STATE
{
	E_BOSS_RAG_ATT,
	E_BOSS_RAG_START,
	E_BOSS_RAG_DEATH,
	E_BOSS_RAG_STAND,
	E_BOSS_RAG_SPELL,
	E_BOSS_RAG_MERGE,
	E_BOSS_RAG_STATE_END = 6
};


enum MONSTER_STATUS
{
	MONSTER_STAND,
	MONSTER_RUN,
	MONSTER_ATTACK,
	MONSTER_HARM,
	MONSTER_DEATH
};

enum MONSTER_KIND
{
	KIND_SPIDER,
	KIND_BOSS_ARTHAS,
	KIND_DRUID,
	KIND_BOSS_RAGNALOS,
	KIND_WORG
	
};
struct tagMon
{
	MONSTER_KIND kind;
	D3DXVECTOR3 pos;
	std::string name;
};
struct tagobject
{
	D3DXVECTOR3 pos;
	std::string name;
};
enum NPC_State
{
	NOTHING,
	TALK,
	YES,
	NO
};
struct Enemy_Sphere
{
	D3DXVECTOR3		vCenter;
	float			fRadius;
	bool			bIsPicked;
	MONSTER_KIND	Mons;
	int				HP;
	int				Max_HP;
};
class cUnit
{

public:
	cUnit();
	~cUnit();
};

