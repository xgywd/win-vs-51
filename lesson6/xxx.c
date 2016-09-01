	while(1)
		{
		    if(SBUF_DATA==0x12)
			{ TR0=0;
			Display()	;
		   	test();
			Display()	;
		   	}		 

		/*	if(SBUF_DATA==0x15)
			{
			TR0=0;
		   	test();
			Display();
			if(S<=10)
			{
				TR0=1;
				push_val_left=6;
				delayms(240);
				delayms(240);
			TR0=0;
		   	test();
			Display();
			S1=S; 
			//TR0=1;
				push_val_left=7;
				delayms(240);
				delayms(240);
				TR0=0;
		   	test();
			Display();
			S2=S;	




			}
			}*/
		   if(flag==1)//如果产生过中断，证明串口接收到了数据
		   {
		     flag=0;
			 /*	switch(SBUF_DATA)
				 {	 //	 case 0x13:			jicun=0x13;      break;								   //舵机
					// case 0x14:			jicun=0x14;      break;	
					 case leftdata:    jicun=SBUF_DATA; break;
					 case rightdata:   jicun=SBUF_DATA; break;
					 case forwarddata: jicun=SBUF_DATA; break;
					 case backdata:    jicun=SBUF_DATA; break;
					 case stopdata:    jicun=SBUF_DATA; break;
					// case 0x12:		   jicun=0x12;		break;
					 case jiasu:       sudu=sudu+20;    break;
					  case 0x15:		   jicun=0x15;		break;
					 case jiansu:      sudu=sudu-20;	break;
					 default: break;
				 }
				 if(sudu>=230)
				 {
				 	sudu=230;
				 }
				 if(sudu<=20)
				 {
				 	sudu=30;
				 }
			  	SBUF_DATA=jicun;  */
			   switch(SBUF_DATA)
			   {
					 case leftdata: Turn_Left(sudu,sudu); break;
					 case rightdata: Turn_Right(sudu,sudu); break;
					 case forwarddata: Forward(sudu,sudu); break;
					 case backdata: Back(sudu,sudu); break;
					 case stopdata: Stop();	 break;
				/*	 	case 0x13: 		TR0=1;	
										push_val_left=6;	
											break;	
											   
					case 0x14: 			TR0=1;		
									  	push_val_left=7;										
											break;	 */
						 default: break;				  
					
			    }
		  
		   }


		  
		}

}
