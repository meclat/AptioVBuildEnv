/*++ BUILD Version: 0000    

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    SoftHIDInputKbdMapper

Abstract:
    Implementation of CSoftHIDInputKbdMapper
 
Revision History:

--*/ 
#include "stdafx.h"
#include <dsfif.h>
#include <SoftHidUsbIf.h>
#include <InputKbd.h>
#include ".\SoftHidDevice.h"
#include "SoftHID.h"
#include "SoftHIDInputKbdMapper.h"
#include "Common.h"

///////////////////////////////////////////////////////////////////////////////
// HID Report Descriptor
// Generated by the HID Descriptor Tool which can be downloaded from usb.org here:
// http://www.usb.org/developers/hidpage/
BYTE CSoftHIDInputKbdMapper::m_ReportDescriptor[63] = 
{
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
    0x95, 0x03,                    //   REPORT_COUNT (3)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x05, 0x08,                    //   USAGE_PAGE (LEDs)
    0x19, 0x01,                    //   USAGE_MINIMUM (Num Lock)
    0x29, 0x03,                    //   USAGE_MAXIMUM (Scroll Lock)
    0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x05,                    //   REPORT_SIZE (5)
    0x91, 0x03,                    //   OUTPUT (Cnst,Var,Abs)
    0x95, 0x06,                    //   REPORT_COUNT (6)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xc0                           // END_COLLECTION
};


// CSoftHIDInputKbdMapper
// SoftHIDInputKbdMapper Class implementation
CSoftHIDInputKbdMapper::CSoftHIDInputKbdMapper()
/*++
Routine Description:
    Constructor for CSoftHIDInputKbdMapper 

Synchronization: None
 
Arguments:
    None

Return Value:
    None
    
--*/
{
    InitMemberVariables();

} // CSoftHIDInputKbdMapper::CSoftHIDInputKbdMapper


CSoftHIDInputKbdMapper::~CSoftHIDInputKbdMapper()
/*++
Routine Description:
    Destructor for CSoftHidInputKbdMapper 

Synchronization: None
 
Arguments:
    None

Return Value:
    None
    
--*/
{
    // Stop internal thread
    (void)CMessageTask::End();

    // Disconnect event sink from the source
    TearDownEventSink(m_piConnectionPointKbd, m_dwKbdSinkCookie);

    // Release the ISoftHIDProtocolXlator interface
    RELEASE(m_piSoftProtXlator);
    // Release the ISoftKeyboard interface
    RELEASE(m_piSoftKeyboard);
    // Release IMalloc interface
    RELEASE(m_pMalloc);

    // Delete safearray with Report Descriptor data
    if (NULL != m_psaReportDescriptor)
    {
        (void)::SafeArrayDestroy(m_psaReportDescriptor);
        m_psaReportDescriptor = NULL;
    }

    // Initialize the member variables 
    InitMemberVariables();

} // CSoftHIDInputKbdMapper::~CSoftHIDInputKbdMapper

void CSoftHIDInputKbdMapper::InitMemberVariables()
/*++
Routine Description:
    Initialize member variables of the class CSoftHIDInputKbdMapper 

Synchronization: 
    None
 
Arguments:
    None
Return Value:
    None
--*/
{
    m_sInputMask = 0;
    m_ucOutputMask = 0;
    m_piSoftKeyboard = NULL;
    m_piSoftProtXlator = NULL;

    m_pMalloc = NULL;
    m_piConnectionPointKbd = NULL;
    m_dwKbdSinkCookie = 0;
    m_bKeySeqLen = 0;
    m_KeyTouchedMsg = 0;
    m_OutReportReadyMsg = 0;
    m_psaReportDescriptor = NULL;

    ZeroMemory(&m_InputReport, sizeof(m_InputReport));

} // CSoftHIDInputKbdMapper::InitMemberVariables

STDMETHODIMP CSoftHIDInputKbdMapper::get_InputReportMask(SHORT* pVal)
/*++
Routine Description:
    Implements the get_InputReportMask property for the interface
    ISoftHIDInputKdbMapper.

Synchronization: 
    None
 
Arguments:
    psMask - caller allocated space to hold the returned value

Return Value:
    E_POINTER
        Invalid pointer for output parameter
    From called function    
    
--*/
{
    HRESULT hr = S_OK;

    // Check if we have valid pointer to returned parameter
    IfFalseHrGo(NULL != pVal, E_POINTER);
    *pVal = m_sInputMask;
    
Exit:
    return hr;

} // CSoftHIDInputKbdMapper::get_InputReportMask

STDMETHODIMP CSoftHIDInputKbdMapper::put_InputReportMask(SHORT newVal)
/*++
Routine Description:
    Implements the put_InputReportMask property for the interface
    ISoftHIDInputKdbMapper.

Synchronization: 
    None
 
Arguments:
    sMask - new value of the mask

Return Value:
    S_OK    
    
--*/
{
    HRESULT hr = S_OK;

    m_sInputMask = newVal;
    
    return hr;

} // CSoftHIDInputKbdMapper::put_InputReportMask


STDMETHODIMP CSoftHIDInputKbdMapper::get_OutputReportMask(BYTE* pVal)
/*++
Routine Description:
    Implements the get_OutputReportMask property for the interface
    ISoftHIDInputKdbMapper.

Synchronization: 
    None
 
Arguments:
    pucMask - caller allocated space to hold the returned value

Return Value:
    E_POINTER
        Invalid pointer for output parameter
    From called function    
    
--*/
{
    HRESULT hr = S_OK;

    // Check if we have valid pointer to returned parameter
    IfFalseHrGo(NULL != pVal, E_POINTER);
    *pVal = m_ucOutputMask;

Exit:
    return hr;

} // CSoftHIDInputKbdMapper::get_OutputReportMask

STDMETHODIMP CSoftHIDInputKbdMapper::put_OutputReportMask(BYTE newVal)
/*++
Routine Description:
    Implements the put_OutputReportMask property for the interface
    ISoftHIDInputKdbMapper.

Synchronization: 
    None
 
Arguments:
    ucMask - new value of the mask

Return Value:
   S_OK   
    
--*/
{
    HRESULT hr = S_OK;

    m_ucOutputMask = newVal;

    return hr;

} // CSoftHIDInputKbdMapper::put_OutputReportMask

STDMETHODIMP CSoftHIDInputKbdMapper::AttachKbd(SoftKeyboard *pSoftKbd)
/*++
Routine Description:
    Implements the AttachKbd method for the interface
    ISoftHIDInputKdbMapper. Allows a keyboard input device
    to attach to the HID device object.

Synchronization: 
    None
 
Arguments:
    pSoftKbd - device to be attached

Return Value:
    S_OK    
    
--*/
{
    HRESULT hr = S_OK;

    KEYBOARD_ATTRIBUTES* pKbdAttrib = NULL;
    KEYBOARD_TYPEMATIC_PARAMETERS* pTypematic = NULL;

    // Disconnect event sink from the old source
    TearDownEventSink(m_piConnectionPointKbd, m_dwKbdSinkCookie);

    // Set reference to ISoftKeyboard interface
    RELEASE(m_piSoftKeyboard);
    if (NULL != pSoftKbd)
    {
        IfFailHrGo(reinterpret_cast<IUnknown *>(pSoftKbd)->QueryInterface(__uuidof(ISoftInputKbdDevice),
                                           reinterpret_cast<void **>(&m_piSoftKeyboard)));

        // Set HID settings
        IfFailHrGo(m_piSoftKeyboard->get_Attributes(&pKbdAttrib));
        pKbdAttrib->usKeyboardMode = KEYBOARD_HID_USAGE;
        IfFailHrGo(m_piSoftKeyboard->put_Attributes(pKbdAttrib));

        // Disable autorepeat function
        IfFailHrGo(m_piSoftKeyboard->get_Typematic(&pTypematic));
        pTypematic->ulDelay = KEYBOARD_TYPEMATIC_DELAY_INFINITE;
        IfFailHrGo(m_piSoftKeyboard->put_Typematic(pTypematic));

        // Install event sink
        IfFailHrGo(SetupEventSink(
                        m_piSoftKeyboard,
                        GetUnknown(),
                        __uuidof(ISoftInputKbdDeviceEvents),
                        m_piConnectionPointKbd,
                        m_dwKbdSinkCookie));
    }

Exit:
    if (NULL != pKbdAttrib)
    {
        m_pMalloc->Free(pKbdAttrib);
    }

    if (NULL != pTypematic)
    {
        m_pMalloc->Free(pTypematic);
    }

    return hr;

} // CSoftHIDInputKbdMapper::AttachKbd

STDMETHODIMP CSoftHIDInputKbdMapper::AttachProtocolXlator(SoftHIDProtocolXlator* pSoftProtXlator)
/*++
Routine Description:
    Implements the AttachProtocolXlator method for the interface
    ISoftHIDInputKdbMapper. Allows a SoftHIDUSBDevice object
    to attach to the HID device object.

Synchronization: 
    None
 
Arguments:
    m_piProtocolXlator - protocol translator to be attached

Return Value:
    S_OK    
    
--*/
{
    HRESULT hr = S_OK;

    // Disconnect from the old object
    IfFailHrGo(Disconnect());

    // Set reference to ISoftHIDProtocolXlator interface
    RELEASE(m_piSoftProtXlator);
    if (NULL != pSoftProtXlator)
    {
        IfFailHrGo(reinterpret_cast<IUnknown *>(pSoftProtXlator)->QueryInterface(__uuidof(ISoftHIDProtocolXlator),
                                           reinterpret_cast<void **>(&m_piSoftProtXlator)));
      
        // Write Report Descriptor
        IfFailHrGo(m_piSoftProtXlator->WriteReportDescriptor(m_psaReportDescriptor));

        // Connect to the new object
        IfFailHrGo(Connect(m_piSoftProtXlator));

        // Set device type as keyboard
        IfFailHrGo(m_piSoftProtXlator->put_DeviceType(DEVICE_TYPE_KEYBOARD));
    }

Exit:
    return hr;

} // CSoftHIDInputKbdMapper::AttachProtocolXlator
STDMETHODIMP CSoftHIDInputKbdMapper::KeyTouched(void)
/*++
Routine Description:
    Implements the KeyTouched event from ISoftInputKbdDeviceEvents 
    interface. Called by SoftKeyboard object when it gets new
    input in its buffer. 
    Schedules processing of contents of keyboard buffer.

Synchronization: 
    None
 
Arguments:
    None

Return Value:
    E_FAIL
        Could not send message to task
    S_OK
        Success
--*/
{
    HRESULT hr = S_OK;

    IfFailHrGo(PostMessage2Task(m_KeyTouchedMsg, 0, 0));

Exit:
    return hr;    

} // CSoftHIDInputKbdMapper::KeyTouched


HRESULT CSoftHIDInputKbdMapper::FinalConstruct()
/*++
Routine Description:
    Overwrites the default FinalConstruct. Creates the default
    properties, gets pointer to COM task memory allocator.

Synchronization: 
    None
 
Arguments:
    None
    
Return Value:
    E_OUTOFMEMORY
        Could not create safearray for Report Descriptor data
    From called function
--*/
{
    BYTE HUGEP* pArrayData = NULL;
    HRESULT     hr = S_OK;

    IfFailHrGo(CoGetMalloc(1, &m_pMalloc));

    // Register notification messages
    IfFailHrGo(RegisterMessage(MSG_KEYTOUCHED, &m_KeyTouchedMsg));
    IfFailHrGo(RegisterMessage(MSG_OUTREPORTREADY, &m_OutReportReadyMsg));

    // Create safearray with Report Descriptor data
    m_psaReportDescriptor = SafeArrayCreateVector(VT_UI1, 0, sizeof(m_ReportDescriptor));
    IfFalseHrGo(NULL != m_psaReportDescriptor, E_OUTOFMEMORY);

    IfFailHrGo(::SafeArrayAccessData(m_psaReportDescriptor, (void HUGEP**)&pArrayData));

    // Copy Report Descriptor data into safearray
    CopyMemory(pArrayData, &m_ReportDescriptor, sizeof(m_ReportDescriptor));

    IfFailHrGo(::SafeArrayUnaccessData(m_psaReportDescriptor));

    // Start internal thread
    IfFailHrGo(CMessageTask::Start(DEFAULT_SYNC_DELAY));

    // Call OnConstruct method of CSoftHIDDevice class
    IfFailHrGo(CSoftHID::OnConstruct(this, m_OutReportReadyMsg));

Exit:
    return hr;

} // CSoftHIDInputKbdMapper::FinalConstruct


BOOLEAN CSoftHIDInputKbdMapper::GenInputReport(
                USHORT usUsageID, USHORT usFlag)
/*++
Routine Description:
    Generates new input report based on new keyboard event

Synchronization: 
    None
 
Arguments:
    usUsageID - HID Usage ID of key pressed/released.
    usFlag - Flag that specifies whether key was pressed or released.
    
Return Value:
    TRUE
        Success
    FALSE
        Could not generate new input report
--*/
{
    BOOLEAN fRet = TRUE;

    // Treat modifier keys separately
    if (IsModifierKey(usUsageID))
    {
        if (KEY_MAKE == (usFlag & KEY_MAKE)) {
            // Set modifier key
            m_InputReport.bModifier |= XlateModifierKey(usUsageID);
        }
        else {
            // Clear modifier key
            m_InputReport.bModifier &= ~XlateModifierKey(usUsageID);
        }
    }
    // Regular keys write to the array
    else
    {
        // New key was pressed: add it to the array
        if (KEY_MAKE == (usFlag & KEY_MAKE))
        {
            if (m_bKeySeqLen < MAX_KEYSEQ) {
                // This keyboard supports only one-byte Usage IDs
                m_InputReport.bUsageID[m_bKeySeqLen++] = (BYTE)usUsageID;
            }
            else
                fRet = FALSE;
        }
        // Old key was released: delete it from the array
        else
        {
            // Find key in the array
            for(BYTE i = 0; i < m_bKeySeqLen; i++)
            {
                if (m_InputReport.bUsageID[i] == usUsageID)
                {
                    // Delete key from the array
                    for(BYTE j = i; j < m_bKeySeqLen-1; j++) {
                        m_InputReport.bUsageID[j] = m_InputReport.bUsageID[j+1];
                    }
                    m_InputReport.bUsageID[--m_bKeySeqLen] = 0;
                    break;
                }
            }
        }
    }

    return fRet;

} // CSoftHIDInputKbdMapper::GenInputReport


HRESULT CSoftHIDInputKbdMapper::ProcessKbdInput()
/*++
Routine Description:
    Reads and handles data from input keyboard buffer.

Synchronization: 
    None
 
Arguments:
    None
    
Return Value:
    S_OK
        Success
    E_FAIL
        Could not read data from keyboard buffer
--*/
{
    USHORT               usUnits = 0;
    KEYBOARD_INPUT_DATA* pKbdData = NULL;
    HRESULT              hr = S_OK;

    // Read data from keyboard buffer
    IfFalseHrGo(NULL != m_piSoftKeyboard, E_FAIL);
    IfFailHrGo(m_piSoftKeyboard->Read(&usUnits, &pKbdData));
    IfFalseHrGo(NULL != pKbdData, E_FAIL);

    // Check whether Protocol Translator interface pointer is set
    // If not, do not fail the function, but dispose the data
    IfFalseHrGo(NULL != m_piSoftProtXlator, S_OK);

    // Process keyboard data
    for(USHORT i = 0; i < usUnits; i++)
    {
        // Generate Input Report
        if (GenInputReport((USHORT)pKbdData[i].ulMakeCode, pKbdData[i].usFlags))
        {
            // Send Input Report
            IfFailHrGo(SendInputReport(&m_InputReport, sizeof(m_InputReport)));
        }
        // Report phantom state
        else
        {
            HID_INPUTREPORT PhantomReport;

            // Initialize Phantom report. Modifier byte is still reported.
            FillMemory(&PhantomReport, sizeof(PhantomReport), 1);
            PhantomReport.bReserved = 0;
            PhantomReport.bModifier = m_InputReport.bModifier;

            // Send Phantom Report
            IfFailHrGo(SendInputReport(&PhantomReport, sizeof(PhantomReport)));
        }
    }

Exit:
    // Release COM buffer
    if (NULL != pKbdData)
    {
        m_pMalloc->Free(pKbdData);
    }

    return hr;

} // CSoftHIDInputKbdMapper::ProcessKbdInput


HRESULT CSoftHIDInputKbdMapper::ProcessKbdOutput(SAFEARRAY* psa)
/*++
Routine Description:
    Processes keyboard output report.

Synchronization: 
    None
 
Arguments:
    psa - pointer to safearray containing Output Report data
    
Return Value:
    S_OK
        Success
    E_UNEXPECTED
        Unxpected size of Output Report data buffer
    E_FAIL
        Could not report indicator status to keyboard object.
--*/
{
    BYTE HUGEP*                   pArrayData = NULL;
    LONG                          lLBound = 0;
    LONG                          lUBound = 0;
    HRESULT                       hr = S_OK;
    KEYBOARD_INDICATOR_PARAMETERS Indicator; ZeroMemory(&Indicator, sizeof(Indicator));

    IfFalseHrGo(NULL != m_piSoftKeyboard, E_FAIL);

    // Get SAFEARRAY size
    IfFailHrGo(SafeArrayGetLBound(psa, 1, &lLBound));
    IfFailHrGo(SafeArrayGetUBound(psa, 1, &lUBound));
    // Check the size of Output Report data
    IfFalseHrGo(1 == (lUBound - lLBound + 1), E_UNEXPECTED);

    IfFailHrGo(::SafeArrayAccessData(psa, (void HUGEP**)&pArrayData));

    // Only 5 least significant bits are valid in output report byte.
    // TODO: this would be controlled by OutputReportMask property later.
    Indicator.usLedFlags = pArrayData[0] & 0xE0;

    IfFailHrGo(::SafeArrayUnaccessData(psa));

    IfFailHrGo(m_piSoftKeyboard->put_Indicators(&Indicator));

Exit:
    // the safe array was allocated by the call to
    // m_piSoftProtXlator->ReadOutputPort in CSoftHID::Run.
    // Now we are done with it so we should free it here.
    if (NULL != psa)
    {
        (void)::SafeArrayDestroy(psa);
    }

    return hr;

} // CSoftHIDInputKbdMapper::ProcessKbdOutput


HRESULT CSoftHIDInputKbdMapper::SendInputReport
(
    PVOID pbReportData,
    ULONG cbReportData
)
/*++
Routine Description:
    Prepares safearray and sends it as Input Report to lower layer.

Synchronization: 
    None
 
Arguments:
    pbReportData - pointer to data buffer with Input Report
    cbReportData - size of the data buffer
    
Return Value:
    S_OK
        Success
    E_OUTOFMEMORY
        Could not allocate enough memory for safearray
    From called function
--*/
{
    SAFEARRAY*  psa = NULL;
    BYTE HUGEP* pArrayData = NULL;
    HRESULT     hr = S_OK;

    // Create safearray
    psa = SafeArrayCreateVector(VT_UI1, 0, cbReportData);
    IfFalseHrGo(NULL != psa, E_OUTOFMEMORY);

    IfFailHrGo(::SafeArrayAccessData(psa, (void HUGEP**)&pArrayData));

    CopyMemory(pArrayData, pbReportData, cbReportData);

    IfFailHrGo(::SafeArrayUnaccessData(psa));

    // Send Input Report
    IfFailHrGo(m_piSoftProtXlator->WriteInputReport(psa));


Exit:
    if (NULL != psa)
    {
        // Delete safearray
        ::SafeArrayDestroy(psa);
        psa = NULL;
    }

    return hr;

} // CSoftHIDInputKbdMapper::SendInputReport


void CSoftHIDInputKbdMapper::OnMsgReceived(
    CMessageTask::TASK_MSG msg, WPARAM wParam,LPARAM lParam)
/*++
Routine Description:
    Message handler routine.

Synchronization: 
    None
 
Arguments:
    msg - message received by the task
    wParam - 1-st message parameter
    lParam - 2-nd message parameter
    
Return Value:
    None
  
--*/
{
    UNREFERENCED_PARAMETER(lParam);

    if (msg == m_KeyTouchedMsg)
    {
        ProcessKbdInput();
    }
    else if (msg == m_OutReportReadyMsg)
    {
        if (0 != wParam)
        {
            ProcessKbdOutput((SAFEARRAY*)wParam);
        }
    }

} // CSoftHIDInputKbdMapper::OnMsgReceived

void CSoftHIDInputKbdMapper::TearDownEventSink
(
    IConnectionPoint *&rpiConnectionPoint,
    DWORD             &rdwCookie
)
/*++

Routine Description:
    Tears down the specified event sink if rpiConnectionPoint non-NULL
    and cookie non-zero

Arguments:
    rpiConnectionPoint - reference to connection point from which to remove event
    sink

    rdwCookie - reference to cookie returned when connection point set
    up

Synchronization:
    None

Return value:
    None
--*/
{
    if (NULL != rpiConnectionPoint)
    {
        if (0 != rdwCookie)
        {
            (void)rpiConnectionPoint->Unadvise(rdwCookie);
            rdwCookie = 0;
        }
        RELEASE(rpiConnectionPoint);
    }
}


HRESULT CSoftHIDInputKbdMapper::SetupEventSink
(
    IUnknown         *punkObject,
    IUnknown         *punkSink,
    REFIID            iidConnectionPoint,
    IConnectionPoint *&rpiConnectionPoint,
    DWORD             &rdwCookie
)
/*++

Routine Description:
    If punkObject is non-NULL installs event sink on specific
    connection point and returns IConnectionPoint and cookie.

Arguments:
    punkObject - IUnknown on object

    punkSink - IUnknown of event sink to install

    iidConnectionPoint - IID of desired connection point

    rpiConnectionPoint - connection point returned here

    rdwCookie - connection point cookie returned here

Synchronization:
    None

Return value:
    S_OK - success
    other - from called routines
--*/
{
    HRESULT                    hr = S_OK;
    IConnectionPointContainer *piConnectionPointContainer = NULL;

    rpiConnectionPoint = NULL;
    rdwCookie = 0;

    IfFalseHrGo(NULL != punkObject, S_OK);

    IfFailHrGo(punkObject->QueryInterface(IID_IConnectionPointContainer,
                                          reinterpret_cast<void **>(&piConnectionPointContainer)));

    IfFailHrGo(piConnectionPointContainer->FindConnectionPoint(iidConnectionPoint,
                                                               &rpiConnectionPoint));

    IfFailHrGo(rpiConnectionPoint->Advise(punkSink, &rdwCookie));

Exit:
    if (FAILED(hr))
    {
        RELEASE(rpiConnectionPoint);
        rdwCookie = 0;
    }
    RELEASE(piConnectionPointContainer);

    return hr;
}

