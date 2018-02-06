#pragma once
struct TagUnit
{
	float		HP;		//ü��
	float		MP;		//����
	float		ATK;	//���ݷ�
	float		DEF;	//����
	float		Speed;	//�̵��ӵ�

	float		LV;		//����;

	float		Power;	//��
	float		Dex;	//��ø
	float		Int;	//����

	bool		Death;	//���

	float		Exp;	//����ġ
	float		Gold;	//��
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
	SPIDER,
	GUARDFEL,
	DRUID,
	BOSS_ARTHAS,
	BOSS_RAGNALOS
};

enum NPC_State
{
	NOTHING,
	TALK,
	YES,
	NO
};
class cUnit
{

public:
	cUnit();
	~cUnit();
};

