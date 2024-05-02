/*
	Copyright (c) Microsoft Corporation.  All rights reserved.
*/


#define NdisAcquireSpinLock sdv_NdisAcquireSpinLock
#define NdisReleaseSpinLock sdv_NdisReleaseSpinLock
#define NdisDprAcquireSpinLock sdv_NdisDprAcquireSpinLock 
#define NdisDprReleaseSpinLock sdv_NdisDprReleaseSpinLock
#define NdisAllocateSpinLock sdv_NdisAllocateSpinLock


#define NdisAllocateMemoryWithTagPriority  sdv_NdisAllocateMemoryWithTagPriority 
#define NdisMRegisterScatterGatherDma sdv_NdisMRegisterScatterGatherDma
#define NdisMRegisterInterruptEx sdv_NdisMRegisterInterruptEx

#define NdisMDeregisterInterruptEx sdv_NdisMDeregisterInterruptEx
#define NdisMDeregisterScatterGatherDma sdv_NdisMDeregisterScatterGatherDma
#define NdisFreeMemory sdv_NdisFreeMemory

#define NdisAdvanceNetBufferDataStart sdv_NdisAdvanceNetBufferDataStart
#define NdisAdvanceNetBufferListDataStart sdv_NdisAdvanceNetBufferListDataStart
#define NdisAllocateCloneNetBufferList sdv_NdisAllocateCloneNetBufferList
#define NdisAllocateCloneOidRequest sdv_NdisAllocateCloneOidRequest
#define NdisAllocateFragmentNetBufferList sdv_NdisAllocateFragmentNetBufferList
#define NdisAllocateGenericObject sdv_NdisAllocateGenericObject
#define NdisAllocateIoWorkItem sdv_NdisAllocateIoWorkItem
#define NdisAllocateMdl sdv_NdisAllocateMdl
#define NdisAllocateNetBuffer sdv_NdisAllocateNetBuffer
#define NdisAllocateNetBufferAndNetBufferList sdv_NdisAllocateNetBufferAndNetBufferList
#define NdisAllocateNetBufferList sdv_NdisAllocateNetBufferList
#define NdisAllocateNetBufferListContext sdv_NdisAllocateNetBufferListContext
#define NdisAllocateNetBufferListPool sdv_NdisAllocateNetBufferListPool
#define NdisAllocateNetBufferMdlAndData sdv_NdisAllocateNetBufferMdlAndData
#define NdisAllocateNetBufferPool sdv_NdisAllocateNetBufferPool
#define NdisAllocateReassembledNetBufferList sdv_NdisAllocateReassembledNetBufferList
#define NdisAllocateTimerObject sdv_NdisAllocateTimerObject
#define NdisCancelOidRequest sdv_NdisCancelOidRequest
#define NdisCancelSendNetBufferLists sdv_NdisCancelSendNetBufferLists
#define NdisCancelTimerObject sdv_NdisCancelTimerObject
#define NdisCloseAdapterEx sdv_NdisCloseAdapterEx
#define NdisCompleteBindAdapterEx sdv_NdisCompleteBindAdapterEx
#define NdisCompleteNetPnPEvent sdv_NdisCompleteNetPnPEvent
#define NdisCompleteUnbindAdapterEx sdv_NdisCompleteUnbindAdapterEx
#define NdisCopyFromNetBufferToNetBuffer sdv_NdisCopyFromNetBufferToNetBuffer
#define NdisCopyReceiveNetBufferListInfo sdv_NdisCopyReceiveNetBufferListInfo
#define NdisCopySendNetBufferListInfo sdv_NdisCopySendNetBufferListInfo
#define NdisDeregisterDeviceEx sdv_NdisDeregisterDeviceEx
#define NdisDeregisterProtocolDriver sdv_NdisDeregisterProtocolDriver
#define NdisEnumerateFilterModules sdv_NdisEnumerateFilterModules
#define NdisFCancelOidRequest sdv_NdisFCancelOidRequest
#define NdisFCancelSendNetBufferLists sdv_NdisFCancelSendNetBufferLists
#define NdisFDeregisterFilterDriver sdv_NdisFDeregisterFilterDriver
#define NdisFDevicePnPEventNotify sdv_NdisFDevicePnPEventNotify
#define NdisFIndicateReceiveNetBufferLists sdv_NdisFIndicateReceiveNetBufferLists
#define NdisFIndicateStatus sdv_NdisFIndicateStatus
#define NdisFNetPnPEvent sdv_NdisFNetPnPEvent
#define NdisFOidRequest sdv_NdisFOidRequest
#define NdisFOidRequestComplete sdv_NdisFOidRequestComplete
#define NdisFPauseComplete sdv_NdisFPauseComplete
#define NdisFreeCloneNetBufferList sdv_NdisFreeCloneNetBufferList
#define NdisFreeCloneOidRequest sdv_NdisFreeCloneOidRequest
#define NdisFreeFragmentNetBufferList sdv_NdisFreeFragmentNetBufferList
#define NdisFreeGenericObject sdv_NdisFreeGenericObject
#define NdisFreeIoWorkItem sdv_NdisFreeIoWorkItem
#define NdisFreeMdl sdv_NdisFreeMdl
#define NdisFreeNetBuffer sdv_NdisFreeNetBuffer
#define NdisFreeNetBufferList sdv_NdisFreeNetBufferList
#define NdisFreeNetBufferListContext sdv_NdisFreeNetBufferListContext
#define NdisFreeNetBufferListPool sdv_NdisFreeNetBufferListPool
#define NdisFreeNetBufferPool sdv_NdisFreeNetBufferPool
#define NdisFreeReassembledNetBufferList sdv_NdisFreeReassembledNetBufferList
#define NdisFreeTimerObject sdv_NdisFreeTimerObject
#define NdisFRegisterFilterDriver sdv_NdisFRegisterFilterDriver
#define NdisFRestartComplete sdv_NdisFRestartComplete
#define NdisFRestartFilter sdv_NdisFRestartFilter
#define NdisFReturnNetBufferLists sdv_NdisFReturnNetBufferLists
#define NdisFSendNetBufferLists sdv_NdisFSendNetBufferLists
#define NdisFSendNetBufferListsComplete sdv_NdisFSendNetBufferListsComplete
#define NdisFSetAttributes sdv_NdisFSetAttributes
#define NdisGetDataBuffer sdv_NdisGetDataBuffer
#define NdisGetMdlPhysicalArraySize sdv_NdisGetMdlPhysicalArraySize
#define NdisGetPoolFromNetBuffer sdv_NdisGetPoolFromNetBuffer
#define NdisGetPoolFromNetBufferList sdv_NdisGetPoolFromNetBufferList
#define NdisMAllocateNetBufferSGList sdv_NdisMAllocateNetBufferSGList
#define NdisMAllocateSharedMemory sdv_NdisMAllocateSharedMemory
#define NdisMAllocateSharedMemoryAsyncEx sdv_NdisMAllocateSharedMemoryAsyncEx
#define NdisMDeregisterMiniportDriver sdv_NdisMDeregisterMiniportDriver
#define NdisMFreeNetBufferSGList sdv_NdisMFreeNetBufferSGList
#define NdisMGetBusData sdv_NdisMGetBusData
#define NdisMIndicateReceiveNetBufferLists sdv_NdisMIndicateReceiveNetBufferLists
#define NdisMIndicateStatusEx sdv_NdisMIndicateStatusEx
#define NdisMNetPnPEvent sdv_NdisMNetPnPEvent
#define NdisMOidRequestComplete sdv_NdisMOidRequestComplete
#define NdisMPauseComplete sdv_NdisMPauseComplete
#define NdisMQueueDpc sdv_NdisMQueueDpc
#define NdisMRegisterMiniportDriver sdv_NdisMRegisterMiniportDriver
#define NdisMRestartComplete sdv_NdisMRestartComplete
#define NdisMSendNetBufferListsComplete sdv_NdisMSendNetBufferListsComplete
#define NdisMSetBusData sdv_NdisMSetBusData
#define NdisMSetMiniportAttributes sdv_NdisMSetMiniportAttributes
#define NdisOidRequest sdv_NdisOidRequest
#define NdisOpenAdapterEx sdv_NdisOpenAdapterEx
#define NdisOpenConfigurationEx sdv_NdisOpenConfigurationEx
#define NdisQueryMdl sdv_NdisQueryMdl
#define NdisQueryMdlOffset sdv_NdisQueryMdlOffset
#define NdisQueryNetBufferPhysicalCount sdv_NdisQueryNetBufferPhysicalCount
#define NdisQueueIoWorkItem sdv_NdisQueueIoWorkItem
#define NdisRegisterDeviceEx sdv_NdisRegisterDeviceEx
#define NdisRegisterProtocolDriver sdv_NdisRegisterProtocolDriver
#define NdisRetreatNetBufferDataStart sdv_NdisRetreatNetBufferDataStart
#define NdisRetreatNetBufferListDataStart sdv_NdisRetreatNetBufferListDataStart
#define NdisReturnNetBufferLists sdv_NdisReturnNetBufferLists
#define NdisSendNetBufferLists sdv_NdisSendNetBufferLists
#define NdisSetOptionalHandlers sdv_NdisSetOptionalHandlers
#define NdisSetTimerObject sdv_NdisSetTimerObject
#define NdisUnbindAdapter sdv_NdisUnbindAdapter
#define NetAllocateMdl sdv_NetAllocateMdl
#define NetFreeMdl sdv_NetFreeMdl
#define NetTimerCallback sdv_NetTimerCallback
#define NdisMRegisterIoPortRange sdv_NdisMRegisterIoPortRange
#define NDIS_LOWER_IRQL sdv_NDIS_LOWER_IRQL
#define NDIS_RAISE_IRQL_TO_DISPATCH sdv_NDIS_RAISE_IRQL_TO_DISPATCH
#define NdisWaitEvent sdv_NdisWaitEvent
#define NdisStallExecution sdv_NdisStallExecution
#define NDIS_RELEASE_MUTEX sdv_NDIS_RELEASE_MUTEX
#define NDIS_WAIT_FOR_MUTEX sdv_NDIS_WAIT_FOR_MUTEX
#define NdisAcquireReadWriteLock sdv_NdisAcquireReadWriteLock
#define NdisAllocateFromNPagedLookasideList sdv_NdisAllocateFromNPagedLookasideList
#define NdisAnsiStringToUnicodeString sdv_NdisAnsiStringToUnicodeString
#define NdisClAddParty sdv_NdisClAddParty
#define NdisClCloseAddressFamily sdv_NdisClCloseAddressFamily
#define NdisClCloseCall sdv_NdisClCloseCall
#define NdisClDeregisterSap sdv_NdisClDeregisterSap
#define NdisClDropParty sdv_NdisClDropParty
#define NdisClGetProtocolVcContextFromTapiCallId sdv_NdisClGetProtocolVcContextFromTapiCallId
#define NdisClIncomingCallComplete sdv_NdisClIncomingCallComplete
#define NdisClMakeCall sdv_NdisClMakeCall
#define NdisClModifyCallQoS sdv_NdisClModifyCallQoS
#define NdisClNotifyCloseAddressFamilyComplete sdv_NdisClNotifyCloseAddressFamilyComplete
#define NdisClOpenAddressFamilyEx sdv_NdisClOpenAddressFamilyEx
#define NdisCloseConfiguration sdv_NdisCloseConfiguration
#define NdisCloseFile sdv_NdisCloseFile
#define NdisClRegisterSap sdv_NdisClRegisterSap
#define NdisCmActivateVc sdv_NdisCmActivateVc
#define NdisCmAddPartyComplete sdv_NdisCmAddPartyComplete
#define NdisCmCloseAddressFamilyComplete sdv_NdisCmCloseAddressFamilyComplete
#define NdisCmCloseCallComplete sdv_NdisCmCloseCallComplete
#define NdisCmDeactivateVc sdv_NdisCmDeactivateVc
#define NdisCmDeregisterSapComplete sdv_NdisCmDeregisterSapComplete
#define NdisCmDispatchCallConnected sdv_NdisCmDispatchCallConnected
#define NdisCmDispatchIncomingCall sdv_NdisCmDispatchIncomingCall
#define NdisCmDispatchIncomingCallQoSChange sdv_NdisCmDispatchIncomingCallQoSChange
#define NdisCmDispatchIncomingCloseCall sdv_NdisCmDispatchIncomingCloseCall
#define NdisCmDispatchIncomingDropParty sdv_NdisCmDispatchIncomingDropParty
#define NdisCmDropPartyComplete sdv_NdisCmDropPartyComplete
#define NdisCmMakeCallComplete sdv_NdisCmMakeCallComplete
#define NdisCmModifyCallQoSComplete sdv_NdisCmModifyCallQoSComplete
#define NdisCmNotifyCloseAddressFamily sdv_NdisCmNotifyCloseAddressFamily
#define NdisCmOpenAddressFamilyComplete sdv_NdisCmOpenAddressFamilyComplete
#define NdisCmRegisterAddressFamilyEx sdv_NdisCmRegisterAddressFamilyEx
#define NdisCmRegisterSapComplete sdv_NdisCmRegisterSapComplete
#define NdisCoAssignInstanceName sdv_NdisCoAssignInstanceName
#define NdisCoCreateVc sdv_NdisCoCreateVc
#define NdisCoDeleteVc sdv_NdisCoDeleteVc
#define NdisCoGetTapiCallId sdv_NdisCoGetTapiCallId
#define NdisCoOidRequest sdv_NdisCoOidRequest
#define NdisCoOidRequestComplete sdv_NdisCoOidRequestComplete
#define NdisCoSendNetBufferLists sdv_NdisCoSendNetBufferLists
#define NdisDeleteNPagedLookasideList sdv_NdisDeleteNPagedLookasideList
#define NdisEqualMemory sdv_NdisEqualMemory
#define NdisEqualString sdv_NdisEqualString
#define NdisEqualUnicodeString sdv_NdisEqualUnicodeString
#define NdisFreeSpinLock sdv_NdisFreeSpinLock
#define NdisFreeString sdv_NdisFreeString
#define NdisFreeToNPagedLookasideList sdv_NdisFreeToNPagedLookasideList
#define NdisGeneratePartialCancelId sdv_NdisGeneratePartialCancelId
#define NdisGetCurrentProcessorCounts sdv_NdisGetCurrentProcessorCounts
#define NdisGetDriverHandle sdv_NdisGetDriverHandle
#define NdisGetRoutineAddress sdv_NdisGetRoutineAddress
#define NdisGetSharedDataAlignment sdv_NdisGetSharedDataAlignment
#define NdisGetVersion sdv_NdisGetVersion
#define NdisIfAddIfStackEntry sdv_NdisIfAddIfStackEntry
#define NdisIfAllocateNetLuidIndex sdv_NdisIfAllocateNetLuidIndex
#define NdisIfDeleteIfStackEntry sdv_NdisIfDeleteIfStackEntry
#define NdisIfDeregisterInterface sdv_NdisIfDeregisterInterface
#define NdisIfDeregisterProvider sdv_NdisIfDeregisterProvider
#define NdisIfFreeNetLuidIndex sdv_NdisIfFreeNetLuidIndex
#define NdisIfGetInterfaceIndexFromNetLuid sdv_NdisIfGetInterfaceIndexFromNetLuid
#define NdisIfGetNetLuidFromInterfaceIndex sdv_NdisIfGetNetLuidFromInterfaceIndex
#define NdisIfQueryBindingIfIndex sdv_NdisIfQueryBindingIfIndex
#define NdisIfRegisterInterface sdv_NdisIfRegisterInterface
#define NdisIfRegisterProvider sdv_NdisIfRegisterProvider
#define NdisIMAssociateMiniport sdv_NdisIMAssociateMiniport
#define NdisIMCancelInitializeDeviceInstance sdv_NdisIMCancelInitializeDeviceInstance
#define NdisIMDeInitializeDeviceInstance sdv_NdisIMDeInitializeDeviceInstance
#define NdisIMGetBindingContext sdv_NdisIMGetBindingContext
#define NdisIMInitializeDeviceInstanceEx sdv_NdisIMInitializeDeviceInstanceEx
#define NdisInitAnsiString sdv_NdisInitAnsiString
#define NdisInitializeListHead sdv_NdisInitializeListHead
#define NdisInitializeNPagedLookasideList sdv_NdisInitializeNPagedLookasideList
#define NdisInitializeSListHead sdv_NdisInitializeSListHead
#define NdisInitializeString sdv_NdisInitializeString
#define NdisInitUnicodeString sdv_NdisInitUnicodeString
#define NdisInterlockedAddUlong sdv_NdisInterlockedAddUlong
#define NdisInterlockedDecrement sdv_NdisInterlockedDecrement
#define NdisInterlockedInsertHeadList sdv_NdisInterlockedInsertHeadList
#define NdisInterlockedInsertTailList sdv_NdisInterlockedInsertTailList
#define NdisInterlockedPopEntrySList sdv_NdisInterlockedPopEntrySList
#define NdisInterlockedPushEntrySList sdv_NdisInterlockedPushEntrySList
#define NdisInterlockedRemoveHeadList sdv_NdisInterlockedRemoveHeadList
#define NdisMapFile sdv_NdisMapFile
#define NdisMCmActivateVc sdv_NdisMCmActivateVc
#define NdisMCmAddPartyComplete sdv_NdisMCmAddPartyComplete
#define NdisMCmCloseAddressFamilyComplete sdv_NdisMCmCloseAddressFamilyComplete
#define NdisMCmCloseCallComplete sdv_NdisMCmCloseCallComplete
#define NdisMCmCreateVc sdv_NdisMCmCreateVc
#define NdisMCmDeactivateVc sdv_NdisMCmDeactivateVc
#define NdisMCmDeleteVc sdv_NdisMCmDeleteVc
#define NdisMCmDeregisterSapComplete sdv_NdisMCmDeregisterSapComplete
#define NdisMCmDispatchCallConnected sdv_NdisMCmDispatchCallConnected
#define NdisMCmDispatchIncomingCall sdv_NdisMCmDispatchIncomingCall
#define NdisMCmDispatchIncomingCallQoSChange sdv_NdisMCmDispatchIncomingCallQoSChange
#define NdisMCmDispatchIncomingCloseCall sdv_NdisMCmDispatchIncomingCloseCall
#define NdisMCmDispatchIncomingDropParty sdv_NdisMCmDispatchIncomingDropParty
#define NdisMCmDropPartyComplete sdv_NdisMCmDropPartyComplete
#define NdisMCmMakeCallComplete sdv_NdisMCmMakeCallComplete
#define NdisMCmModifyCallQoSComplete sdv_NdisMCmModifyCallQoSComplete
#define NdisMCmNotifyCloseAddressFamily sdv_NdisMCmNotifyCloseAddressFamily
#define NdisMCmOidRequest sdv_NdisMCmOidRequest
#define NdisMCmOidRequestComplete sdv_NdisMCmOidRequestComplete
#define NdisMCmOpenAddressFamilyComplete sdv_NdisMCmOpenAddressFamilyComplete
#define NdisMCmRegisterAddressFamilyEx sdv_NdisMCmRegisterAddressFamilyEx
#define NdisMCmRegisterSapComplete sdv_NdisMCmRegisterSapComplete
#define NdisMCoActivateVcComplete sdv_NdisMCoActivateVcComplete
#define NdisMCoDeactivateVcComplete sdv_NdisMCoDeactivateVcComplete
#define NdisMCoIndicateReceiveNetBufferLists sdv_NdisMCoIndicateReceiveNetBufferLists
#define NdisMCoIndicateStatusEx sdv_NdisMCoIndicateStatusEx
#define NdisMCompleteDmaTransfer sdv_NdisMCompleteDmaTransfer
#define NdisMCoOidRequestComplete sdv_NdisMCoOidRequestComplete
#define NdisMCoSendNetBufferListsComplete sdv_NdisMCoSendNetBufferListsComplete
#define NdisMCreateLog sdv_NdisMCreateLog
#define NdisMDeregisterDmaChannel sdv_NdisMDeregisterDmaChannel
#define NdisMDeregisterIoPortRange sdv_NdisMDeregisterIoPortRange
#define NdisMFlushLog sdv_NdisMFlushLog
#define NdisMFreePort sdv_NdisMFreePort
#define NdisMFreeSharedMemory sdv_NdisMFreeSharedMemory
#define NdisMGetDeviceProperty sdv_NdisMGetDeviceProperty
#define NdisMGetDmaAlignment sdv_NdisMGetDmaAlignment
#define NdisMMapIoSpace sdv_NdisMMapIoSpace
#define NdisMQueryAdapterInstanceName sdv_NdisMQueryAdapterInstanceName
#define NdisMReadDmaCounter sdv_NdisMReadDmaCounter
#define NdisMRegisterDmaChannel sdv_NdisMRegisterDmaChannel
#define NdisMRemoveMiniport sdv_NdisMRemoveMiniport
#define NdisMResetComplete sdv_NdisMResetComplete
#define NdisMSetupDmaTransfer sdv_NdisMSetupDmaTransfer
#define NdisMSleep sdv_NdisMSleep
#define NdisMUnmapIoSpace sdv_NdisMUnmapIoSpace
#define NdisMUpdateSharedMemory sdv_NdisMUpdateSharedMemory
#define NdisMWriteLogData sdv_NdisMWriteLogData
#define NdisOpenConfigurationKeyByIndex sdv_NdisOpenConfigurationKeyByIndex
#define NdisOpenConfigurationKeyByName sdv_NdisOpenConfigurationKeyByName
#define NdisOpenFile sdv_NdisOpenFile
#define NdisQueryAdapterInstanceName sdv_NdisQueryAdapterInstanceName
#define NdisQueryDepthSList sdv_NdisQueryDepthSList
#define NdisReadConfiguration sdv_NdisReadConfiguration
#define NdisReadNetworkAddress sdv_NdisReadNetworkAddress
#define NdisReEnumerateProtocolBindings sdv_NdisReEnumerateProtocolBindings
#define NdisReleaseReadWriteLock sdv_NdisReleaseReadWriteLock
#define NdisResetEvent sdv_NdisResetEvent
#define NdisSetEvent sdv_NdisSetEvent
#define NdisSystemProcessorCount sdv_NdisSystemProcessorCount
#define NdisUnicodeStringToAnsiString sdv_NdisUnicodeStringToAnsiString
#define NdisUnmapFile sdv_NdisUnmapFile
#define NdisUpcaseUnicodeString sdv_NdisUpcaseUnicodeString
#define NdisWriteConfiguration sdv_NdisWriteConfiguration
#define NdisWriteErrorLogEntry sdv_NdisWriteErrorLogEntry
#define NdisWriteEventLogEntry sdv_NdisWriteEventLogEntry
#define NdisReadPortBufferUchar sdv_NdisReadPortBufferUchar
#define NdisWritePortBufferUchar sdv_NdisWritePortBufferUchar
#define NdisReadPortBufferUlong sdv_NdisReadPortBufferUlong
#define NdisWritePortBufferUlong sdv_NdisWritePortBufferUlong
#define NdisReadPortBufferUshort sdv_NdisReadPortBufferUshort
#define NdisWritePortBufferUshort sdv_NdisWritePortBufferUshort
#define NdisReadPortUchar sdv_NdisReadPortUchar
#define NdisWritePortUchar sdv_NdisWritePortUchar
#define NdisReadPortUlong sdv_NdisReadPortUlong
#define NdisWritePortUlong sdv_NdisWritePortUlong
#define NdisReadPortUshort sdv_NdisReadPortUshort
#define NdisWritePortUshort sdv_NdisWritePortUshort
