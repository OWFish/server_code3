#ifndef _ALLOC_H_
#define _ALLOC_H_

#if 1
typedef BaseAllocator RankAlloc;
typedef AlignAllocator MsgSysAlloc;
typedef AlignAllocator LuaAlloc;
typedef AlignAllocator StrAlloc;
typedef BufferAllocator ActorMgrAlloc;
typedef BufferAllocator FightAlloc;
typedef BufferAllocator	 QuestAlloc;
typedef BufferAllocator FriendAlloc;
typedef BufferAllocator GridAlloc;
typedef BufferAllocator SceneGridAlloc;
typedef BufferAllocator SceneTeleAlloc;
typedef BufferAllocator TimerCallAlloc;
typedef BaseAllocator  GEAlloc;
#else
typedef BaseAllocator RankAlloc;
typedef BaseAllocator MsgSysAlloc;
typedef BaseAllocator LuaAlloc;
typedef BaseAllocator StrAlloc;
typedef BaseAllocator ActorMgrAlloc;
typedef BaseAllocator FightAlloc;
typedef BaseAllocator QuestAlloc;
typedef BaseAllocator FriendAlloc;
typedef BaseAllocator GridAlloc;
typedef BaseAllocator SceneGridAlloc;
typedef BaseAllocator SceneTeleAlloc;
typedef BaseAllocator TimerCallAlloc;
typedef BaseAllocator  GEAlloc;
#endif
#endif
