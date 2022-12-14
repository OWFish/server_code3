/*
** Generated automatically by lua .
*/

#ifndef _TIP_MSG_ID_H_
#define _TIP_MSG_ID_H_



enum tagTipmsgID
{
	tpNoError=0,
	tpSkillConfigError,
	tpSkillTrainLevelLimited,
	tpSkillTrainCoinLimited,
	tpSkillTrainBindcoinLimited,
	tpSkillTrainExpLimited,
	tpSkillTrainVocationLimited,
	tpSkillTrainHasLearned,
	tpSkillSpellHpLimited,
	tpSkillSpellMpLimited,
	tpSkillSpellBuffLimited,
	tpSkillSpellNotLeared,
	tpSkillSellCDLimited,
	tpSkillSpellNoTarget,
	tpSkillTrainItemLimited ,
	tpSkillTrainXiuweiLimited ,
	tpSkillTrainWithBuff ,
	tpSkillTrainWithoutBuff ,
	tpSkillTrainDistance ,
	tpSkillTrainOverLap ,
	tpSkillTrainFaceTarget,
	tpSkillTrainOneDirTarget,
	tpAngerLimited,
	tpSkillTrainHpRateBelow,
	tpSkillTrainFriendTarget ,
	tpSkillTrainEnemyTarget ,
	tpSkillTrainCanAttackTarget ,
	tpSkillTrainCanAttackTarget1 ,
	tpSkillTrainEfficicyNotEnough ,
	tpSkillTrainJumpPowerNotEnough,
	tpSkillTrainJumpTooLong,
	tpSkillTrainCampTitleLimit,
	tpSkillTrainYDistance,
	tpSkillInnerDamage,
	tpSkillOutDamage,
	tpSkillGiveSelfInnerDamage,
	tpSkillGiveSelfOutDamage,
	tpNearAttackSkillName,
	tpSkillKillEntity,
	tpBeSkilled,
	tpSkillMijiNotMatch,
	tpSkillMijiLevelLimit,
	tpSkillMijiHasLearn,
	tpSkillMijiLearnSucceed,
	tpSkillForgetSkill,
	tpSkillGetExp,
	tpSkillGetMultiplyExp,
	tpSkillGetSubExp ,
	tpSkillAbsortExp,
	tpSkillNotUseSkill,
	tpExpPotIsFull,
	tpSkillIsUpMostLevel ,
	tpSkillCannotSpell,
	tpSkillSingParamError,
	tpQuestNotGiveUp,
	tpGiveUpSucc,
	tpQuestFinishSucc,
	tpQuestFullBag,
	tpQuestAutoFinishErr,
	tpQuestRemain,
	tpChatPlayerBeShutup,
	tpChatTargetOffLine,
	tpChatEquipIsDelete,
	tpItemConfigError,
	tpItemNotExist,
	tpItemCannotTakeOn,
	tpItemCannotTakeoff,
	tpItemTakeoffFailForBagFull,
	tpItemCannotTakeOnForLevel,
	tpItemCannotTakeOnForSex,
	tpItemCannotTakeOnForVocation,
	tpItemNotifyEnlargeMoney,
	tpItemSplitBagFail ,
	tpItemMergeFail ,
	tpBagSortInDeal,
	tpBagFullQuest,
	tpEnergyIsFull,
	tpXiuweiIsFull,
	tpPkValueIsEmpty,
	tpItemBagGetItem,
	tpItemBagLostItem,
	tpItemCanNotDelete,
	tpBagIsFull,
	tpItemTakenOnBinded,
	tpItemCanNotUseNow,
	tpItemNeedMoreGrid,
	tpBagFullNotGetSysItem,
	tpItemRegionCanNotUseItem,
	tpItemInCD,
	tpSkillNoBattlePet,
	tpSkillPetHaveNot,
	tpDepotBagIsFull,
	tpDeportEnlargeFee,
	tpItemCanNotPutDepot,
	tpFailForDealing,
	tpEquipEnhanceNotEquip,
	tpEquipEnhanceMaxLevel,
	tpEquipEnhanceMoneyLack,
	tpEquipEnhanceStoneLack,
	tpEquipEnhanceSuccess,
	tpEquipEnhanceFaile,
	tpEquipBreakMoney,
	tpInjectionMoney,
	tpInjectionAssistItem,
	tpForgeMoney,
	tpForgeAssistItem,
	tpJobMakeAssistItem,
	tpJobMakeToolItem,
	tpEngLack,
	tpJobMakeBorad,
	tpCreateGuildErrorLevel,
	tpCreateGuildNotEnough,
	tpCreateGuildHasInGuild,
	tpNoRightToDelete,
	tpCreateGuildNameErr,
	tpCreateGuildNameInUse,
	tpCreateGuildBroadcast,
	tpCreateGuildBroadcast1,
	tpJoinGuildSucc,
	tpLeftGuild,
	tpKickGuild,
	tpLeftGuildCanNotJoin,
	tpKickoutGuildCanNotJoin,
	tpNotInGuild,
	tpBeLeader,
	tpUpPos,
	tpDownPos,
	tpDeleteGuildSucc,
	tpDeleteGuildErr,
	tpZjOneDayOneTime,
	tpGetWealSucc,
	tpGuildWealNotGX,
	tpGuildStoreNotGx,
	tpGuildUpgrade,
	tpDelGuildTimeErr,
	tpGuildHasApply,
	tpDeleteGuildMemo,
	tpRefuseCall,
	tpLeftGuildCannotJoin,
	tpOtherLeftGuild,
	tpRefuseInviteGuild,
	tpChangeGuildPos_pt,
	tpChangeGuildPos_jy,
	tpChangeGuildPos_hf,
	tpChangeGuildPos_fbz,
	tpChangeGuildPos_bz,
	tpGuildLeaderChange,
	tpGuildNoItemFr,
	tpGuildFullBag,
	tpOtherZyCanNotEnter,
	tpCanJoinSameCampGuild,
	tpStoreItemNotExists,
	tpStoreNotEnoughBagSpace,
	tpStoreNotEnoughMoney,
	tpStoreNoYuanBaoCanWithdraw,
	tpStoreWithdrawYuanBaoFailed,
	tpYouAreDealingNow,
	tpDealTargetNotExists,
	tpOtherServerDeal1,
	tpOtherServerDeal2,
	tpOtherServerDeal3,
	tpTargetIsDealing,
	tpAlreadyInvaiteDeal,
	tpCancelLock,
	tpTargetDoNotDealWithYou,
	tpDealRequesterHasLeaved,
	tpDealRequesterCancel,
	tpDealBlankWasFull,
	tpDealBlankWasFullSelf,
	tpTargetBagMaybeFull,
	tpYouMustLockDealFirst,
	tpDealCanceledOfMyBagWasFull,
	tpDealcanceldOfTargetBagWasFull,
	tpDealDataValidateFailure,
	tpDealCountChange,
	tpDealTargetConfimed,
	tpTargetHasLockedDeal,
	tpYouMayClickDealBtnNow,
	tpWaitTargetLockDeal,
	tpItemIsBinded,
	tpItemIsQuestItem,
	tpDealNoMoney,
	tpNoDealItem,
	tpDealHasLocked,
	tpTargetMoneyIsFull,
	tpSelfMoneryIsFull,
	tpLootBagTooFar,
	tpLootItemIsnotYou,
	tpItemNotExisting,
	tpLootFailForBagFull,
	tpLootItem,
	tpLootTaskItemBagFull,
	tpLootBroadcast,
	tpGetBindCoin,
	tpLostBindCoin,
	tpGetCoin,
	tpLostCoin,
	tpGetBindYuanbao,
	tpLostBindYuanbao,
	tpGetYuanbao,
	tpLostYuanbao,
	tpTeamOpOfflineUser,
	tpTeamCreated,
	tpTeamChatFail,
	tpSetNewCaptin,
	tpSceneErr,
	tpExpNotEnough,
	tpNoMount,
	tpPkCannotMount,
	tpInItem,
	tpNpcTooFar,
	tpMatchIng,
	tpMatchTimeout,
	tpSceneCannotMatch,
	tpRefuseMatch,
	tpOtherIsMatching,
	tpWinmatch1,
	tpMatchLost1,
	tpWinmatch2,
	tpMatchLost2,
	tpFreePkLevelErr,
	tpPkChange,
	tpZhanHunChange,
	tpSendMatchInvite,
	tpNPCTradeMoneyLack,
	tpNPCTradeBagFull,
	tpStorehouseExtendYBLack,
	tpConsiHaveNotItem,
	tpConsiItemBinded,
	tpConsiDuraErr,
	tpConsiTimeLimit,
	tpConsiHasItemTimeout,
	tpConsiSellGetMoney,
	tpConsiSellGetMoneyButton,
	tpConsiItemCannotDeal,
	tpFcmNotifyBeFcm,
	tpFcm1Hour,
	tpFcm2Hour,
	tpFcm2Hour55Minute,
	tpFcm3Hour,
	tpFcm5Hour,
	tpChatPosNotMoney,
	tpSystemClosing,
	tpConfirm,
	tpAchieveGetAchieve,
	tpAchieveBroadcastGetAchieve,
	tpAchieveLostTitle,
	tpMoneyTypeYuanbao,
	tpMoneyTyeBindYuanbao,
	tpMoneyTypeCoin,
	tpMoneyTypeBindCoin,
	tpLeftParentheses,
	tpRightParentheses,
	tpAddRenown,
	tpDelRenown,
	tpAddRenowFail,
	tpCampArrivedTopCampStatus,
	tpCampNeedMoreContribute,
	tpCampNeedMoreFame,
	tpCampNameInvalid,
	tpCampNotOnline,
	tpCampNotInSameCamp,
	tpCampPlayerLevelTooLow,
	tpCampPlayerCampContrTooLow,
	tpCampHaveNoRightToSetTitle,
	tpCampRejectTitleInvite,
	tpCampKingFiredBecauseOfOffline,
	tpCampTitleFiredBecauseOfOffline,
	tpCampWaitTargetAck,
	tpCampGetCampContributeVal,
	tpCampNpcFail,
	tpCampTargetHasTitle,
	tpCampCannotSetBulletin,
	tpCampSetTitleSuccBoardCast,
	tpCampAllyDismissed,
	tpCampHasNoKing,
	tpCampKingOffLine,
	tpCampAllySucc,
	tpCampAllySuccBulletin,
	tpCampRefuseAlly,
	tpCampHasSendAlly,
	tpCampAllyCD,
	tpCampAllyCD2,
	tpGemSlotNotOpen,
	tpGemExistGemInTheSlot,
	tpGemEquipGemInCD,
	tpGemAddExp,
	tpGemUpLevel,
	tpGemUpGrade,
	tpGemGotWish,
	tpGemLackSpriteStren,
	tpCannotMountInTheArea,
	tpCannotMountInPractise,
	tpGemLevelUpLmt,
	tpGemLevelUpToTop,
	tpGetXiuwei,
	tpLostXiuwei,
	tpGetVipXiuwei,
	tpSelfCancelDoublePractice,
	tpOtherCancleDoublePractice,
	tpLootCatherMonsterBroadCast,
	tpStoreBroadCast ,
	tpRootFail,
	tpRootFailCoin,
	tpStoreItemLaterbuy,
	tpStoreItemActorLimitCount,
	tpStoreItemLimitCount,
	tpRankNoActor,
	tpStoreItemMax,
	tpGuildJoin,
	tpAddRootExp,
	tpNoYuanbaoToQuickFinish,
	tpQuestUnableQuickFinish,
	tpGuildGX,
	tpGuildPeach,
	tpdecGuildGx,
	tpNotVIPForAddFunbenCount,
	tpMaxAddItemCount,
	tpNoYuanbaoAddItemCount,
	tpSplitDepotFail,
	tpMergeDepotFail,
	tpNotUseMount,
	tpNotTeleprot,
	tpCannotEnterSceneLevelLimit,
	tpExistSoulType,
	tpStoneNotice,
	tpStoneNoticeChat,
	tpBagItemUnableUse,
	tpActorOffline,
	tpAchieveAwardTips,
	tpNoMountWithBattle,
	tpNoYB,
	tpNotChangePKMode,
	tpNotMountForProtection,
	tpImIsPeaceful,
	tpOtherIsPeaceful,
	tpNoChangeUnionMode,
	tpBagFullLottery,
	tpGetMultiplyRootExp,
	tpCampBattleEndTips1,
	tpCampBattleEndTips2,
	tpQuestAwardToDepot,
	tpAddShengWang,
	tpDelShengWang,
	tpPetOpOfflinePet,
	tpChatLevelLimit,
	tpMailBoxWillFull,
	tpMailDeleteSucess,
	tpMailBoxAlreadyFull,
	tpSendMailNoEnoughMoney,
	tpMailAcceptorNoNull,
	tpMailContextNoNull,
	tpMailAcceptorIsMine,
	tpMailNoOPenLevelLack,
	tpMailObjectNotExist,
	tpBangBangTangExp,
	tpWorldLevelExp,
	tpAddHonor,
	tpDelHonor,
	tpEquipDenyTakeoff,
	tpSortGuildDepotPos,
	tpGuildDepotCount,
	tpGuildDepotColor,
	tpGuildDepotBind,
	tpGuildDepotStoreMsg,
	tpGuildDepotGetMsg,
	tpHasGetActivityAward,
	tpCannotGetActivityAward,
	tpMailTypeSystem,
	tpMailTypePrivate,
	tpMailTypeAttachment,
	tpForbidSendMail,
	tpForbidChat,
	tpCampDesc,
	tpJobDesc,
	tpJob1,
	tpJob2,
	tpJob3,
	tpJob4,
	tpCamp1,
	tpCamp2,
	tpCamp3,
	tpGuildDepotNotUpdate,
	tpActorDataErr,
	tpLingWenNotice,
	tpLingWenNoticeChat,
	tpWarTeamUserOffline,
	tpWarTeamSelfForbid,
	tpWarNotInTeam,
	tpWarNotTeamLeader,
	tpWarTeamIsFull,
	tpInWarTeam,
	tpWarTeamNotExist,
	tpWarTeamCampDiff,
	tpWarTeamLeaderOffline,
	tpNotWarTeamLeader,
	tpWarTeamActorOffline,
	tpWarTeamJoin,
	tpWarTeamReject,
	tpWarTeamSendJoin,
	tpWarTeamJoinReject,
	tpWarTeamHaveNotMember,
	tpWarTeamChangeLeaderTimeErr,
	tpWarTeamTimeErr,
	tpImpeachChangeLeader,
	tpImpeachKickCandidate,
	tpKickByAssistLeader,
	tpCandidateExitInImpeach,
	tpTotalExpRate,
	tpHasAlliance,
	tpAllinaceLimitLevel,
	tpAllianceDisTime,
	tpAllianceDisMsg,
	tpAllianceDisBroadGuildMsg,
	tpInviteAlliance,
	tpRejectAlliance,
	tpMakeAlliance,
	tpBroadMakeAlliance,
	tpCannotChangeAlliance,
	tpCreateGuildErrorVIPLevel,
	tpGuildLeaderAgainError,
	tpTeamBuffExp,
	tpNotChangePKArea,
	tpEnterPKArea,
	tpReachAchieveMedal,
	tpMaxMemberCount,
	tpGuildSystemNotOpen,
	tpNoRight,
	tpNoThisGuild,
	tpKickOut,
	tpCheckScene,
	tpSysNoOpen,
	tpPetHoleNoOpen,
	tp5hourFcmItemTips,
	tpFpPeaceful,
	tpFpTeam,
	tpFpGuild,
	tpFpZY,
	tpFpPk,
	tpFpAlly,
	tpFpUnion,
	tpFpServer,
	tpFpSpecialPeaceful,
	tpPkModleAutoChange,
	tpForbiddenSpecialPkmodel,
	tpGuildDepotToBag,
	tpGuildDepotMail1,
	tpGuildDepotMail2,
	tpNotChangePKModeSp,
	tpItemCannotTakeOnForReincarnation,


	tpMax,
};

#endif


