' Windows Installer utility to preview dialogs from a install database
' For use with Windows Scripting Host, CScript.exe or WScript.exe
' Copyright (c) Microsoft Corporation. All rights reserved.
' Demonstrates the use of preview APIs
'
Option Explicit

Const msiOpenDatabaseModeReadOnly = 0

' Show help if no arguments or if argument contains ?
Dim argCount : argCount = Wscript.Arguments.Count
If argCount > 0 Then If InStr(1, Wscript.Arguments(0), "?", vbTextCompare) > 0 Then argCount = 0
If argCount = 0 Then
	Wscript.Echo "Windows Installer utility to preview dialogs from an install database." &_
		vbLf & " The 1st argument is the path to an install database, relative or complete path" &_
		vbLf & " Subsequent arguments are dialogs to display (primary key of Dialog table)" &_
		vbLf & " To show a billboard, append the Control name (Control table key) and Billboard" &_
		vbLf & "       name (Billboard table key) to the Dialog name, separated with colons." &_
		vbLf & " If no dialogs specified, all dialogs in Dialog table are displayed sequentially" &_
		vbLf & " Note: The name of the dialog, if provided,  is case-sensitive" &_
		vblf &_
		vblf & "Copyright (C) Microsoft Corporation.  All rights reserved."
	Wscript.Quit 1
End If

' Connect to Windows Installer object
On Error Resume Next
Dim installer : Set installer = Nothing
Set installer = Wscript.CreateObject("WindowsInstaller.Installer") : CheckError

' Open database
Dim databasePath : databasePath = Wscript.Arguments(0)
Dim database : Set database = installer.OpenDatabase(databasePath, msiOpenDatabaseModeReadOnly) : CheckError

' Create preview object
Dim preview : Set preview = Database.EnableUIpreview : CheckError

' Get properties from Property table and put into preview object
Dim record, view : Set view = database.OpenView("SELECT `Property`,`Value` FROM `Property`") : CheckError
view.Execute : CheckError
Do
	Set record = view.Fetch : CheckError
	If record Is Nothing Then Exit Do
	preview.Property(record.StringData(1)) = record.StringData(2) : CheckError
Loop

' Loop through list of dialog names and display each one
If argCount = 1 Then ' No dialog name, loop through all dialogs
	Set view = database.OpenView("SELECT `Dialog` FROM `Dialog`") : CheckError
	view.Execute : CheckError
	Do
		Set record = view.Fetch : CheckError
		If record Is Nothing Then Exit Do
		preview.ViewDialog(record.StringData(1)) : CheckError
		Wait
	Loop
Else ' explicit dialog names supplied
	Set view = database.OpenView("SELECT `Dialog` FROM `Dialog` WHERE `Dialog`=?") : CheckError
	Dim paramRecord, argNum, argArray, dialogName, controlName, billboardName
	Set paramRecord = installer.CreateRecord(1)
	For argNum = 1 To argCount-1
		dialogName = Wscript.Arguments(argNum)
		argArray = Split(dialogName,":",-1,vbTextCompare)
		If UBound(argArray) <> 0 Then  ' billboard to add to dialog
			If UBound(argArray) <> 2 Then Fail "Incorrect billboard syntax, must specify 3 values"
			dialogName    = argArray(0)
			controlName   = argArray(1) ' we could validate that controlName is in the Control table
			billboardName = argArray(2) ' we could validate that billboard is in the Billboard table
		End If
		paramRecord.StringData(1) = dialogName
		view.Execute paramRecord : CheckError
		If view.Fetch Is Nothing Then Fail "Dialog not found: " & dialogName
		preview.ViewDialog(dialogName) : CheckError
		If UBound(argArray) = 2 Then preview.ViewBillboard controlName, billboardName : CheckError
		Wait
	Next
End If
preview.ViewDialog ""  ' clear dialog, must do this to release object deadlock

' Wait until user input to clear dialog. Too bad there's no function to wait for keyboard input
Sub Wait
	Dim shell : Set shell = Wscript.CreateObject("Wscript.Shell")
	MsgBox "Next",0,"Drag me away"
End Sub

Sub CheckError
	Dim message, errRec
	If Err = 0 Then Exit Sub
	message = Err.Source & " " & Hex(Err) & ": " & Err.Description
	If Not installer Is Nothing Then
		Set errRec = installer.LastErrorRecord
		If Not errRec Is Nothing Then message = message & vbLf & errRec.FormatText
	End If
	Fail message
End Sub

Sub Fail(message)
	Wscript.Echo message
	Wscript.Quit 2
End Sub

'' SIG '' Begin signature block
'' SIG '' MIIiTQYJKoZIhvcNAQcCoIIiPjCCIjoCAQExDzANBglg
'' SIG '' hkgBZQMEAgEFADB3BgorBgEEAYI3AgEEoGkwZzAyBgor
'' SIG '' BgEEAYI3AgEeMCQCAQEEEE7wKRaZJ7VNj+Ws4Q8X66sC
'' SIG '' AQACAQACAQACAQACAQAwMTANBglghkgBZQMEAgEFAAQg
'' SIG '' mOr7DzNLA7B3kQygPHKkFo0lJ4ImjipM2G/ZKh4w1cKg
'' SIG '' gguPMIIFFzCCA/+gAwIBAgITMwAAAVVp/7a3A86SrgAA
'' SIG '' AAABVTANBgkqhkiG9w0BAQsFADB+MQswCQYDVQQGEwJV
'' SIG '' UzETMBEGA1UECBMKV2FzaGluZ3RvbjEQMA4GA1UEBxMH
'' SIG '' UmVkbW9uZDEeMBwGA1UEChMVTWljcm9zb2Z0IENvcnBv
'' SIG '' cmF0aW9uMSgwJgYDVQQDEx9NaWNyb3NvZnQgQ29kZSBT
'' SIG '' aWduaW5nIFBDQSAyMDEwMB4XDTE3MDExODE3MzcxNVoX
'' SIG '' DTE4MDQxMjE3MzcxNVowgY4xCzAJBgNVBAYTAlVTMRMw
'' SIG '' EQYDVQQIEwpXYXNoaW5ndG9uMRAwDgYDVQQHEwdSZWRt
'' SIG '' b25kMR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRp
'' SIG '' b24xDTALBgNVBAsTBE1PUFIxKTAnBgNVBAMTIE1pY3Jv
'' SIG '' c29mdCBXaW5kb3dzIEtpdHMgUHVibGlzaGVyMIIBIjAN
'' SIG '' BgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAtWlP6kJd
'' SIG '' 2OeI8GBCw3xSZqk5jmpNr2s9nflfnX9H5yIeZKX2VH6x
'' SIG '' TWXwGsin5MigTbyIStQqo7LAWv4G9tOQ4zcrHZc3vgpe
'' SIG '' 4RnoMbpibkLgmCNNwZJ2PV7NtZPkxurz42tm+XT9dWXT
'' SIG '' Gn42yIpiaT8kGrs5VLvqi7a5QzUbm5IhAfZfpAn4K4FZ
'' SIG '' 47lqJ3gTmbkQ4ODC/3whJTngCi1UJMmDP7kEFLm4J6GC
'' SIG '' DZgnNoZRlbNdxL9Y0pJtsbm+EdZuy1cx+O7YaWmrjJi8
'' SIG '' ghcvaxZuZEzAPX9bEfCnRoF5PFnsBFH84qcoHbkUhEMI
'' SIG '' m1DFIvyFWcfchz0pGOZCkwj5pQIDAQABo4IBezCCAXcw
'' SIG '' HwYDVR0lBBgwFgYKKwYBBAGCNwoDFAYIKwYBBQUHAwMw
'' SIG '' HQYDVR0OBBYEFD5mS2iWthzVVdM+D3JrW9fwwEmbMFIG
'' SIG '' A1UdEQRLMEmkRzBFMQ0wCwYDVQQLEwRNT1BSMTQwMgYD
'' SIG '' VQQFEysyMjk5MDMrZjY5MzBlOGEtMDZjZi00ZTFkLThi
'' SIG '' ZGMtMjE0OGE3YTk5OTFmMB8GA1UdIwQYMBaAFOb8X3u7
'' SIG '' IgBY5HJOtfQhdCMy5u+sMFYGA1UdHwRPME0wS6BJoEeG
'' SIG '' RWh0dHA6Ly9jcmwubWljcm9zb2Z0LmNvbS9wa2kvY3Js
'' SIG '' L3Byb2R1Y3RzL01pY0NvZFNpZ1BDQV8yMDEwLTA3LTA2
'' SIG '' LmNybDBaBggrBgEFBQcBAQROMEwwSgYIKwYBBQUHMAKG
'' SIG '' Pmh0dHA6Ly93d3cubWljcm9zb2Z0LmNvbS9wa2kvY2Vy
'' SIG '' dHMvTWljQ29kU2lnUENBXzIwMTAtMDctMDYuY3J0MAwG
'' SIG '' A1UdEwEB/wQCMAAwDQYJKoZIhvcNAQELBQADggEBAOge
'' SIG '' oOdvZVXDSb0HtYATwNXxJ3qcSKlgcvQVAJ+oRz9uixUK
'' SIG '' j02r4LZTPZFIQJM3ELa6lhz9AgPDQnuaJwZ6OarFlinx
'' SIG '' yKap4iA3ofxnwnLA7TXZ4jcMXMRdiD/a0/5YqzWSgC1d
'' SIG '' uUK/7Swv33Sz1zUqekaMui4c8cejmVknme4i05YpJTPJ
'' SIG '' G5hS0l6ZAx90cz795+o+pEwOZ4wiyf/8JVQXvJ9uHXy6
'' SIG '' LKuck+dsEUnbJ4eE9TcSrk9Ab2EshixEVUl1Mtal8r0Z
'' SIG '' LlFUH4Di3pnt+J2a81WhZcsjst1lNJcqThyoZwqhYSFr
'' SIG '' qpRHvadd2K3FNEuuZwYLEMOxc5vwrGgwggZwMIIEWKAD
'' SIG '' AgECAgphDFJMAAAAAAADMA0GCSqGSIb3DQEBCwUAMIGI
'' SIG '' MQswCQYDVQQGEwJVUzETMBEGA1UECBMKV2FzaGluZ3Rv
'' SIG '' bjEQMA4GA1UEBxMHUmVkbW9uZDEeMBwGA1UEChMVTWlj
'' SIG '' cm9zb2Z0IENvcnBvcmF0aW9uMTIwMAYDVQQDEylNaWNy
'' SIG '' b3NvZnQgUm9vdCBDZXJ0aWZpY2F0ZSBBdXRob3JpdHkg
'' SIG '' MjAxMDAeFw0xMDA3MDYyMDQwMTdaFw0yNTA3MDYyMDUw
'' SIG '' MTdaMH4xCzAJBgNVBAYTAlVTMRMwEQYDVQQIEwpXYXNo
'' SIG '' aW5ndG9uMRAwDgYDVQQHEwdSZWRtb25kMR4wHAYDVQQK
'' SIG '' ExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKDAmBgNVBAMT
'' SIG '' H01pY3Jvc29mdCBDb2RlIFNpZ25pbmcgUENBIDIwMTAw
'' SIG '' ggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDp
'' SIG '' DmRQeWe1xOP9CQBMnpSs91Zo6kTYz8VYT6mldnxtRbrT
'' SIG '' OZK0pB75+WWC5BfSj/1EnAjoZZPOLFWEv30I4y4rqEEr
'' SIG '' GLeiS25JTGsVB97R0sKJHnGUzbV/S7SvCNjMiNZrF5Q6
'' SIG '' k84mP+zm/jSYV9UdXUn2siou1YW7WT/4kLQrg3TKK7M7
'' SIG '' RuPwRknBF2ZUyRy9HcRVYldy+Ge5JSA03l2mpZVeqyiA
'' SIG '' zdWynuUDtWPTshTIwciKJgpZfwfs/w7tgBI1TBKmvlJb
'' SIG '' 9aba4IsLSHfWhUfVELnG6Krui2otBVxgxrQqW5wjHF9F
'' SIG '' 4xoUHm83yxkzgGqJTaNqZmN4k9Uwz5UfAgMBAAGjggHj
'' SIG '' MIIB3zAQBgkrBgEEAYI3FQEEAwIBADAdBgNVHQ4EFgQU
'' SIG '' 5vxfe7siAFjkck619CF0IzLm76wwGQYJKwYBBAGCNxQC
'' SIG '' BAweCgBTAHUAYgBDAEEwCwYDVR0PBAQDAgGGMA8GA1Ud
'' SIG '' EwEB/wQFMAMBAf8wHwYDVR0jBBgwFoAU1fZWy4/oolxi
'' SIG '' aNE9lJBb186aGMQwVgYDVR0fBE8wTTBLoEmgR4ZFaHR0
'' SIG '' cDovL2NybC5taWNyb3NvZnQuY29tL3BraS9jcmwvcHJv
'' SIG '' ZHVjdHMvTWljUm9vQ2VyQXV0XzIwMTAtMDYtMjMuY3Js
'' SIG '' MFoGCCsGAQUFBwEBBE4wTDBKBggrBgEFBQcwAoY+aHR0
'' SIG '' cDovL3d3dy5taWNyb3NvZnQuY29tL3BraS9jZXJ0cy9N
'' SIG '' aWNSb29DZXJBdXRfMjAxMC0wNi0yMy5jcnQwgZ0GA1Ud
'' SIG '' IASBlTCBkjCBjwYJKwYBBAGCNy4DMIGBMD0GCCsGAQUF
'' SIG '' BwIBFjFodHRwOi8vd3d3Lm1pY3Jvc29mdC5jb20vUEtJ
'' SIG '' L2RvY3MvQ1BTL2RlZmF1bHQuaHRtMEAGCCsGAQUFBwIC
'' SIG '' MDQeMiAdAEwAZQBnAGEAbABfAFAAbwBsAGkAYwB5AF8A
'' SIG '' UwB0AGEAdABlAG0AZQBuAHQALiAdMA0GCSqGSIb3DQEB
'' SIG '' CwUAA4ICAQAadO9XTyl7xBaFeLhQ0yL8CZ2sgpf4NP8q
'' SIG '' LJeVEuXkv8+/k8jjNKnbgbjcHgC+0jVvr+V/eZV35QLU
'' SIG '' 8evYzU4eG2GiwlojGvCMqGJRRWcI4z88HpP4MIUXyDlA
'' SIG '' ptcOsyEp5aWhaYwik8x0mOehR0PyU6zADzBpf/7SJSBt
'' SIG '' b2HT3wfV2XIALGmGdj1R26Y5SMk3YW0H3VMZy6fWYcK/
'' SIG '' 4oOrD+Brm5XWfShRsIlKUaSabMi3H0oaDmmp19zBftFJ
'' SIG '' cKq2rbtyR2MX+qbWoqaG7KgQRJtjtrJpiQbHRoZ6GD/o
'' SIG '' xR0h1Xv5AiMtxUHLvx1MyBbvsZx//CJLSYpuFeOmf3Zb
'' SIG '' 0VN5kYWd1dLbPXM18zyuVLJSR2rAqhOV0o4R2plnXjKM
'' SIG '' +zeF0dx1hZyHxlpXhcK/3Q2PjJst67TuzyfTtV5p+qQW
'' SIG '' BAGnJGdzz01Ptt4FVpd69+lSTfR3BU+FxtgL8Y7tQgnR
'' SIG '' DXbjI1Z4IiY2vsqxjG6qHeSF2kczYo+kyZEzX3EeQK+Y
'' SIG '' Zcki6EIhJYocLWDZN4lBiSoWD9dhPJRoYFLv1keZoIBA
'' SIG '' 7hWBdz6c4FMYGlAdOJWbHmYzEyc5F3iHNs5Ow1+y9T1H
'' SIG '' U7bg5dsLYT0q15IszjdaPkBCMaQfEAjCVpy/JF1RAp1q
'' SIG '' edIX09rBlI4HeyVxRKsGaubUxt8jmpZ1xTGCFhYwghYS
'' SIG '' AgEBMIGVMH4xCzAJBgNVBAYTAlVTMRMwEQYDVQQIEwpX
'' SIG '' YXNoaW5ndG9uMRAwDgYDVQQHEwdSZWRtb25kMR4wHAYD
'' SIG '' VQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKDAmBgNV
'' SIG '' BAMTH01pY3Jvc29mdCBDb2RlIFNpZ25pbmcgUENBIDIw
'' SIG '' MTACEzMAAAFVaf+2twPOkq4AAAAAAVUwDQYJYIZIAWUD
'' SIG '' BAIBBQCgggEEMBkGCSqGSIb3DQEJAzEMBgorBgEEAYI3
'' SIG '' AgEEMBwGCisGAQQBgjcCAQsxDjAMBgorBgEEAYI3AgEV
'' SIG '' MC8GCSqGSIb3DQEJBDEiBCBAQNzG0p24TUN1L8ZDRKn3
'' SIG '' RWNowySEKvCa5C9u9njgujA8BgorBgEEAYI3CgMcMS4M
'' SIG '' LEhMc2dwMk50UkZnbkwzMndJVzVtY01ROURXN2k5dyt4
'' SIG '' VmUrZ2d5T3ZuaFk9MFoGCisGAQQBgjcCAQwxTDBKoCSA
'' SIG '' IgBNAGkAYwByAG8AcwBvAGYAdAAgAFcAaQBuAGQAbwB3
'' SIG '' AHOhIoAgaHR0cDovL3d3dy5taWNyb3NvZnQuY29tL3dp
'' SIG '' bmRvd3MwDQYJKoZIhvcNAQEBBQAEggEAARNCEJtGit0i
'' SIG '' UuoKBQapYgUy+G6X46Vault8YZGAqMCUd53UxAFrJL3/
'' SIG '' mxP8xtWFuyYyAWk9ebQ8Moqjf8BM2YNqRpRq8Ytw9p32
'' SIG '' XYXyvII8KSXVhj+vbb6qpK8IXVubwzWIn86CstUbcd+4
'' SIG '' KiWs7tT82DYzF3oHNjnoIBR6ajf6ij9jvCt9DVzZgKCz
'' SIG '' rL+ftDCi1va+5bakNxl8jmViWJsRaCtaPdGOSzC3i9LT
'' SIG '' AKFH5QeCg5Nfrcqv442RbVK8+HCndhuuP88AxSsPLjUS
'' SIG '' iR+FjlRsxbMAxsxn/opImyb1g/EMBZ7tqQCP/wAT6EPm
'' SIG '' ElmIpI+BgR31cE/YcBs/QqGCE0kwghNFBgorBgEEAYI3
'' SIG '' AwMBMYITNTCCEzEGCSqGSIb3DQEHAqCCEyIwghMeAgED
'' SIG '' MQ8wDQYJYIZIAWUDBAIBBQAwggE9BgsqhkiG9w0BCRAB
'' SIG '' BKCCASwEggEoMIIBJAIBAQYKKwYBBAGEWQoDATAxMA0G
'' SIG '' CWCGSAFlAwQCAQUABCD3mB9Zh0PLfN1qDv6qecmNdpYl
'' SIG '' /Chj4c+gAgn5Ii8SkwIGWK+C3vuVGBMyMDE3MDMxOTEy
'' SIG '' NDg1Ny44MDFaMAcCAQGAAgH0oIG5pIG2MIGzMQswCQYD
'' SIG '' VQQGEwJVUzETMBEGA1UECBMKV2FzaGluZ3RvbjEQMA4G
'' SIG '' A1UEBxMHUmVkbW9uZDEeMBwGA1UEChMVTWljcm9zb2Z0
'' SIG '' IENvcnBvcmF0aW9uMQ0wCwYDVQQLEwRNT1BSMScwJQYD
'' SIG '' VQQLEx5uQ2lwaGVyIERTRSBFU046QjFCNy1GNjdGLUZF
'' SIG '' QzIxJTAjBgNVBAMTHE1pY3Jvc29mdCBUaW1lLVN0YW1w
'' SIG '' IFNlcnZpY2Wggg7MMIIGcTCCBFmgAwIBAgIKYQmBKgAA
'' SIG '' AAAAAjANBgkqhkiG9w0BAQsFADCBiDELMAkGA1UEBhMC
'' SIG '' VVMxEzARBgNVBAgTCldhc2hpbmd0b24xEDAOBgNVBAcT
'' SIG '' B1JlZG1vbmQxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jw
'' SIG '' b3JhdGlvbjEyMDAGA1UEAxMpTWljcm9zb2Z0IFJvb3Qg
'' SIG '' Q2VydGlmaWNhdGUgQXV0aG9yaXR5IDIwMTAwHhcNMTAw
'' SIG '' NzAxMjEzNjU1WhcNMjUwNzAxMjE0NjU1WjB8MQswCQYD
'' SIG '' VQQGEwJVUzETMBEGA1UECBMKV2FzaGluZ3RvbjEQMA4G
'' SIG '' A1UEBxMHUmVkbW9uZDEeMBwGA1UEChMVTWljcm9zb2Z0
'' SIG '' IENvcnBvcmF0aW9uMSYwJAYDVQQDEx1NaWNyb3NvZnQg
'' SIG '' VGltZS1TdGFtcCBQQ0EgMjAxMDCCASIwDQYJKoZIhvcN
'' SIG '' AQEBBQADggEPADCCAQoCggEBAKkdDbx3EYo6IOz8E5f1
'' SIG '' +n9plGt0VBDVpQoAgoX77XxoSyxfxcPlYcJ2tz5mK1vw
'' SIG '' FVMnBDEfQRsalR3OCROOfGEwWbEwRA/xYIiEVEMM1024
'' SIG '' OAizQt2TrNZzMFcmgqNFDdDq9UeBzb8kYDJYYEbyWEeG
'' SIG '' MoQedGFnkV+BVLHPk0ySwcSmXdFhE24oxhr5hoC732H8
'' SIG '' RsEnHSRnEnIaIYqvS2SJUGKxXf13Hz3wV3WsvYpCTUBR
'' SIG '' 0Q+cBj5nf/VmwAOWRH7v0Ev9buWayrGo8noqCjHw2k4G
'' SIG '' kbaICDXoeByw6ZnNPOcvRLqn9NxkvaQBwSAJk3jN/LzA
'' SIG '' yURdXhacAQVPIk0CAwEAAaOCAeYwggHiMBAGCSsGAQQB
'' SIG '' gjcVAQQDAgEAMB0GA1UdDgQWBBTVYzpcijGQ80N7fEYb
'' SIG '' xTNoWoVtVTAZBgkrBgEEAYI3FAIEDB4KAFMAdQBiAEMA
'' SIG '' QTALBgNVHQ8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAf
'' SIG '' BgNVHSMEGDAWgBTV9lbLj+iiXGJo0T2UkFvXzpoYxDBW
'' SIG '' BgNVHR8ETzBNMEugSaBHhkVodHRwOi8vY3JsLm1pY3Jv
'' SIG '' c29mdC5jb20vcGtpL2NybC9wcm9kdWN0cy9NaWNSb29D
'' SIG '' ZXJBdXRfMjAxMC0wNi0yMy5jcmwwWgYIKwYBBQUHAQEE
'' SIG '' TjBMMEoGCCsGAQUFBzAChj5odHRwOi8vd3d3Lm1pY3Jv
'' SIG '' c29mdC5jb20vcGtpL2NlcnRzL01pY1Jvb0NlckF1dF8y
'' SIG '' MDEwLTA2LTIzLmNydDCBoAYDVR0gAQH/BIGVMIGSMIGP
'' SIG '' BgkrBgEEAYI3LgMwgYEwPQYIKwYBBQUHAgEWMWh0dHA6
'' SIG '' Ly93d3cubWljcm9zb2Z0LmNvbS9QS0kvZG9jcy9DUFMv
'' SIG '' ZGVmYXVsdC5odG0wQAYIKwYBBQUHAgIwNB4yIB0ATABl
'' SIG '' AGcAYQBsAF8AUABvAGwAaQBjAHkAXwBTAHQAYQB0AGUA
'' SIG '' bQBlAG4AdAAuIB0wDQYJKoZIhvcNAQELBQADggIBAAfm
'' SIG '' iFEN4sbgmD+BcQM9naOhIW+z66bM9TG+zwXiqf76V20Z
'' SIG '' MLPCxWbJat/15/B4vceoniXj+bzta1RXCCtRgkQS+7lT
'' SIG '' jMz0YBKKdsxAQEGb3FwX/1z5Xhc1mCRWS3TvQhDIr79/
'' SIG '' xn/yN31aPxzymXlKkVIArzgPF/UveYFl2am1a+THzvbK
'' SIG '' egBvSzBEJCI8z+0DpZaPWSm8tv0E4XCfMkon/VWvL/62
'' SIG '' 5Y4zu2JfmttXQOnxzplmkIz/amJ/3cVKC5Em4jnsGUpx
'' SIG '' Y517IW3DnKOiPPp/fZZqkHimbdLhnPkd/DjYlPTGpQqW
'' SIG '' hqS9nhquBEKDuLWAmyI4ILUl5WTs9/S/fmNZJQ96LjlX
'' SIG '' dqJxqgaKD4kWumGnEcua2A5HmoDF0M2n0O99g/DhO3EJ
'' SIG '' 3110mCIIYdqwUB5vvfHhAN/nMQekkzr3ZUd46PioSKv3
'' SIG '' 3nJ+YWtvd6mBy6cJrDm77MbL2IK0cs0d9LiFAR6A+xuJ
'' SIG '' KlQ5slvayA1VmXqHczsI5pgt6o3gMy4SKfXAL1QnIffI
'' SIG '' rE7aKLixqduWsqdCosnPGUFN4Ib5KpqjEWYw07t0Mkvf
'' SIG '' Y3v1mYovG8chr1m1rtxEPJdQcdeh0sVV42neV8HR3jDA
'' SIG '' /czmTfsNv11P6Z0eGTgvvM9YBS7vDaBQNdrvCScc1bN+
'' SIG '' NR4Iuto229Nfj950iEkSMIIE2jCCA8KgAwIBAgITMwAA
'' SIG '' ALFxE3nfdfY1yAAAAAAAsTANBgkqhkiG9w0BAQsFADB8
'' SIG '' MQswCQYDVQQGEwJVUzETMBEGA1UECBMKV2FzaGluZ3Rv
'' SIG '' bjEQMA4GA1UEBxMHUmVkbW9uZDEeMBwGA1UEChMVTWlj
'' SIG '' cm9zb2Z0IENvcnBvcmF0aW9uMSYwJAYDVQQDEx1NaWNy
'' SIG '' b3NvZnQgVGltZS1TdGFtcCBQQ0EgMjAxMDAeFw0xNjA5
'' SIG '' MDcxNzU2NTdaFw0xODA5MDcxNzU2NTdaMIGzMQswCQYD
'' SIG '' VQQGEwJVUzETMBEGA1UECBMKV2FzaGluZ3RvbjEQMA4G
'' SIG '' A1UEBxMHUmVkbW9uZDEeMBwGA1UEChMVTWljcm9zb2Z0
'' SIG '' IENvcnBvcmF0aW9uMQ0wCwYDVQQLEwRNT1BSMScwJQYD
'' SIG '' VQQLEx5uQ2lwaGVyIERTRSBFU046QjFCNy1GNjdGLUZF
'' SIG '' QzIxJTAjBgNVBAMTHE1pY3Jvc29mdCBUaW1lLVN0YW1w
'' SIG '' IFNlcnZpY2UwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAw
'' SIG '' ggEKAoIBAQCqpCSUbVjWW7yhvQ/t166a5Gfgm9GLYYSu
'' SIG '' Yr3i+BudY+Z3SP/1qsDvnf0cPV2kbW6FhuacDFz6qy68
'' SIG '' wzR+kS+21MriVlJTuyzmsl9aZsWf8nyRIYjwr2IFoHqF
'' SIG '' CQm4hfiyL2mk2v1Hehkjcdsn/JGQpQ+TiGjOljoKR6FF
'' SIG '' zT9l+7q1CLKojuYKVdhlNePD6suyHf+B0G9gN3fzMUGW
'' SIG '' Vp/7e6KYpCBRNcaNsp+plmTe0RTeJtZU9TECabGUbexZ
'' SIG '' OVeZTfV8LD/pNXMaDbnWWr5Djo6Nt4f28HZM5yoSyjg1
'' SIG '' qLcnUJ0wBhR2V6VVW2BB0jH9z7ke+vDRjpbu4YEBadbn
'' SIG '' AgMBAAGjggEbMIIBFzAdBgNVHQ4EFgQUTlc994suFEtX
'' SIG '' svwiXtPPtydEEDswHwYDVR0jBBgwFoAU1WM6XIoxkPND
'' SIG '' e3xGG8UzaFqFbVUwVgYDVR0fBE8wTTBLoEmgR4ZFaHR0
'' SIG '' cDovL2NybC5taWNyb3NvZnQuY29tL3BraS9jcmwvcHJv
'' SIG '' ZHVjdHMvTWljVGltU3RhUENBXzIwMTAtMDctMDEuY3Js
'' SIG '' MFoGCCsGAQUFBwEBBE4wTDBKBggrBgEFBQcwAoY+aHR0
'' SIG '' cDovL3d3dy5taWNyb3NvZnQuY29tL3BraS9jZXJ0cy9N
'' SIG '' aWNUaW1TdGFQQ0FfMjAxMC0wNy0wMS5jcnQwDAYDVR0T
'' SIG '' AQH/BAIwADATBgNVHSUEDDAKBggrBgEFBQcDCDANBgkq
'' SIG '' hkiG9w0BAQsFAAOCAQEAc+6N+7Rbw8FOmN9ho+sAogEs
'' SIG '' pyWNPj5idZtuAa+ZdTw68hQMGSS/yA0YYdE7kNLJJoIB
'' SIG '' EjOCfbIiF4CqHobAzbIqt9vh5UJg97UJOUKx5LlM6/5O
'' SIG '' f/3mZeP43FOq+42auGAJWvQJDtvfGgpzANxBuDtOZ6sO
'' SIG '' Bsi/aTtwSpthtT8Hcy1JfxmON/RmeB0qhfQliQAQNtly
'' SIG '' E6tGJS0Mki16A8pk9/oKN4diOuYrC9M5ULO/eVbS7KHX
'' SIG '' Jv84N5Ef5WoQ1IcJugWISKr0qkow6l6TVW9CGYjYptOV
'' SIG '' G8rzr2CPU3C5QcfxzdZe7gDRfX4IGZTy3SC9398WVC/D
'' SIG '' Ti94paH3zqGCA3UwggJdAgEBMIHjoYG5pIG2MIGzMQsw
'' SIG '' CQYDVQQGEwJVUzETMBEGA1UECBMKV2FzaGluZ3RvbjEQ
'' SIG '' MA4GA1UEBxMHUmVkbW9uZDEeMBwGA1UEChMVTWljcm9z
'' SIG '' b2Z0IENvcnBvcmF0aW9uMQ0wCwYDVQQLEwRNT1BSMScw
'' SIG '' JQYDVQQLEx5uQ2lwaGVyIERTRSBFU046QjFCNy1GNjdG
'' SIG '' LUZFQzIxJTAjBgNVBAMTHE1pY3Jvc29mdCBUaW1lLVN0
'' SIG '' YW1wIFNlcnZpY2WiJQoBATAJBgUrDgMCGgUAAxUAOrrf
'' SIG '' kyhl5HrT56P24qdEbliqU9KggcIwgb+kgbwwgbkxCzAJ
'' SIG '' BgNVBAYTAlVTMRMwEQYDVQQIEwpXYXNoaW5ndG9uMRAw
'' SIG '' DgYDVQQHEwdSZWRtb25kMR4wHAYDVQQKExVNaWNyb3Nv
'' SIG '' ZnQgQ29ycG9yYXRpb24xDTALBgNVBAsTBE1PUFIxJzAl
'' SIG '' BgNVBAsTHm5DaXBoZXIgTlRTIEVTTjo0REU5LTBDNUUt
'' SIG '' M0UwOTErMCkGA1UEAxMiTWljcm9zb2Z0IFRpbWUgU291
'' SIG '' cmNlIE1hc3RlciBDbG9jazANBgkqhkiG9w0BAQUFAAIF
'' SIG '' ANx4jiowIhgPMjAxNzAzMTkwNDU3MTRaGA8yMDE3MDMy
'' SIG '' MDA0NTcxNFowczA5BgorBgEEAYRZCgQBMSswKTAKAgUA
'' SIG '' 3HiOKgIBADAGAgEAAgEgMAcCAQACAh0BMAoCBQDced+q
'' SIG '' AgEAMDYGCisGAQQBhFkKBAIxKDAmMAwGCisGAQQBhFkK
'' SIG '' AwGgCjAIAgEAAgMW42ChCjAIAgEAAgMHoSAwDQYJKoZI
'' SIG '' hvcNAQEFBQADggEBAIt5y4WyM7Flaq27LUQpSb1u/8NA
'' SIG '' g7QthzmblqayXk5jdHat9C+bIAMKDOOF6EZLw/bzyAZi
'' SIG '' h2SR26qhJ/gO0wZA1TSJdmBTDp82sxfo+pyiwuxIMlV6
'' SIG '' xjd75kKbAkwzEXTgY8ToQTgJbupm9IDYJR4AIlWuPXox
'' SIG '' tUDdiGFbOURG5k8JG5tbNB/PHyhpwPf9nEx/3Eaojbgh
'' SIG '' F58oqxcrSk02rZY8I6FyE/q8BQYX2e3bHLEfOsSLSpnz
'' SIG '' JVGhCUGE5hDWwLdSv/FVVs+KdYUfge5O3mXVrFcOPyq0
'' SIG '' UFrMy+UOC9/VolgyNTm08+M8X/ZRYnTgk8eFu/ZVaoKm
'' SIG '' q/Jyt0cxggL1MIIC8QIBATCBkzB8MQswCQYDVQQGEwJV
'' SIG '' UzETMBEGA1UECBMKV2FzaGluZ3RvbjEQMA4GA1UEBxMH
'' SIG '' UmVkbW9uZDEeMBwGA1UEChMVTWljcm9zb2Z0IENvcnBv
'' SIG '' cmF0aW9uMSYwJAYDVQQDEx1NaWNyb3NvZnQgVGltZS1T
'' SIG '' dGFtcCBQQ0EgMjAxMAITMwAAALFxE3nfdfY1yAAAAAAA
'' SIG '' sTANBglghkgBZQMEAgEFAKCCATIwGgYJKoZIhvcNAQkD
'' SIG '' MQ0GCyqGSIb3DQEJEAEEMC8GCSqGSIb3DQEJBDEiBCC0
'' SIG '' WR0PxxQNtM/1PKxPQIFzgVIcHdj5b5lYr3Nw1Thv9jCB
'' SIG '' 4gYLKoZIhvcNAQkQAgwxgdIwgc8wgcwwgbEEFDq635Mo
'' SIG '' ZeR60+ej9uKnRG5YqlPSMIGYMIGApH4wfDELMAkGA1UE
'' SIG '' BhMCVVMxEzARBgNVBAgTCldhc2hpbmd0b24xEDAOBgNV
'' SIG '' BAcTB1JlZG1vbmQxHjAcBgNVBAoTFU1pY3Jvc29mdCBD
'' SIG '' b3Jwb3JhdGlvbjEmMCQGA1UEAxMdTWljcm9zb2Z0IFRp
'' SIG '' bWUtU3RhbXAgUENBIDIwMTACEzMAAACxcRN533X2NcgA
'' SIG '' AAAAALEwFgQUkupwqbOXHyyj5lazJgx9ar3lOIowDQYJ
'' SIG '' KoZIhvcNAQELBQAEggEAdkzMxJHDdzm1W0DoBjeEHfjA
'' SIG '' Xso+j4AhI6ycU9APH3724VF+lFCFSRWFAt4QYZtfGMpI
'' SIG '' OugnRA4uPL/219/QLzky7zWE7iJ9NBcGLFSG4PqH87xq
'' SIG '' 2hw1HWq2f7B/NdnrAUXhMR0TPRxpKiDxfvBMyggo9/ZW
'' SIG '' QU6GRJSEpuIfI2iw76UEx8if6y8amzNgO9qTOZ8DKlR7
'' SIG '' PLMjqEPiNRTyVwjF/n7AGwZvhcTvDQJn2UI9SsR6tWHG
'' SIG '' LzVZxRsu5KnQ/F2u8oPuB8QFco+DgnFwksZb72RYwa5R
'' SIG '' /0wbiKFzn/irx/pLSf98O8+y6k0PAJoescCNgleY+N0F
'' SIG '' mlORyprUJw==
'' SIG '' End signature block