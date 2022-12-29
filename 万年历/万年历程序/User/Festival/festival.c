#include "festival.h"
#include "lcd12864.h"
#include "calendar.h"

//char *JieQi1[] = {"立","雨","惊","春","清","谷","立","小","芒","夏","小","大","立","处","白","秋","寒","霜","立","小","大","冬","小","大"}; 
//char *JieQi2[] = {"春","水","蛰","分","明","雨","夏","满","种","至","暑","暑","秋","暑","露","分","露","降","冬","雪","雪","至","寒","寒"}; 
	
uint8_t Festival_Yearly(uint16_t Year,uint8_t Mouth,uint8_t Day)
{
	uint8_t Father_Day,Mother_Day;
	
	Mother_Day = Judge_Week(Year,5,1);             // 把xx年的5月1号写入，判断五月的第二个星期天是几号
	if(Mother_Day == 0) Mother_Day = 7;
	Mother_Day = 15-Mother_Day;
	
	Father_Day = Judge_Week(Year,6,1);             // 把xx年的6月1号写入，判断六月的第三个星期天是几号
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
if(Valu == 1) {LCD12864_DisplayStrChin(3 ,0,"    元旦快乐    ");}
else if(Valu == 2) {LCD12864_DisplayStrChin(3 ,0,"周恩来逝世纪念日");  }
else if(Valu == 3) {LCD12864_DisplayStrChin(3 ,0,"列宁逝世纪念日  ");  }
else if(Valu == 4) {LCD12864_DisplayStrChin(3 ,0,"  国际海关日    ");   }
else if(Valu == 5) {LCD12864_DisplayStrChin(3 ,0,"  世界湿地日    ");   }
else if(Valu == 6) {LCD12864_DisplayStrChin(3 ,0,"  国际气象节    ");   }
else if(Valu == 7) {LCD12864_DisplayStrChin(3 ,0,"  西方情人节    ");	}
else if(Valu == 8) {LCD12864_DisplayStrChin(3 ,0,"中国12亿人口日  "); }
else if(Valu == 9) {LCD12864_DisplayStrChin(3 ,0,"邓小平逝世纪念日"); }
else if(Valu == 10) {LCD12864_DisplayStrChin(3 ,0,"  国际母语日    ");    }
else if(Valu == 11) {LCD12864_DisplayStrChin(3 ,0,"第三世界青年日  ");}
else if(Valu == 12) {LCD12864_DisplayStrChin(3 ,0,"  国际海豹日    ");}
else if(Valu == 13) {LCD12864_DisplayStrChin(3 ,0,"  全国爱耳日    ");}
else if(Valu == 14) {LCD12864_DisplayStrChin(3 ,0,"周恩来诞辰纪念日");}
else if(Valu == 15) {LCD12864_DisplayStrChin(3 ,0,"国际劳动妇女节  ");}
else if(Valu == 16) {LCD12864_DisplayStrChin(3 ,0,"孙中山逝世纪念日");}
else if(Valu == 17) {LCD12864_DisplayStrChin(3 ,0,"  国际警察日    ");}
else if(Valu == 18) {LCD12864_DisplayStrChin(3 ,0,"国际消费者权益日");}
else if(Valu == 19) {LCD12864_DisplayStrChin(3 ,0,"  中国国医节    ");}
else if(Valu == 20) {LCD12864_DisplayStrChin(3 ,0,"  世界林业节    ");}
else if(Valu == 21) {LCD12864_DisplayStrChin(3 ,0,"    世界水日    ");}
else if(Valu == 22) {LCD12864_DisplayStrChin(3 ,0,"  世界气象日    ");}
else if(Valu == 23) {LCD12864_DisplayStrChin(3 ,0,"世界防治结核病日");}
else if(Valu == 24) {LCD12864_DisplayStrChin(3 ,0,"  国际愚人节    ");}
else if(Valu == 25) {LCD12864_DisplayStrChin(3 ,0,"国际儿童图书日  ");}
else if(Valu == 26) {LCD12864_DisplayStrChin(3 ,0,"  世界卫生日    ");}
else if(Valu == 27) {LCD12864_DisplayStrChin(3 ,0,"  非洲自由日    ");}
else if(Valu == 28) {LCD12864_DisplayStrChin(3 ,0,"全国企业家活动日");}
else if(Valu == 29) {LCD12864_DisplayStrChin(3 ,0,"  世界地球日    ");}
else if(Valu == 30) {LCD12864_DisplayStrChin(3 ,0,"世界图书和版权日");}
else if(Valu == 31) {LCD12864_DisplayStrChin(3 ,0,"亚非新闻工作者日");}
else if(Valu == 32) {LCD12864_DisplayStrChin(3 ,0,"世界知识产权日  ");}
else if(Valu == 33) {LCD12864_DisplayStrChin(3 ,0,"    联谊城日    ");}
else if(Valu == 34) {LCD12864_DisplayStrChin(3 ,0,"  国际劳动节    ");}
else if(Valu == 35) {LCD12864_DisplayStrChin(3 ,0,"世界新闻自由日  ");}
else if(Valu == 36) {LCD12864_DisplayStrChin(3 ,0,"  中国青年节    ");}
else if(Valu == 37) {LCD12864_DisplayStrChin(3 ,0,"马克思诞辰纪念日");}
else if(Valu == 38) {LCD12864_DisplayStrChin(3 ,0,"  世界红十字日  ");}
else if(Valu == 39) {LCD12864_DisplayStrChin(3 ,0,"  国际护士节    ");}
else if(Valu == 40) {LCD12864_DisplayStrChin(3 ,0,"  国际家庭日    ");}
else if(Valu == 41) {LCD12864_DisplayStrChin(3 ,0,"  世界电信日    ");}
else if(Valu == 42) {LCD12864_DisplayStrChin(3 ,0,"  国际博物馆日  ");}
else if(Valu == 43) {LCD12864_DisplayStrChin(3 ,0,"中国学生营养日  ");}
else if(Valu == 44) {LCD12864_DisplayStrChin(3 ,0,"生物多样性国际日");}
else if(Valu == 45) {LCD12864_DisplayStrChin(3 ,0,"  非洲解放日    ");}
else if(Valu == 46) {LCD12864_DisplayStrChin(3 ,0,"  上海解放日    ");}
else if(Valu == 47) {LCD12864_DisplayStrChin(3 ,0,"国际维和人员日  ");}
else if(Valu == 48) {LCD12864_DisplayStrChin(3 ,0,"  世界无烟日    ");}
else if(Valu == 49) {LCD12864_DisplayStrChin(3 ,0,"  国际儿童节    ");}
else if(Valu == 50) {LCD12864_DisplayStrChin(3 ,0,"  世界环境日    ");}
else if(Valu == 51) {LCD12864_DisplayStrChin(3 ,0,"  全国爱眼日    ");}
else if(Valu == 52) {LCD12864_DisplayStrChin(3 ,0,"  中国人口日    ");}
else if(Valu == 53) {LCD12864_DisplayStrChin(3 ,0,"  世界无童工日  ");}
else if(Valu == 54) {LCD12864_DisplayStrChin(3 ,0,"  世界献血日    ");}
else if(Valu == 55) {LCD12864_DisplayStrChin(3 ,0,"  世界难民日    ");}
else if(Valu == 56) {LCD12864_DisplayStrChin(3 ,0,"国际奥林匹克日  ");}
else if(Valu == 57) {LCD12864_DisplayStrChin(3 ,0,"  全国土地日    ");}
else if(Valu == 58) {LCD12864_DisplayStrChin(3 ,0,"  全国土地日    ");}
else if(Valu == 59) {LCD12864_DisplayStrChin(3 ,0,"中国共产党诞生日");}
else if(Valu == 60) {LCD12864_DisplayStrChin(3 ,0,"国际体育记者日  ");}
else if(Valu == 61) {LCD12864_DisplayStrChin(3 ,0,"抗日战争纪念日  ");}
else if(Valu == 62) {LCD12864_DisplayStrChin(3 ,0,"  世界人口日    ");}
else if(Valu == 63) {LCD12864_DisplayStrChin(3 ,0,"  世界语创立日  ");}
else if(Valu == 64) {LCD12864_DisplayStrChin(3 ,0,"  非洲妇女日    ");}
else if(Valu == 65) {LCD12864_DisplayStrChin(3 ,0,"人民解放军建军节");}
else if(Valu == 66) {LCD12864_DisplayStrChin(3 ,0,"恩格斯逝世纪念日");}
else if(Valu == 67) {LCD12864_DisplayStrChin(3 ,0,"  国际电影节    ");}
else if(Valu == 68) {LCD12864_DisplayStrChin(3 ,0,"  全民健身日    ");}
else if(Valu == 69) {LCD12864_DisplayStrChin(3 ,0,"  国际青年日    ");}
else if(Valu == 70) {LCD12864_DisplayStrChin(3 ,0,"邓小平诞辰纪念日");}
else if(Valu == 71) {LCD12864_DisplayStrChin(3 ,0,"全国律师咨询日  ");}
else if(Valu == 72) {LCD12864_DisplayStrChin(3 ,0,"抗战胜利纪念日  ");}
else if(Valu == 73) {LCD12864_DisplayStrChin(3 ,0,"  世界扫盲日    ");}
else if(Valu == 74) {LCD12864_DisplayStrChin(3 ,0,"毛泽东逝世纪念日");}
else if(Valu == 75) {LCD12864_DisplayStrChin(3 ,0,"  中国教师节    ");}
else if(Valu == 76) {LCD12864_DisplayStrChin(3 ,0,"世界清洁地球日  ");}
else if(Valu == 77) {LCD12864_DisplayStrChin(3 ,0,"  中国国耻日    ");}
else if(Valu == 78) {LCD12864_DisplayStrChin(3 ,0,"  全国爱牙日    ");}
else if(Valu == 79) {LCD12864_DisplayStrChin(3 ,0,"  国际和平日    ");}
else if(Valu == 80) {LCD12864_DisplayStrChin(3 ,0,"  世界无车日    ");}
else if(Valu == 81) {LCD12864_DisplayStrChin(3 ,0,"  世界旅游日    ");}
else if(Valu == 82) {LCD12864_DisplayStrChin(3 ,0,"    国庆节      ");}
else if(Valu == 83) {LCD12864_DisplayStrChin(3 ,0,"  世界动物日    ");}
else if(Valu == 84) {LCD12864_DisplayStrChin(3 ,0,"  世界教师日     ");}
else if(Valu == 85) {LCD12864_DisplayStrChin(3 ,0,"  世界邮政日     ");}
else if(Valu == 86) {LCD12864_DisplayStrChin(3 ,0,"辛亥革命纪念日  ");}
else if(Valu == 87) {LCD12864_DisplayStrChin(3 ,0,"  世界镇痛日    ");}
else if(Valu == 88) {LCD12864_DisplayStrChin(3 ,0,"  世界保健日    ");}
else if(Valu == 89) {LCD12864_DisplayStrChin(3 ,0,"  世界标准日    ");}
else if(Valu == 90) {LCD12864_DisplayStrChin(3 ,0,"  国际盲人节    ");}
else if(Valu == 91) {LCD12864_DisplayStrChin(3 ,0,"  世界粮食日    ");}
else if(Valu == 92) {LCD12864_DisplayStrChin(3 ,0,"世界消除贫困日  ");}
else if(Valu == 93) {LCD12864_DisplayStrChin(3 ,0,"世界传统医药日  ");}
else if(Valu == 94) {LCD12864_DisplayStrChin(3 ,0,"    联合国日    ");}
else if(Valu == 95) {LCD12864_DisplayStrChin(3 ,0,"抗美援朝纪念日  ");}
else if(Valu == 96) {LCD12864_DisplayStrChin(3 ,0,"  万圣节前夕    ");}
else if(Valu == 97) {LCD12864_DisplayStrChin(3 ,0,"  植树造林日    ");}
else if(Valu == 98) {LCD12864_DisplayStrChin(3 ,0,"  中国记者节    ");}
else if(Valu == 99) {LCD12864_DisplayStrChin(3 ,0,"中国消防宣传日  ");}
else if(Valu == 100) {LCD12864_DisplayStrChin(3 ,0,"  世界青年节    ");}
else if(Valu == 101) {LCD12864_DisplayStrChin(3 ,0,"孙中山诞辰纪念日");}
else if(Valu == 102) {LCD12864_DisplayStrChin(3 ,0,"  世界糖尿病日  ");}
else if(Valu == 103) {LCD12864_DisplayStrChin(3 ,0,"  国际容忍日    ");}
else if(Valu == 104) {LCD12864_DisplayStrChin(3 ,0,"  国际大学生节  ");}
else if(Valu == 105) {LCD12864_DisplayStrChin(3 ,0,"  国际儿童日    ");}
else if(Valu == 106) {LCD12864_DisplayStrChin(3 ,0,"  世界电视日    ");}
else if(Valu == 107) {LCD12864_DisplayStrChin(3 ,0,"刘少奇诞辰纪念日");}
else if(Valu == 108) {LCD12864_DisplayStrChin(3 ,0,"恩格斯诞辰纪念日");}
else if(Valu == 109) {LCD12864_DisplayStrChin(3 ,0,"  世界艾滋病日  ");}
else if(Valu == 110) {LCD12864_DisplayStrChin(3 ,0,"废除奴隶制国际日");}
else if(Valu == 111) {LCD12864_DisplayStrChin(3 ,0,"  世界残疾人日  ");}
else if(Valu == 112) {LCD12864_DisplayStrChin(3 ,0,"世界强化免疫日  ");}
else if(Valu == 113) {LCD12864_DisplayStrChin(3 ,0,"废除奴隶制国际日");}
else if(Valu == 114) {LCD12864_DisplayStrChin(3 ,0,"  国际民航日    ");}
else if(Valu == 115) {LCD12864_DisplayStrChin(3 ,0,"一二九运动纪念日");}
else if(Valu == 116) {LCD12864_DisplayStrChin(3 ,0,"  世界人权日    ");}
else if(Valu == 117) {LCD12864_DisplayStrChin(3 ,0,"西安事变纪念日  ");}
else if(Valu == 118) {LCD12864_DisplayStrChin(3 ,0,"南京大屠杀纪念日");}
else if(Valu == 119) {LCD12864_DisplayStrChin(3 ,0,"  国际移徙者日  ");}
else if(Valu == 120) {LCD12864_DisplayStrChin(3 ,0,"澳门回归纪念日  ");} 

else if(Valu == 121)   {LCD12864_DisplayStrChin(3 ,0,"  国际篮球日    ") ; }
else if(Valu == 122)   {LCD12864_DisplayStrChin(3 ,0,"  西方圣诞节    ") ;}
else if(Valu == 123)   {LCD12864_DisplayStrChin(3 ,0,"毛泽东诞辰纪念日") ;}
	
	else if(Valu == 124){ LCD12864_DisplayStrChin(3 ,0,"  明天母亲节    ") ;}
	else if(Valu == 125)  { LCD12864_DisplayStrChin(3 ,0,"  今天母亲节    ") ; }	
	
	else if(Valu == 126) {LCD12864_DisplayStrChin(3 ,0,"  明天父亲节    "); ;}
	else if(Valu == 127)   {LCD12864_DisplayStrChin(3 ,0,"  今天父亲节    ") ; }
}

void Festival_YearlyongLi_N(uint8_t Mouth,uint8_t Day)
{
	if(Mouth == 1&& Day == 1)   LCD12864_DisplayStrChin(3 ,0,"      春节      "); 
	if(Mouth == 1&& Day == 15)  LCD12864_DisplayStrChin(3 ,0,"    元宵节      "); 
	if(Mouth == 5&& Day == 5)   LCD12864_DisplayStrChin(3 ,0,"    端午节      "); 
	if(Mouth == 7&& Day == 7)   LCD12864_DisplayStrChin(3 ,0,"  七夕情人节    "); 
	if(Mouth == 8&& Day == 15)  LCD12864_DisplayStrChin(3 ,0,"    中秋节      "); 
	if(Mouth == 12&& Day == 8)  LCD12864_DisplayStrChin(3 ,0,"    腊八节      "); 
	if(Mouth == 12&& Day == 30) LCD12864_DisplayStrChin(3 ,0,"      除夕      "); 
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


















