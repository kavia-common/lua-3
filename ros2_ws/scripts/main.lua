--Start To Write RL

Fix1HPCB=false
Fix2HPCB=false
Fix3HPCB=false
Fix4HPCB=false
Fix5HPCB=false
Fix6HPCB=false
Fix7HPCB=false
Fix8HPCB=false
Fix9HPCB=false
Fix10HPCB=false
Fix11HPCB=false

GrHPcb = false

Fix1Finish=false
Fix2Finish=false
Fix3Finish=false
Fix4Finish=false
Fix5Finish=false
Fix6Finish=false
Fix7Finish=false
Fix8Finish=false
Fix9Finish=false
Fix10Finish=false
Fix11Finish=false

Fix1Test=false
Fix2Test=false
Fix3Test=false
Fix4Test=false
Fix5Test=false
Fix6Test=false
Fix7Test=false
Fix8Test=false
Fix9Test=false
Fix10Test=false
Fix11Test=false

Scan1=false
Scan2=false

Rec1=""
CheckResult=1
Result=""

Connect=false

Testing1=false
Testing2=false
Testing3=false
Testing4=false
Testing5=false
Testing6=false
Testing7=false
Testing8=false
Testing9=false
Testing10=false
Testing11=false
rets = 0
ss = 0
ss1 = 0
ss2 = 0
b1 = 0
b2 = 0
b3 = 0
boot1 = false
boot2 = false
boot2 = false
bootOk1 = false
bootOk2 = false
bootOk3 = false
smcMove = false
x1 = 0
x2 = 0
sn3 = ""
tt = 0
RobotServoOn()
function Timer66()
	tt = tt + 1
	DELAY(0.5)
	--print(tt)
	if tt < 3 then
		DO("TowerLightG","ON")
		DO("TowerLightY","OFF")
		DO("TowerLightR","OFF")
	end
	if tt > 120 then
		DO("TowerLightG","OFF")
		DO("TowerLightY","OFF")
		DO("TowerLightR","OFF")
	end
end

function SpeedLow()
	SpdJ (30)
	AccJ (7)
	DecJ (7)
	SpdL (1000)
	AccL (10000)
	DecL (10000)
	Accur ("ROUGH")
end 

function SpeedHigh()
	SpdJ (40)
	AccJ (50)
	DecJ (50)
	SpdL (1000)
	AccL (12000)
	DecL (12000)
	Accur ("ROUGH")
end 

function Speed(percent)
    SpdJ(percent)
    AccJ(percent-10)
    DecJ(percent-10)
    SpdL(percent*20)
    AccL(percent*250)
    DecL(percent*250)
    Accur ("ROUGH")
    --print("SpdJ="..percent..+"AccJ=")--..(percent-10)..+"DecJ="..(percent-10))
end
function TestIo()

	ExtDO(3,1,"ON")
	WAIT (ExtDI,{3,1},"ON")
	DELAY(1)
	ExtDO(3,1,"OFF")
	WAIT (ExtDI,{3,2},"ON")
		
	ExtDO(3,2,"ON")
	WAIT(ExtDI,{3,3},"ON")
	DELAY(1)
	ExtDO(3,2,"OFF")
	WAIT(ExtDI,{3,4},"ON")
	
	ExtDO(3,3,"ON")
	WAIT (ExtDI,{3,5},"ON")
	DELAY(1)
	ExtDO(3,3,"OFF")
	WAIT (ExtDI,{3,6},"ON")
		
	ExtDO(3,4,"ON")
	WAIT(ExtDI,{3,7},"ON")
	DELAY(1)
	ExtDO(3,4,"OFF")
	WAIT(ExtDI,{3,8},"ON")
	
	ExtDO(3,5,"ON")
	WAIT (ExtDI,{3,9},"ON")
	DELAY(1)
	ExtDO(3,5,"OFF")
	WAIT (ExtDI,{3,10},"ON")
		
	ExtDO(3,6,"ON")
	WAIT(ExtDI,{3,11},"ON")
	DELAY(1)
	ExtDO(3,6,"OFF")
	WAIT(ExtDI,{3,12},"ON")
	
	ExtDO(3,7,"ON")
	WAIT (ExtDI,{3,13},"ON")
	DELAY(1)
	ExtDO(3,7,"OFF")
	WAIT (ExtDI,{3,14},"ON")
		
	ExtDO(3,9,"ON")
	WAIT(ExtDI,{3,15},"ON")
	DELAY(1)
	ExtDO(3,9,"OFF")
	WAIT(ExtDI,{3,16},"ON")
	
	ExtDO(3,1,"ON")
	WAIT (ExtDI,{3,1},"ON")
	DELAY(1)
	ExtDO(3,1,"OFF")
	WAIT (ExtDI,{3,2},"ON")
		
	ExtDO(3,2,"ON")
	WAIT(ExtDI,{3,3},"ON")
	DELAY(1)
	ExtDO(3,2,"OFF")
	WAIT(ExtDI,{3,4},"ON")
	
	ExtDO(3,3,"ON")
	WAIT (ExtDI,{3,5},"ON")
	DELAY(1)
	ExtDO(3,3,"OFF")
	WAIT (ExtDI,{3,6},"ON")	
end
--[[
while 1 do
	TestIo()	
end
]]
function TestPoint()
	local a = 1
	while 1 do
        if DI(14) == ON and a == 1 then
            PickToCVIN()
            PlaceToFix1()
            PickToFix1()
            PlacePASS()
            PickToCamera()
            PlaceToFix9()
            PickToFix9()
            PlacePASS2()
            a = 2
        end
        if DI(14) == ON and a == 2 then
            PickToCVIN()
            PlaceToFix2()
            PickToFix2()
            PlacePASS()
            PickToCamera()
            PlaceToFix10()
            PickToFix10()
            PlacePASS2()
            a = 3
        end
        if DI(14) == ON and a == 3 then
            PickToCVIN()
            PlaceToFix3()
            PickToFix3()
            PlacePASS()
            PickToCamera()
            PlaceToFix11()
            PickToFix11()
            PlacePASS2()
            a = 4
        end
        if DI(14) == ON and a == 4 then
            PickToCVIN()
            PlaceToFix4()
            PickToFix4()
            PlacePASS()
            PickToCamera()
            PlaceToFix9()
            PickToFix9()
            PlacePASS2()
            a = 5
        end
        if DI(14) == ON and a == 5 then
            PickToCVIN()
            PlaceToFix5()
            PickToFix5()
            PlacePASS()
            PickToCamera()
            PlaceToFix10()
            PickToFix10()
            PlacePASS2()
            a = 6
        end
        if DI(14) == ON and a == 6 then
            PickToCVIN()
            PlaceToFix6()
            PickToFix6()
            PlacePASS()
            PickToCamera()
            PlaceToFix11()
            PickToFix11()
            PlacePASS2()
            a = 7
        end
        if DI(14) == ON and a == 7 then
            PickToCVIN()
            PlaceToFix7()
            PickToFix7()
            PlacePASS()
            PickToCamera()
            PlaceToFix9()
            PickToFix9()
            PlacePASS2()
            a = 8
        end
        if DI(14) == ON and a == 8 then
            PickToCVIN()
            PlaceToFix8()
            PickToFix8()
            PlacePASS()
            PickToCamera()
            PlaceToFix10()
            PickToFix10()
            PlacePASS2()
            
            break
        end
	end
	
	
end



function CheckFixCam(fix,unit)
	if fix==9 then
		if unit==0 then
            PlaceToFix9()
            Fix9Finish=false
            Fix9HPCB=true
            Fix9Test=true            
            DELAY(1)
            --sn2 = "NPG02C100003807" 
            sendCam="01_"..sn2            
            print("Data ok ",sendCam)
            DELAY(0.5)
            WriteModbus(0x3200,"W",9)                        
		elseif unit==1 then
			PickToFix9()
            Fix9Test=false		
            if GrHPcb == true then
            	GrHPcb = false
            	WAIT(DI,20,"ON")
            end
            if DI(3)==ON then
                PlaceToFix9() 
                Fix9Finish=false
                Fix9HPCB=true
                Fix9Test=true
                DELAY(1)
                --sn2 = "NPG02C100003807" 
                sendCam="01_"..sn2            
                print("Data ok ",sendCam)
                DELAY(0.5)
                WriteModbus(0x3200,"W",9)
            end	
        end
    elseif fix==10 then
		if unit==0 then
            PlaceToFix10()
            Fix10Finish=false
            Fix10HPCB=true
            Fix10Test=true            
            DELAY(1)
            --sn2 = "NPG02C100003807" 
            sendCam="02_"..sn2            
            print("Data ok ",sendCam)
            DELAY(0.5)
            WriteModbus(0x3200,"W",10)                        
		elseif unit==1 then
			PickToFix10()
            Fix10Test=false		
            if GrHPcb == true then
            	GrHPcb = false
            	WAIT(DI,20,"ON")
            end
            if DI(3)==ON then
                PlaceToFix10() 
                Fix10Finish=false
                Fix10HPCB=true
                Fix10Test=true
                DELAY(1)
                --sn2 = "NPG02C100003807" 
                sendCam="02_"..sn2            
                print("Data ok ",sendCam)
                DELAY(0.5)
                WriteModbus(0x3200,"W",10)
            end	
        end    
                            
	elseif fix==11 then
		if unit==0 then
            PlaceToFix11()
            Fix11Finish=false
            Fix11HPCB=true
            Fix11Test=true            
            DELAY(1)
            --sn2 = "NPG02C100003807" 
            sendCam="03_"..sn2            
            print("Data ok ",sendCam)
            DELAY(0.5)
            WriteModbus(0x3200,"W",11)                        
		elseif unit==1 then
			PickToFix11()
            Fix11Test=false		
            if GrHPcb == true then
            	GrHPcb = false
            	WAIT(DI,20,"ON")
            end
            if DI(3)==ON then
                PlaceToFix11() 
                Fix11Finish=false
                Fix11HPCB=true
                Fix11Test=true
                DELAY(1)
                --sn2 = "NPG02C100003807" 
                sendCam="03_"..sn2            
                print("Data ok ",sendCam)
                DELAY(0.5)
                WriteModbus(0x3200,"W",11)
            end	
        end
    end      
end

function PlacePASS()
	MovP("SBuffer")
	MovP("BufFixSpare")
	--WAIT(DI,21,"OFF")
	MovL("FixSpare"+Z(80))	
    MovL("FixSpare")
	
	DO("Gripper2","OFF")
	WAIT(DI,18,"ON")
	MovL("FixSpare"+Z(80))	
	MovL("BufFixSpare")
	MovP("SBuffer")
end

function PlacePASS5()
	MovP("SBuffer")
	MovP("BufFixSpare")
	--WAIT(DI,21,"OFF")
	MovL("FixSpare"+Z(80)+RZ(6))	
    MovL("FixSpare"+RZ(6))
	
	DO("Gripper2","OFF")
	WAIT(DI,18,"ON")
	MovL("FixSpare"+Z(80)+RZ(6))	
	MovL("BufFixSpare")
	MovP("SBuffer")
end


function PlaceCamera()
	MovP("SBuffer")
	MovP("BufPlaceCam")
	WAIT(DI,21,"OFF")	
    MovL("PlaceCam")
	
	DO("Gripper1","OFF")
	WAIT(DI,21,"ON")
	MovL("BufPlaceCam")
	MovP("SBuffer")
end

function PickPASS2()
	ppp=ReadModbus(0x3FFE,"W")
	if ppp > 0 then			
		MovP("SBuffer")
		WAIT(DI,18,"ON")
		--MovP("BufCvPass2")				
        MovL("CvPass2" +Y((ppp-1)*100) +Z(150))	
        MovL("CvPass2" +Y((ppp-1)*100))            
        DO("Gripper2","ON")
        WAIT(DI,19,"ON")
        MovL("CvPass2" +Y((ppp-1)*100) +Z(150))
        ppp = ppp-1
        WriteModbus(0x3FFE,"W",ppp)
        --MovP("BufCvPass2")
        MovP("SBuffer")        
        PlacePASS2()
	end
end
function PlacePASS2()
	MovP("SBuffer")	
	CountErr = 0
  ::CheckCvOut::
	if  DI(12)==ON or DI(13)==ON then
		DELAY(1)
		CountErr = CountErr+1
		if CountErr > -1 and ppp < 8 and DI(14)==ON then
			MovP("SBuffer")
			--MovP("BufCvPass2")
			ppp=ReadModbus(0x3FFE,"W")	
            MovL("CvPass2" +Y(ppp*100) +Z(150))	
            MovL("CvPass2" +Y(ppp*100))            
            DO("Gripper2","OFF")
            WAIT(DI,18,"ON")
            MovL("CvPass2" +Y(ppp*100) +Z(150))
            --MovP("BufCvPass2")
            MovP("SBuffer")
            ppp = ppp+1
            WriteModbus(0x3FFE,"W",ppp)
            if ppp > 7 then
            	DO("TowerLightG","OFF")
            	DO("TowerLightY","ON")
            	--DO("TowerLightR","ON")
            	WAIT(DI,12,"OFF")
                WAIT(DI,13,"OFF")
            	ppp = 8
            	WriteModbus(0x3FFE,"W",ppp)
            	DO("TowerLightG","ON")
            	DO("TowerLightY","OFF")
            	DO("TowerLightR","OFF")
            end
            --WriteModbus(0x3FFE,"W",ppp)
            CountErr = 0
        else
            goto CheckCvOut
		end
    else
        MovP("BufCvPass")
        WAIT(DI,12,"OFF")
        WAIT(DI,13,"OFF")
        MovP("CvPass" +Z(200))	
        WAIT(DI,12,"OFF")
        WAIT(DI,13,"OFF")	
        MovL("CvPass")
	
        DO("Gripper2","OFF")
        WAIT(DI,18,"ON")
        MovP("CvPass" +Z(200))
        MovL("BufCvPass")
        MovP("SBuffer")
	end
end

--[[

function PlacePASS2()
	MovP("SBuffer")
	MovP("BufCvPass")
	WAIT(DI,12,"OFF")
	WAIT(DI,13,"OFF")
	MovP("CvPass" +Z(200))	
	WAIT(DI,12,"OFF")
	WAIT(DI,13,"OFF")	
    MovL("CvPass")
	
	DO("Gripper2","OFF")
	WAIT(DI,18,"ON")
	MovP("CvPass" +Z(200))
	MovL("BufCvPass")
	MovP("SBuffer")
end
]]
 function PlaceFAIL()
	MovP("SBuffer")
	MovP("BufCvFail2")
::RetryFail::
	if DI(11)==OFF then			
		MovP("BufCvFail1")		
		MovL("CvFail1" +Z(80))
		MovL("CvFail1")
        DO("Gripper2","OFF")
        WAIT(DI,18,"OFF")
        MovL("CvFail1" +Z(80))
        MovP("BufCvFail1")
    elseif DI(10)==OFF then			
		MovP("BufCvFail2")		
		MovL("CvFail2" +Z(80))
		MovL("CvFail2")
        DO("Gripper2","OFF")
        WAIT(DI,18,"OFF")
        MovL("CvFail2" +Z(80))
        MovP("BufCvFail2")     
	else
        DELAY(1)
        goto RetryFail
    end 	
	
	MovP("SBuffer")
end

function PlaceFAIL3()
	MovP("SBuffer")
	MovP("BufCvFail3")
::RetryFail::
	--if DI(24)==OFF  then			
            ddd=ReadModbus(0x3FFC,"W")
            if DI(16)==OFF  then
            	ddd = 0
            end
            MovL("CvFail3" +Y(300) +Z(90))
            MovL("CvFail3" +Y(300) +Z(30))	
            MovL("CvFail3" +Y(ddd*90) +Z(30))	
            MovL("CvFail3" +Y(ddd*90))            
            DO("Gripper1","OFF")
            WAIT(DI,21,"ON")
            MovL("CvFail3" +Y(ddd*90) +Z(90))
            MovP("BufCvFail3")
            MovP("SBuffer")
            ddd = ddd+1
            if ddd > 2 then
            	DO("TowerLightG","OFF")
            	DO("TowerLightY","OFF")
            	DO("TowerLightR","ON")
            	WAIT(DI,10,"ON")
            	WAIT(DI,10,"OFF")
            	DELAY(1)               
            	ddd = 0
            	DO("TowerLightG","ON")
            	DO("TowerLightY","OFF")
            	DO("TowerLightR","OFF")
            end
            WriteModbus(0x3FFC,"W",ddd)    
	--else
    --    DELAY(1)
    --    goto RetryFail
    --end 	
	
	MovP("SBuffer")
end

function PlaceFailGripper(Gripper)	
	if Gripper == 1 then
        MovP("BufScanFail")	
    elseif Gripper == 2 then
    	MovP("BufCvFail1")
    end
	if DI("SsFail1") == OFF then
        fff = 0
        WriteModbus(0x3FFD,"W",fff)
    end     
  ::CheckCvFail::
    fff=ReadModbus(0x3FFD,"W")	
	if  fff < 5 then
		if Gripper == 1 then		
            MovP("BufScanFail")		
            MovP("ScanFail" +Y(fff*90) +Z(130))	
            MovL("ScanFail" +Y(fff*90))            
            DO("Gripper1","OFF")
            WAIT(DI,21,"ON")            
            fff = fff+1
            WriteModbus(0x3FFD,"W",fff)
            MovP("ScanFail" +Y(fff*90) +Z(130))
            MovP("BufScanFail")
        elseif Gripper == 2 then
        	MovP("BufCvFail1")		
            MovP("CvFail1" +Y(fff*90) +Z(130))	
            MovL("CvFail1" +Y(fff*90))            
            DO("Gripper2","OFF")
            WAIT(DI,18,"ON")            
            fff = fff+1
            WriteModbus(0x3FFD,"W",fff)
            MovP("CvFail1" +Y(fff*90) +Z(130))
            MovP("BufCvFail1")
        end 
        if fff > 4 then
            DO("TowerLightG","OFF")
            DO("TowerLightY","ON")
            WAIT(DI,10,"OFF")
            fff = 0
            WriteModbus(0x3FFD,"W",fff)
            DO("TowerLightG","ON")
            DO("TowerLightY","OFF")
            DO("TowerLightR","OFF")
        end                
        MovP("SBuffer")          
    else
        DO("TowerLightG","OFF")
        DO("TowerLightY","ON")
        WAIT(DI,10,"OFF")
        fff = 0
        WriteModbus(0x3FFD,"W",fff)
        DO("TowerLightG","ON")
        DO("TowerLightY","OFF")
        DO("TowerLightR","OFF")
        goto CheckCvFail
    end  
end



function PlaceScanFAIL()
	MovP("SBuffer")
	MovP("BufScanFail")
::RetryFail2::
	if DI(10)==OFF and DI(11)==OFF then			
		MovP("BufScanFail")		
		MovL("ScanFail" +Z(50))
		MovL("ScanFail")
        DO("Gripper1","OFF")
        WAIT(DI,21,"ON")
        MovL("ScanFail" +Z(50))
        MovP("BufScanFail")    
	else
        DELAY(1)
        goto RetryFail2
    end 
	
	
	MovP("SBuffer")
end
 
function PickToCVIN()
	WAIT(DI,14,"ON")
	WAIT(DI,21,"ON")
	WAIT(DI,20,"OFF")	
	MovP("SBuffer")
	MovP("BufLifter")	
	MovP("BufLifter1")
    MovL("Lifter1")    
    DO("Gripper1","ON")
	WAIT(DI,20,"ON")	
    MovL("BufLifter1")
    MovP("BufLifter")
    MovP("SBuffer")
   
end
function PickToCamera()
	WAIT(DI,21,"ON")
	WAIT(DI,20,"OFF")	
	WAIT(DI,21,"ON")
	MovP("SBuffer")
	MovP("BufLifter2")
    MovL("Lifter2")    
    DO("Gripper1","ON")
	WAIT(DI,20,"ON")	
    MovL("BufLifter2")    
    MovP("SBuffer")   
end

function PlaceToFix1()
	WAIT(ExtDI,{3,2},"ON")
	MovP("BufFix1")
    MovP("Fix1" + Z(80)+X(20))
    MovP("Fix1" +Z(40)+X(20))
    MovP("Fix1" +Z(40))
    MovL("Fix1")    
    DO("Gripper1","OFF")
    WAIT(DI,21,"ON")	
    MovL("Fix1" + Z(80))
    MovP("BufFix1")
end
function PlaceToFix2()
	WAIT(ExtDI,{3,4},"ON")
	MovP("BufFix2")
    MovP("Fix2" + Z(80)+X(20))
    MovP("Fix2" +Z(40)+X(20))
    MovP("Fix2" +Z(40))
    MovL("Fix2")    
    DO("Gripper1","OFF")
    WAIT(DI,21,"ON")	
    MovL("Fix2" + Z(80))
    MovP("BufFix2")
end
function PlaceToFix3()
	WAIT(ExtDI,{3,6},"ON")
	MovP("BufFix3")
    MovP("Fix3" + Z(80)+X(20))
    MovP("Fix3" +Z(40)+X(20))
    MovP("Fix3" +Z(40))
    MovL("Fix3")    
    DO("Gripper1","OFF")
    WAIT(DI,21,"ON")	
    MovL("Fix3" + Z(80))
    MovP("BufFix3")
end
function PlaceToFix4()
	WAIT(ExtDI,{3,8},"ON")
	MovP("BufFix4")
    MovP("Fix4" + Z(80)+X(20))
    MovP("Fix4" +Z(40)+X(20))
    MovP("Fix4" +Z(40))
    MovL("Fix4")    
    DO("Gripper1","OFF")
    WAIT(DI,21,"ON")	
    MovL("Fix4" + Z(80))
    MovP("BufFix4")
end
function PlaceToFix5()
	WAIT(ExtDI,{3,10},"ON")
	MovP("BufFix5")
    MovP("Fix5" + Z(80)+X(20))
    MovP("Fix5" +Z(40)+X(20))
    MovP("Fix5" +Z(40))
    MovL("Fix5")    
    DO("Gripper1","OFF")
    WAIT(DI,21,"ON")	
    MovL("Fix5" + Z(80))
    MovP("BufFix5")
end
function PlaceToFix6()
	WAIT(ExtDI,{3,12},"ON")
	MovP("BufFix6")
    MovP("Fix6" + Z(80)+X(20))
    MovP("Fix6" +Z(40)+X(20))
    MovP("Fix6" +Z(40))
    MovL("Fix6")    
    DO("Gripper1","OFF")
    WAIT(DI,21,"ON")	
    MovL("Fix6" + Z(80))
    MovP("BufFix6")
end
function PlaceToFix7()
	WAIT(ExtDI,{3,14},"ON")
	MovP("BufFix7")
    MovP("Fix7" + Z(80)+X(20))
    MovP("Fix7" +Z(40)+X(20))
    MovP("Fix7" +Z(40))
    MovL("Fix7")    
    DO("Gripper1","OFF")
    WAIT(DI,21,"ON")	
    MovL("Fix7" + Z(80))
    MovP("BufFix7")
end
function PlaceToFix8()
	WAIT(ExtDI,{3,16},"ON")
	MovP("BufFix8")
    MovP("Fix8" + Z(80)+X(20))
    MovP("Fix8" +Z(40)+X(20))
    MovP("Fix8" +Z(40))
    MovL("Fix8")    
    DO("Gripper1","OFF")
    WAIT(DI,21,"ON")	
    MovL("Fix8" + Z(80))
    MovP("BufFix8")
end
function PlaceToFix9()
	WAIT(ExtDI,{3,2},"ON")	
	MovP("BufFix9")
    MovP("Fix9" + Z(80))
    MovL("Fix9")    
    DO("Gripper1","OFF")
    WAIT(DI,21,"ON")	
    MovL("Fix9" + Z(80))
    MovP("BufFix9")
end
function PlaceToFix10()
	WAIT(ExtDI,{3,4},"ON")
	MovP("BufFix10")
    MovP("Fix10" + Z(80))
    MovL("Fix10")    
    DO("Gripper1","OFF")
    WAIT(DI,21,"ON")	
    MovL("Fix10" + Z(80))
    MovP("BufFix10")
end
function PlaceToFix11()
	WAIT(ExtDI,{3,6},"ON")
	MovP("BufFix11")
    MovP("Fix11" + Z(80))
    MovL("Fix11")    
    DO("Gripper1","OFF")
    WAIT(DI,21,"ON")	
    MovL("Fix11" + Z(80))
    MovP("BufFix11")
end

function PickToFix1()
	WAIT(ExtDI,{3,2},"ON")	
	Fix1Finish=false
	MovP("BufFix1" +RZ(-180) +RX(ReadPoint("BufFix1","RX")-(180)) +RY(ReadPoint("BufFix1","RY")*(-1)))
    MovP("Fix1" +RZ(-180) +RX(ReadPoint("Fix1","RX")-(180)) +RY(ReadPoint("Fix1","RY")*(-1)) +Z(80)+Y(-4))
    MovL("Fix1" +RZ(-180) +RX(ReadPoint("Fix1","RX")-(180)) +RY(ReadPoint("Fix1","RY")*(-1))+Y(-4))   	

	DO("Gripper2","ON")
	WAIT(DI,19,"ON")
    Fix1HPCB=false
    MovL("Fix1" +RZ(-180) +RX(ReadPoint("Fix1","RX")-(180)) +RY(ReadPoint("Fix1","RY")*(-1)) +Z(80)+Y(-4))
    MovP("BufFix1" +RZ(-180) +RX(ReadPoint("BufFix1","RX")-(180)) +RY(ReadPoint("BufFix1","RY")*(-1)))
end 
function PickToFix2()
	WAIT(ExtDI,{3,4},"ON")	
	Fix2Finish=false
	MovP("BufFix2" +RZ(-180) +RX(ReadPoint("BufFix2","RX")-(180)) +RY(ReadPoint("BufFix2","RY")*(-1)))
    MovP("Fix2" +RZ(-180) +RX(ReadPoint("Fix2","RX")-(180)) +RY(ReadPoint("Fix2","RY")*(-1)) +Z(80)+Y(-4))
    MovL("Fix2" +RZ(-180) +RX(ReadPoint("Fix2","RX")-(180)) +RY(ReadPoint("Fix2","RY")*(-1))+Y(-4))   	

	DO("Gripper2","ON")
	WAIT(DI,19,"ON")
    Fix2HPCB=false
    MovL("Fix2" +RZ(-180) +RX(ReadPoint("Fix2","RX")-(180)) +RY(ReadPoint("Fix2","RY")*(-1)) +Z(80)+Y(-4))
    MovP("BufFix2" +RZ(-180) +RX(ReadPoint("BufFix2","RX")-(180)) +RY(ReadPoint("BufFix2","RY")*(-1)))
end 
function PickToFix3()
	WAIT(ExtDI,{3,6},"ON")	
	Fix3Finish=false
	MovP("BufFix3" +RZ(-180) +RX(ReadPoint("BufFix3","RX")-(180)) +RY(ReadPoint("BufFix3","RY")*(-1)))
    MovP("Fix3" +RZ(-180) +RX(ReadPoint("Fix3","RX")-(180)) +RY(ReadPoint("Fix3","RY")*(-1)) +Z(80)+Y(-4))
    MovL("Fix3" +RZ(-180) +RX(ReadPoint("Fix3","RX")-(180)) +RY(ReadPoint("Fix3","RY")*(-1))+Y(-4))   	

	DO("Gripper2","ON")
	WAIT(DI,19,"ON")
    Fix3HPCB=false
    MovL("Fix3" +RZ(-180) +RX(ReadPoint("Fix3","RX")-(180)) +RY(ReadPoint("Fix3","RY")*(-1)) +Z(80)+Y(-4))
    MovP("BufFix3" +RZ(-180) +RX(ReadPoint("BufFix3","RX")-(180)) +RY(ReadPoint("BufFix3","RY")*(-1)))
end 
function PickToFix4()
	WAIT(ExtDI,{3,8},"ON")	
	Fix4Finish=false
	MovP("BufFix4" +RZ(-180) +RX(ReadPoint("BufFix4","RX")-(180)) +RY(ReadPoint("BufFix4","RY")*(-1)))
    MovP("Fix4" +RZ(-180) +RX(ReadPoint("Fix4","RX")-(180)) +RY(ReadPoint("Fix4","RY")*(-1)) +Z(80)+Y(-4))
    MovL("Fix4" +RZ(-180) +RX(ReadPoint("Fix4","RX")-(180)) +RY(ReadPoint("Fix4","RY")*(-1))+Y(-4))   	

	DO("Gripper2","ON")
	WAIT(DI,19,"ON")
    Fix4HPCB=false
    MovL("Fix4" +RZ(-180) +RX(ReadPoint("Fix4","RX")-(180)) +RY(ReadPoint("Fix4","RY")*(-1)) +Z(80)+Y(-4))
    MovP("BufFix4" +RZ(-180) +RX(ReadPoint("BufFix4","RX")-(180)) +RY(ReadPoint("BufFix4","RY")*(-1)))
end 
function PickToFix5()
	WAIT(ExtDI,{3,10},"ON")	
	Fix5Finish=false
	MovP("BufFix5" +RZ(-180) +RX(ReadPoint("BufFix5","RX")-(180)) +RY(ReadPoint("BufFix5","RY")*(-1)))
    MovP("Fix5" +RZ(-180) +RX(ReadPoint("Fix5","RX")-(180)) +RY(ReadPoint("Fix5","RY")*(-1)) +Z(80)+Y(-4))
    MovL("Fix5" +RZ(-180) +RX(ReadPoint("Fix5","RX")-(180)) +RY(ReadPoint("Fix5","RY")*(-1))+Y(-4))   	

	DO("Gripper2","ON")
	WAIT(DI,19,"ON")
    Fix5HPCB=false
    MovL("Fix5" +RZ(-180) +RX(ReadPoint("Fix5","RX")-(180)) +RY(ReadPoint("Fix5","RY")*(-1)) +Z(80)+Y(-4))
    MovP("BufFix5" +RZ(-180) +RX(ReadPoint("BufFix5","RX")-(180)) +RY(ReadPoint("BufFix5","RY")*(-1)))
end 
function PickToFix6()
	WAIT(ExtDI,{3,12},"ON")	
	Fix6Finish=false
	MovP("BufFix6" +RZ(-180) +RX(ReadPoint("BufFix6","RX")-(180)) +RY(ReadPoint("BufFix6","RY")*(-1)))
    MovP("Fix6" +RZ(-180) +RX(ReadPoint("Fix6","RX")-(180)) +RY(ReadPoint("Fix6","RY")*(-1)) +Z(80)+Y(-4))
    MovL("Fix6" +RZ(-180) +RX(ReadPoint("Fix6","RX")-(180)) +RY(ReadPoint("Fix6","RY")*(-1))+Y(-4))   	

	DO("Gripper2","ON")
	WAIT(DI,19,"ON")
    Fix6HPCB=false
    MovL("Fix6" +RZ(-180) +RX(ReadPoint("Fix6","RX")-(180)) +RY(ReadPoint("Fix6","RY")*(-1)) +Z(80)+Y(-4))
    MovP("BufFix6" +RZ(-180) +RX(ReadPoint("BufFix6","RX")-(180)) +RY(ReadPoint("BufFix6","RY")*(-1)))
end 
function PickToFix7()
	WAIT(ExtDI,{3,14},"ON")	
	Fix7Finish=false
	MovP("BufFix7" +RZ(-180) +RX(ReadPoint("BufFix7","RX")-(180)) +RY(ReadPoint("BufFix7","RY")*(-1)))
    MovP("Fix7" +RZ(-180) +RX(ReadPoint("Fix7","RX")-(180)) +RY(ReadPoint("Fix7","RY")*(-1)) +Z(80)+Y(-4))
    MovL("Fix7" +RZ(-180) +RX(ReadPoint("Fix7","RX")-(180)) +RY(ReadPoint("Fix7","RY")*(-1))+Y(-4))   	

	DO("Gripper2","ON")
	WAIT(DI,19,"ON")
    Fix7HPCB=false
    MovL("Fix7" +RZ(-180) +RX(ReadPoint("Fix7","RX")-(180)) +RY(ReadPoint("Fix7","RY")*(-1)) +Z(80)+Y(-4))
    MovP("BufFix7" +RZ(-180) +RX(ReadPoint("BufFix7","RX")-(180)) +RY(ReadPoint("BufFix7","RY")*(-1)))
end 
function PickToFix8()
	WAIT(ExtDI,{3,16},"ON")	
	Fix8Finish=false
	MovP("BufFix8" +RZ(-180) +RX(ReadPoint("BufFix8","RX")-(180)) +RY(ReadPoint("BufFix8","RY")*(-1)))
    MovP("Fix8" +RZ(-180) +RX(ReadPoint("Fix8","RX")-(180)) +RY(ReadPoint("Fix8","RY")*(-1)) +Z(80)+Y(-4))
    MovL("Fix8" +RZ(-180) +RX(ReadPoint("Fix8","RX")-(180)) +RY(ReadPoint("Fix8","RY")*(-1))+Y(-4))   	

	DO("Gripper2","ON")
	WAIT(DI,19,"ON")
    Fix8HPCB=false
    MovL("Fix8" +RZ(-180) +RX(ReadPoint("Fix8","RX")-(180)) +RY(ReadPoint("Fix8","RY")*(-1)) +Z(80)+Y(-4))
    MovP("BufFix8" +RZ(-180) +RX(ReadPoint("BufFix8","RX")-(180)) +RY(ReadPoint("BufFix8","RY")*(-1)))
end 

function PickToFix9()	
	WAIT(ExtDI,{3,2},"ON")	
	Fix9Finish=false
	MovP("BufFix9" +RZ(-180) +RX(ReadPoint("BufFix9","RX")-(180)) +RY(ReadPoint("BufFix9","RY")*(-1)))
    MovL("Fix9" +RZ(-180) +RX(ReadPoint("Fix9","RX")-(180)) +RY(ReadPoint("Fix9","RY")*(-1)) +Z(80)+Y(3))
    MovL("Fix9" +RZ(-180) +RX(ReadPoint("Fix9","RX")-(180)) +RY(ReadPoint("Fix9","RY")*(-1))+Y(3))   	

	DO("Gripper2","ON")
	WAIT(DI,19,"ON")
    Fix9HPCB=false
    MovL("Fix9" +RZ(-180) +RX(ReadPoint("Fix9","RX")-(180)) +RY(ReadPoint("Fix9","RY")*(-1)) +Z(80)+Y(3))
    WriteModbus(0x3109,"W",1)
    MovP("BufFix9" +RZ(-180) +RX(ReadPoint("BufFix9","RX")-(180)) +RY(ReadPoint("BufFix9","RY")*(-1)))
end
function PickToFix10()
	WAIT(ExtDI,{3,4},"ON")	
	Fix10Finish=false
	MovP("BufFix10" +RZ(-180) +RX(ReadPoint("BufFix10","RX")-(180)) +RY(ReadPoint("BufFix10","RY")*(-1)))
    MovL("Fix10" +RZ(-180) +RX(ReadPoint("Fix10","RX")-(180)) +RY(ReadPoint("Fix10","RY")*(-1)) +Z(80)+Y(3))
    MovL("Fix10" +RZ(-180) +RX(ReadPoint("Fix10","RX")-(180)) +RY(ReadPoint("Fix10","RY")*(-1))+Y(3))   	

	DO("Gripper2","ON")
	WAIT(DI,19,"ON")
    Fix10HPCB=false
    MovL("Fix10" +RZ(-180) +RX(ReadPoint("Fix10","RX")-(180)) +RY(ReadPoint("Fix10","RY")*(-1)) +Z(80)+Y(3))
    WriteModbus(0x310A,"W",1)
    MovP("BufFix10" +RZ(-180) +RX(ReadPoint("BufFix10","RX")-(180)) +RY(ReadPoint("BufFix10","RY")*(-1)))
end 
function PickToFix11()
	WAIT(ExtDI,{3,6},"ON")		
	Fix11Finish=false
	MovP("BufFix11" +RZ(-180) +RX(ReadPoint("BufFix11","RX")-(180)) +RY(ReadPoint("BufFix11","RY")*(-1)))
    MovL("Fix11" +RZ(-180) +RX(ReadPoint("Fix11","RX")-(180)) +RY(ReadPoint("Fix11","RY")*(-1)) +Z(80)+Y(3))
    MovL("Fix11" +RZ(-180) +RX(ReadPoint("Fix11","RX")-(180)) +RY(ReadPoint("Fix11","RY")*(-1))+Y(3))   	

	DO("Gripper2","ON")
	WAIT(DI,19,"ON")
    Fix11HPCB=false
    MovL("Fix11" +RZ(-180) +RX(ReadPoint("Fix11","RX")-(180)) +RY(ReadPoint("Fix11","RY")*(-1)) +Z(80)+Y(3))
    WriteModbus(0x310B,"W",1)
    MovP("BufFix11" +RZ(-180) +RX(ReadPoint("BufFix11","RX")-(180)) +RY(ReadPoint("BufFix11","RY")*(-1)))
end 

function CheckVision(point)
	if point == 0 then
        MovP("Vision1")
        DELAY(1)
        MovP("SBuffer")
        x2 = x2 + 1
    elseif point == 100 then
        MovP("Vision2")
        DELAY(1)
        MovP("SBuffer")
    elseif point == 200 then
        MovP("Vision3")
        DELAY(1)
        MovP("SBuffer")
    elseif point == 300 then
        MovP("Vision4")
        DELAY(1)
        MovP("SBuffer")
    elseif point == 400 then
        MovP("Vision5")
        DELAY(1)
        MovP("SBuffer")
    elseif point == 500 then
        MovP("Vision6")
        DELAY(1)
        MovP("SBuffer")
    elseif point == 600 then
        MovP("Vision7")
        DELAY(1)
        MovP("SBuffer")
    
    end
end
function ThreadFix1()	
		Enable1=ReadModbus(0x3001,"W")
		if Enable1==1 then
			if iStep1==1 then
				if Fix1Test==true then
					WAIT (ExtDI,{3,2},"ON")
					ExtDO(3,1,"ON")
					WAIT (ExtDI,{3,1},"ON")
					DELAY(0.5)
					WriteModbus(0x3101,"W",2)
                    Fix1Finish=false
                    iStep1=2					
				end	
			elseif iStep1==2 then
				if Fix1Finish==true then					
					ExtDO(3,1,"OFF")
					WAIT (ExtDI,{3,2},"ON")
					DELAY(0.5)					
					Testing1=false
					WriteModbus(0x3101,"W",1)
					Fix1Test=false
					iStep1 = 1
				else
                    WriteModbus(0x3210,"W",1)
				end 
            end
		else
            Fix1Finish=false
			Fix1Test=false
			Fix1HPCB=false
			WriteModbus(0x3101,"W",1)
			iStep1 = 1
		end		 
end

function ThreadFix2()
		Enable2=ReadModbus(0x3002,"W")
		if Enable2==1 then
			if iStep2==1 then
				if Fix2Test==true then
					WAIT (ExtDI,{3,4},"ON")
					ExtDO(3,2,"ON")
					WAIT (ExtDI,{3,3},"ON")
					DELAY(0.5)
					WriteModbus(0x3102,"W",2)
                    Fix2Finish=false
                    iStep2=2					
				end	
			elseif iStep2==2 then
				if Fix2Finish==true then					
					ExtDO(3,2,"OFF")
					WAIT (ExtDI,{3,4},"ON")
					DELAY(0.5)					
					Testing2=false
					WriteModbus(0x3102,"W",1)
					Fix2Test=false
					iStep2 = 1
				else
                    WriteModbus(0x3210,"W",1)				
				end 
            end
		else
            Fix2Finish=false
			Fix2Test=false
			Fix2HPCB=false
			WriteModbus(0x3102,"W",1)
			iStep2 = 1
		end	
end

function ThreadFix3()	
		Enable3=ReadModbus(0x3003,"W")
		if Enable3==1 then
			if iStep3==1 then
				if Fix3Test==true then
					WAIT (ExtDI,{3,6},"ON")
					ExtDO(3,3,"ON")
					WAIT (ExtDI,{3,5},"ON")
					DELAY(0.5)
					WriteModbus(0x3102,"W",2)
                    Fix3Finish=false
                    iStep3=2					
				end	
			elseif iStep3==2 then
				if Fix3Finish==true then					
					ExtDO(3,3,"OFF")
					WAIT (ExtDI,{3,6},"ON")
					DELAY(0.5)					
					Testing3=false
					WriteModbus(0x3103,"W",1)
					Fix3Test=false
					iStep3 = 1
				else
                    WriteModbus(0x3210,"W",1)				
				end 
            end
		else
            Fix3Finish=false
			Fix3Test=false
			Fix3HPCB=false
			WriteModbus(0x3103,"W",1)
			iStep3 = 1
		end
end

function ThreadFix4()
	
		Enable4=ReadModbus(0x3004,"W")
		if Enable4==1 then
			if iStep4==1 then
				if Fix4Test==true then
					WAIT (ExtDI,{3,8},"ON")
					ExtDO(3,4,"ON")
					WAIT (ExtDI,{3,7},"ON")
					DELAY(0.5)
					WriteModbus(0x3104,"W",2)
                    Fix4Finish=false
                    iStep4=2
					
				end	
			elseif iStep4==2 then
				if Fix4Finish==true then					
					ExtDO(3,4,"OFF")
					WAIT (ExtDI,{3,8},"ON")
					DELAY(0.5)					
					Testing4=false
					WriteModbus(0x3104,"W",1)
					Fix4Test=false
					iStep4 = 1
				else
                    WriteModbus(0x3210,"W",1)				
				end 
            end
		else
            Fix4Finish=false
			Fix4Test=false
			Fix4HPCB=false
			WriteModbus(0x3104,"W",1)
			iStep4 = 1
		end
end

function ThreadFix5()
	
		Enable5=ReadModbus(0x3005,"W")
		if Enable5==1 then
			if iStep5==1 then
				if Fix5Test==true then
					WAIT (ExtDI,{3,10},"ON")
					ExtDO(3,5,"ON")
					WAIT (ExtDI,{3,9},"ON")
					DELAY(0.5)
					WriteModbus(0x3105,"W",2)
                    Fix5Finish=false
                    iStep5=2
					
				end	
			elseif iStep5==2 then
				if Fix5Finish==true then					
					ExtDO(3,5,"OFF")
					WAIT (ExtDI,{3,10},"ON")
					DELAY(0.5)					
					Testing5=false
					WriteModbus(0x3105,"W",1)
					Fix5Test=false
					iStep5 = 1
				else
                    WriteModbus(0x3220,"W",1)				
				end 
            end
		else
            Fix5Finish=false
			Fix5Test=false
			Fix5HPCB=false
			WriteModbus(0x3105,"W",1)
			iStep5 = 1
		end
end

function ThreadFix6()
	
		Enable6=ReadModbus(0x3006,"W")
		if Enable6==1 then
			if iStep6==1 then
				if Fix6Test==true then
					WAIT (ExtDI,{3,12},"ON")
					ExtDO(3,6,"ON")
					WAIT (ExtDI,{3,11},"ON")
					DELAY(0.5)
					WriteModbus(0x3106,"W",2)
                    Fix6Finish=false
                    iStep6=2
					
				end	
			elseif iStep6==2 then
				if Fix6Finish==true then					
					ExtDO(3,6,"OFF")
					WAIT (ExtDI,{3,12},"ON")
					DELAY(0.5)					
					Testing6=false
					WriteModbus(0x3106,"W",1)
					Fix6Test=false
					iStep6 = 1	
				else
                    WriteModbus(0x3220,"W",1)			
				end 
            end
		else
            Fix6Finish=false
			Fix6Test=false
			Fix6HPCB=false
			WriteModbus(0x3106,"W",1)
			iStep6 = 1
		end 
end

function ThreadFix7()
	
		Enable7=ReadModbus(0x3007,"W")
		if Enable7==1 then
			if iStep7==1 then
				if Fix7Test==true then
					WAIT (ExtDI,{3,14},"ON")
					ExtDO(3,7,"ON")
					WAIT (ExtDI,{3,13},"ON")
					DELAY(0.5)
					WriteModbus(0x3107,"W",2)
                    Fix7Finish=false
                    iStep7=2
					
				end	
			elseif iStep7==2 then
				if Fix7Finish==true then					
					ExtDO(3,7,"OFF")
					WAIT (ExtDI,{3,14},"ON")
					DELAY(0.5)					
					Testing7=false
					WriteModbus(0x3107,"W",1)
					Fix7Test=false
					iStep7 = 1
				else
                    WriteModbus(0x3220,"W",1)				
				end 
            end
		else
            Fix7Finish=false
			Fix7Test=false
			Fix7HPCB=false
			WriteModbus(0x3107,"W",1)
			iStep7 = 1
		end
end

function ThreadFix8()
	
		Enable8=ReadModbus(0x3008,"W")
		if Enable8==1 then
			if iStep8==1 then
				if Fix8Test==true then
					WAIT (ExtDI,{3,16},"ON")
					ExtDO(3,9,"ON")
					WAIT (ExtDI,{3,15},"ON")
					DELAY(0.5)
					WriteModbus(0x3108,"W",2)
                    Fix8Finish=false
                    iStep8=2					
				end	
			elseif iStep8==2 then
				if Fix8Finish==true then					
					ExtDO(3,9,"OFF")
					WAIT (ExtDI,{3,16},"ON")
					DELAY(0.5)					
					Testing8=false
					WriteModbus(0x3108,"W",1)
					Fix8Test=false
					iStep8 = 1
				else
                    WriteModbus(0x3220,"W",1)				
				end 
            end
		else
            Fix8Finish=false
			Fix8Test=false
			Fix8HPCB=false
			WriteModbus(0x3108,"W",1)
			iStep8 = 1
		end
end

function ThreadFix9()
		Enable9=ReadModbus(0x3009,"W")
		if Enable9==1 then
			if iStep9==1 then
				if Fix9Test==true then
					WAIT (ExtDI,{3,2},"ON")
					ExtDO(3,1,"ON")
					WAIT (ExtDI,{3,1},"ON")
					DELAY(0.5)
					WriteModbus(0x3109,"W",2)
                    Fix9Finish=false
                    iStep9=2					
				end	
			elseif iStep9==2 then
				if Fix9Finish==true then					
					ExtDO(3,1,"OFF")
					WAIT (ExtDI,{3,2},"ON")
					DELAY(0.5)					
					Testing9=false
					--WriteModbus(0x3109,"W",1)
					Fix9Test=false
					iStep9 = 1	
				else
                    WriteModbus(0x3500,"W",1)			
				end 
            end
		else
            Fix9Finish=false
			Fix9Test=false
			Fix9HPCB=false
			WriteModbus(0x3109,"W",1)
			iStep9 = 1
		end
end

function ThreadFix10()
	
		Enable10=ReadModbus(0x300A,"W")
		if Enable10==1 then
			if iStep10==1 then
				if Fix10Test==true then
					WAIT (ExtDI,{3,4},"ON")
					ExtDO(3,2,"ON")
					WAIT (ExtDI,{3,3},"ON")
					DELAY(0.5)
					WriteModbus(0x310A,"W",2)
                    Fix10Finish=false
                    iStep10=2
					
				end	
			elseif iStep10==2 then
				if Fix10Finish==true then					
					ExtDO(3,2,"OFF")
					WAIT (ExtDI,{3,4},"ON")
					DELAY(0.5)					
					Testing10=false
					--WriteModbus(0x310A,"W",1)
					Fix10Test=false
					iStep10 = 1	
				else
                    WriteModbus(0x3500,"W",1)			
				end 
            end
		else
            Fix10Finish=false
			Fix10Test=false
			Fix10HPCB=false
			WriteModbus(0x310A,"W",1)
			iStep10 = 1
		end
end

function ThreadFix11()
	
		Enable11=ReadModbus(0x300B,"W")
		if Enable11==1 then
			if iStep11==1 then
				if Fix11Test==true then
					WAIT (ExtDI,{3,6},"ON")
					ExtDO(3,3,"ON")
					WAIT (ExtDI,{3,5},"ON")
					DELAY(0.5)
					WriteModbus(0x310B,"W",2)
                    Fix11Finish=false
                    iStep11=2
					
				end	
			elseif iStep11==2 then
				if Fix11Finish==true then					
					ExtDO(3,3,"OFF")
					WAIT (ExtDI,{3,6},"ON")
					DELAY(0.5)					
					Testing11=false
					--WriteModbus(0x310B,"W",1)
					Fix11Test=false
					iStep11 = 1	
				else
                    WriteModbus(0x3500,"W",1)			
				end 
            end
		else
            Fix11Finish=false
			Fix11Test=false
			Fix11HPCB=false
			WriteModbus(0x310B,"W",1)
			iStep11 = 1
		end
end

tcp5 = SocketClass( "192.168.1.100",2005,nil, ",", nil,0.3,2)
DELAY(3)
 while true do
    rets5=tcp5:Receive()
    if rets5~=nil then
    	data5=rets5[1]
    	rets5=nil
    end 
    if data5=="IOT" then
    	print("msgIOT=",data5);
    	data5=""
    	break
    end 
end 

function SocketLogfile()	
    tcp5: Send(send5)
    print("Senddata5: ",send5)
end 


RBSocket01=SocketClass("192.168.1.100",2000," ",",",nil, 0.3,5)
DELAY(3)
 while true do
    RBrets = RBSocket01:Receive()
    if RBrets~=nil then
    	CMD=RBrets[1]    	
    	RBrets=nil
    end 
    if CMD=="01_R" or CMD=="01_R,01_R" then
    	print("msgR=",CMD)
    	CMD=""
    	break
    end 
end

function TcpIpScan()
    print("Client started.");
    DELAY (0.5)
    while true do
    	dataScan=ReadModbus(0x3140,"W")
        if dataScan==1 then
            WriteModbus(0x3140,"W",0)
            ABC = "01_S"
            RBSocket01:Send(ABC)
            print("senddata1: 01_S")
            break            
        end 
    end	    
    while true do
        RBrets = RBSocket01:Receive()          
        if RBrets ~= nil then
            CMD=RBrets[1]   
            print("CMD: ", CMD)
            --ret = split (CMD,",")                  
            sn1 = CMD
            print("1 = ",sn1)
            --end
            RBrets = nil
            break            
        end
        
    end 
end


--[[
SocketTest6 = SocketClass("192.168.1.100",503,nil, "\r\n", nil,0.3,5)
function TcpIpVision()
        SocketTest6:Send(SendVi)
        print("senddd      ",SendVi)
end 
function TcpIpVisionRev()
	--if SocketRecieve == true then
	VisionRes = "PENDING"
	while 1 do		
        rets6 = SocketTest6:Receive()
        if rets6 ~= nil then
            cmd6 = rets6[1]
            print(cmd6) 
            if cmd6 == "A1P" then
                VisionRes = "PASS"       	
            else                
                VisionRes = "FAIL"
            end
            print(VisionRes)         
            visionOk = true                                
            break                 
        end
    end  
end


]]
--SocketTest4 = SocketClass("192.168.1.104",2004,"\r\n", "\r\n", nil,0.3,5)
--WriteModbus(0x3240,"W",0)
function TcpIpSocket4()
	--while true do
        datasendLog1=ReadModbus(0x3110,"W")
        if datasendLog1==44 then
            WriteModbus(0x3110,"W",0)
            SocketTest4:Send(sendVb4)
            print("4=send 1 ",sendVb4)
            DELAY(0.5)            
            WriteModbus(0x3240,"W",1)  
                    
        end
        
        datareadLog1=ReadModbus(0x3240,"W")
        if datareadLog1==1  then        	
            TcpIpSocket4Rev()
        end       
        
        
    --end
end 

function TcpIpSocket4Rev()	
	--while 1 do		
        rets4 = SocketTest4:Receive()
        if rets4 ~= nil then
            cmd4 = rets4[1]
            print(cmd4)
            --WriteModbus(0x3400,"W",0) 
            if cmd4=="01_P" then   
                WriteModbus(0x3240,"W",0)  
                WriteModbus(0x3400,"W",1)       
                print("4=data pass");                
                cmd4=" "                           
            elseif cmd4=="01_F" then   
                WriteModbus(0x3240,"W",0)  
                WriteModbus(0x3400,"W",2)          
                print("4=data fail");                
                cmd4=" " 
            elseif cmd4=="01_O" then   
                WriteModbus(0x3240,"W",0)   
                WriteModbus(0x3400,"W",3)         
                print("4=data OBA");                
                cmd4=" "  
            end 
        end      
        
        
    --end  
end

SocketTest3 = SocketClass("192.168.1.103",2003," ", ",", nil,0.3,3)
function TcpIpSocket3()
	--while true do
        datasendLog3=ReadModbus(0x3200,"W")
        if datasendLog3==9 then
            WriteModbus(0x3200,"W",0)
            --sn2 = "NPG02C100003807" 
            --sendCam = "01_"..sn2
            SocketTest3:Send(sendCam)
            print("3=send 3 ",sendCam)
            DELAY(0.5)            
            WriteModbus(0x3500,"W",1)
        elseif datasendLog3==10 then
            WriteModbus(0x3200,"W",0)
            --sn2 = "NPG02C100003807" 
            --sendCam = "01_"..sn2
            SocketTest3:Send(sendCam)
            print("3=send 3 ",sendCam)
            DELAY(0.5)            
            WriteModbus(0x3500,"W",1)
        elseif datasendLog3==11 then
            WriteModbus(0x3200,"W",0)
            --sn2 = "NPG02C100003807" 
            --sendCam = "01_"..sn2
            SocketTest3:Send(sendCam)
            print("3=send 3 ",sendCam)
            DELAY(0.5)            
            WriteModbus(0x3500,"W",1)                        
        end
        
        datareadLog3=ReadModbus(0x3500,"W")
        if datareadLog3==1 then
            TcpIpSocket3Rev()
        end
        
    --end
end 

function TcpIpSocket3Rev()	
	--while 1 do		
        rets3 = SocketTest3:Receive()
        if rets3 ~= nil then
            cmd3 = rets3[1]
            print(cmd3) 
            if cmd3=="01_P" then  
            	WriteModbus(0x3500,"W",0)  
                Fix9Finish=true
                WriteModbus(0x3319,"W",1)
                print("3=09_",cmd3);
                cmd3=" "             
            elseif cmd3=="01_F" then  
            	WriteModbus(0x3500,"W",0)  
                Fix9Finish=true
                WriteModbus(0x3319,"W",2)
                print("3=09_",cmd3);
                cmd3=" "                                                  
            end 
            if cmd3=="02_P" then  
            	WriteModbus(0x3500,"W",0)  
                Fix10Finish=true
                WriteModbus(0x331A,"W",1)
                print("3=10_",cmd3);
                cmd3=" "             
            elseif cmd3=="02_F" then  
            	WriteModbus(0x3500,"W",0)  
                Fix10Finish=true
                WriteModbus(0x331A,"W",2)
                print("3=10_",cmd3);
                cmd3=" "                                                  
            end  
            if cmd3=="03_P" then  
            	WriteModbus(0x3500,"W",0)  
                Fix11Finish=true
                WriteModbus(0x331B,"W",1)
                print("3=11_",cmd3);
                cmd3=" "             
            elseif cmd3=="03_F" then  
            	WriteModbus(0x3500,"W",0)  
                Fix11Finish=true
                WriteModbus(0x331B,"W",2)
                print("3=11_",cmd3);
                cmd3=" "                                                  
            end                  
        end      
        
        
    --end  
end

function Initail()
	
	--HomeAuto()
	Speed(ReadModbus(0x3FFF,"W"))
	
	IStep = 99
	
	--SpeedHigh()
	--DO("Gripper1","OFF")
	--DO("Gripper2","OFF")
	WAIT(DI,9,"ON") --smc alarm
	ExtDO(3,9,"OFF")
	ExtDO(3,10,"OFF")
	ExtDO(3,11,"OFF")
	ExtDO(3,12,"OFF")
	ExtDO(3,13,"OFF")
	ExtDO(3,14,"OFF") --home
	ExtDO(3,15,"OFF") --drive
	ExtDO(3,16,"OFF") --reset
	DELAY(1)
	ExtDO(3,16,"ON") --reset
	DELAY(0.5)
	ExtDO(3,16,"OFF") 
	DELAY(0.5)
	ExtDO(3,14,"ON") --home
	--WAIT(DI,8,"ON") --smc busy
	DELAY(0.5)
	ExtDO(3,14,"OFF")
	
	Status1=ReadModbus(0x3101,"W")
	Enable1=ReadModbus(0x3001,"W")
	
	WriteModbus(0x3333,"W",1)
	
	if Status1==2 then        
		Fix1HPCB=true
        Fix1Finish=false
        Fix1Test=true
        iStep1 = 2
	elseif Status1==3 then		
		Fix1HPCB=true
        Fix1Finish=true
        Fix1Test=false        
        iStep1 = 3
        print"1Err_0"
	else        
		Fix1HPCB=false
        Fix1Finish=false
        Fix1Test=false
        iStep1 = 1
	end
	
	Status2=ReadModbus(0x3102,"W")
	Enable2=ReadModbus(0x3002,"W")
	if Status2==2 then        
		Fix2HPCB=true
        Fix2Finish=false
        Fix2Test=true
        iStep2 = 2
	elseif Status2==3 then		
		Fix2HPCB=true
        Fix2Finish=true
        Fix2Test=false       
        iStep2 = 3
        print"2Err_0"
	else        
		Fix2HPCB=false
        Fix2Finish=false
        Fix2Test=false
        iStep2 = 1
	end
	
	Status3=ReadModbus(0x3103,"W")
	Enable3=ReadModbus(0x3003,"W")
	if Status3==2 then        
		Fix3HPCB=true
        Fix3Finish=false
        Fix3Test=true
        iStep3 = 2
	elseif Status3==3 then		
		Fix3HPCB=true
        Fix3Finish=true
        Fix3Test=false       
        iStep3 = 3
        print"3Err_0"
	else        
		Fix3HPCB=false
        Fix3Finish=false
        Fix3Test=false
        iStep3 = 1
	end
	
	Status4=ReadModbus(0x3104,"W")
	Enable4=ReadModbus(0x3004,"W")
	if Status4==2 then        
		Fix4HPCB=true
        Fix4Finish=false
        Fix4Test=true
        iStep4 = 2
	elseif Status4==3 then		
		Fix4HPCB=true
        Fix4Finish=true
        Fix4Test=false       
        iStep4 = 3
        print"4Err_0"
	else        
		Fix4HPCB=false
        Fix4Finish=false
        Fix4Test=false
        iStep4 = 1
	end
	
	Status5=ReadModbus(0x3105,"W")
	Enable5=ReadModbus(0x3005,"W")
	if Status5==2 then        
		Fix5HPCB=true
        Fix5Finish=false
        Fix5Test=true
        iStep5 = 2
	elseif Status5==3 then		
		Fix5HPCB=true
        Fix5Finish=true
        Fix5Test=false       
        iStep5 = 3
        print"5Err_0"
	else        
		Fix5HPCB=false
        Fix5Finish=false
        Fix5Test=false
        iStep5 = 1
	end
	
	Status6=ReadModbus(0x3106,"W")
	Enable6=ReadModbus(0x3006,"W")
	if Status6==2 then        
		Fix6HPCB=true
        Fix6Finish=false
        Fix6Test=true
        iStep6 = 2
	elseif Status6==3 then		
		Fix6HPCB=true
        Fix6Finish=true
        Fix6Test=false       
        iStep6 = 3
        print"6Err_0"
	else        
		Fix6HPCB=false
        Fix6Finish=false
        Fix6Test=false
        iStep6 = 1
	end
	
	Status7=ReadModbus(0x3107,"W")
	Enable7=ReadModbus(0x3007,"W")
	if Status7==2 then        
		Fix7HPCB=true
        Fix7Finish=false
        Fix7Test=true
        iStep7 = 2
	elseif Status7==3 then		
		Fix7HPCB=true
        Fix7Finish=true
        Fix7Test=false       
        iStep7 = 3
        print"7Err_0"
	else        
		Fix7HPCB=false
        Fix7Finish=false
        Fix7Test=false
        iStep7 = 1
	end
	
	Status8=ReadModbus(0x3108,"W")
	Enable8=ReadModbus(0x3008,"W")
	if Status8==2 then        
		Fix8HPCB=true
        Fix8Finish=false
        Fix8Test=true
        iStep8 = 2
	elseif Status8==3 then		
		Fix8HPCB=true
        Fix8Finish=true
        Fix8Test=false        
        iStep8 = 3
        print"8Err_0"       
	else        
		Fix8HPCB=false
        Fix8Finish=false
        Fix8Test=false
        iStep8 = 1
	end
	
	Status9=ReadModbus(0x3109,"W")
	Enable9=ReadModbus(0x3009,"W")
	if Status9==2 then        
		Fix9HPCB=true
        Fix9Finish=false
        Fix9Test=true
        iStep9 = 2
	elseif Status9==3 then		
		Fix9HPCB=true
        Fix9Finish=true
        Fix9Test=false       
        iStep9 = 3
        print"9Err_0"
	else        
		Fix9HPCB=false
        Fix9Finish=false
        Fix9Test=false
        iStep9 = 1
	end
	
	Status10=ReadModbus(0x310A,"W")
	Enable10=ReadModbus(0x300A,"W")
	if Status10==2 then        
		Fix10HPCB=true
        Fix10Finish=false
        Fix10Test=true
        iStep10 = 2
	elseif Status10==3 then		
		Fix10HPCB=true
        Fix10Finish=true
        Fix10Test=false       
        iStep10 = 3
        print"10Err_0"
	else        
		Fix10HPCB=false
        Fix10Finish=false
        Fix10Test=false
        iStep10 = 1
	end
	
	Status11=ReadModbus(0x310B,"W")
	Enable11=ReadModbus(0x300B,"W")
	if Status11==2 then        
		Fix11HPCB=true
        Fix11Finish=false
        Fix11Test=true
        iStep11 = 2
	elseif Status11==3 then		
		Fix11HPCB=true
        Fix11Finish=true
        Fix11Test=false       
        iStep11 = 3
        print"11Err_0"
	else        
		Fix11HPCB=false
        Fix11Finish=false
        Fix11Test=false
        iStep11 = 1
	end
	
end 

--SocketClient1 = SocketClass("192.168.1.101",2001,nil, "\r\n", nil,0.3,5)	
function Main()	
	Initail()
	if DO(8)==ON then
		--PlaceFAIL()
		PlaceFailGripper(2)
	end
	if DO(7)==ON then
		--PlaceScanFAIL()
		PlaceFailGripper(1)	
	end
	DO("TowerLightG","ON")
	while true do
		if IStep==99 then						
			ppp=ReadModbus(0x3FFE,"W")
			Status9=ReadModbus(0x3109,"W")
            Status10=ReadModbus(0x310A,"W")
            if ppp > 0 and DI(12)==OFF and DI(13)==OFF and (ExtDI(3,1)==ON or Fix9HPCB==false)  and (ExtDI(3,3)==ON or Fix10HPCB==false) then
            	tt = 0
            	PickPASS2()
                IStep = 99                
            elseif DI(14)==ON  then
                tt = 0
                c1 = 0
			::TryScan::
				WriteModbus(0x3140,"W",1)
				TcpIpScan()
				DELAY(1)
				print("2 = ",sn1)
				if sn1 ~= nil and #sn1 == 15 and sn3 ~= sn1 and c1> 0  then
					sn3 = sn1
                    PickToCVIN()                    
                    testCam = ReadModbus(0x3333,"W")
                    testCam = 1
                    sn2 = sn1
                    IStep=9004
                elseif sn1 == "NO"  then   
                	PickToCVIN()
                	PlaceFAIL3()                	                   
                    IStep = 99 
                elseif sn1 == "ng" or  sn1 == "NG" or c1 > 5 then   
                	PickToCVIN()
                	PlaceFAIL3()               	                   
                    IStep = 99 
                elseif c1 < 6 then
                	c1 = c1 + 1
                	goto TryScan                                   
				else                    
                    IStep = 99
				end
            else
                MovP("SBuffer")
                IStep=8000 
			end 
		elseif IStep==88 then	
					
			if DI(21)==ON   then
				tt = 0	
				PickToCamera()								
				IStep=9004
			else
                MovP("SBuffer")
                IStep=99
			end		
		elseif IStep==9000 then-- FINISH
						
			if Fix1Test==false and Fix1Finish==true and Fix1HPCB==true and ExtDI(3,2)==ON and DI(18)==ON and Enable1==1  then
                tt = 0
                	PickToFix1()
                    sn2 = serial1
                    print("sn2 = ",sn2) 
                    Fix1Test=false	            	
                    if DO(7)==ON then
                        PlaceToFix1() 
                        Fix1Finish=false
                        Fix1HPCB=true
                        Fix1Test=true           
                        DELAY(1)                             
                        serial1 = sn1
                        sn1 = ""
                        sendVb="01_"..serial1            
                        print("Data ok ",sendVb)
                        DELAY(0.5)
                        WriteModbus(0x3110,"W",1)
                    end  
                CheckResult =1
                DELAY(0.5)
                --sn2 = serial1 
                print("sn2 = ",sn2)
                IStep=901
            elseif Fix5Test==false and Fix5Finish==true and Fix5HPCB==true and ExtDI(3,10)==ON and DI(18)==ON and Enable5==1  then
                --CheckFix(5,1)
                	PickToFix5()
                    sn2 = serial5
                    print("sn2 = ",sn2) 
                    Fix5Test=false	            	
                    if DO(7)==ON then
                        PlaceToFix5() 
                        Fix5Finish=false
                        Fix5HPCB=true
                        Fix5Test=true           
                        DELAY(1)                             
                        serial5 = sn1
                        sn1 = ""
                        sendVb2="01_"..serial5            
                        print("Data ok2 ",sendVb2)
                        DELAY(0.5)
                        WriteModbus(0x3120,"W",5)
                    end
                CheckResult =5
                DELAY(0.5)
                --sn2 = serial1 
                print("sn2 = ",sn2)
                IStep=901
			elseif Fix2Test==false and Fix2Finish==true and Fix2HPCB==true and ExtDI(3,4)==ON and DI(18)==ON and Enable2==1  then
                --CheckFix(2,1)
                	PickToFix2()
                    sn2 = serial2
                    print("sn2 = ",sn2) 
                    Fix2Test=false	            	
                    if DO(7)==ON then
                        PlaceToFix2() 
                        Fix2Finish=false
                        Fix2HPCB=true
                        Fix2Test=true           
                        DELAY(1)                             
                        serial2 = sn1
                        sn1 = ""
                        sendVb="02_"..serial2            
                        print("Data ok ",sendVb)
                        DELAY(0.5)
                        WriteModbus(0x3110,"W",2)
                    end
                CheckResult =2
                DELAY(0.5)
                --sn2 = serial1 
                print("sn2 = ",sn2)
                IStep=901
			elseif Fix6Test==false and Fix6Finish==true and Fix6HPCB==true and ExtDI(3,12)==ON and DI(18)==ON and Enable6==1  then
                --CheckFix(6,1)
                	PickToFix6()
                    sn2 = serial6
                    print("sn2 = ",sn2) 
                    Fix6Test=false	            	
                    if DO(7)==ON then
                        PlaceToFix6() 
                        Fix6Finish=false
                        Fix6HPCB=true
                        Fix6Test=true           
                        DELAY(1)                             
                        serial6 = sn1
                        sn1 = ""
                        sendVb2="02_"..serial6            
                        print("Data ok2 ",sendVb2)
                        DELAY(0.5)
                        WriteModbus(0x3120,"W",6)
                    end
                CheckResult =6
                DELAY(0.5)
                --sn2 = serial1 
                print("sn2 = ",sn2)
                IStep=901
			elseif Fix3Test==false and Fix3Finish==true and Fix3HPCB==true and ExtDI(3,6)==ON and DI(18)==ON and Enable3==1  then
                --CheckFix(3,1)
                	PickToFix3()
                    sn2 = serial3
                    print("sn2 = ",sn2) 
                    Fix3Test=false	            	
                    if DO(7)==ON then
                        PlaceToFix3() 
                        Fix3Finish=false
                        Fix3HPCB=true
                        Fix3Test=true           
                        DELAY(1)                             
                        serial3 = sn1
                        sn1 = ""
                        sendVb="03_"..serial3            
                        print("Data ok ",sendVb)
                        DELAY(0.5)
                        WriteModbus(0x3110,"W",3)
                    end
                CheckResult =3
                DELAY(0.5)
                --sn2 = serial1 
                print("sn2 = ",sn2)
                IStep=901
			elseif Fix7Test==false and Fix7Finish==true and Fix7HPCB==true and ExtDI(3,15)==ON and DI(18)==ON and Enable7==1  then
                --CheckFix(7,1)
                	PickToFix7()
                    sn2 = serial7
                    print("sn2 = ",sn2) 
                    Fix7Test=false	            	
                    if DO(7)==ON then
                        PlaceToFix7() 
                        Fix7Finish=false
                        Fix7HPCB=true
                        Fix7Test=true           
                        DELAY(1)                             
                        serial7 = sn1
                        sn1 = ""
                        sendVb2="03_"..serial7            
                        print("Data ok ",sendVb2)
                        DELAY(0.5)
                        WriteModbus(0x3120,"W",7)
                    end
                CheckResult =7
                DELAY(0.5)
                --sn2 = serial1 
                print("sn2 = ",sn2)
                IStep=901
			elseif Fix4Test==false and Fix4Finish==true and Fix4HPCB==true and ExtDI(3,8)==ON and DI(18)==ON and Enable4==1  then
                --CheckFix(3,1)
                	PickToFix4()
                    sn2 = serial4
                    print("sn2 = ",sn2) 
                    Fix4Test=false	            	
                    if DO(7)==ON then
                        PlaceToFix4() 
                        Fix4Finish=false
                        Fix4HPCB=true
                        Fix4Test=true           
                        DELAY(1)                             
                        serial4 = sn1
                        sn1 = ""
                        sendVb="04_"..serial4            
                        print("Data ok ",sendVb)
                        DELAY(0.5)
                        WriteModbus(0x3110,"W",4)
                    end
                CheckResult =4
                DELAY(0.5)
                --sn2 = serial1 
                print("sn2 = ",sn2)
                IStep=901			
			elseif Fix8Test==false and Fix8Finish==true and Fix8HPCB==true and ExtDI(3,16)==ON and DI(18)==ON and Enable8==1  then
                --CheckFix(8,1)
                	PickToFix8()
                    sn2 = serial8
                    print("sn2 = ",sn2) 
                    Fix8Test=false	            	
                    if DO(7)==ON then
                        PlaceToFix8() 
                        Fix8Finish=false
                        Fix8HPCB=true
                        Fix8Test=true           
                        DELAY(1)                             
                        serial8 = sn1
                        sn1 = ""
                        sendVb2="04_"..serial8            
                        print("Data ok2 ",sendVb2)
                        DELAY(0.5)
                        WriteModbus(0x3120,"W",8)
                    end
                CheckResult =8
                DELAY(0.5)
                --sn2 = serial1 
                print("sn2 = ",sn2)
                IStep=901
            else
				IStep=8000
			end
		elseif IStep==8000 then-- FINISH
						
			if Fix9Test==false and Fix9Finish==true and Fix9HPCB==true and ExtDI(3,2)==ON and DI(18)==ON and Enable9==1 and smcMove == false  then
                tt = 0
                smcMove = true
                --CheckFixCam(10,1)
                    ExtDO(3,9,"ON") --home
                    DELAY(0.2)	
                    ExtDO(3,15,"ON") 
                    DELAY(0.5)
                    ExtDO(3,9,"OFF")
                    ExtDO(3,15,"OFF")	
                    WAIT(DI,3,"ON") 
                    if ReadModbus(0x3319,"W") == 5 then                   
                    sendVb4="01_"..serial9
                    print("4 check result data9 ",sendVb4)
                    WriteModbus(0x3110,"W",44)
                    end
                  	PickToFix9()
                    Fix9Test=false
                    if DO(7)==ON then
                        PlaceToFix9() 
                        Fix9Finish=false
                        Fix9HPCB=true
                        Fix9Test=true
                        DELAY(0.3)
                        --sn2 = "NPG02C100003807" 
                        sendCam="01_"..sn2            
                        print("Data ok ",sendCam)
                        DELAY(0.5)
                        WriteModbus(0x3200,"W",9)
                    end
                CheckResult =9
                smcMove = false
                IStep=901			
			elseif Fix10Test==false and Fix10Finish==true and Fix10HPCB==true and ExtDI(3,4)==ON and DI(18)==ON and Enable10==1 and smcMove == false  then
                tt = 0
                smcMove = true
                --CheckFixCam(10,1)
                    ExtDO(3,10,"ON") --home
                    DELAY(0.2)	
                    ExtDO(3,15,"ON") 
                    DELAY(0.5)
                    ExtDO(3,10,"OFF")
                    ExtDO(3,15,"OFF")	
                    WAIT(DI,4,"ON") 
                    if ReadModbus(0x331A,"W") == 5 then                    
                    sendVb4="01_"..serial10
                    print("4 check result data10 ",sendVb4)
                    WriteModbus(0x3110,"W",44)
                    end
                	PickToFix10()
                    Fix10Test=false
                    if DO(7)==ON then
                        PlaceToFix10() 
                        Fix10Finish=false
                        Fix10HPCB=true
                        Fix10Test=true
                        DELAY(0.3)
                        --sn2 = "NPG02C100003807" 
                        sendCam="02_"..sn2            
                        print("Data ok ",sendCam)
                        DELAY(0.5)
                        WriteModbus(0x3200,"W",10)
                    end
                CheckResult =10
                smcMove = false
                IStep=901			
			elseif Fix11Test==false and Fix11Finish==true and Fix11HPCB==true and ExtDI(3,6)==ON and DI(18)==ON and Enable11==1 and smcMove == false  then
                tt = 0
                smcMove = true
                --CheckFixCam(11,1)
                    ExtDO(3,11,"ON") --home
                    DELAY(0.2)	
                    ExtDO(3,15,"ON") 
                    DELAY(0.5)
                    ExtDO(3,11,"OFF")
                    ExtDO(3,15,"OFF")	
                    WAIT(DI,5,"ON")
                    if ReadModbus(0x331B,"W") == 5 then                     
                    sendVb4="01_"..serial11
                    print("4 check result data11 ",sendVb4)
                    WriteModbus(0x3110,"W",44)
                    end
                	PickToFix11()
                    Fix11Test=false
                    if DO(7)==ON then
                        PlaceToFix11() 
                        Fix11Finish=false
                        Fix11HPCB=true
                        Fix11Test=true
                        DELAY(0.3)
                        --sn2 = "NPG02C100003807" 
                        --sendCam="03_"..sn2            
                        --print("Data ok ",sendCam)
                        DELAY(0.5)
                        WriteModbus(0x3200,"W",11)
                    end
                CheckResult =11
                smcMove = false
                IStep=901			
            else
                x1 = x1 + 1 
                if x1 > 700 then
                	x1 = 0
                end
                if x2 < 10 then
                    CheckVision(x1)
                end
                --IStep=88
				IStep=99
			end	
		elseif IStep==9003 then			
			if  (Fix1Test== false or Fix1Finish==true) and ExtDI(3,2)==ON and DI(20)==ON and Enable1==1 then
                tt = 0
                	if Fix1HPCB==false then
                    --CheckFix(1,0)
                    PlaceToFix1()
                    Fix1Finish=false
                    Fix1HPCB=true
                    Fix1Test=true            
                    DELAY(1)   
                    serial1 = sn1
                    sn1 = ""
                    sendVb="01_"..serial1            
                    print("Data ok ",sendVb)
                    DELAY(0.5)
                    WriteModbus(0x3110,"W",1)             
                    IStep=99
                elseif Fix1HPCB==true then
                	--CheckFix(1,1)
                	PickToFix1()
                    sn2 = serial1
                    print("sn2 = ",sn2) 
                    Fix1Test=false	            	
                    if DO(7)==ON then
                        PlaceToFix1() 
                        Fix1Finish=false
                        Fix1HPCB=true
                        Fix1Test=true           
                        DELAY(1)                             
                        serial1 = sn1
                        sn1 = ""
                        sendVb="01_"..serial1            
                        print("Data ok ",sendVb)
                        DELAY(0.5)
                        WriteModbus(0x3110,"W",1)
                    end                
                	CheckResult =1
                	DELAY(0.5)
                	--sn2 = serial1 
                	print("sn2 = ",sn2)               	
                	IStep=901
                end								
			elseif  (Fix5Test== false or Fix5Finish==true) and ExtDI(3,10)==ON and DI(20)==ON and Enable5==1 then
                tt = 0
                	if Fix5HPCB==false then
                    --CheckFix(5,0)
                    PlaceToFix5()
                    Fix5Finish=false
                    Fix5HPCB=true
                    Fix5Test=true            
                    DELAY(1)   
                    serial5 = sn1
                    sn1 = ""
                    sendVb2="01_"..serial5            
                    print("Data ok2 ",sendVb2)
                    DELAY(0.5)
                    WriteModbus(0x3120,"W",5)
                    IStep=99
                elseif Fix5HPCB==true then
                	--CheckFix(5,1)
                	PickToFix5()
                    sn2 = serial5
                    print("sn2 = ",sn2) 
                    Fix5Test=false	            	
                    if DO(7)==ON then
                        PlaceToFix5() 
                        Fix5Finish=false
                        Fix5HPCB=true
                        Fix5Test=true           
                        DELAY(1)                             
                        serial5 = sn1
                        sn1 = ""
                        sendVb2="01_"..serial5            
                        print("Data ok2 ",sendVb2)
                        DELAY(0.5)
                        WriteModbus(0x3120,"W",5)
                    end
                	CheckResult =5
                	DELAY(0.5)
                	--sn2 = serial1 
                	print("sn2 = ",sn2)               	
                	IStep=901
                end	
			elseif  (Fix2Test== false or Fix2Finish==true) and ExtDI(3,4)==ON and DI(20)==ON and Enable2==1 then
                tt = 0
                	if Fix2HPCB==false then
                    --eckFix(2,0)
                    PlaceToFix2()
                    Fix2Finish=false
                    Fix2HPCB=true
                    Fix2Test=true            
                    DELAY(1)   
                    serial2 = sn1
                    sn1 = ""
                    sendVb="02_"..serial2            
                    print("Data ok ",sendVb)
                    DELAY(0.5)
                    WriteModbus(0x3110,"W",2)                    
                    IStep=99
                elseif Fix2HPCB==true then
                	--CheckFix(2,1)
                	PickToFix2()
                    sn2 = serial2
                    print("sn2 = ",sn2) 
                    Fix2Test=false	            	
                    if DO(7)==ON then
                        PlaceToFix2() 
                        Fix2Finish=false
                        Fix2HPCB=true
                        Fix2Test=true           
                        DELAY(1)                             
                        serial2 = sn1
                        sn1 = ""
                        sendVb="02_"..serial2            
                        print("Data ok ",sendVb)
                        DELAY(0.5)
                        WriteModbus(0x3110,"W",2)
                    end
                	CheckResult =2
                	DELAY(0.5)
                	--sn2 = serial1 
                	print("sn2 = ",sn2)               	
                	IStep=901
                end								
			elseif  (Fix6Test== false or Fix6Finish==true) and ExtDI(3,12)==ON and DI(20)==ON and Enable6==1 then
                tt = 0
                	if Fix6HPCB==false then
                    --CheckFix(6,0)
                    PlaceToFix6()
                    Fix6Finish=false
                    Fix6HPCB=true
                    Fix6Test=true            
                    DELAY(1)   
                    serial6 = sn1
                    sn1 = ""
                    sendVb2="02_"..serial6            
                    print("Data ok2 ",sendVb2)
                    DELAY(0.5)
                    WriteModbus(0x3120,"W",6)
                    IStep=99
                elseif Fix6HPCB==true then
                	--CheckFix(6,1)
                	PickToFix6()
                    sn2 = serial6
                    print("sn2 = ",sn2) 
                    Fix6Test=false	            	
                    if DO(7)==ON then
                        PlaceToFix6() 
                        Fix6Finish=false
                        Fix6HPCB=true
                        Fix6Test=true           
                        DELAY(1)                             
                        serial6 = sn1
                        sn1 = ""
                        sendVb2="02_"..serial6            
                        print("Data ok2 ",sendVb2)
                        DELAY(0.5)
                        WriteModbus(0x3120,"W",6)
                    end
                	CheckResult =6
                	DELAY(0.5)
                	--sn2 = serial1 
                	print("sn2 = ",sn2)               	
                	IStep=901
                end							
			
            elseif  (Fix3Test== false or Fix3Finish==true) and ExtDI(3,6)==ON and DI(20)==ON and Enable3==1 then
                if Fix3HPCB==false then
                    --CheckFix(3,0)                    
                    PlaceToFix3()
                    Fix3Finish=false
                    Fix3HPCB=true
                    Fix3Test=true            
                    DELAY(1)   
                    serial3 = sn1
                    sn1 = ""
                    sendVb="03_"..serial3            
                    print("Data ok ",sendVb)
                    DELAY(0.5)
                    WriteModbus(0x3110,"W",3)
                    IStep=99
                elseif Fix3HPCB==true then
                	--CheckFix(3,1)
                	PickToFix3()
                    sn2 = serial3
                    print("sn2 = ",sn2) 
                    Fix3Test=false	            	
                    if DO(7)==ON then
                        PlaceToFix3() 
                        Fix3Finish=false
                        Fix3HPCB=true
                        Fix3Test=true           
                        DELAY(1)                             
                        serial3 = sn1
                        sn1 = ""
                        sendVb="03_"..serial3            
                        print("Data ok ",sendVb)
                        DELAY(0.5)
                        WriteModbus(0x3110,"W",3)
                    end
                	CheckResult =3
                	DELAY(0.5)
                	--sn2 = serial1 
                	print("sn2 = ",sn2)               	
                	IStep=901
                end									
			elseif  (Fix7Test== false or Fix7Finish==true) and ExtDI(3,15)==ON and DI(20)==ON and Enable7==1 then
                if Fix7HPCB==false then
                    --CheckFix(7,0)
                    PlaceToFix7()
                    Fix7Finish=false
                    Fix7HPCB=true
                    Fix7Test=true            
                    DELAY(1)   
                    serial7 = sn1
                    sn1 = ""
                    sendVb2="03_"..serial7            
                    print("Data ok2 ",sendVb2)
                    DELAY(0.5)
                    WriteModbus(0x3120,"W",7)
                    IStep=99
                elseif Fix7HPCB==true then
                	--CheckFix(7,1)
                	PickToFix7()
                    sn2 = serial7
                    print("sn2 = ",sn2) 
                    Fix7Test=false	            	
                    if DO(7)==ON then
                        PlaceToFix7() 
                        Fix7Finish=false
                        Fix7HPCB=true
                        Fix7Test=true           
                        DELAY(1)                             
                        serial7 = sn1
                        sn1 = ""
                        sendVb2="03_"..serial7            
                        print("Data ok2 ",sendVb2)
                        DELAY(0.5)
                        WriteModbus(0x3120,"W",7)
                    end
                	CheckResult =7
                	DELAY(0.5)
                	--sn2 = serial1 
                	print("sn2 = ",sn2)               	
                	IStep=901
                end	
            elseif  (Fix4Test== false or Fix4Finish==true) and ExtDI(3,8)==ON and DI(20)==ON and Enable4==1 then
                if Fix4HPCB==false then
                    --CheckFix(4,0)
                    PlaceToFix4()
                    Fix4Finish=false
                    Fix4HPCB=true
                    Fix4Test=true            
                    DELAY(1)   
                    serial4 = sn1
                    sn1 = ""
                    sendVb="04_"..serial4            
                    print("Data ok ",sendVb)
                    DELAY(0.5)
                    WriteModbus(0x3110,"W",4)
                    IStep=99
                elseif Fix4HPCB==true then
                	--CheckFix(3,1)
                	PickToFix4()
                    sn2 = serial4
                    print("sn2 = ",sn2) 
                    Fix4Test=false	            	
                    if DO(7)==ON then
                        PlaceToFix4() 
                        Fix4Finish=false
                        Fix4HPCB=true
                        Fix4Test=true           
                        DELAY(1)                             
                        serial4 = sn1
                        sn1 = ""
                        sendVb="04_"..serial4            
                        print("Data ok ",sendVb)
                        DELAY(0.5)
                        WriteModbus(0x3110,"W",4)
                    end
                	CheckResult =4
                	DELAY(0.5)
                	--sn2 = serial1 
                	print("sn2 = ",sn2)               	
                	IStep=901
                end						
			elseif  (Fix8Test== false or Fix8Finish==true) and ExtDI(3,16)==ON and DI(20)==ON and Enable8==1 then
                if Fix8HPCB==false then
                    --CheckFix(8,0)
                    PlaceToFix8()
                    Fix8Finish=false
                    Fix8HPCB=true
                    Fix8Test=true            
                    DELAY(1)   
                    serial8 = sn1
                    sn1 = ""
                    sendVb2="04_"..serial8            
                    print("Data ok2 ",sendVb2)
                    DELAY(0.5)
                    WriteModbus(0x3120,"W",8)
                    IStep=99
                elseif Fix8HPCB==true then
                	--CheckFix(8,1)
                	PickToFix8()
                    sn2 = serial8
                    print("sn2 = ",sn2) 
                    Fix8Test=false	            	
                    if DO(7)==ON then
                        PlaceToFix8() 
                        Fix8Finish=false
                        Fix8HPCB=true
                        Fix8Test=true           
                        DELAY(1)                             
                        serial8 = sn1
                        sn1 = ""
                        sendVb2="04_"..serial8            
                        print("Data ok2 ",sendVb2)
                        DELAY(0.5)
                        WriteModbus(0x3120,"W",8)
                    end
                	CheckResult =8
                	DELAY(0.5)
                	--sn2 = serial1 
                	print("sn2 = ",sn2)               	
                	IStep=901
                end    
			end
		elseif IStep==9004 then
            if  (Fix9Test== false or Fix9Finish==true) and ExtDI(3,2)==ON and DI(20)==ON and Enable9==1 then
                tt = 0
                	if Fix9HPCB==false and smcMove == false then
                	smcMove = true
                	
                	serial9 = sn2
                    sn2 =""  
                    boot1 = true                    
                    testCam = ReadModbus(0x3333,"W")
                    if testCam == 0 then                  
                        sendCam="01_"..serial9            
                        print("Data ok ",sendCam)
                        DELAY(0.5)
                        WriteModbus(0x3200,"W",9)
                    end
                    
                    ExtDO(3,9,"ON") --home
                    DELAY(0.2)	
                    ExtDO(3,15,"ON") 
                    DELAY(0.5)
                    ExtDO(3,9,"OFF")
                    ExtDO(3,15,"OFF")	
                    WAIT(DI,3,"ON")
                    PlaceToFix9()
                    Fix9Finish=false
                    Fix9HPCB=true
                    Fix9Test=true            
                    DELAY(0.3)
                    
                    smcMove = false
                    IStep=99
                elseif Fix9HPCB==true and smcMove == false then
                	smcMove = true
                	--CheckFixCam(9,1)
                    ExtDO(3,9,"ON") --home
                    DELAY(0.2)	
                    ExtDO(3,15,"ON") 
                    DELAY(0.5)
                    ExtDO(3,9,"OFF")
                    ExtDO(3,15,"OFF")	
                    WAIT(DI,3,"ON")
                    if ReadModbus(0x3319,"W") == 5 then                     
                    sendVb4="01_"..serial9
                    print("4 check result data9 ",sendVb4)
                    WriteModbus(0x3110,"W",44)
                    end
                    
                    if DO(7)==ON then
                    	
                    	serial9 = sn2
                        sn2 ="" 
                        boot1 = true 
                        testCam = ReadModbus(0x3333,"W")
                        if testCam == 0 then
                            sendCam="01_"..serial9            
                            print("Data ok ",sendCam)
                            DELAY(0.5)
                            WriteModbus(0x3200,"W",9)
                        end
                    end
                	PickToFix9()
                    Fix9Test=false
                    if DO(7)==ON then
                    	
                    	--serial9 = sn2
                        --sn2 ="" 
                        --boot1 = true 
                        --testCam = ReadModbus(0x3333,"W")
                        --if testCam == 0 then
                        --    sendCam="01_"..serial9            
                        --    print("Data ok ",sendCam)
                        --    DELAY(0.5)
                        --    WriteModbus(0x3200,"W",9)
                        --end
                        
                        PlaceToFix9() 
                        Fix9Finish=false
                        Fix9HPCB=true
                        Fix9Test=true
                        DELAY(0.3)                        
                        
                    end
                	CheckResult =9 
                    smcMove = false               	                	
                	IStep=901                	
                end
            elseif  (Fix10Test== false or Fix10Finish==true) and ExtDI(3,4)==ON and DI(20)==ON and Enable10==1 then
                tt = 0
                	if Fix10HPCB==false and smcMove == false then
                	smcMove = true
                	
                	serial10 = sn2
                    sn2 ="" 
                    boot2 = true 
                    testCam = ReadModbus(0x3333,"W")
                    if testCam == 0 then                   
                        sendCam="02_"..serial10            
                        print("Data ok ",sendCam)
                        DELAY(0.5)
                        WriteModbus(0x3200,"W",10)
                    end
                    
                    ExtDO(3,10,"ON") --home
                    DELAY(0.2)	
                    ExtDO(3,15,"ON") 
                    DELAY(0.5)
                    ExtDO(3,10,"OFF")
                    ExtDO(3,15,"OFF")	
                    WAIT(DI,4,"ON")
                    PlaceToFix10()
                    Fix10Finish=false
                    Fix10HPCB=true
                    Fix10Test=true            
                    DELAY(0.3)
                    
                    smcMove = false
                    IStep=99
                elseif Fix10HPCB==true and smcMove == false then 
                	smcMove = true 
                    ExtDO(3,10,"ON") --home
                    DELAY(0.2)	
                    ExtDO(3,15,"ON") 
                    DELAY(0.5)
                    ExtDO(3,10,"OFF")
                    ExtDO(3,15,"OFF")	
                    WAIT(DI,4,"ON") 
                    if ReadModbus(0x331A,"W") == 5 then                   
                    sendVb4="01_"..serial10
                    print("4 check result data10 ",sendVb4)
                    WriteModbus(0x3110,"W",44)
                    end 
                    
                    if DO(7)==ON then
                    	
                    	serial10 = sn2
                        sn2 ="" 
                        boot2 = true
                        testCam = ReadModbus(0x3333,"W")
                        if testCam == 0 then 
                            sendCam="02_"..serial10            
                            print("Data ok ",sendCam)
                            DELAY(0.5)
                            WriteModbus(0x3200,"W",10)
                        end
                    end 
                               	            	
                	PickToFix10()
                    Fix10Test=false
                    if DO(7)==ON then
                    	
                    	--serial10 = sn2
                        --sn2 ="" 
                        --boot2 = true
                        --testCam = ReadModbus(0x3333,"W")
                        --if testCam == 0 then 
                        --    sendCam="02_"..serial10            
                        --    print("Data ok ",sendCam)
                        --    DELAY(0.5)
                        --    WriteModbus(0x3200,"W",10)
                        --end
                        
                        PlaceToFix10() 
                        Fix10Finish=false
                        Fix10HPCB=true
                        Fix10Test=true
                        DELAY(0.3)                                                
                        
                    end
                	CheckResult =10   
                    smcMove = false             	               	                	
                	IStep=901
                end
            elseif (Fix11Test== false or Fix11Finish==true) and ExtDI(3,6)==ON and DI(20)==ON and Enable11==1 then
                tt = 0
                	if Fix11HPCB==false and smcMove == false then
                	smcMove = true
                	
                	serial11 = sn2
                    sn2 =""
                    boot3 = true   
                    testCam = ReadModbus(0x3333,"W")
                    if testCam == 0 then                  
                        sendCam="03_"..serial11                              
                        print("Data ok ",sendCam)
                        DELAY(0.5)
                        WriteModbus(0x3200,"W",11)
                    end
                    
                    ExtDO(3,11,"ON") --home
                    DELAY(0.2)	
                    ExtDO(3,15,"ON") 
                    DELAY(0.5)
                    ExtDO(3,11,"OFF")
                    ExtDO(3,15,"OFF")	
                    WAIT(DI,5,"ON")
                    PlaceToFix11()
                    Fix11Finish=false
                    Fix11HPCB=true
                    Fix11Test=true            
                    DELAY(0.3)
                    
                    smcMove = false
                    IStep=99
                elseif Fix11HPCB==true and smcMove == false then
                	smcMove = true
                	
                	serial11 = sn2
                        sn2 =""
                        boot3 = true  
                        testCam = ReadModbus(0x3333,"W")
                        if testCam == 0 then
                            sendCam="03_"..serial11           
                            print("Data ok ",sendCam)
                            DELAY(0.5)
                            WriteModbus(0x3200,"W",11)
                        end
                        
                    ExtDO(3,11,"ON") --home
                    DELAY(0.2)	
                    ExtDO(3,15,"ON") 
                    DELAY(0.5)
                    ExtDO(3,11,"OFF")
                    ExtDO(3,15,"OFF")	
                    WAIT(DI,5,"ON") 
                    if ReadModbus(0x331B,"W") == 5 then                   
                    sendVb4="01_"..serial11
                    print("4 check result data11 ",sendVb4)
                    WriteModbus(0x3110,"W",44)
                    end
                	PickToFix11()
                    Fix11Test=false
                    if DO(7)==ON then
                        PlaceToFix11() 
                        Fix11Finish=false
                        Fix11HPCB=true
                        Fix11Test=true
                        DELAY(0.3)                        
                        
                    end
                	CheckResult =11 
                    smcMove = false               	                	
                	IStep=901
                end
            else
                x1 = x1 + 1 
                if x1 > 210 then
                	x1 = 0
                end
                x2 = 0           
                CheckVision(x1)
                
            end
        elseif IStep==901 then
            CheckPassFail()
            DELAY(0.5)
            if Result=="PASS" then
                PlacePASS2()
                IStep=99            	
            elseif Result=="FAIL" then
                PlaceFailGripper(2) 
                IStep=99                       	
            elseif Result=="OBA" then
                PlaceFAIL3()
                IStep=99
            end
            --IStep=88
            
		end
	end 
end 

function CheckPassFail()
	if CheckResult == 1 then
        ResultLog1=ReadModbus(0x3310,"W")
        if ResultLog1 == 1 then 
        	Result="PASS"
        else
            Result="FAIL"
        end
	elseif CheckResult == 2 then
        ResultLog1=ReadModbus(0x3312,"W")
        if ResultLog1 == 1 then
        	Result="PASS"
        else
            Result="FAIL"
        end
	elseif CheckResult == 3 then
        ResultLog1=ReadModbus(0x3313,"W")
        if ResultLog1 == 1 then
        	Result="PASS"
        else
            Result="FAIL"
        end
	elseif CheckResult == 4 then
        ResultLog1=ReadModbus(0x3314,"W")
        if ResultLog1 == 1 then
        	Result="PASS"
        else
            Result="FAIL"
        end 
    elseif CheckResult == 5 then
        ResultLog1=ReadModbus(0x3315,"W")
        if ResultLog1 == 1 then
        	Result="PASS"
        else
            Result="FAIL"
        end
	elseif CheckResult == 6 then
        ResultLog1=ReadModbus(0x3316,"W")
        if ResultLog1 == 1 then
        	Result="PASS"
        else
            Result="FAIL"
        end
	elseif CheckResult == 7 then
        ResultLog1=ReadModbus(0x3317,"W")
        if ResultLog1 == 1 then
        	Result="PASS"
        else
            Result="FAIL"
        end
	elseif CheckResult == 8 then
        ResultLog1=ReadModbus(0x3318,"W")
        if ResultLog1 == 1 then
        	Result="PASS"
        else
            Result="FAIL"
        end
            
    elseif CheckResult == 9 then
        ResultLog1=ReadModbus(0x3319,"W")      
        	kA1 = ReadModbus(0x3699,"W")
        	WriteModbus(0x36A9,"W",kA1)
        	k91 = ReadModbus(0x3689,"W")
        	WriteModbus(0x3699,"W",k91)
        	k81 = ReadModbus(0x3679,"W")
        	WriteModbus(0x3689,"W",k81)
        	k71 = ReadModbus(0x3669,"W")
        	WriteModbus(0x3679,"W",k71)
        	k61 = ReadModbus(0x3659,"W")
        	WriteModbus(0x3669,"W",k61)
        	k51 = ReadModbus(0x3649,"W")
        	WriteModbus(0x3659,"W",k51)
        	k41 = ReadModbus(0x3639,"W")
        	WriteModbus(0x3649,"W",k41)
        	k31 = ReadModbus(0x3629,"W")
        	WriteModbus(0x3639,"W",k31)
        	k21 = ReadModbus(0x3619,"W")
        	WriteModbus(0x3629,"W",k21)
        if ResultLog1 == 1 then
        	Result="PASS"
        	WriteModbus(0x3619,"W",1)
        	send5 ="Pass"
        	SocketLogfile()
        else
            Result="FAIL"
            WriteModbus(0x3619,"W",0)
        	send5 ="Fail"
        	SocketLogfile()
        end    
    elseif CheckResult == 10 then
        ResultLog1=ReadModbus(0x331A,"W")    
        	kA1 = ReadModbus(0x369A,"W")
        	WriteModbus(0x36AA,"W",kA1)
        	k91 = ReadModbus(0x368A,"W")
        	WriteModbus(0x369A,"W",k91)
        	k81 = ReadModbus(0x367A,"W")
        	WriteModbus(0x368A,"W",k81)
        	k71 = ReadModbus(0x366A,"W")
        	WriteModbus(0x367A,"W",k71)
        	k61 = ReadModbus(0x365A,"W")
        	WriteModbus(0x366A,"W",k61)
        	k51 = ReadModbus(0x364A,"W")
        	WriteModbus(0x365A,"W",k51)
        	k41 = ReadModbus(0x363A,"W")
        	WriteModbus(0x364A,"W",k41)
        	k31 = ReadModbus(0x362A,"W")
        	WriteModbus(0x363A,"W",k31)
        	k21 = ReadModbus(0x361A,"W")
        	WriteModbus(0x362A,"W",k21)
        if ResultLog1 == 1 then
        	Result="PASS"
        	WriteModbus(0x361A,"W",1)
        	send5 ="Pass"
        	SocketLogfile()
        else
            Result="FAIL"
            WriteModbus(0x361A,"W",0)
        	send5 ="Fail"
        	SocketLogfile()
        end    
    elseif CheckResult == 11 then
        ResultLog1=ReadModbus(0x331B,"W")    
        	kA1 = ReadModbus(0x369B,"W")
        	WriteModbus(0x36AB,"W",kA1)
        	k91 = ReadModbus(0x368B,"W")
        	WriteModbus(0x369B,"W",k91)
        	k81 = ReadModbus(0x367B,"W")
        	WriteModbus(0x368B,"W",k81)
        	k71 = ReadModbus(0x366B,"W")
        	WriteModbus(0x367B,"W",k71)
        	k61 = ReadModbus(0x365B,"W")
        	WriteModbus(0x366B,"W",k61)
        	k51 = ReadModbus(0x364B,"W")
        	WriteModbus(0x365B,"W",k51)
        	k41 = ReadModbus(0x363B,"W")
        	WriteModbus(0x364B,"W",k41)
        	k31 = ReadModbus(0x362B,"W")
        	WriteModbus(0x363B,"W",k31)
        	k21 = ReadModbus(0x361B,"W")
        	WriteModbus(0x362B,"W",k21)
        if ResultLog1 == 1 then
        	Result="PASS"
        	WriteModbus(0x361B,"W",1)
        	send5 ="Pass"
        	SocketLogfile()
        else
            Result="FAIL"
            WriteModbus(0x361B,"W",0)
        	send5 ="Fail"
        	SocketLogfile()
        end 
    end
    
  
    if Result=="PASS" then
    	Result=""
    	WriteModbus(0x3400,"W",1)
        ResultData = ReadModbus(0x3400,"W")
        --ResultData = 1 
        if ResultData == 1 then
        	WriteModbus(0x3400,"W",0)
        	Result="PASS"        	
        elseif ResultData == 2 then
        	WriteModbus(0x3400,"W",0)
        	Result="PASS"
        elseif ResultData == 3 then
        	WriteModbus(0x3400,"W",0)
        	Result="PASS"        
        end
    end
end
function CheckThread()	
	--while 1 do
	Enable1=ReadModbus(0x3001,"W")
	if Enable1 == 1 and ss == 0 then
		ThreadFix1()
		ss = 1
	elseif Enable1 == 0 then
        ss = 1
	end
	Enable2=ReadModbus(0x3002,"W")
	if Enable2 == 1 and ss == 1 then
		ThreadFix2()
		ss = 2
	elseif Enable2 == 0 then
        ss = 2	
	end
	Enable3=ReadModbus(0x3003,"W")
	if Enable3 == 1 and ss == 2 then
		ThreadFix3()
		ss = 3
	elseif Enable3 == 0 then
        ss = 3
	end
	Enable4=ReadModbus(0x3004,"W")
	if Enable4 == 1 and ss == 3 then
		ThreadFix4()
		ss = 0
	elseif Enable4 == 0 then
        ss = 0	
	end	
    --end
end
function CheckThread1()	
	--while 1 do	
	Enable5=ReadModbus(0x3005,"W")
	if Enable5 == 1 and ss1 == 0 then
		ThreadFix5()
		ss1 = 1
	elseif Enable5 == 0 then
        ss1 = 1	
	end
	Enable6=ReadModbus(0x3006,"W")
	if Enable6 == 1 and ss1 == 1 then
		ThreadFix6()
		ss1 = 2
	elseif Enable6 == 0 then
        ss1 = 2		
	end
	Enable7=ReadModbus(0x3007,"W")
	if Enable7 == 1 and ss1 == 2 then
		ThreadFix7()
		ss1 = 3
	elseif Enable7 == 0 then
        ss1 = 3		
	end
	Enable8=ReadModbus(0x3008,"W")
	if Enable8 == 1 and ss1 == 3 then
		ThreadFix8()
		ss1 = 0
	elseif Enable8 == 0 then
        ss1 = 0		
	end
    --end
end
function CheckThread2()	
	--while 1 do	
	Enable9=ReadModbus(0x3009,"W")
	if Enable9 == 1 and ss2 == 0 then
		ThreadFix9()
		ss2 = 1	            
          	kA1 = ReadModbus(0x3691,"W")
        	WriteModbus(0x36A1,"W",kA1)
        	WriteModbus(0x36A2,"W",kA1)
        	WriteModbus(0x36A3,"W",kA1)
        	WriteModbus(0x36A4,"W",kA1)
        	WriteModbus(0x36A5,"W",kA1)
        	WriteModbus(0x36A6,"W",kA1)
        	WriteModbus(0x36A7,"W",kA1)
        	WriteModbus(0x36A8,"W",kA1)
        	k91 = ReadModbus(0x3681,"W")
        	WriteModbus(0x3691,"W",k91)
        	WriteModbus(0x3692,"W",k91)
        	WriteModbus(0x3693,"W",k91)
        	WriteModbus(0x3694,"W",k91)
        	WriteModbus(0x3695,"W",k91)
        	WriteModbus(0x3696,"W",k91)
        	WriteModbus(0x3697,"W",k91)
        	WriteModbus(0x3698,"W",k91)
        	k81 = ReadModbus(0x3671,"W")
        	WriteModbus(0x3681,"W",k81)
        	WriteModbus(0x3682,"W",k81)
        	WriteModbus(0x3683,"W",k81)
        	WriteModbus(0x3684,"W",k81)
        	WriteModbus(0x3685,"W",k81)
        	WriteModbus(0x3686,"W",k81)
        	WriteModbus(0x3687,"W",k81)
        	WriteModbus(0x3688,"W",k81)
        	k71 = ReadModbus(0x3661,"W")
        	WriteModbus(0x3671,"W",k71)
        	WriteModbus(0x3672,"W",k71)
        	WriteModbus(0x3673,"W",k71)
        	WriteModbus(0x3674,"W",k71)
        	WriteModbus(0x3675,"W",k71)
        	WriteModbus(0x3676,"W",k71)
        	WriteModbus(0x3677,"W",k71)
        	WriteModbus(0x3678,"W",k71)
        	k61 = ReadModbus(0x3651,"W")
        	WriteModbus(0x3661,"W",k61)
        	WriteModbus(0x3662,"W",k61)
        	WriteModbus(0x3663,"W",k61)
        	WriteModbus(0x3664,"W",k61)
        	WriteModbus(0x3665,"W",k61)
        	WriteModbus(0x3666,"W",k61)
        	WriteModbus(0x3667,"W",k61)
        	WriteModbus(0x3668,"W",k61)
        	k51 = ReadModbus(0x3641,"W")
        	WriteModbus(0x3651,"W",k51)
        	WriteModbus(0x3652,"W",k51)
        	WriteModbus(0x3653,"W",k51)
        	WriteModbus(0x3654,"W",k51)
        	WriteModbus(0x3655,"W",k51)
        	WriteModbus(0x3656,"W",k51)
        	WriteModbus(0x3657,"W",k51)
        	WriteModbus(0x3658,"W",k51)
        	k41 = ReadModbus(0x3631,"W")
        	WriteModbus(0x3641,"W",k41)
        	WriteModbus(0x3642,"W",k41)
        	WriteModbus(0x3643,"W",k41)
        	WriteModbus(0x3644,"W",k41)
        	WriteModbus(0x3645,"W",k41)
        	WriteModbus(0x3646,"W",k41)
        	WriteModbus(0x3647,"W",k41)
        	WriteModbus(0x3648,"W",k41)
        	k31 = ReadModbus(0x3621,"W")
        	WriteModbus(0x3631,"W",k31)
        	WriteModbus(0x3632,"W",k31)
        	WriteModbus(0x3633,"W",k31)
        	WriteModbus(0x3634,"W",k31)
        	WriteModbus(0x3635,"W",k31)
        	WriteModbus(0x3636,"W",k31)
        	WriteModbus(0x3637,"W",k31)
        	WriteModbus(0x3638,"W",k31)
        	k21 = ReadModbus(0x3611,"W")
        	WriteModbus(0x3621,"W",k21)
        	WriteModbus(0x3622,"W",k21)
        	WriteModbus(0x3623,"W",k21)
        	WriteModbus(0x3624,"W",k21)
        	WriteModbus(0x3625,"W",k21)
        	WriteModbus(0x3626,"W",k21)
        	WriteModbus(0x3627,"W",k21)
        	WriteModbus(0x3628,"W",k21)
        	
        	WriteModbus(0x3611,"W",2)
        	WriteModbus(0x3612,"W",2)
        	WriteModbus(0x3613,"W",2)
        	WriteModbus(0x3614,"W",2)
        	WriteModbus(0x3616,"W",2)
        	WriteModbus(0x3615,"W",2)
        	WriteModbus(0x3616,"W",2) 
        	WriteModbus(0x3617,"W",2)
        	WriteModbus(0x3618,"W",2)
        	
	elseif Enable9 == 0 then
        ss2 = 1	            
          	kA1 = ReadModbus(0x3699,"W")
        	WriteModbus(0x36A9,"W",kA1)
        	WriteModbus(0x36A1,"W",kA1)
        	WriteModbus(0x36A2,"W",kA1)
        	WriteModbus(0x36A3,"W",kA1)
        	WriteModbus(0x36A4,"W",kA1)
        	WriteModbus(0x36A5,"W",kA1)
        	WriteModbus(0x36A6,"W",kA1)
        	WriteModbus(0x36A7,"W",kA1)
        	WriteModbus(0x36A8,"W",kA1)
        	k91 = ReadModbus(0x3689,"W")
        	WriteModbus(0x3699,"W",k91)
        	WriteModbus(0x3691,"W",k91)
        	WriteModbus(0x3692,"W",k91)
        	WriteModbus(0x3693,"W",k91)
        	WriteModbus(0x3694,"W",k91)
        	WriteModbus(0x3695,"W",k91)
        	WriteModbus(0x3696,"W",k91)
        	WriteModbus(0x3697,"W",k91)
        	WriteModbus(0x3698,"W",k91)
        	k81 = ReadModbus(0x3679,"W")
        	WriteModbus(0x3689,"W",k81)
        	WriteModbus(0x3681,"W",k81)
        	WriteModbus(0x3682,"W",k81)
        	WriteModbus(0x3683,"W",k81)
        	WriteModbus(0x3684,"W",k81)
        	WriteModbus(0x3685,"W",k81)
        	WriteModbus(0x3686,"W",k81)
        	WriteModbus(0x3687,"W",k81)
        	WriteModbus(0x3688,"W",k81)
        	k71 = ReadModbus(0x3669,"W")
        	WriteModbus(0x3679,"W",k71)
        	WriteModbus(0x3671,"W",k71)
        	WriteModbus(0x3672,"W",k71)
        	WriteModbus(0x3673,"W",k71)
        	WriteModbus(0x3674,"W",k71)
        	WriteModbus(0x3675,"W",k71)
        	WriteModbus(0x3676,"W",k71)
        	WriteModbus(0x3677,"W",k71)
        	WriteModbus(0x3678,"W",k71)
        	k61 = ReadModbus(0x3659,"W")
        	WriteModbus(0x3669,"W",k61)
        	WriteModbus(0x3661,"W",k61)
        	WriteModbus(0x3662,"W",k61)
        	WriteModbus(0x3663,"W",k61)
        	WriteModbus(0x3664,"W",k61)
        	WriteModbus(0x3665,"W",k61)
        	WriteModbus(0x3666,"W",k61)
        	WriteModbus(0x3667,"W",k61)
        	WriteModbus(0x3668,"W",k61)
        	k51 = ReadModbus(0x3649,"W")
        	WriteModbus(0x3659,"W",k51)
        	WriteModbus(0x3651,"W",k51)
        	WriteModbus(0x3652,"W",k51)
        	WriteModbus(0x3653,"W",k51)
        	WriteModbus(0x3654,"W",k51)
        	WriteModbus(0x3655,"W",k51)
        	WriteModbus(0x3656,"W",k51)
        	WriteModbus(0x3657,"W",k51)
        	WriteModbus(0x3658,"W",k51)
        	k41 = ReadModbus(0x3639,"W")
        	WriteModbus(0x3649,"W",k41)
        	WriteModbus(0x3641,"W",k41)
        	WriteModbus(0x3642,"W",k41)
        	WriteModbus(0x3643,"W",k41)
        	WriteModbus(0x3644,"W",k41)
        	WriteModbus(0x3645,"W",k41)
        	WriteModbus(0x3646,"W",k41)
        	WriteModbus(0x3647,"W",k41)
        	WriteModbus(0x3648,"W",k41)
        	k31 = ReadModbus(0x3629,"W")
        	WriteModbus(0x3639,"W",k31)
        	WriteModbus(0x3631,"W",k31)
        	WriteModbus(0x3632,"W",k31)
        	WriteModbus(0x3633,"W",k31)
        	WriteModbus(0x3634,"W",k31)
        	WriteModbus(0x3635,"W",k31)
        	WriteModbus(0x3636,"W",k31)
        	WriteModbus(0x3637,"W",k31)
        	WriteModbus(0x3638,"W",k31)
        	k21 = ReadModbus(0x3619,"W")
        	WriteModbus(0x3629,"W",k21)
        	WriteModbus(0x3621,"W",k21)
        	WriteModbus(0x3622,"W",k21)
        	WriteModbus(0x3623,"W",k21)
        	WriteModbus(0x3624,"W",k21)
        	WriteModbus(0x3625,"W",k21)
        	WriteModbus(0x3626,"W",k21)
        	WriteModbus(0x3627,"W",k21)
        	WriteModbus(0x3628,"W",k21)
        	
        	WriteModbus(0x3619,"W",2)
        	WriteModbus(0x3611,"W",2)
        	WriteModbus(0x3612,"W",2)
        	WriteModbus(0x3613,"W",2)
        	WriteModbus(0x3614,"W",2)
        	WriteModbus(0x3616,"W",2)
        	WriteModbus(0x3615,"W",2)
        	WriteModbus(0x3616,"W",2) 
        	WriteModbus(0x3617,"W",2)
        	WriteModbus(0x3618,"W",2)	
	end
	Enable10=ReadModbus(0x300A,"W")
	if Enable10 == 1 and ss2 == 1  then
		ThreadFix10()
		ss2 = 2
	elseif Enable10 == 0 then
        ss2 = 2	            
          	kA1 = ReadModbus(0x369A,"W")
        	WriteModbus(0x36AA,"W",k21)
        	k91 = ReadModbus(0x368A,"W")
        	WriteModbus(0x369A,"W",k21)
        	k81 = ReadModbus(0x367A,"W")
        	WriteModbus(0x368A,"W",k21)
        	k71 = ReadModbus(0x366A,"W")
        	WriteModbus(0x367A,"W",k21)
        	k61 = ReadModbus(0x365A,"W")
        	WriteModbus(0x366A,"W",k21)
        	k51 = ReadModbus(0x364A,"W")
        	WriteModbus(0x365A,"W",k21)
        	k41 = ReadModbus(0x363A,"W")
        	WriteModbus(0x364A,"W",k21)
        	k31 = ReadModbus(0x362A,"W")
        	WriteModbus(0x363A,"W",k21)
        	k21 = ReadModbus(0x361A,"W")
        	WriteModbus(0x362A,"W",k21)
        	
        	WriteModbus(0x361A,"W",2)		
	end
	Enable11=ReadModbus(0x300B,"W")
	if Enable11 == 1 and ss2 == 2  then
		ThreadFix11()
		ss2 = 0
	elseif Enable11 == 0 then
        ss2 = 0		            
          	kA1 = ReadModbus(0x369B,"W")
        	WriteModbus(0x36AB,"W",k21)
        	k91 = ReadModbus(0x368B,"W")
        	WriteModbus(0x369B,"W",k21)
        	k81 = ReadModbus(0x367B,"W")
        	WriteModbus(0x368B,"W",k21)
        	k71 = ReadModbus(0x366B,"W")
        	WriteModbus(0x367B,"W",k21)
        	k61 = ReadModbus(0x365B,"W")
        	WriteModbus(0x366B,"W",k21)
        	k51 = ReadModbus(0x364B,"W")
        	WriteModbus(0x365B,"W",k21)
        	k41 = ReadModbus(0x363B,"W")
        	WriteModbus(0x364B,"W",k21)
        	k31 = ReadModbus(0x362B,"W")
        	WriteModbus(0x363B,"W",k21)
        	k21 = ReadModbus(0x361B,"W")
        	WriteModbus(0x362B,"W",k21)
        	
        	WriteModbus(0x361B,"W",2)		
	end	
	--end
end
function DriveSmc()
	if smcMove == false then
		DELAY(3)
		if smcMove == false then					
		if bootOk1 == true then	
			smcMove = true
			bootOk1 = false
			
			sendCam="01_"..serial9            
            print("Data ok ",sendCam)
            DELAY(0.5)
            		
			DELAY(0.5)		
            ExtDO(3,9,"ON") --home
            DELAY(0.2)	
            ExtDO(3,15,"ON") 
            DELAY(0.5)
            ExtDO(3,9,"OFF")
            ExtDO(3,15,"OFF")	
            DELAY(0.5)        
            
            WriteModbus(0x3200,"W",9)
            WAIT (ExtDI,{3,2},"ON")            
        elseif bootOk2 == true then
        	smcMove = true
			bootOk2 = false	
			
			sendCam="02_"..serial10           
            print("Data ok ",sendCam)
            DELAY(0.5)
            
			DELAY(0.5)				
            ExtDO(3,10,"ON") --home
            DELAY(0.2)	
            ExtDO(3,15,"ON") 
            DELAY(0.5)
            ExtDO(3,10,"OFF")
            ExtDO(3,15,"OFF")	
            DELAY(0.5)        
            
            WriteModbus(0x3200,"W",10)
            WAIT (ExtDI,{3,4},"ON")            
        elseif bootOk3 == true then
        	smcMove = true
			bootOk3 = false	
			
			sendCam="03_"..serial11           
            print("Data ok ",sendCam)
            DELAY(0.5)
            
			DELAY(0.5)				
            ExtDO(3,11,"ON") --home
            DELAY(0.2)	
            ExtDO(3,15,"ON") 
            DELAY(0.5)
            ExtDO(3,11,"OFF")
            ExtDO(3,15,"OFF")	
            DELAY(0.5)        
            
            WriteModbus(0x3200,"W",11)
            WAIT (ExtDI,{3,6},"ON")            
        end
        smcMove = false
        end
	end
end
function TimerDelta()
	
	if boot1 == true  then
		b1 = b1 + 1
		print("boot1 = ",b1)
		ttm1 = ReadModbus(0x3801,"W")
		if b1 > ttm1 then			
            boot1 = false
            b1 = 0
            bootOk1 = true            
        end
        if boot2 == true and boot3 == true then	
            DELAY(0.3)
        elseif ( boot2 == true and boot3 == false ) or ( boot2 == false and boot3 == true ) then	
            DELAY(0.5)
        else
            DELAY(0.5)
        end
	end
	
	if boot2 == true  then
		b2 = b2 + 1
		print("boot2 = ",b2)
		ttm2 = ReadModbus(0x3802,"W")
		if b2 > ttm2 then			
            boot2 = false
            b2 = 0
            bootOk2 = true            
        end
        if boot1 == true and boot3 == true then	
            DELAY(0.3)
        elseif ( boot1 == true and boot3 == false ) or ( boot1 == false and boot3 == true ) then	
            DELAY(0.5)
        else
            DELAY(0.5)
        end
	end
	
	if boot3 == true  then
		b3 = b3 + 1
		print("boot3 = ",b3)
		ttm3 = ReadModbus(0x3803,"W")
		if b3 >ttm3 then			
            boot3 = false
            b3 = 0
            bootOk3 = true            
        end
        if boot1 == true and boot2 == true then	
            DELAY(0.3)
        elseif ( boot1 == true and boot2 == false ) or ( boot1 == false and boot2 == true ) then	
            DELAY(0.5)
        else
            DELAY(0.5)
        end
	end
end

AuxTasksAdd(Main,TcpIpSocket3,TimerDelta,DriveSmc,CheckThread2,Timer66)--,TCPFix2)--,TCPFix3)

while true do
	--collectgarbage("collect")
	--TimerDelta()			
	AuxTasks()	
end
