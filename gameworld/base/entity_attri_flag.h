#pragma once


//实体的属性标志位
struct EntityFlags
{
	union
	{
		int nValue;
		struct
		{
			bool DenyMove:1;        //不能移动(实现)
			bool DenyBeMove:1;      //不能被移动，比如牢门(实现)
			bool DenyAttackActor:1;  //不攻击玩家(实现)
			bool DenyBeAttack:1;       //不能被攻击(实现)
			bool DenyAttackedByActor:1;  //不能被玩家攻击(实现)
			bool CanAttackMonster:1;    //能够攻击怪物(实现)
			bool DenyBeTaunt:1;      //不能被嘲讽(实现)
			bool DenyAutoAddHp:1;    //不能自动添加HP(实现)
			bool DenyAutoAddMp:1;     //不能自动添加MP(实现)
			bool CanSceneTelport:1;    //能否跨场景传送(实现)
			bool CanSeeHideActor:1;     //能否看到隐身的玩家(实现)
			bool DenyDieSubExp:1;       //不进行经验衰减(实现)
			bool TelByOwnerEntity:1;	// 传送的时候跟着归属者传送
			bool MonsterLazyFollow:1;	// 懒惰跟随属性。惰性跟随距离远了会自动拉到被跟随者；非惰性跟随会检测跟随距离，距离符合会传送。（部分实现）
			bool DenyUseNearAttack:1;     //不使用肉搏（取消）
			bool DenyDizzyBuff:1;          //不能添加晕眩的buff
			bool DenyMoveForbidBuff:1;      //不能添加定身的Buff
			bool DenyInnnerSkillForbidBuff:1; //不能添加封的buff
			bool DenyOutSkillForbidBuff:1;    //不能添加断的buff
			bool DenyMoveSpeedSlowBuff:1;     //禁止移动速度降低的buff
			bool DenySee:1;                   //不能被看到
			bool DenyInitiativeAttackActor:1;	// 不主动攻击玩家（针对主动怪）
			bool ActorModel:1;		// 是否有人物的外观
			bool DenyHpPower:1;		// 是否禁止血倍率增加的buff的作用
			bool OnlyAttkackByPet:1; //是否只能被宠物攻击(实现)
			bool DenyTurnDir:1;		// 是否禁止转向
			bool DenyUseSkill:1;		// 是否禁止使用任何技能
		};
	};
	EntityFlags()
	{
		nValue = 0;
	}
};
