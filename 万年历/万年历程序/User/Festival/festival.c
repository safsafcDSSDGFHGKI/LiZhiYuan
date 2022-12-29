#include "festival.h"
#include "lcd12864.h"
#include "calendar.h"

//char *JieQi1[] = {"��","��","��","��","��","��","��","С","â","��","С","��","��","��","��","��","��","˪","��","С","��","��","С","��"}; 
//char *JieQi2[] = {"��","ˮ","��","��","��","��","��","��","��","��","��","��","��","��","¶","��","¶","��","��","ѩ","ѩ","��","��","��"}; 
	
uint8_t Festival_Yearly(uint16_t Year,uint8_t Mouth,uint8_t Day)
{
	uint8_t Father_Day,Mother_Day;
	
	Mother_Day = Judge_Week(Year,5,1);             // ��xx���5��1��д�룬�ж����µĵڶ����������Ǽ���
	if(Mother_Day == 0) Mother_Day = 7;
	Mother_Day = 15-Mother_Day;
	
	Father_Day = Judge_Week(Year,6,1);             // ��xx���6��1��д�룬�ж����µĵ������������Ǽ���
	if(Father_Day == 0) Father_Day = 7;
	Father_Day = 22-Father_Day;
	
if(Mouth == 1&& Day == 1)        {  return 1; }
else if(Mouth == 1&& Day == 8  ) {	return 2;	}
else if(Mouth == 1&& Day == 21 ) {	return 3;	}
else if(Mouth == 1&& Day == 26 ) { 	return 4;	}
else if(Mouth == 2&& Day == 2  ) { 	return 5;	}
else if(Mouth == 2&& Day == 10 ) { 	return 6;	}
else if(Mouth == 2&& Day == 14)  {	return 7;	}
else if(Mouth == 2&& Day == 15)  {	return 8;	}
else if(Mouth == 2&& Day == 19)  {	return 9;	}
else if(Mouth == 2&& Day == 21)  {	return 10;	}
else if(Mouth == 2&& Day == 24)  {	return 11;	}
else if(Mouth == 3&& Day == 1)   {	return 12; 	}
else if(Mouth == 3&& Day == 3)   {	return 13; 	}
else if(Mouth == 3&& Day == 5)   {	return 14;	}
else if(Mouth == 3&& Day == 8)   {	return 15;	}
else if(Mouth == 3&& Day == 12)  {	return 16;	}
else if(Mouth == 3&& Day == 14)  {	return 17;	}
else if(Mouth == 3&& Day == 15)  {	return 18; 	}
else if(Mouth == 3&& Day == 17)  {	return 19; 	}
else if(Mouth == 3&& Day == 21)  {	return 20;	}
else if(Mouth == 3&& Day == 22)  { 	return 21;	}
else if(Mouth == 3&& Day == 23)  {	return 22;	}	
else if(Mouth == 3&& Day == 24)  {	return 23;	}
else if(Mouth == 4&& Day == 1)   {	return 24; 	}
else if(Mouth == 4&& Day == 2)   {	return 25;	}
else if(Mouth == 4&& Day == 7)   {	return 26;	}
else if(Mouth == 4&& Day == 15)  {	return 27;	}
else if(Mouth == 4&& Day == 21)  {	return 28; 	}
else if(Mouth == 4&& Day == 22)  {	return 29; 	}
else if(Mouth == 4&& Day == 23)  {	return 30;	}
else if(Mouth == 4&& Day == 24)  {	return 31;	}
else if(Mouth == 4&& Day == 26)  {	return 32;	}
else if(Mouth == 4&& Day == 27)  {	return 33; 	}
else if(Mouth == 5&& Day == 1) 	 {	return 34;	}
else if(Mouth == 5&& Day == 3)   {	return 35;	}
else if(Mouth == 5&& Day == 4)   {	return 36; 	}
else if(Mouth == 5&& Day == 5)   {	return 37;	}
else if(Mouth == 5&& Day == 8)   {	return 38;	}
else if(Mouth == 5&& Day == 12)  {	return 39; 	}
else if(Mouth == 5&& Day == 15)  {	return 40;	}
else if(Mouth == 5&& Day == 17)  {	return 41;	}
else if(Mouth == 5&& Day == 18)  {	return 42; 	}
else if(Mouth == 5&& Day == 20)  {	return 43;	}
else if(Mouth == 5&& Day == 22)  {	return 44;	}
else if(Mouth == 5&& Day == 25)  {	return 45;	}
else if(Mouth == 5&& Day == 27)  {	return 46;	}
else if(Mouth == 5&& Day == 29)  {	return 47;	}
else if(Mouth == 5&& Day == 31)  {	return 48;	}
else if(Mouth == 6&& Day == 1)   {	return 49;	}
else if(Mouth == 6&& Day == 5)   {	return 50;	}
else if(Mouth == 6&& Day == 6)   {	return 51;	}
else if(Mouth == 6&& Day == 11)  {	return 52; 	}
else if(Mouth == 6&& Day == 12)  {	return 53;	}
else if(Mouth == 6&& Day == 14)  {	return 54; 	}
else if(Mouth == 6&& Day == 20)  {	return 55; 	}
else if(Mouth == 6&& Day == 23)  {	return 56;	}
else if(Mouth == 6&& Day == 25)  {	return 57; 	}
else if(Mouth == 6&& Day == 26)  {	return 58; 	}
else if(Mouth == 7&& Day == 1)   {	return 59; 	}
else if(Mouth == 7&& Day == 2)   {	return 60; 	}
else if(Mouth == 7&& Day == 7)   {	return 61;	}
else if(Mouth == 7&& Day == 11)  {	return 62; 	}
else if(Mouth == 7&& Day == 26)  {	return 63; 	}
else if(Mouth == 7&& Day == 31)  {	return 64; 	}
else if(Mouth == 8&& Day == 1)   {	return 65;	}
else if(Mouth == 8&& Day == 5)   {	return 66;	}
else if(Mouth == 8&& Day == 6)   {	return 67;	}
else if(Mouth == 8&& Day == 8)   { 	return 68;	}
else if(Mouth == 8&& Day == 12)  {	return 69; 	}
else if(Mouth == 8&& Day == 22)  {	return 70;	}
else if(Mouth == 8&& Day == 26)  {	return 71; 	}
else if(Mouth == 9&& Day == 3)   {	return 72;	}
else if(Mouth == 9&& Day == 8)   {	return 73; 	}
else if(Mouth == 9&& Day == 9)   {	return 74; 	}
else if(Mouth == 9&& Day == 10)  {	return 75; 	}
else if(Mouth == 9&& Day == 14)  {	return 76; 	}
else if(Mouth == 9&& Day == 18)  {	return 77; 	}
else if(Mouth == 9&& Day == 20)  {	return 78; 	}
else if(Mouth == 9&& Day == 21)  {	return 79; 	}
else if(Mouth == 9&& Day == 22)  {	return 80;	}
else if(Mouth == 9&& Day == 27)  {	return 81;	}
else if(Mouth == 10&& Day == 1)  { 	return 82;	}
else if(Mouth == 10&& Day == 4)  {	return 83;	}
else if(Mouth == 10&& Day == 5)  {	return 84; 	}
else if(Mouth == 10&& Day == 9)  {	return 85;	}
else if(Mouth == 10&& Day == 10) {	return 86; 	}
else if(Mouth == 10&& Day == 11) {	return 87; 	}
else if(Mouth == 10&& Day == 13) { 	return 88;	}
else if(Mouth == 10&& Day == 14) {	return 89;	}
else if(Mouth == 10&& Day == 15) {	return 89;	}
else if(Mouth == 10&& Day == 16) {	return 90;	}
else if(Mouth == 10&& Day == 17) {	return 91;	}
else if(Mouth == 10&& Day == 22) {	return 92;	}
else if(Mouth == 10&& Day == 24) {	return 93;	}
else if(Mouth == 10&& Day == 25) {	return 94; 	}
else if(Mouth == 10&& Day == 31) {	return 95;	}
else if(Mouth == 11&& Day == 1)  {	return 96;	}
else if(Mouth == 11&& Day == 8)  {	return 97; 	}
else if(Mouth == 11&& Day == 9)  {	return 98; 	}
else if(Mouth == 11&& Day == 10) {	return 99; 	}
else if(Mouth == 11&& Day == 12) {	return 100;	}
else if(Mouth == 11&& Day == 14) {	return 101; }
else if(Mouth == 11&& Day == 16) {	return 102; }
else if(Mouth == 11&& Day == 17) {	return 103;	}
else if(Mouth == 11&& Day == 20) {	return 104; }
else if(Mouth == 11&& Day == 21) {	return 105;	}
else if(Mouth == 11&& Day == 24) {	return 106;	}
else if(Mouth == 11&& Day == 28) {	return 107; }
else if(Mouth == 12&& Day == 1)  {	return 108;	}
else if(Mouth == 12&& Day == 2)  {	return 109;	}
else if(Mouth == 12&& Day == 3)  {	return 110;	}
else if(Mouth == 12&& Day == 4)  {	return 111;	}
else if(Mouth == 12&& Day == 5)  {	return 112;	}
else if(Mouth == 12&& Day == 7)  {	return 113; }
else if(Mouth == 12&& Day == 9)  {	return 114;	}
else if(Mouth == 12&& Day == 10) {	return 115; }
else if(Mouth == 12&& Day == 12) {	return 116;	}
else if(Mouth == 12&& Day == 13) {	return 117;	}
else if(Mouth == 12&& Day == 18) {	return 118; }
else if(Mouth == 12&& Day == 20) {  return 119; }
else if(Mouth == 12&& Day == 21) {	return 120; }
else if(Mouth == 12&& Day == 25) { 	return 121;	}
else if(Mouth == 12&& Day == 26) {	return 122;	}



else if(Mouth == 5&& Day == Mother_Day-1){  return 123;}
else if(Mouth == 5&& Day == Mother_Day)  {  return 124; }	

else if(Mouth == 6&& Day == Father_Day-1) { return 125;}
else if(Mouth == 6&& Day == Father_Day)   { return 126; }
	
	else 
		return 0;
}

void Return_Festival(uint8_t Valu)
{
if(Valu == 1) {LCD12864_DisplayStrChin(3 ,0,"    Ԫ������    ");}
else if(Valu == 2) {LCD12864_DisplayStrChin(3 ,0,"�ܶ�������������");  }
else if(Valu == 3) {LCD12864_DisplayStrChin(3 ,0,"��������������  ");  }
else if(Valu == 4) {LCD12864_DisplayStrChin(3 ,0,"  ���ʺ�����    ");   }
else if(Valu == 5) {LCD12864_DisplayStrChin(3 ,0,"  ����ʪ����    ");   }
else if(Valu == 6) {LCD12864_DisplayStrChin(3 ,0,"  ���������    ");   }
else if(Valu == 7) {LCD12864_DisplayStrChin(3 ,0,"  �������˽�    ");	}
else if(Valu == 8) {LCD12864_DisplayStrChin(3 ,0,"�й�12���˿���  "); }
else if(Valu == 9) {LCD12864_DisplayStrChin(3 ,0,"��Сƽ����������"); }
else if(Valu == 10) {LCD12864_DisplayStrChin(3 ,0,"  ����ĸ����    ");    }
else if(Valu == 11) {LCD12864_DisplayStrChin(3 ,0,"��������������  ");}
else if(Valu == 12) {LCD12864_DisplayStrChin(3 ,0,"  ���ʺ�����    ");}
else if(Valu == 13) {LCD12864_DisplayStrChin(3 ,0,"  ȫ��������    ");}
else if(Valu == 14) {LCD12864_DisplayStrChin(3 ,0,"�ܶ�������������");}
else if(Valu == 15) {LCD12864_DisplayStrChin(3 ,0,"�����Ͷ���Ů��  ");}
else if(Valu == 16) {LCD12864_DisplayStrChin(3 ,0,"����ɽ����������");}
else if(Valu == 17) {LCD12864_DisplayStrChin(3 ,0,"  ���ʾ�����    ");}
else if(Valu == 18) {LCD12864_DisplayStrChin(3 ,0,"����������Ȩ����");}
else if(Valu == 19) {LCD12864_DisplayStrChin(3 ,0,"  �й���ҽ��    ");}
else if(Valu == 20) {LCD12864_DisplayStrChin(3 ,0,"  ������ҵ��    ");}
else if(Valu == 21) {LCD12864_DisplayStrChin(3 ,0,"    ����ˮ��    ");}
else if(Valu == 22) {LCD12864_DisplayStrChin(3 ,0,"  ����������    ");}
else if(Valu == 23) {LCD12864_DisplayStrChin(3 ,0,"������ν�˲���");}
else if(Valu == 24) {LCD12864_DisplayStrChin(3 ,0,"  �������˽�    ");}
else if(Valu == 25) {LCD12864_DisplayStrChin(3 ,0,"���ʶ�ͯͼ����  ");}
else if(Valu == 26) {LCD12864_DisplayStrChin(3 ,0,"  ����������    ");}
else if(Valu == 27) {LCD12864_DisplayStrChin(3 ,0,"  ����������    ");}
else if(Valu == 28) {LCD12864_DisplayStrChin(3 ,0,"ȫ����ҵ�һ��");}
else if(Valu == 29) {LCD12864_DisplayStrChin(3 ,0,"  ���������    ");}
else if(Valu == 30) {LCD12864_DisplayStrChin(3 ,0,"����ͼ��Ͱ�Ȩ��");}
else if(Valu == 31) {LCD12864_DisplayStrChin(3 ,0,"�Ƿ����Ź�������");}
else if(Valu == 32) {LCD12864_DisplayStrChin(3 ,0,"����֪ʶ��Ȩ��  ");}
else if(Valu == 33) {LCD12864_DisplayStrChin(3 ,0,"    �������    ");}
else if(Valu == 34) {LCD12864_DisplayStrChin(3 ,0,"  �����Ͷ���    ");}
else if(Valu == 35) {LCD12864_DisplayStrChin(3 ,0,"��������������  ");}
else if(Valu == 36) {LCD12864_DisplayStrChin(3 ,0,"  �й������    ");}
else if(Valu == 37) {LCD12864_DisplayStrChin(3 ,0,"���˼����������");}
else if(Valu == 38) {LCD12864_DisplayStrChin(3 ,0,"  �����ʮ����  ");}
else if(Valu == 39) {LCD12864_DisplayStrChin(3 ,0,"  ���ʻ�ʿ��    ");}
else if(Valu == 40) {LCD12864_DisplayStrChin(3 ,0,"  ���ʼ�ͥ��    ");}
else if(Valu == 41) {LCD12864_DisplayStrChin(3 ,0,"  ���������    ");}
else if(Valu == 42) {LCD12864_DisplayStrChin(3 ,0,"  ���ʲ������  ");}
else if(Valu == 43) {LCD12864_DisplayStrChin(3 ,0,"�й�ѧ��Ӫ����  ");}
else if(Valu == 44) {LCD12864_DisplayStrChin(3 ,0,"��������Թ�����");}
else if(Valu == 45) {LCD12864_DisplayStrChin(3 ,0,"  ���޽����    ");}
else if(Valu == 46) {LCD12864_DisplayStrChin(3 ,0,"  �Ϻ������    ");}
else if(Valu == 47) {LCD12864_DisplayStrChin(3 ,0,"����ά����Ա��  ");}
else if(Valu == 48) {LCD12864_DisplayStrChin(3 ,0,"  ����������    ");}
else if(Valu == 49) {LCD12864_DisplayStrChin(3 ,0,"  ���ʶ�ͯ��    ");}
else if(Valu == 50) {LCD12864_DisplayStrChin(3 ,0,"  ���绷����    ");}
else if(Valu == 51) {LCD12864_DisplayStrChin(3 ,0,"  ȫ��������    ");}
else if(Valu == 52) {LCD12864_DisplayStrChin(3 ,0,"  �й��˿���    ");}
else if(Valu == 53) {LCD12864_DisplayStrChin(3 ,0,"  ������ͯ����  ");}
else if(Valu == 54) {LCD12864_DisplayStrChin(3 ,0,"  ������Ѫ��    ");}
else if(Valu == 55) {LCD12864_DisplayStrChin(3 ,0,"  ����������    ");}
else if(Valu == 56) {LCD12864_DisplayStrChin(3 ,0,"���ʰ���ƥ����  ");}
else if(Valu == 57) {LCD12864_DisplayStrChin(3 ,0,"  ȫ��������    ");}
else if(Valu == 58) {LCD12864_DisplayStrChin(3 ,0,"  ȫ��������    ");}
else if(Valu == 59) {LCD12864_DisplayStrChin(3 ,0,"�й�������������");}
else if(Valu == 60) {LCD12864_DisplayStrChin(3 ,0,"��������������  ");}
else if(Valu == 61) {LCD12864_DisplayStrChin(3 ,0,"����ս��������  ");}
else if(Valu == 62) {LCD12864_DisplayStrChin(3 ,0,"  �����˿���    ");}
else if(Valu == 63) {LCD12864_DisplayStrChin(3 ,0,"  �����ﴴ����  ");}
else if(Valu == 64) {LCD12864_DisplayStrChin(3 ,0,"  ���޸�Ů��    ");}
else if(Valu == 65) {LCD12864_DisplayStrChin(3 ,0,"�����ž�������");}
else if(Valu == 66) {LCD12864_DisplayStrChin(3 ,0,"����˹����������");}
else if(Valu == 67) {LCD12864_DisplayStrChin(3 ,0,"  ���ʵ�Ӱ��    ");}
else if(Valu == 68) {LCD12864_DisplayStrChin(3 ,0,"  ȫ������    ");}
else if(Valu == 69) {LCD12864_DisplayStrChin(3 ,0,"  ����������    ");}
else if(Valu == 70) {LCD12864_DisplayStrChin(3 ,0,"��Сƽ����������");}
else if(Valu == 71) {LCD12864_DisplayStrChin(3 ,0,"ȫ����ʦ��ѯ��  ");}
else if(Valu == 72) {LCD12864_DisplayStrChin(3 ,0,"��սʤ��������  ");}
else if(Valu == 73) {LCD12864_DisplayStrChin(3 ,0,"  ����ɨä��    ");}
else if(Valu == 74) {LCD12864_DisplayStrChin(3 ,0,"ë������������");}
else if(Valu == 75) {LCD12864_DisplayStrChin(3 ,0,"  �й���ʦ��    ");}
else if(Valu == 76) {LCD12864_DisplayStrChin(3 ,0,"������������  ");}
else if(Valu == 77) {LCD12864_DisplayStrChin(3 ,0,"  �й�������    ");}
else if(Valu == 78) {LCD12864_DisplayStrChin(3 ,0,"  ȫ��������    ");}
else if(Valu == 79) {LCD12864_DisplayStrChin(3 ,0,"  ���ʺ�ƽ��    ");}
else if(Valu == 80) {LCD12864_DisplayStrChin(3 ,0,"  �����޳���    ");}
else if(Valu == 81) {LCD12864_DisplayStrChin(3 ,0,"  ����������    ");}
else if(Valu == 82) {LCD12864_DisplayStrChin(3 ,0,"    �����      ");}
else if(Valu == 83) {LCD12864_DisplayStrChin(3 ,0,"  ���綯����    ");}
else if(Valu == 84) {LCD12864_DisplayStrChin(3 ,0,"  �����ʦ��     ");}
else if(Valu == 85) {LCD12864_DisplayStrChin(3 ,0,"  ����������     ");}
else if(Valu == 86) {LCD12864_DisplayStrChin(3 ,0,"��������������  ");}
else if(Valu == 87) {LCD12864_DisplayStrChin(3 ,0,"  ������ʹ��    ");}
else if(Valu == 88) {LCD12864_DisplayStrChin(3 ,0,"  ���籣����    ");}
else if(Valu == 89) {LCD12864_DisplayStrChin(3 ,0,"  �����׼��    ");}
else if(Valu == 90) {LCD12864_DisplayStrChin(3 ,0,"  ����ä�˽�    ");}
else if(Valu == 91) {LCD12864_DisplayStrChin(3 ,0,"  ������ʳ��    ");}
else if(Valu == 92) {LCD12864_DisplayStrChin(3 ,0,"��������ƶ����  ");}
else if(Valu == 93) {LCD12864_DisplayStrChin(3 ,0,"���紫ͳҽҩ��  ");}
else if(Valu == 94) {LCD12864_DisplayStrChin(3 ,0,"    ���Ϲ���    ");}
else if(Valu == 95) {LCD12864_DisplayStrChin(3 ,0,"����Ԯ��������  ");}
else if(Valu == 96) {LCD12864_DisplayStrChin(3 ,0,"  ��ʥ��ǰϦ    ");}
else if(Valu == 97) {LCD12864_DisplayStrChin(3 ,0,"  ֲ��������    ");}
else if(Valu == 98) {LCD12864_DisplayStrChin(3 ,0,"  �й����߽�    ");}
else if(Valu == 99) {LCD12864_DisplayStrChin(3 ,0,"�й�����������  ");}
else if(Valu == 100) {LCD12864_DisplayStrChin(3 ,0,"  ���������    ");}
else if(Valu == 101) {LCD12864_DisplayStrChin(3 ,0,"����ɽ����������");}
else if(Valu == 102) {LCD12864_DisplayStrChin(3 ,0,"  ����������  ");}
else if(Valu == 103) {LCD12864_DisplayStrChin(3 ,0,"  ����������    ");}
else if(Valu == 104) {LCD12864_DisplayStrChin(3 ,0,"  ���ʴ�ѧ����  ");}
else if(Valu == 105) {LCD12864_DisplayStrChin(3 ,0,"  ���ʶ�ͯ��    ");}
else if(Valu == 106) {LCD12864_DisplayStrChin(3 ,0,"  ���������    ");}
else if(Valu == 107) {LCD12864_DisplayStrChin(3 ,0,"�����浮��������");}
else if(Valu == 108) {LCD12864_DisplayStrChin(3 ,0,"����˹����������");}
else if(Valu == 109) {LCD12864_DisplayStrChin(3 ,0,"  ���簬�̲���  ");}
else if(Valu == 110) {LCD12864_DisplayStrChin(3 ,0,"�ϳ�ū���ƹ�����");}
else if(Valu == 111) {LCD12864_DisplayStrChin(3 ,0,"  ����м�����  ");}
else if(Valu == 112) {LCD12864_DisplayStrChin(3 ,0,"����ǿ��������  ");}
else if(Valu == 113) {LCD12864_DisplayStrChin(3 ,0,"�ϳ�ū���ƹ�����");}
else if(Valu == 114) {LCD12864_DisplayStrChin(3 ,0,"  ��������    ");}
else if(Valu == 115) {LCD12864_DisplayStrChin(3 ,0,"һ�����˶�������");}
else if(Valu == 116) {LCD12864_DisplayStrChin(3 ,0,"  ������Ȩ��    ");}
else if(Valu == 117) {LCD12864_DisplayStrChin(3 ,0,"�����±������  ");}
else if(Valu == 118) {LCD12864_DisplayStrChin(3 ,0,"�Ͼ�����ɱ������");}
else if(Valu == 119) {LCD12864_DisplayStrChin(3 ,0,"  ������������  ");}
else if(Valu == 120) {LCD12864_DisplayStrChin(3 ,0,"���Żع������  ");} 

else if(Valu == 121)   {LCD12864_DisplayStrChin(3 ,0,"  ����������    ") ; }
else if(Valu == 122)   {LCD12864_DisplayStrChin(3 ,0,"  ����ʥ����    ") ;}
else if(Valu == 123)   {LCD12864_DisplayStrChin(3 ,0,"ë�󶫵���������") ;}
	
	else if(Valu == 124){ LCD12864_DisplayStrChin(3 ,0,"  ����ĸ�׽�    ") ;}
	else if(Valu == 125)  { LCD12864_DisplayStrChin(3 ,0,"  ����ĸ�׽�    ") ; }	
	
	else if(Valu == 126) {LCD12864_DisplayStrChin(3 ,0,"  ���츸�׽�    "); ;}
	else if(Valu == 127)   {LCD12864_DisplayStrChin(3 ,0,"  ���츸�׽�    ") ; }
}

void Festival_YearlyongLi_N(uint8_t Mouth,uint8_t Day)
{
	if(Mouth == 1&& Day == 1)   LCD12864_DisplayStrChin(3 ,0,"      ����      "); 
	if(Mouth == 1&& Day == 15)  LCD12864_DisplayStrChin(3 ,0,"    Ԫ����      "); 
	if(Mouth == 5&& Day == 5)   LCD12864_DisplayStrChin(3 ,0,"    �����      "); 
	if(Mouth == 7&& Day == 7)   LCD12864_DisplayStrChin(3 ,0,"  ��Ϧ���˽�    "); 
	if(Mouth == 8&& Day == 15)  LCD12864_DisplayStrChin(3 ,0,"    �����      "); 
	if(Mouth == 12&& Day == 8)  LCD12864_DisplayStrChin(3 ,0,"    ���˽�      "); 
	if(Mouth == 12&& Day == 30) LCD12864_DisplayStrChin(3 ,0,"      ��Ϧ      "); 
}


void Get_JieQi(uint8_t mouth,uint8_t day)
{
	if(mouth == 2 && day > 2 && day < 6)
	{
		LCD12864_DrowPicNum(0, 16, 12); 
	}
	if(mouth == 2 && day > 17 && day < 21)
	{
		LCD12864_DrowPicNum(0, 16, 13); 
	}
	if(mouth == 3 && day > 4 && day < 8)
	{
		LCD12864_DrowPicNum(0, 16, 14); 
	}
	if(mouth == 3 && day > 19 && day < 22)
	{
		LCD12864_DrowPicNum(0, 16, 15);
	}
	if(mouth == 4 && day > 3 && day < 7)
	{
		LCD12864_DrowPicNum(0, 16, 16);
	}
	if(mouth == 4 && day > 18 && day < 22)
	{
		LCD12864_DrowPicNum(0, 16, 17); 
	}
	if(mouth == 5 && day > 4 && day < 8)
	{
		LCD12864_DrowPicNum(0, 16, 18); 
	}
	if(mouth == 5 && day > 19 && day < 23)
	{
		LCD12864_DrowPicNum(0, 16, 19); 
	}
	if(mouth == 6 && day > 4 && day < 8)
	{
		LCD12864_DrowPicNum(0, 16, 20);
	}
	if(mouth == 6 && day > 20 && day < 23)
	{
		LCD12864_DrowPicNum(0, 16, 21); 
	}
	if(mouth == 7 && day > 5 && day < 9)
	{
		LCD12864_DrowPicNum(0, 16, 22);
	}
	if(mouth == 7 && day > 21 && day < 25)
	{
		LCD12864_DrowPicNum(0, 16, 23);
	}
	if(mouth == 8 && day > 6 && day < 10)
	{
		LCD12864_DrowPicNum(0, 16, 24); 
	}
	if(mouth == 8 && day > 21 && day < 25)
	{
		LCD12864_DrowPicNum(0, 16, 25); 
	}
	if(mouth == 9 && day > 6 && day < 10)
	{
		LCD12864_DrowPicNum(0, 16, 26);
	}
	if(mouth == 9 && day > 21 && day < 25)
	{
		LCD12864_DrowPicNum(0, 16, 27);
	}
	if(mouth == 10 && day > 7 && day < 10)
	{
		LCD12864_DrowPicNum(0, 16, 28);
	}
	if(mouth == 10 && day > 22 && day < 25)
	{
		LCD12864_DrowPicNum(0, 16, 29);
	}
	if(mouth == 11 && day > 6 && day < 9)
	{
		LCD12864_DrowPicNum(0, 16, 30); 
	}
	if(mouth == 11 && day > 21 && day < 24)
	{
		LCD12864_DrowPicNum(0, 16, 31);
	}
	if(mouth == 12 && day > 5 && day < 9)
	{
		LCD12864_DrowPicNum(0, 16, 32);
	}
	if(mouth == 12 && day > 20 && day < 24)
	{
		LCD12864_DrowPicNum(0, 16, 33);
	}
	if(mouth == 1 && day > 4 && day < 8)
	{
		LCD12864_DrowPicNum(0, 16, 34);
	}
	if(mouth == 1 && day > 19 && day < 22)
	{
		LCD12864_DrowPicNum(0, 16, 35);
	}
}


















